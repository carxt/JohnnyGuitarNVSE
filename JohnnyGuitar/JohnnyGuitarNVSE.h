#include "..\..\nvse\nvse\ScriptUtils.h"
#pragma once

NVSEArrayVarInterface *ArrIfc = NULL;
NVSEStringVarInterface *StrIfc = NULL;
NVSEMessagingInterface *g_msg = NULL;
NVSEScriptInterface *g_script = NULL;
NVSECommandTableInterface *CmdIfc = NULL; 
bool isShowLevelUp = true;

char* StrArgBuf;
#define ExtractArgsEx(...) g_script->ExtractArgsEx(__VA_ARGS__)
#define ExtractFormatStringArgs(...) g_script->ExtractFormatStringArgs(__VA_ARGS__)
#define IS_TYPE(form, type) (*(UInt32*)form == kVtbl_##type)
#define NOT_ID(form, type) (form->typeID != kFormType_##type)
#define IS_ID(form, type) (form->typeID == kFormType_##type)
#define REG_CMD(name) nvse->RegisterCommand(&kCommandInfo_##name);
#define REG_TYPED_CMD(name, type) nvse->RegisterTypedCommand(&kCommandInfo_##name,kRetnType_##type);
IDebugLog ParamLog;

__declspec(naked) bool __fastcall HasSeenData(TESObjectCELL *cell) {
	__asm {
		push	kExtraData_SeenData
		add		ecx, 0x28
		call	BaseExtraList::GetByType
		test	eax, eax
		setnz	al
		retn
	}
}
__declspec(naked) SInt32 __fastcall GetDetachTime(TESObjectCELL *cell) {
	__asm {
		push	kExtraData_DetachTime
		add		ecx, 0x28
		call	BaseExtraList::GetByType
		test	eax, eax
		jz done
		mov eax, [eax+0xC]
		done:
			retn
	}
}
// returns daysPassed times 24 and floored
__declspec(naked) UInt32 __fastcall GetHoursPassed(UInt32 *gameTimeGlobal) {
	static const UInt32 procAddr = 0x867E30;
	__asm {
		jmp procAddr
	}
}
// checks gmst
__declspec(naked) UInt32 GetHoursToRespawn() {
	static const UInt32 procAddr = 0x526100;
	__asm {
		jmp procAddr
	}
}
_declspec(naked) void LevelUpHook() {
	static const UInt32 noShowAddr = 0x77D903;
	static const UInt32 showAddr = 0x77D618;
	_asm {
		jne noLevelUp
		cmp dword ptr ds : [isShowLevelUp], 0
		je noLevelUp
		jmp showAddr
		noLevelUp:
		jmp noShowAddr
	}
}
void HandleGameHooks()
{

	WriteRelJump(0x77D612, UInt32(LevelUpHook));


}



