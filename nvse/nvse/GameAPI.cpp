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

const _ExtractArgs ExtractArgs = (_ExtractArgs)0x005ACCB0;

const _CreateFormInstance CreateFormInstance = (_CreateFormInstance)0x00465110;

const _QueueUIMessage QueueUIMessage = (_QueueUIMessage)0x007052F0;

const _ShowMessageBox ShowMessageBox = (_ShowMessageBox)0x00703E80;
const _ShowMessageBox_Callback ShowMessageBox_Callback = (_ShowMessageBox_Callback)0x005B4A70;
const _ShowMessageBox_pScriptRefID ShowMessageBox_pScriptRefID = (_ShowMessageBox_pScriptRefID)0x011CAC64;
const _ShowMessageBox_button ShowMessageBox_button = (_ShowMessageBox_button)0x0118C684;

const _GetActorValueName GetActorValueName = (_GetActorValueName)0x00066EAC0;	// See Cmd_GetActorValue_Eval
const _MarkBaseExtraListScriptEvent MarkBaseExtraListScriptEvent = (_MarkBaseExtraListScriptEvent)0x005AC790;

bool IsConsoleMode() {
	return TLSData::Get()->bConsoleOutput;
}

ConsoleManager* ConsoleManager::GetSingleton(void) {
	return CdeclCall<ConsoleManager*>(0x71B160, true);
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