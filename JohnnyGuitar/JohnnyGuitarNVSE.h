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
void CellExpiredHook();
__declspec(naked) void __fastcall AddExtraCrimeList(UInt32* data, TESObjectREFR* a2, UInt32 time) {
	static const UInt32 procAddr = 0x41CE50;
	__asm {	
		jmp procAddr
	}
}
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
__declspec(naked) UInt32 __fastcall GetGameTime(UInt32 *gameTimeGlobal) {
	static const UInt32 procAddr = 0x867DA0;
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
	WriteRelJump(0x79A0D8, UInt32(CellExpiredHook));
	WriteRelJump(0x77D612, UInt32(LevelUpHook));
}

bool __fastcall checkExpired(TileImage* mapMarkerTile, tList<TESObjectREFR>	*mapMarkerList) {
	UInt32 valueID = TraitNameToID("_MarkerIndex");
	tList<TESObjectREFR> mapMarkerLis = *mapMarkerList;
	if (valueID) {
		Tile::Value *markerIdx = mapMarkerTile->GetValue(valueID);
		if (markerIdx) {
		TESObjectREFR *mapMarker = mapMarkerLis.GetNthItem(markerIdx->num);
		if (mapMarker) {
		float hoursToRespawn = 0;
		float detachTime = 0;
		float gameHoursPassed = 0;
		if (mapMarker->parentCell)
		detachTime = GetDetachTime(mapMarker->parentCell);
		if (detachTime == 0) return false;
		else if (detachTime == -1) return true;
		else {
		hoursToRespawn = GetHoursToRespawn();
		gameHoursPassed = GetHoursPassed((UInt32*)0x11DE7B8);
		if ((gameHoursPassed - detachTime) > hoursToRespawn) return true;
		}
		}
		} 

	}
	return false;
}
_declspec(naked) void CellExpiredHook() {
	static const UInt32 retnAddr = 0x79A0DD;
	static const UInt32 func = 0x700320;
	static const char* one = "1";
	_asm {
		call func
		mov ecx, [ebp-0x48]
		mov edx, [ecx+0xD8]
		mov ecx, [ecx+0xD4]
		call checkExpired
		test al, al
		jz done
		push offset one
		call Console_Print
		jmp done
		done :
		jmp retnAddr
	}
}
const char* plus = "+";
char MarkerAddedNameBuffer[MAX_PATH];
char* __fastcall AppendName(char* text) {
	MarkerAddedNameBuffer[0] = 0;
	const char* text2 = text;
	strcpy_s(MarkerAddedNameBuffer, MAX_PATH, text2);
	strcat_s(MarkerAddedNameBuffer, plus);
	return MarkerAddedNameBuffer;
}