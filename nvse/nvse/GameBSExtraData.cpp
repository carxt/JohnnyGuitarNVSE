#include "GameBSExtraData.h"
#include "GameAPI.h"
#include "GameExtraData.h"

bool BaseExtraList::HasType(uint32_t type) const {
	uint32_t index = (type >> 3);
	uint8_t bitMask = 1 << (type % 8);
	return (m_presenceBitfield[index] & bitMask) != 0;
}

__declspec(naked) BSExtraData* BaseExtraList::GetByType(uint32_t type) const {
	__asm
	{
		cmp		dword ptr[ecx + 4], 0
		jz		retnNULL
		mov		edx, [esp + 4]
		shr		edx, 3
		movzx	eax, byte ptr[ecx + edx + 8]
		mov		edx, [esp + 4]
		and edx, 7
		bt		eax, edx
		jnc		retnNULL
		push	ecx
		mov		ecx, 0x11C3920
		call	LightCS::EnterSleep
		pop		ecx
		mov		eax, [ecx + 4]
		mov		edx, [esp + 4]
		ALIGN	16
		iterHead:
		cmp[eax + 4], dl
			jz		lockLeave
			mov		eax, [eax + 8]
			test	eax, eax
			jnz		iterHead
			lockLeave :
		mov		edx, 0x11C3920
			dec		dword ptr[edx + 4]
			jnz		done
			mov		dword ptr[edx], 0
			done :
			retn	4
			retnNULL :
			xor eax, eax
			retn	4
	}
}

void BaseExtraList::MarkType(uint32_t type, bool bCleared) {
	uint32_t index = (type >> 3);
	uint8_t bitMask = 1 << (type % 8);
	uint8_t& flag = m_presenceBitfield[index];
	if (bCleared) flag &= ~bitMask;
	else flag |= bitMask;
}

__declspec(naked) void BaseExtraList::Remove(BSExtraData* toRemove, bool doFree) {
	static const uint32_t procAddr = 0x410020;
	__asm	jmp		procAddr
}

__declspec(naked) BSExtraData* BaseExtraList::Add(BSExtraData* xData) {
	static const uint32_t procAddr = 0x40FF60;
	__asm	jmp		procAddr
}

ExtraDataList* ExtraDataList::Create(BSExtraData* xBSData) {
	ExtraDataList* xData = BSMemory::malloc<ExtraDataList>();
	MemZero(xData, sizeof(ExtraDataList));
	*(uint32_t*)xData = 0x10143E8;
	if (xBSData) xData->Add(xBSData);
	return xData;
}

__declspec(naked) void BaseExtraList::RemoveByType(uint32_t type) {
	static const uint32_t procAddr = 0x410140;
	__asm	jmp		procAddr
}

__declspec(naked) void BaseExtraList::RemoveAll(bool doFree) {
	static const uint32_t procAddr = 0x411FD0;
	__asm	jmp		procAddr
}

__declspec(naked) void BaseExtraList::Copy(BaseExtraList* sourceList) {
	static const uint32_t procAddr = 0x411EC0;
	__asm	jmp		procAddr
}

bool BaseExtraList::IsWorn() {
	return HasType(kExtraData_Worn);
}

char BaseExtraList::GetExtraFactionRank(TESFaction* faction) {
	ExtraFactionChanges* xFactionChanges = GetExtraType((*this), FactionChanges);
	if (xFactionChanges && xFactionChanges->data) {
		ListNode<FactionListData>* traverse = xFactionChanges->data->Head();
		FactionListData* pData;
		do {
			pData = traverse->data;
			if (pData && (pData->faction == faction))
				return pData->rank;
		} while (traverse = traverse->next);
	}
	return -1;
}

bool BaseExtraList::MarkScriptEvent(uint32_t eventMask, TESForm* eventTarget) {
	return MarkBaseExtraListScriptEvent(eventTarget, this, eventMask);
}