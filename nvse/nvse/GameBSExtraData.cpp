#include "GameBSExtraData.h"
#include "GameAPI.h"
#include "GameExtraData.h"

bool BaseExtraList::HasType(UInt32 type) const
{
	UInt32 index = (type >> 3);
	UInt8 bitMask = 1 << (type % 8);
	return (m_presenceBitfield[index] & bitMask) != 0;
}

__declspec(naked) BSExtraData *BaseExtraList::GetByType(UInt32 type) const
{
	__asm
	{
		cmp		dword ptr[ecx + 4], 0
		jz		retnNULL
		mov		edx, [esp + 4]
		shr		edx, 3
		movzx	eax, byte ptr[ecx + edx + 8]
		mov		edx, [esp + 4]
		and		edx, 7
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
		cmp		[eax + 4], dl
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
		xor		eax, eax
		retn	4
	}
}

void BaseExtraList::MarkType(UInt32 type, bool bCleared)
{
	UInt32 index = (type >> 3);
	UInt8 bitMask = 1 << (type % 8);
	UInt8 &flag = m_presenceBitfield[index];
	if (bCleared) flag &= ~bitMask;
	else flag |= bitMask;
}

__declspec(naked) void BaseExtraList::Remove(BSExtraData *toRemove, bool doFree)
{
	static const UInt32 procAddr = 0x410020;
	__asm	jmp		procAddr
}

__declspec(naked) BSExtraData *BaseExtraList::Add(BSExtraData *xData)
{
	static const UInt32 procAddr = 0x40FF60;
	__asm	jmp		procAddr
}

ExtraDataList *ExtraDataList::Create(BSExtraData *xBSData)
{
	ExtraDataList *xData = (ExtraDataList*)GameHeapAlloc(sizeof(ExtraDataList));
	MemZero(xData, sizeof(ExtraDataList));
	*(UInt32*)xData = 0x10143E8;
	if (xBSData) xData->Add(xBSData);
	return xData;
}

__declspec(naked) void BaseExtraList::RemoveByType(UInt32 type)
{
	static const UInt32 procAddr = 0x410140;
	__asm	jmp		procAddr
}

__declspec(naked) void BaseExtraList::RemoveAll(bool doFree)
{
	static const UInt32 procAddr = 0x411FD0;
	__asm	jmp		procAddr
}

__declspec(naked) void BaseExtraList::Copy(BaseExtraList *sourceList)
{
	static const UInt32 procAddr = 0x411EC0;
	__asm	jmp		procAddr
}

bool BaseExtraList::IsWorn()
{
	return HasType(kExtraData_Worn);
}

char BaseExtraList::GetExtraFactionRank(TESFaction *faction)
{
	ExtraFactionChanges *xFactionChanges = GetExtraType((*this), FactionChanges);
	if (xFactionChanges && xFactionChanges->data)
	{
		ListNode<FactionListData> *traverse = xFactionChanges->data->Head();
		FactionListData *pData;
		do
		{
			pData = traverse->data;
			if (pData && (pData->faction == faction))
				return pData->rank;
		}
		while (traverse = traverse->next);
	}
	return -1;
}

void BaseExtraList::DebugDump() const
{
	_MESSAGE("\nBaseExtraList Dump:");
	Console_Print("BaseExtraList Dump:");
	gLog.Indent();
	if (m_data)
	{
		for (BSExtraData *traverse = m_data; traverse; traverse = traverse->next)
		{
			_MESSAGE("%08X\t%02X\t%s\t%08X", traverse, traverse->type, GetExtraDataName(traverse->type), ((UInt32*)traverse)[3]);
			Console_Print("%08X  %02X  %s  %08X", traverse, traverse->type, GetExtraDataName(traverse->type), ((UInt32*)traverse)[3]);
		}
		Console_Print(" ");
	}
	else
	{
		_MESSAGE("No data in list");
		Console_Print("No data in list");
	}
	gLog.Outdent();
}

bool BaseExtraList::MarkScriptEvent(UInt32 eventMask, TESForm* eventTarget)
{
	return MarkBaseExtraListScriptEvent(eventTarget, this, eventMask);
}
