#include "GameAPI.h"
#include "GameRTTI.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "GameTypes.h"
#include "CommandTable.h"
#include "GameScript.h"
#include "StringVar.h"

static NVSEStringVarInterface* s_StringVarInterface = NULL;
bool extraTraces = false;

// arg1 = 1, ignored if canCreateNew is false, passed to 'init' function if a new object is created
typedef void* (*_GetSingleton)(bool canCreateNew);

#if 1

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

#elif EDITOR

//	FormMap* g_FormMap = (FormMap *)0x009EE18C;		// currently unused
//	TESDataHandler ** g_dataHandler = (TESDataHandler **)0x00A0E064;
//	TES** g_TES = (TES**)0x00A0ABB0;
const _LookupFormByID LookupFormByID = (_LookupFormByID)0x004F9620;	// Call between third reference to RTTI_TESWorldspace and RuntimeDynamicCast
const _GetFormByID GetFormByID = (_GetFormByID)(0x004F9650); // Search for aNonPersistentR and aPlayer (third call below aPlayer, second is LookupFomrByID)
const _FormHeap_Allocate FormHeap_Allocate = (_FormHeap_Allocate)0x00401000;
const _FormHeap_Free FormHeap_Free = (_FormHeap_Free)0x0000401180;
const _ShowCompilerError ShowCompilerError = (_ShowCompilerError)0x005C5730;	// Called with aNonPersistentR (still same sub as the other one)

#else

#error RUNTIME_VERSION unknown

#endif

#if RUNTIME

struct TLSData {
	// thread local storage

	uint32_t	pad000[(0x260 - 0x000) >> 2];	// 000
	NiNode* lastNiNode;			// 260
	TESObjectREFR* lastNiNodeREFR;		// 264
	uint8_t			consoleMode;			// 268
	uint8_t			pad269[3];				// 269
	// 25C is used as do not head track the player , 2B8 is used to init QueudFile::unk0018
};

static TLSData* GetTLSData() {
	uint32_t TlsIndex = *g_TlsIndexPtr;
	TLSData* data = NULL;

	__asm {
		mov		ecx, [TlsIndex]
		mov		edx, fs: [2Ch]	// linear address of thread local storage array
		mov		eax, [edx + ecx * 4]
		mov[data], eax
	}

	return data;
}

