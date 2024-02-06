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

#if RUNTIME_VERSION == RUNTIME_VERSION_1_4_0_525

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
const UInt32* g_TlsIndexPtr = (UInt32*)0x0126FD98;
const _MarkBaseExtraListScriptEvent MarkBaseExtraListScriptEvent = (_MarkBaseExtraListScriptEvent)0x005AC790;

SaveGameManager** g_saveGameManager = (SaveGameManager**)0x011DE134;

#elif EDITOR

//	FormMap* g_FormMap = (FormMap *)0x009EE18C;		// currently unused
//	DataHandler ** g_dataHandler = (DataHandler **)0x00A0E064;
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

	UInt32	pad000[(0x260 - 0x000) >> 2];	// 000
	NiNode* lastNiNode;			// 260
	TESObjectREFR* lastNiNodeREFR;		// 264
	UInt8			consoleMode;			// 268
	UInt8			pad269[3];				// 269
	// 25C is used as do not head track the player , 2B8 is used to init QueudFile::unk0018
};

static TLSData* GetTLSData() {
	UInt32 TlsIndex = *g_TlsIndexPtr;
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
		TESFullName* fullName = baseForm->GetFullName();
		if (fullName && fullName->name.m_data) {
			if (fullName->name.m_dataLen)
				return fullName->name.m_data;
		}
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

TESSaveLoadGame* TESSaveLoadGame::Get() {
	return (TESSaveLoadGame*)0x011DE45C;
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
ScriptEventList* ResolveExternalVar(ScriptEventList* in_EventList, Script* in_Script, UInt8*& scriptData) {
	ScriptEventList* refEventList = NULL;
	UInt16 varIdx = *((UInt16*)++scriptData);
	scriptData += 2;

	Script::RefVariable* refVar = in_Script->GetVariable(varIdx);
	if (refVar) {
		refVar->Resolve(in_EventList);
		TESForm* refObj = refVar->form;
		if (refObj) {
			if (refObj->typeID == kFormType_TESObjectREFR) {
				TESObjectREFR* refr = DYNAMIC_CAST(refObj, TESForm, TESObjectREFR);
				if (refr)
					refEventList = refr->GetEventList();
			}
			else if (refObj->typeID == kFormType_TESQuest) {
				TESQuest* quest = DYNAMIC_CAST(refObj, TESForm, TESQuest);
				if (quest)
					refEventList = quest->scriptEventList;
			}
		}
	}

	return refEventList;
}

TESGlobal* ResolveGlobalVar(ScriptEventList* in_EventList, Script* in_Script, UInt8*& scriptData) {
	TESGlobal* global = NULL;
	UInt16 varIdx = *((UInt16*)++scriptData);
	scriptData += 2;

	Script::RefVariable* globalRef = in_Script->GetVariable(varIdx);
	if (globalRef)
		global = (TESGlobal*)DYNAMIC_CAST(globalRef->form, TESForm, TESGlobal);

	return global;
}

static bool ExtractFloat(double& out, UInt8*& scriptData, Script* scriptObj, ScriptEventList* eventList) {
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
				out = global->data;
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
			UInt16 varIdx = *((UInt16*)++scriptData);
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

TESForm* ExtractFormFromFloat(UInt8*& scriptData, Script* scriptObj, ScriptEventList* eventList) {
	TESForm* outForm = NULL;
	if (*scriptData == 'r')		//doesn't work as intended yet so refs must be local vars
	{
		eventList = ResolveExternalVar(eventList, scriptObj, scriptData);
		if (!eventList)
			return NULL;
	}

	UInt16 varIdx = *(UInt16*)++scriptData;
	scriptData += 2;

	ScriptVar* var = eventList->GetVariable(varIdx);
	if (var)
		outForm = LookupFormByID(*((UInt64*)&var->data));

	return outForm;
}

TESForm* ResolveForm(UInt8*& scriptData, Script* scriptObj, ScriptEventList* eventList) {
	TESForm* outForm = NULL;
	char argType = *scriptData;
	UInt16	varIdx = *((UInt16*)(scriptData + 1));
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

static const char* StringFromStringVar(UInt32 strID) {
	if (s_StringVarInterface)
		return s_StringVarInterface->GetString(strID);
	else
		return "";
}

static const char* ResolveStringArgument(ScriptEventList* eventList, const char* stringArg) {
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

void ScriptEventList::Dump(void) {
	UInt32 nEvents = m_eventList->Count();

	for (SInt32 n = 0; n < nEvents; ++n) {
		Event* pEvent = m_eventList->GetNthItem(n);
		if (pEvent) {
			Console_Print("%08X (%s) %08X", pEvent->object, GetObjectClassName(pEvent->object), pEvent->eventMask);
		}
	}
}

UInt32 ScriptEventList::ResetAllVariables() {
	if (!m_vars) return 0;
	ListNode<ScriptVar>* varIter = m_vars->Head();
	ScriptVar* scriptVar;
	UInt32 numVars = 0;
	do {
		scriptVar = varIter->data;
		if (scriptVar) {
			scriptVar->data = 0;
			numVars++;
		}
	} while (varIter = varIter->next);
	return numVars;
}

ScriptVar* ScriptEventList::GetVariable(UInt32 id) {
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

ScriptEventList* EventListFromForm(TESForm* form) {
	ScriptEventList* eventList = NULL;
	TESObjectREFR* refr = DYNAMIC_CAST(form, TESForm, TESObjectREFR);
	if (refr)
		eventList = refr->GetEventList();
	else {
		TESQuest* quest = DYNAMIC_CAST(form, TESForm, TESQuest);
		if (quest)
			eventList = quest->scriptEventList;
	}

	return eventList;
}

static void ConvertLiteralPercents(std::string* str) {
	UInt32 idx = 0;
	while ((idx = str->find('%', idx)) != -1) {
		str->insert(idx, "%");
		idx += 2;
	}
}

static void SkipArgs(UInt8*& scriptData) {
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
	UInt32 strIdx = 0;
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

//static bool ExtractFormattedString(UInt32 &numArgs, char* buffer, UInt8* &scriptData, Script* scriptObj, ScriptEventList* eventList)
bool ExtractFormattedString(FormatStringArgs& args, char* buffer) {
	//extracts args based on format string, prints formatted string to buffer
	static const int maxArgs = 20;
	double f[maxArgs] = { 0.0 };
	UInt32 argIdx = 0;

	std::string fmtString = args.GetFormatString();
	UInt32 strIdx = 0;

	//extract args
	while ((strIdx = fmtString.find('%', strIdx)) != -1) {
		char argType = fmtString.at(strIdx + 1);
		switch (argType) {
			case '%':										//literal %
				strIdx += 2;
				break;
			case 'z':
			case 'Z':										//string variable
			{
				fmtString.erase(strIdx, 2);
				double strID = 0;
				if (!args.Arg(args.kArgType_Float, &strID))
					return false;

				const char* toInsert = StringFromStringVar(strID);
				//#if NVSE_CORE
				//				StringVar* insStr = NULL;
				//				insStr = g_StringMap.Get(strID);
				//
				//				if (insStr)
				//					toInsert = insStr->GetCString();
				//#else			// called from a plugin command
				//				if (s_StringVarInterface)
				//					toInsert = s_StringVarInterface->GetString(strID);
				//#endif
				if (toInsert && toInsert[0])
					fmtString.insert(strIdx, toInsert);
				else
					fmtString.insert(strIdx, "NULL");
			}
			break;
			case 'r':										//newline
			case 'R':
				fmtString.erase(strIdx, 2);
				fmtString.insert(strIdx, "\n");
				break;
			case 'e':
			case 'E':										//workaround for CS not accepting empty strings
				fmtString.erase(strIdx, 2);
				break;
			case 'a':
			case 'A':										//character specified by ASCII code
			{
				fmtString.erase(strIdx, 2);
				double fCharCode = 0;
				if (args.Arg(args.kArgType_Float, &fCharCode))
					fmtString.insert(strIdx, 1, (char)fCharCode);
				else
					return false;
			}
			break;
			case 'n':										// name of obj/ref
			case 'N':
			{
				fmtString.erase(strIdx, 2);
				TESForm* form = NULL;
				if (!args.Arg(args.kArgType_Form, &form))
					return false;

				std::string strName(GetFullName(form));
				ConvertLiteralPercents(&strName);
				fmtString.insert(strIdx, strName);
				strIdx += strName.length();
			}
			break;
			case 'i':											//formID
			case 'I':
			{
				fmtString.erase(strIdx, 2);
				TESForm* form = NULL;
				if (!(args.Arg(args.kArgType_Form, &form)))
					return false;
				else if (!form)
					fmtString.insert(strIdx, "00000000");
				else {
					char formID[9];
					sprintf_s(formID, 9, "%08X", form->refID);
					fmtString.insert(strIdx, formID);
				}
			}
			break;
			case 'c':											//named component of another object
			case 'C':											//2 args - object and index
			{
				TESForm* form = NULL;
				if (!args.Arg(args.kArgType_Form, &form))
					return false;

				fmtString.erase(strIdx, 2);
				if (!form)
					fmtString.insert(strIdx, "NULL");
				else {
					double objIdx = 0;

					if (!args.Arg(args.kArgType_Float, &objIdx))
						return false;
					else {
						std::string strName("");

						switch (form->typeID) {
#if 0
							case kFormType_SpellItem:
							case kFormType_EnchantmentItem:
							case kFormType_IngredientItem:
							case kFormType_AlchemyItem:
							{
								MagicItem* magItm = DYNAMIC_CAST(form, TESForm, MagicItem);
								if (!magItm)
									strName = "NULL";
								else {
									strName = magItm->list.GetNthEIName(objIdx);
									EffectItem* effItem = magItm->list.ItemAt(objIdx);
									if (effItem && effItem->HasActorValue()) {
										UInt32 valIdx = strName.find(' ');
										if (valIdx != -1) {
											strName.erase(valIdx + 1, strName.length() - valIdx);
											strName.insert(valIdx + 1, std::string(GetActorValueString(effItem->actorValueOrOther)));
										}
									}
								}
							}
							break;
#endif

							case kFormType_TESAmmo:
							{
								TESAmmo* ammo = DYNAMIC_CAST(form, TESForm, TESAmmo);

								if (!ammo)
									strName = "NULL";	// something is very wrong
								else switch ((int)objIdx) {
									default:
									case 0:	// full name
										strName = GetFullName(ammo);
										break;

									case 1:	// short name
										strName = ammo->shortName.CStr();
										break;

									case 2:	// abbrev
										strName = ammo->abbreviation.CStr();
										break;
								}
							}
							break;

#if 1	// to be tested
							case kFormType_TESFaction:
							{
								TESFaction* fact = DYNAMIC_CAST(form, TESForm, TESFaction);
								if (!fact)
									strName = "NULL";
								else {
									strName = fact->GetNthRankName(objIdx);
								}
							}
							break;
#endif

							default:
								strName = "unknown";
								break;
						}

						ConvertLiteralPercents(&strName);

						fmtString.insert(strIdx, strName);
						strIdx += strName.length();
					}
				}
			}
			break;
			case 'k':
			case 'K':											//DX code
			{
				double keycode = 0;
				fmtString.erase(strIdx, 2);
				if (!args.Arg(args.kArgType_Float, &keycode))
					return false;

				const char* desc = GetDXDescription(keycode);
				fmtString.insert(strIdx, desc);
			}
			break;
			case 'v':
			case 'V':											//actor value
			{
				double actorVal = eActorVal_FalloutMax;
				fmtString.erase(strIdx, 2);
				if (!args.Arg(args.kArgType_Float, &actorVal))
					return false;

				std::string valStr(GetActorValueString(actorVal));
				if (valStr.length()) {
					for (UInt32 idx = 1; idx < valStr.length(); idx++)
						if (isupper(valStr[idx])) {								//insert spaces to make names more presentable
							valStr.insert(idx, " ");
							idx += 2;
						}
				}
				fmtString.insert(strIdx, valStr);
			}
			break;
			case 'p':
			case 'P':											//pronouns
			{
				fmtString.erase(strIdx, 2);
				char pronounType = fmtString[strIdx];
				fmtString.erase(strIdx, 1);
				TESForm* form = NULL;
				if (!args.Arg(args.kArgType_Form, &form))
					return false;

				if (!form)
					fmtString.insert(strIdx, "NULL");
				else {
					TESObjectREFR* refr = DYNAMIC_CAST(form, TESForm, TESObjectREFR);
					if (refr)
						form = refr->baseForm;

					short objType = 0;
					if (form->typeID == kFormType_TESNPC) {
						TESActorBaseData* actorBase = DYNAMIC_CAST(form, TESForm, TESActorBaseData);
						objType = (actorBase->IsFemale()) ? 2 : 1;
					}

					switch (pronounType) {
						case 'o':
						case 'O':
							if (objType == 1)
								fmtString.insert(strIdx, "him");
							else if (objType == 2)
								fmtString.insert(strIdx, "her");
							else
								fmtString.insert(strIdx, "it");
							break;
						case 's':
						case 'S':
							if (objType == 1)
								fmtString.insert(strIdx, "he");
							else if (objType == 2)
								fmtString.insert(strIdx, "she");
							else
								fmtString.insert(strIdx, "it");
							break;
						case 'p':
						case 'P':
							if (objType == 1)
								fmtString.insert(strIdx, "his");
							else if (objType == 2)
								fmtString.insert(strIdx, "her");
							else
								fmtString.insert(strIdx, "its");
							break;
						default:
							fmtString.insert(strIdx, "NULL");
					}
				}
			}
			break;
			case 'q':
			case 'Q':											//double quote
				fmtString.erase(strIdx, 2);
				fmtString.insert(strIdx, "\"");
				break;
			case '{':											//omit portion of string based on flag param
			{
				fmtString.erase(strIdx, 2);
				double flag = 0;
				if (!args.Arg(args.kArgType_Float, &flag))
					return false;

				UInt32 omitEnd = fmtString.find("%}", strIdx);
				if (omitEnd == -1)
					omitEnd = fmtString.length();

				if (!flag) {
					OmitFormatStringArgs(fmtString.substr(strIdx, omitEnd - strIdx), args);
					fmtString.erase(strIdx, omitEnd - strIdx + 2);
				}
				else
					fmtString.erase(omitEnd, 2);
			}
			break;
			case '}':											//in case someone left a stray closing bracket
				fmtString.erase(strIdx, 2);
				break;
			case 'x':											//hex
			case 'X':
			{
				double data = 0;
				if (!args.Arg(args.kArgType_Float, &data))
					return false;

				UInt64* hexArg = (UInt64*)(&f[argIdx++]);
				*hexArg = data;
				fmtString.erase(strIdx, 2);
				char width = 0;
				if (strIdx < fmtString.length()) {
					if (isdigit(fmtString[strIdx]))	//single-digit width specifier optionally follows %x
					{
						width = fmtString[strIdx];
						fmtString.erase(strIdx, 1);
					}
				}
				fmtString.insert(strIdx, "%0llX");
				if (width)
					fmtString.insert(strIdx + 2, 1, width);
				strIdx++;
			}
			break;
			default:											//float
			{
				double data = 0;
				if (!args.Arg(args.kArgType_Float, &data))
					return false;

				f[argIdx++] = data;
				strIdx++;
			}
			break;
		}
	}

	if (sprintf_s(buffer, kMaxMessageLength - 2, fmtString.c_str(), f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7], f[8], f[9], f[10], f[11], f[12], f[13], f[14], f[15], f[16], f[17], f[18], f[19]) > 0) {
		buffer[kMaxMessageLength - 1] = '\0';
		return true;
	}
	else if (fmtString.length() == 0) {
		buffer[0] = '\0';
		return true;
	}
	else
		return false;
}

void RegisterStringVarInterface(NVSEStringVarInterface* intfc) {
	s_StringVarInterface = intfc;
}

bool ExtractSetStatementVar(Script* script, ScriptEventList* eventList, void* scriptDataIn, double* outVarData, UInt8* outModIndex, bool shortPath) {
	/*	DOES NOT WORK WITH FalloutNV, we are going to abuse the stack instead:
	//when script command called as righthand side of a set statement, the script data containing the variable
	//to assign to remains on the stack as arg to a previous function. We can get to it through scriptData in COMMAND_ARGS
	*/
	UInt8* dataStart = (UInt8*)scriptDataIn;	// should be 0x58 (or 0x72 if called with dot syntax)

	if (!((*dataStart == 0x58 || *dataStart == 0x72))) {
		return false;
	}

	// Calculate frame pointer for 4 calls above:
	void* callerFramePointer;
	_asm {
		mov callerFramePointer, ebp
	}
	for (int i = 0; i < 3; i++)
		callerFramePointer = (void*)(*(UInt32*)callerFramePointer);
	if (!shortPath) {
		callerFramePointer = (void*)(*(UInt32*)callerFramePointer);	// sv_Destruct calls us directly, others goes through AssignToStringVar
		callerFramePointer = (void*)(*(UInt32*)callerFramePointer);	// one more added for when multiple commands are grouped (like GetBipedModelPath)
	}

	UInt32 scriptDataPtrAddr = (UInt32)(callerFramePointer)+0x08;
	UInt32* scriptDataAddr = (UInt32*)scriptDataPtrAddr;
	UInt8* scriptData = (UInt8*)(*scriptDataAddr);

	SInt32 scriptDataOffset = (UInt32)scriptData - (UInt32)(script->data);
	if (scriptDataOffset < 5)
		return false;

	bool bExtracted = false;
	scriptData -= 5;

	switch (*scriptData)			//work backwards from opcode to find lefthand var
	{
		case 'G':						//global
		{
			UInt16 refIdx = *(UInt16*)(scriptData + 1);
			Script::RefVariable* refVar = script->GetVariable(refIdx);
			if (!refVar)
				break;

			TESGlobal* globalVar = DYNAMIC_CAST(refVar->form, TESForm, TESGlobal);
			if (globalVar) {
				*outVarData = globalVar->data;
				if (outModIndex)
					*outModIndex = (globalVar->refID >> 24);
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
				UInt16 refIdx = *(UInt16*)(scriptData - 2);
				Script::RefVariable* refVar = script->GetVariable(refIdx);
				if (!refVar)
					break;

				refVar->Resolve(eventList);
				TESForm* refForm = refVar->form;
				if (!refForm)
					break;

				if (refForm->typeID == kFormType_TESObjectREFR) {
					TESObjectREFR* refr = DYNAMIC_CAST(refForm, TESForm, TESObjectREFR);
					TESScriptableForm* scriptable = DYNAMIC_CAST(refr->baseForm, TESForm, TESScriptableForm);
					if (scriptable) {
						script = scriptable->script;
						eventList = refr->GetEventList();
					}
					else
						break;
				}
				else if (refForm->typeID == kFormType_TESQuest) {
					TESScriptableForm* scriptable = DYNAMIC_CAST(refForm, TESForm, TESScriptableForm);
					if (scriptable) {
						script = scriptable->script;
						TESQuest* quest = DYNAMIC_CAST(scriptable, TESScriptableForm, TESQuest);
						eventList = quest->scriptEventList;
					}
					else
						break;
				}
				else
					break;
			}

			UInt16 varIdx = *(UInt16*)(scriptData + 1);
			ScriptVar* var = eventList->GetVariable(varIdx);
			if (var) {
				*outVarData = var->data;
				if (outModIndex)
					*outModIndex = (script->refID >> 24);
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
const char* GetActorValueString(UInt32 actorValue) {
	const char* name = 0;
	if (actorValue <= eActorVal_FalloutMax)
		name = GetActorValueName(actorValue);
	if (!name)
		name = "unknown";

	return name;
}

UInt32 GetActorValueForScript(const char* avStr) {
	for (UInt32 i = 0; i <= eActorVal_FalloutMax; i++) {
		char* name = GetActorValueName(i);
		if (_stricmp(avStr, name) == 0)
			return i;
	}

	return eActorVal_NoActorValue;
}

UInt32 GetActorValueForString(const char* strActorVal, bool bForScript) {
	if (bForScript)
		return GetActorValueForScript(strActorVal);

	for (UInt32 n = 0; n <= eActorVal_FalloutMax; n++) {
		char* name = GetActorValueName(n);
		if (_stricmp(strActorVal, name) == 0)
			return n;
	}
	return eActorVal_NoActorValue;
}

ScriptFormatStringArgs::ScriptFormatStringArgs(UInt32 _numArgs, UInt8* _scriptData, Script* _scriptObj, ScriptEventList* _eventList)
	: numArgs(_numArgs), scriptData(_scriptData), scriptObj(_scriptObj), eventList(_eventList) {
	//extract format string
	UInt16 len = *((UInt16*)scriptData);
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

UInt32 ScriptFormatStringArgs::GetNumArgs() {
	return numArgs;
}

UInt8* ScriptFormatStringArgs::GetScriptData() {
	return scriptData;
}

bool ScriptFormatStringArgs::SkipArgs(UInt32 numToSkip) {
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
	//	static std::set<UInt32> naughtyScripts;	//one error per script to avoid thrashing
	//
	//	if (!expr && naughtyScripts.find(script->refID) == naughtyScripts.end())
	//	{
	//		const ModEntry ** activeMods = (*g_dataHandler)->GetActiveModList();
	//		UInt8 modIndex = script->GetModIndex();
	//		const ModEntry * modEntry = activeMods[modIndex];
	//
	//		const char * modName;
	//		if (modIndex != 0xFF && modEntry && modEntry->data && modEntry->data->name)
	//			modName = modEntry->data->name;
	//		else
	//			modName = "Unknown";
	//
	////		sprintf_s(errorHeader, sizeof(errorHeader) - 1, "** Error: Script %08X in file \"%s\" **", script->refID, modName);
	////		_MESSAGE("%s", errorHeader);
	//		_MESSAGE("** Script Error: Script %08x in file \"%s\" **", script->refID, modName);
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
	//		naughtyScripts.insert(script->refID);
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

UInt32 GetActorValueMax(UInt32 actorValueCode) {
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