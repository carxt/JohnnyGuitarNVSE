#include "..\..\nvse\nvse\ScriptUtils.h"
#pragma once

NVSEArrayVarInterface *ArrIfc = NULL;
//PlayerCharacter *thePlayer = *(PlayerCharacter**) 0x011DEA3C;
NVSEStringVarInterface *StrIfc = NULL;
NVSEMessagingInterface *g_msg = NULL;
NVSEScriptInterface *g_script = NULL;
NVSECommandTableInterface *CmdIfc = NULL; 

char* StrArgBuf;
#define ExtractArgsEx(...) g_script->ExtractArgsEx(__VA_ARGS__)
#define ExtractFormatStringArgs(...) g_script->ExtractFormatStringArgs(__VA_ARGS__)
#define IS_TYPE(form, type) (*(UInt32*)form == kVtbl_##type)
#define REG_CMD(name) nvse->RegisterCommand(&kCommandInfo_##name);
#define REG_TYPED_CMD(name, type) nvse->RegisterTypedCommand(&kCommandInfo_##name,kRetnType_##type);
IDebugLog ParamLog;




