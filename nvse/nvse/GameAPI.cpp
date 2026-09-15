#include "GameAPI.h"
#include "GameRTTI.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameTypes.h"
#include "CommandTable.h"
#include "GameScript.h"
#include "StringVar.h"
#include <Bethesda/TLSData.hpp>

static NVSEStringVarInterface* s_StringVarInterface = NULL;
bool extraTraces = false;

// arg1 = 1, ignored if canCreateNew is false, passed to 'init' function if a new object is created
typedef void* (*_GetSingleton)(bool canCreateNew);

#ifdef GAME

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x005ACCB0;

const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x00401030;

const _LookupFormByID LookupFormByID = (_LookupFormByID)0x004839C0;
const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x00465110;

const _GetSingleton ConsoleManager_GetSingleton = (_GetSingleton)0x0071B160;
bool* bEchoConsole = (bool*)0x011F158C;

const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x007052F0;

const _ShowMessageBox ShowMessageBox = (_ShowMessageBox)0x00703E80;
const _ShowMessageBox_Callback ShowMessageBox_Callback = (_ShowMessageBox_Callback)0x005B4A70;
const _ShowMessageBox_pScriptRefID ShowMessageBox_pScriptRefID = (_ShowMessageBox_pScriptRefID)0x011CAC64;
const _ShowMessageBox_button ShowMessageBox_button = (_ShowMessageBox_button)0x0118C684;

const _GetActorValueName GetActorValueName = (_GetActorValueName)0x00066EAC0;	// See Cmd_GetActorValue_Eval
const uint32_t* g_TlsIndexPtr = (uint32_t*)0x0126FD98;
const _MarkBaseExtraListScriptEvent MarkBaseExtraListScriptEvent = (_MarkBaseExtraListScriptEvent)0x005AC790;

SaveGameManager** g_saveGameManager = (SaveGameManager**)0x011DE134;

#else

//	FormMap* g_FormMap = (FormMap *)0x009EE18C;		// currently unused
//	TESDataHandler ** g_dataHandler = (TESDataHandler **)0x00A0E064;
//	TES** g_TES = (TES**)0x00A0ABB0;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x004F9620;	// Call between third reference to RTTI_TESWorldspace and RuntimeDynamicCast
const _GetFormByID GetFormByID = (_GetFormByID)(0x004F9650); // Search for aNonPersistentR and aPlayer (third call below aPlayer, second is LookupFomrByID)
const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x0000401180;
const _ShowCompilerError ShowCompilerError = (_ShowCompilerError)0x005C5730;	// Called with aNonPersistentR (still same sub as the other one)

#endif

#if RUNTIME

bool IsConsoleMode() {
	return TLSData::Get()->bConsoleOutput;
}

bool GetConsoleEcho() {
	return *bEchoConsole != 0;
}

void SetConsoleEcho(bool doEcho) {
	*bEchoConsole = doEcho ? 1 : 0;
}

const char* GetFullName(TESForm* baseForm) {
	if (baseForm) {
		const char* pName = TESFullName::GetFullName(baseForm);
		if (pName && pName[0])
			return pName;
		return "<no name>";
	}
	return "<NULL>";
}

ConsoleManager* ConsoleManager::GetSingleton(void) {
	return (ConsoleManager*)ConsoleManager_GetSingleton(true);
}

void Console_Print(const char* fmt, ...) {
	ConsoleManager* mgr = ConsoleManager::GetSingleton();
	if (mgr) {
		va_list	args;

		va_start(args, fmt);

		CALL_MEMBER_FN(mgr, Print)(fmt, args);

		va_end(args);
	}
}

SaveGameManager* SaveGameManager::GetSingleton() {
	return *g_saveGameManager;
}

std::string GetSavegamePath() {
	char path[0x104];
	CALL_MEMBER_FN(SaveGameManager::GetSingleton(), ConstructSavegamePath)(path);
	return path;
}

void ScriptLocals::Dump(void) {
	uint32_t nEvents = m_eventList->Count();

	for (uint32_t n = 0; n < nEvents; ++n) {
		Event* pEvent = m_eventList->GetNthItem(n);
		if (pEvent) {
			Console_Print("%08X (%s) %08X", pEvent->object, GetObjectClassName(pEvent->object), pEvent->eventMask);
		}
	}
}

uint32_t ScriptLocals::ResetAllVariables() {
	if (!m_vars) return 0;
	ListNode<ScriptVar>* varIter = m_vars->Head();
	ScriptVar* scriptVar;
	uint32_t numVars = 0;
	do {
		scriptVar = varIter->data;
		if (scriptVar) {
			scriptVar->data = 0;
			numVars++;
		}
	} while (varIter = varIter->next);
	return numVars;
}

ScriptVar* ScriptLocals::GetVariable(uint32_t id) {
	if (m_vars) {
		ListNode<ScriptVar>* varIter = m_vars->Head();
		ScriptVar* scriptVar;
		do {
			scriptVar = varIter->data;
			if (scriptVar && (scriptVar->id == id))
				return scriptVar;
		} while (varIter = varIter->next);
	}
	return NULL;
}

void RegisterStringVarInterface(NVSEStringVarInterface* intfc) {
	s_StringVarInterface = intfc;
}

