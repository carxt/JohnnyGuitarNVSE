#include "..\..\nvse\nvse\ScriptUtils.h"
#pragma once

NVSEArrayVarInterface *ArrIfc = NULL;
NVSEStringVarInterface *StrIfc = NULL;
NVSEMessagingInterface *g_msg = NULL;
NVSEScriptInterface *g_script = NULL;
NVSECommandTableInterface *CmdIfc = NULL; 
InventoryRef* (*InventoryRefGetForID)(UInt32 refID);
float(*GetWeaponDPS)(ActorValueOwner *avOwner, TESObjectWEAP *weapon, float condition, UInt8 arg4, ContChangesEntry *entry, UInt8 arg6, UInt8 arg7, int arg8, float arg9, float arg10, UInt8 arg11, UInt8 arg12, TESForm *ammo) =
(float(*)(ActorValueOwner*, TESObjectWEAP*, float, UInt8, ContChangesEntry*, UInt8, UInt8, int, float, float, UInt8, UInt8, TESForm*))0x645380;
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
bool loadEditorIDs = 0;
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
__declspec(naked) void Tile::SetFloat(UInt32 id, float fltVal, bool bPropagate)
{
	static const UInt32 procAddr = 0xA012D0;
	__asm	jmp		procAddr
}

__declspec(naked) float ExtraContainerChanges::EntryData::GetItemHealthPerc(bool arg1)
{
	static const UInt32 procAddr = 0x4BCDB0;
	__asm	jmp		procAddr
}
__declspec(naked) ContChangesEntry *ExtraContainerChanges::EntryDataList::FindForItem(TESForm *item)
{
	__asm
	{
		mov		edx, [esp + 4]
		listIter:
		mov		eax, [ecx]
			test	eax, eax
			jz		listNext
			cmp[eax + 8], edx
			jz		done
			listNext :
		mov		ecx, [ecx + 4]
			test	ecx, ecx
			jnz		listIter
			xor		eax, eax
			done :
		retn	4
	}
}

__declspec(naked) ExtraContainerChanges::EntryDataList *TESObjectREFR::GetContainerChangesList()
{
	__asm
	{
		push	kExtraData_ContainerChanges
		add		ecx, 0x44
		call	BaseExtraList::GetByType
		test	eax, eax
		jz		done
		mov		eax, [eax + 0xC]
		test	eax, eax
		jz		done
		mov		eax, [eax]
		done:
		retn
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
bool isInPerkMenu = false;
_declspec(naked) void PerkMenuHook() {
	static const UInt32 noBackBtnAddr = 0x785DE8;
	static const UInt32 retnAddr = 0x785D1B;
	_asm {
		cmp dword ptr ds : [isInPerkMenu], 0
		je noBackBtn
		mov eax, [ebp-0x10]
		jmp retnAddr
		noBackBtn:
		jmp noBackBtnAddr
	}
}
__declspec(naked) void GetFullTypeNameHook() {
	__asm jmp TESForm::hk_GetFullTypeName
}
__declspec(naked) void GetNameHook() {
	__asm jmp TESForm::hk_GetName
}
__declspec(naked) void GetRefNameHook() {
	__asm jmp TESObjectREFR::hk_GetName
}
__declspec(naked) void SetEditorIdHook() {
	__asm jmp TESForm::hk_SetEditorId
}

void LoadEditorIDs() {
	for (uint32_t i = 0; i < ARRAYSIZE(TESForm_Vtables); i++)
	{
		// Sanity check, certain ones like TESObjectCELL shouldn't be hooked
		if (*(uintptr_t *)(TESForm_Vtables[i] + 0x90) == 0x004868F0)
			SafeWrite32(TESForm_Vtables[i] + 0x90, (UInt32)GetFullTypeNameHook);

		if (*(uintptr_t *)(TESForm_Vtables[i] + 0x130) == 0x00401280)
			SafeWrite32(TESForm_Vtables[i] + 0x130, (UInt32)GetNameHook);

		if (*(uintptr_t *)(TESForm_Vtables[i] + 0x130) == 0x0055D480)
			SafeWrite32(TESForm_Vtables[i] + 0x130, (UInt32)GetRefNameHook);

		if (*(uintptr_t *)(TESForm_Vtables[i] + 0x134) == 0x00401290)
			SafeWrite32(TESForm_Vtables[i] + 0x134, (UInt32)SetEditorIdHook);
	}
}
void HandleGameHooks()
{
	WriteRelJump(0x77D612, UInt32(LevelUpHook));
	//	WriteRelJump(0x785D18, UInt32(PerkMenuHook)); TBD
	if (loadEditorIDs) LoadEditorIDs();
}
static void PatchMemoryNop(ULONG_PTR Address, SIZE_T Size)
{
	DWORD d = 0;
	VirtualProtect((LPVOID)Address, Size, PAGE_EXECUTE_READWRITE, &d);

	for (SIZE_T i = 0; i < Size; i++)
		*(volatile BYTE *)(Address + i) = 0x90; //0x90 == opcode for NOP

	VirtualProtect((LPVOID)Address, Size, d, &d);

	FlushInstructionCache(GetCurrentProcess(), (LPVOID)Address, Size);
}
