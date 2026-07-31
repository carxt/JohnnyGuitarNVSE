#include "InventoryChanges.hpp"

// GAME - 0x4BEFB0
InventoryChanges::InventoryChanges(TESObjectREFR* apOwner) {
	ThisCall(0x4BEFB0, this, apOwner);
}

// GAME - 0x4BF150
InventoryChanges::~InventoryChanges() {
	ThisCall(0x4BF150, this);
}

// GAME - 0x4BF220
InventoryChanges* InventoryChanges::GetInventoryChanges(TESObjectREFR* apOwner) {
	return CdeclCall<InventoryChanges*>(0x4BF220, apOwner);
}

// GAME - 0x4D1960
void InventoryChanges::InitScripts() {
	ThisCall(0x4D1960, this);
}

// GAME - 0x4C8F30
int32_t InventoryChanges::GetObjectCount(TESBoundObject* apObject) const {
	return ThisCall<int32_t>(0x4C8F30, this, apObject);
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
