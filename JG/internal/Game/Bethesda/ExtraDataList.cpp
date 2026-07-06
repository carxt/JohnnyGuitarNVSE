#include "ExtraDataList.hpp"

ExtraDataList* ExtraDataList::Create() {
	return BSMemory::create<ExtraDataList, 0x410360>();
}

// GAME - 0x411EC0
void ExtraDataList::CopyList(ExtraDataList* apCopy) {
	ThisCall(0x411EC0, this, apCopy);
}

// GAME - 0x4121E0
void ExtraDataList::CopyListForContainer(ExtraDataList* apCopy, bool abDontRemove) {
	ThisCall(0x4121E0, this, apCopy, abDontRemove);
}

// GAME - 0x412490
void ExtraDataList::CopyListForReference(ExtraDataList* apCopy, bool abRemove) {
	ThisCall(0x412490, this, apCopy, abRemove);
}

// GAME - 0x419D10
void ExtraDataList::SetPoison(AlchemyItem* apPoison) {
	ThisCall(0x419D10, this, apPoison);
}

// GAME - 0x41AF30
void ExtraDataList::RemovePoison() {
	ThisCall(0x41AF30, this);
}

// GAME - 0x421720
TESActorBase* ExtraDataList::GetLevCreaTemplate() const {
	return ThisCall<TESActorBase*>(0x421720, this);
}

// GAME - 0x4216F0
TESActorBase* ExtraDataList::GetLevCreaOriginalBase() const {
	return ThisCall<TESActorBase*>(0x4216F0, this);
}

// GAME - 0x42F2D0
bool ExtraDataList::GetIgnoredBySandbox() const {
	return ThisCall<bool>(0x42F2D0, this);
}

// GAME - 0x42F200
void ExtraDataList::SetIgnoredBySandbox(bool abVal) {
	ThisCall(0x42F200, this, abVal);
}

// GAME - 0x418520
InventoryChanges* ExtraDataList::GetContainerChanges() const {
	return ThisCall<InventoryChanges*>(0x418520, this);
}

// GAME - 0x419650
void ExtraDataList::SetContainerChanges(InventoryChanges* apChanges) {
	ThisCall(0x419650, this, apChanges);
}
