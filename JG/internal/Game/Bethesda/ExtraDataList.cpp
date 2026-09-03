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

// GAME - 0x421D20
TESForm* ExtraDataList::GetEmittanceSource() const {
	return ThisCall<TESForm*>(0x421D20, this);
}

// GAME - 0x421D50
void ExtraDataList::SetEmittanceSource(TESForm* apSource) {
	ThisCall(0x421D50, this, apSource);
}

// GAME - 0x418C00
bool ExtraDataList::GetWeaponModSlotActive(uint8_t aucSlot) const {
	return ThisCall<bool>(0x418C00, this, aucSlot);
}

// GAME - 0x42E380
void ExtraDataList::SetWeaponModSlot(uint8_t aucSlot) {
	ThisCall(0x42E380, this, aucSlot);
}

// GAME - 0x42E560
uint8_t ExtraDataList::GetWeaponModFlags() const {
	return ThisCall<uint8_t>(0x42E560, this);
}

// GAME - 0x42E4A0
void ExtraDataList::SetWeaponModFlags(uint8_t aucFlags) {
	ThisCall(0x42E4A0, this, aucFlags);
}
