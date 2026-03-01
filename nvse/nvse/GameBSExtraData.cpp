#include "GameBSExtraData.h"
#include "GameAPI.h"
#include "GameExtraData.h"

bool BaseExtraList::HasType(uint32_t type) const {
	return ThisCall<bool>(0x40FE80, this, type);
}

BSExtraData* BaseExtraList::GetByType(uint32_t type) const {
	return ThisCall<BSExtraData*>(0x410220, this, type);
}

void BaseExtraList::MarkType(uint32_t type, bool bCleared) {
	ThisCall(0x40FEE0, this, type, !bCleared);
}

void BaseExtraList::Remove(BSExtraData* toRemove, bool doFree) {
	ThisCall(0x410020, this, toRemove, doFree);
}

BSExtraData* BaseExtraList::Add(BSExtraData* xData) {
	return ThisCall<BSExtraData*>(0x40FF60, this, xData);
}

ExtraDataList* ExtraDataList::Create(BSExtraData* xBSData) {
	ExtraDataList* xData = BSMemory::create<ExtraDataList, 0x410360>();
	if (xBSData) 
		xData->Add(xBSData);
	return xData;
}

void BaseExtraList::RemoveByType(uint32_t type) {
	ThisCall(0x410140, this, type);
}

void BaseExtraList::RemoveAll(bool doFree) {
	ThisCall(0x411FD0, this, doFree);
}

void BaseExtraList::Copy(BaseExtraList* sourceList) {
	ThisCall(0x411EC0, this, sourceList);
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