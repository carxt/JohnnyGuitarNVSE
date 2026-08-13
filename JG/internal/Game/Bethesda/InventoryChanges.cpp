#include "InventoryChanges.hpp"

// GAME - 0x4BEFB0
// GECK - 0x52A1A0
InventoryChanges::InventoryChanges(TESObjectREFR* apOwner) {
#ifdef GAME
	ThisCall(0x4BEFB0, this, apOwner);
#else
	ThisCall(0x52A1A0, this, apOwner);
#endif
}

// GAME - 0x4BF150
// GECK - 0x52CA90
InventoryChanges::~InventoryChanges() {
#ifdef GAME
	ThisCall(0x4BF150, this);
#else
	ThisCall(0x52CA90, this);
#endif
}

// GAME - 0x4BF220
// GECK - 0x52A280
InventoryChanges* InventoryChanges::GetInventoryChanges(TESObjectREFR* apOwner) {
#ifdef GAME
	return CdeclCall<InventoryChanges*>(0x4BF220, apOwner);
#else
	return CdeclCall<InventoryChanges*>(0x52A280, apOwner);
#endif
}

// GAME - 0x4C8F30
// GECK - 0x52A580
int32_t InventoryChanges::GetObjectCount(TESBoundObject* apObject) const {
#ifdef GAME
	return ThisCall<int32_t>(0x4C8F30, this, apObject);
#else
	return ThisCall<int32_t>(0x52A580, this, apObject);
#endif
}

#ifdef GAME
// GAME - 0x4D1960
void InventoryChanges::InitScripts() {
	ThisCall(0x4D1960, this);
}

// GAME - 0x4D4530
int32_t InventoryChanges::IterateInventory(IterateFunc apFunc, void* apArgument, uint32_t auiIterateFlags) const {
	return ThisCall<int32_t>(0x4D4530, this, apFunc, apArgument, auiIterateFlags);
}

// GAME - 0x4D4830
bool InventoryChanges::GetNextItem(InventoryIterator& arIter, ItemChange*& arItem, uint8_t aucFindFlags) {
	return ThisCall<bool>(0x4D4830, this, &arIter, &arItem, aucFindFlags);
}

// GAME - 0x4C7300
TESAmmo* InventoryChanges::GetAmmoForWeapon(TESObjectWEAP* apWeapon, bool& arbHasAmmo) const {
	return ThisCall<TESAmmo*>(0x4C7300, this, apWeapon, &arbHasAmmo);
}

// GAME - 0x4BF0E0
void InventoryChanges::ResetCachedWeights() {
	ThisCall(0x4BF0E0, this);
}

// GAME - 0x4BF4B0
ItemChange* InventoryChanges::GetHotkeyItem(int32_t aiHotkey) const {
	return ThisCall<ItemChange*>(0x4BF4B0, this, aiHotkey);
}

// GAME - 0x4BF330
void InventoryChanges::RemoveHotkeyItem(ItemChange* apItem, int32_t aiHotkey) const {
	ThisCall(0x4BF330, this, apItem, aiHotkey);
}

// GAME - 0x4BF800
void InventoryChanges::SetHotkeyItem(ItemChange* apItem, ExtraDataList* apExtra, int32_t aiHotkey) const {
	ThisCall(0x4BF800, this, apItem, apExtra, aiHotkey);
}
#endif