bool IsConsoleMode() {
	TLSData* tlsData = GetTLSData();

	if (tlsData)
		return tlsData->consoleMode != 0;

	return false;
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

// ExtractArgsEx code
ScriptLocals* ResolveExternalVar(ScriptLocals* in_EventList, Script* in_Script, uint8_t*& scriptData) {
	ScriptLocals* refEventList = NULL;
	uint16_t varIdx = *((uint16_t*)++scriptData);
	scriptData += 2;

	Script::RefVariable* refVar = in_Script->GetVariable(varIdx);
	if (refVar) {
		refVar->Resolve(in_EventList);
		TESForm* refObj = refVar->form;
		if (refObj) {
			if (refObj->GetFormType() == FORM_TYPE::TESObjectREFR) {
				TESObjectREFR* refr = DYNAMIC_CAST(refObj, TESForm, TESObjectREFR);
				if (refr)
					refEventList = refr->GetScriptLocals();
			}
			else if (refObj->GetFormType() == FORM_TYPE::TESQuest) {
				TESQuest* quest = DYNAMIC_CAST(refObj, TESForm, TESQuest);
				if (quest)
					refEventList = quest->scriptEventList;
			}
		}
	}

	return refEventList;
}

TESGlobal* ResolveGlobalVar(ScriptLocals* in_EventList, Script* in_Script, uint8_t*& scriptData) {
	TESGlobal* global = NULL;
	uint16_t varIdx = *((uint16_t*)++scriptData);
	scriptData += 2;

	Script::RefVariable* globalRef = in_Script->GetVariable(varIdx);
	if (globalRef)
		global = (TESGlobal*)DYNAMIC_CAST(globalRef->form, TESForm, TESGlobal);

	return global;
}

static bool ExtractFloat(double& out, uint8_t*& scriptData, Script* scriptObj, ScriptLocals* eventList) {
	//extracts one float arg

	bool ret = false;
	if (*scriptData == 'r')		//reference to var in another script
	{
		eventList = ResolveExternalVar(eventList, scriptObj, scriptData);
		if (!eventList)			//couldn't resolve script ref
			return false;
	}

	switch (*scriptData) {
		case 'G':		//global var
		{
			TESGlobal* global = ResolveGlobalVar(eventList, scriptObj, scriptData);
			if (global) {
				out = global->GetValue();
				ret = true;
			}
			break;
		}
		case 'z':		//literal double
		{
			out = *((double*)++scriptData);
			scriptData += sizeof(double);
			ret = true;
			break;
		}
		case 'f':
		case 's':		//local var
		{
			uint16_t varIdx = *((uint16_t*)++scriptData);
			scriptData += 2;
			ScriptVar* var = eventList->GetVariable(varIdx);
			if (var) {
				out = var->data;
				ret = true;
			}
			break;
		}
	}
	return ret;
}

TESForm* ExtractFormFromFloat(uint8_t*& scriptData, Script* scriptObj, ScriptLocals* eventList) {
	TESForm* outForm = NULL;
	if (*scriptData == 'r')		//doesn't work as intended yet so refs must be local vars
	{
		eventList = ResolveExternalVar(eventList, scriptObj, scriptData);
		if (!eventList)
			return NULL;
	}

	uint16_t varIdx = *(uint16_t*)++scriptData;
	scriptData += 2;

	ScriptVar* var = eventList->GetVariable(varIdx);
	if (var)
		outForm = LookupFormByID(*((uint64_t*)&var->data));

	return outForm;
}

TESForm* ResolveForm(uint8_t*& scriptData, Script* scriptObj, ScriptLocals* eventList) {
	TESForm* outForm = NULL;
	char argType = *scriptData;
	uint16_t	varIdx = *((uint16_t*)(scriptData + 1));
	//	scriptData += 2;

	switch (argType) {
		case 'r':
		{
			Script::RefVariable* var = scriptObj->GetVariable(varIdx);
			if (var) {
				var->Resolve(eventList);
				outForm = var->form;
				scriptData += 3;
			}
		}
		break;
		case 'f':
			outForm = ExtractFormFromFloat(scriptData, scriptObj, eventList);
			break;
	}
	return outForm;
}

static const char* StringFromStringVar(uint32_t strID) {
	if (s_StringVarInterface)
		return s_StringVarInterface->GetString(strID);
	else
		return "";
}

static const char* ResolveStringArgument(ScriptLocals* eventList, const char* stringArg) {
	const char* result = stringArg;

	if (stringArg && stringArg[0] == '$') {
		VariableInfo* varInfo = eventList->m_script->GetVariableByName(stringArg + 1);
		if (varInfo) {
			ScriptVar* var = eventList->GetVariable(varInfo->idx);
			if (var)
				result = StringFromStringVar(var->data);
		}
	}

	return result;
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

ScriptLocals* EventListFromForm(TESForm* form) {
	ScriptLocals* eventList = NULL;
	TESObjectREFR* refr = DYNAMIC_CAST(form, TESForm, TESObjectREFR);
	if (refr)
		eventList = refr->GetScriptLocals();
	else {
		TESQuest* quest = DYNAMIC_CAST(form, TESForm, TESQuest);
		if (quest)
			eventList = quest->scriptEventList;
	}

	return eventList;
}

static void ConvertLiteralPercents(std::string* str) {
	uint32_t idx = 0;
	while ((idx = str->find('%', idx)) != -1) {
		str->insert(idx, "%");
		idx += 2;
	}
}

static void SkipArgs(uint8_t*& scriptData) {
	switch (*scriptData) {
		case 'z':
			scriptData += sizeof(double) + 1;
			break;
		case 'r':
			scriptData += 6;
			break;
		default:
			scriptData += 3;
			break;
	}
}

static void OmitFormatStringArgs(std::string str, FormatStringArgs& args) {
	//skip any args omitted by the %{ specifier
	uint32_t strIdx = 0;
	while ((strIdx = str.find('%', strIdx)) != -1 && args.HasMoreArgs()) {
		switch (str[++strIdx]) {
			case '%':
			case 'q':
			case 'Q':
			case 'r':
			case 'R':
				break;
			case 'c':
			case 'C':
				args.SkipArgs(2);
				break;
			default:
				args.SkipArgs(1);
		}
		strIdx++;
	}
}

void RegisterStringVarInterface(NVSEStringVarInterface* intfc) {
	s_StringVarInterface = intfc;
}

bool ExtractSetStatementVar(Script* script, ScriptLocals* eventList, void* scriptDataIn, double* outVarData, uint8_t* outModIndex, bool shortPath) {
	/*	DOES NOT WORK WITH FalloutNV, we are going to abuse the stack instead:
	//when script command called as righthand side of a set statement, the script data containing the variable
	//to assign to remains on the stack as arg to a previous function. We can get to it through scriptData in COMMAND_ARGS
	*/
	uint8_t* dataStart = (uint8_t*)scriptDataIn;	// should be 0x58 (or 0x72 if called with dot syntax)

	if (!((*dataStart == 0x58 || *dataStart == 0x72))) {
		return false;
	}

	// Calculate frame pointer for 4 calls above:
	void* callerFramePointer;
	_asm {
		mov callerFramePointer, ebp
	}
	for (int i = 0; i < 3; i++)
		callerFramePointer = (void*)(*(uint32_t*)callerFramePointer);
	if (!shortPath) {
		callerFramePointer = (void*)(*(uint32_t*)callerFramePointer);	// sv_Destruct calls us directly, others goes through AssignToStringVar
		callerFramePointer = (void*)(*(uint32_t*)callerFramePointer);	// one more added for when multiple commands are grouped (like GetBipedModelPath)
	}

	uint32_t scriptDataPtrAddr = (uint32_t)(callerFramePointer)+0x08;
	uint32_t* scriptDataAddr = (uint32_t*)scriptDataPtrAddr;
	uint8_t* scriptData = (uint8_t*)(*scriptDataAddr);

	int32_t scriptDataOffset = (uint32_t)scriptData - (uint32_t)(script->data);
	if (scriptDataOffset < 5)
		return false;

	bool bExtracted = false;
	scriptData -= 5;

	switch (*scriptData)			//work backwards from opcode to find lefthand var
	{
		case 'G':						//global
		{
			uint16_t refIdx = *(uint16_t*)(scriptData + 1);
			Script::RefVariable* refVar = script->GetVariable(refIdx);
			if (!refVar)
				break;

			TESGlobal* globalVar = DYNAMIC_CAST(refVar->form, TESForm, TESGlobal);
			if (globalVar) {
				*outVarData = globalVar->GetValue();
				if (outModIndex)
					*outModIndex = (globalVar->GetFormID() >> 24);
				bExtracted = true;
			}
		}
		break;
		case 'l':
		case 'f':
		case 's':
		{
			if (scriptDataOffset >= 8 && *(scriptData - 3) == 'r')	//external var
			{
				uint16_t refIdx = *(uint16_t*)(scriptData - 2);
				Script::RefVariable* refVar = script->GetVariable(refIdx);
				if (!refVar)
					break;

				refVar->Resolve(eventList);
				TESForm* refForm = refVar->form;
				if (!refForm)
					break;

				if (refForm->GetFormType() == FORM_TYPE::TESObjectREFR) {
					TESObjectREFR* refr = DYNAMIC_CAST(refForm, TESForm, TESObjectREFR);
					TESScriptableForm* scriptable = DYNAMIC_CAST(refr->baseForm, TESForm, TESScriptableForm);
					if (scriptable) {
						script = scriptable->GetFormScript();
						eventList = refr->GetScriptLocals();
					}
					else
						break;
				}
				else if (refForm->GetFormType() == FORM_TYPE::TESQuest) {
					TESScriptableForm* scriptable = DYNAMIC_CAST(refForm, TESForm, TESScriptableForm);
					if (scriptable) {
						script = scriptable->GetFormScript();
						TESQuest* quest = DYNAMIC_CAST(scriptable, TESScriptableForm, TESQuest);
						eventList = quest->scriptEventList;
					}
					else
						break;
				}
				else
					break;
			}

			uint16_t varIdx = *(uint16_t*)(scriptData + 1);
			ScriptVar* var = eventList->GetVariable(varIdx);
			if (var) {
				*outVarData = var->data;
				if (outModIndex)
					*outModIndex = (script->GetFormID() >> 24);
				bExtracted = true;
			}
		}
		break;
		default:
			SCRIPT_ASSERT(false, script, "Function must be used within a Set statement");
	}

	return bExtracted;
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

ScriptFormatStringArgs::ScriptFormatStringArgs(uint32_t _numArgs, uint8_t* _scriptData, Script* _scriptObj, ScriptLocals* _eventList)
	: numArgs(_numArgs), scriptData(_scriptData), scriptObj(_scriptObj), eventList(_eventList) {
	//extract format string
	uint16_t len = *((uint16_t*)scriptData);
	char* szFmt = new char[len + 1];
	scriptData += 2;
	memcpy(szFmt, scriptData, len);
	szFmt[len] = '\0';

	scriptData += len;
	fmtString = std::string(std::string(ResolveStringArgument(eventList, szFmt)));
	delete szFmt;
}

std::string ScriptFormatStringArgs::GetFormatString() {
	return fmtString;
}

bool ScriptFormatStringArgs::HasMoreArgs() {
	return (numArgs > 0);
}

uint32_t ScriptFormatStringArgs::GetNumArgs() {
	return numArgs;
}

uint8_t* ScriptFormatStringArgs::GetScriptData() {
	return scriptData;
}

bool ScriptFormatStringArgs::SkipArgs(uint32_t numToSkip) {
	while (numToSkip--) {
		switch (*scriptData) {
			case 'z':
				scriptData += sizeof(double) + 1;
				break;
			case 'r':
				scriptData += 6;
				break;
			default:
				scriptData += 3;
				break;
		}

		numArgs--;
	}

	return true;
}

//Log error if expression evaluates to false
bool SCRIPT_ASSERT(bool expr, Script* script, const char* errorMsg, ...) {
	//	static bool bAlerted = false;			//only alert user on first error
	//	static std::set<uint32_t> naughtyScripts;	//one error per script to avoid thrashing
	//
	//	if (!expr && naughtyScripts.find(script->GetFormID()) == naughtyScripts.end())
	//	{
	//		const ModEntry ** activeMods = (*g_dataHandler)->GetActiveModList();
	//		uint8_t modIndex = script->GetModIndex();
	//		const ModEntry * modEntry = activeMods[modIndex];
	//
	//		const char * modName;
	//		if (modIndex != 0xFF && modEntry && modEntry->data && modEntry->data->name)
	//			modName = modEntry->data->name;
	//		else
	//			modName = "Unknown";
	//
	////		sprintf_s(errorHeader, sizeof(errorHeader) - 1, "** Error: Script %08X in file \"%s\" **", script->GetFormID(), modName);
	////		_MESSAGE("%s", errorHeader);
	//		_MESSAGE("** Script Error: Script %08x in file \"%s\" **", script->GetFormID(), modName);
	//
	//		va_list args;
	//		va_start(args, errorMsg);
	//
	//		char errorBuf[512];
	//		vsprintf_s(errorBuf, sizeof(errorBuf) - 1, errorMsg, args);
	//		va_end(args);
	//
	//		gLog.Indent();
	//		_MESSAGE("%s", errorBuf);
	//		gLog.Outdent();
	//
	//		if (!bAlerted)
	//		{
	//			MessageBoxAlert("NVSE has detected a script error. \n\nPlease check nvse.log for details.");
	//			bAlerted = true;
	//		}
	//
	//		naughtyScripts.insert(script->GetFormID());
	//	}
	return expr;
}

bool ScriptFormatStringArgs::Arg(FormatStringArgs::argType asType, void* outResult) {
	if (!SCRIPT_ASSERT((numArgs > 0), scriptObj, "Too few args for format specifier"))
		return false;

	numArgs--;

	switch (asType) {
		case kArgType_Float:
		{
			double data = 0;
			if (ExtractFloat(data, scriptData, scriptObj, eventList)) {
				*((double*)outResult) = data;
				return true;
			}
		}
		break;
		case kArgType_Form:
		{
			TESForm* form = ExtractFormFromFloat(scriptData, scriptObj, eventList);
			*((TESForm**)outResult) = form;
			return true;
		}
	}

	return false;
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