// g_baseActorValueNames is only filled in after oblivion's global initializers run
const char* GetActorValueString(uint32_t actorValue) {
	const char* name = 0;
	if (actorValue <= eActorVal_FalloutMax)
		name = GetActorValueName(actorValue);
	if (!name)
		name = "unknown";

	return name;
}

uint32_t GetActorValueForScript(const char* avStr) {
	for (uint32_t i = 0; i <= eActorVal_FalloutMax; i++) {
		char* name = GetActorValueName(i);
		if (_stricmp(avStr, name) == 0)
			return i;
	}

	return eActorVal_NoActorValue;
}

uint32_t GetActorValueForString(const char* strActorVal, bool bForScript) {
	if (bForScript)
		return GetActorValueForScript(strActorVal);

	for (uint32_t n = 0; n <= eActorVal_FalloutMax; n++) {
		char* name = GetActorValueName(n);
		if (_stricmp(strActorVal, name) == 0)
			return n;
	}
	return eActorVal_NoActorValue;
}

uint32_t GetActorValueMax(uint32_t actorValueCode) {
	switch (actorValueCode) {
		case eActorVal_Aggression:			return   3; break;
		case eActorVal_Confidence:			return   4; break;
		case eActorVal_Energy:				return 100; break;
		case eActorVal_Responsibility:		return 100; break;
		case eActorVal_Mood:				return   8; break;

		case eActorVal_Strength:			return  10; break;
		case eActorVal_Perception:			return  10; break;
		case eActorVal_Endurance:			return  10; break;
		case eActorVal_Charisma:			return  10; break;
		case eActorVal_Intelligence:		return  10; break;
		case eActorVal_Agility:				return  10; break;
		case eActorVal_Luck:				return  10; break;

		case eActorVal_ActionPoints:		return   1; break;
		case eActorVal_CarryWeight:			return   1; break;
		case eActorVal_CritChance:			return 100; break;
		case eActorVal_HealRate:			return   1; break;
		case eActorVal_Health:				return   1; break;
		case eActorVal_MeleeDamage:			return   1; break;
		case eActorVal_DamageResistance:	return   1; break;
		case eActorVal_PoisonResistance:	return   1; break;
		case eActorVal_RadResistance:		return   1; break;
		case eActorVal_SpeedMultiplier:		return   1; break;
		case eActorVal_Fatigue:				return   1; break;
		case eActorVal_Karma:				return   1; break;
		case eActorVal_XP:					return   1; break;

		case eActorVal_Head:				return 100; break;
		case eActorVal_Torso:				return 100; break;
		case eActorVal_LeftArm:				return 100; break;
		case eActorVal_RightArm:			return 100; break;
		case eActorVal_LeftLeg:				return 100; break;
		case eActorVal_RightLeg:			return 100; break;
		case eActorVal_Brain:				return 100; break;

		case eActorVal_Barter:				return 100; break;
		case eActorVal_BigGuns:				return 100; break;
		case eActorVal_EnergyWeapons:		return 100; break;
		case eActorVal_Explosives:			return 100; break;
		case eActorVal_Lockpick:			return 100; break;
		case eActorVal_Medicine:			return 100; break;
		case eActorVal_MeleeWeapons:		return 100; break;
		case eActorVal_Repair:				return 100; break;
		case eActorVal_Science:				return 100; break;
		case eActorVal_Guns:				return 100; break;
		case eActorVal_Sneak:				return 100; break;
		case eActorVal_Speech:				return 100; break;
		case eActorVal_Survival:			return 100; break;
		case eActorVal_Unarmed:				return 100; break;

		case eActorVal_InventoryWeight:		return   1; break;
		case eActorVal_Paralysis:			return   1; break;
		case eActorVal_Invisibility:		return   1; break;
		case eActorVal_Chameleon:			return   1; break;
		case eActorVal_NightEye:			return   1; break;
		case eActorVal_Turbo:				return   1; break;
		case eActorVal_FireResistance:		return   1; break;
		case eActorVal_WaterBreathing:		return   1; break;
		case eActorVal_RadLevel:			return   1; break;
		case eActorVal_BloodyMess:			return   1; break;
		case eActorVal_UnarmedDamage:		return   1; break;
		case eActorVal_Assistance:			return   2; break;

		case eActorVal_ElectricResistance:	return   1; break;

		case eActorVal_EnergyResistance:	return   1; break;
		case eActorVal_EMPResistance:		return   1; break;
		case eActorVal_Var1Medical:			return   1; break;
		case eActorVal_Var2:				return   1; break;
		case eActorVal_Var3:				return   1; break;
		case eActorVal_Var4:				return   1; break;
		case eActorVal_Var5:				return   1; break;
		case eActorVal_Var6:				return   1; break;
		case eActorVal_Var7:				return   1; break;
		case eActorVal_Var8:				return   1; break;
		case eActorVal_Var9:				return   1; break;
		case eActorVal_Var10:				return   1; break;

		case eActorVal_IgnoreCrippledLimbs:	return   1; break;
		case eActorVal_Dehydration:			return   1; break;
		case eActorVal_Hunger:				return   1; break;
		case eActorVal_Sleepdeprevation:	return   1; break;
		case eActorVal_Damagethreshold:		return   1; break;
		default: return 1;
	}
}

#endif