#include "InventoryChanges.hpp"
#include "TESObjectREFR.hpp"

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
// Officially "GetInventoryChanges", using CE's name here due to better accuracy
InventoryChanges* InventoryChanges::GetOrAddInventoryChanges(TESObjectREFR* apOwner) {
#ifdef GAME
	return CdeclCall<InventoryChanges*>(0x4BF220, apOwner);
#else
	return CdeclCall<InventoryChanges*>(0x52A280, apOwner);
#endif
}

InventoryChanges* InventoryChanges::GetInventoryChanges(const TESObjectREFR* apOwner) {
	return apOwner ? apOwner->GetExtra()->GetContainerChanges() : nullptr;
}

// GAME - 0x4BFFB0
TESContainer* InventoryChanges::GetOriginalContainer() const {
#ifdef GAME
	return ThisCall<TESContainer*>(0x4BFFB0, this);
#else
	return pOwner ? pOwner->HasContainer() : nullptr;
#endif
}

// GAME - 0x42CDE0
bool InventoryChanges::IsEmpty() const {
	return pItems->IsEmpty();
}

// GAME - 0x4BFBA0
// GECK - 0x52A370
ItemChange* InventoryChanges::GetObjectInList(const TESBoundObject* apObject, bool abLeveled, FormID auiFormID) const {
#ifdef GAME
	return ThisCall<ItemChange*>(0x4BFBA0, this, apObject, abLeveled, auiFormID);
#else
	return ThisCall<ItemChange*>(0x52A370, this, apObject, abLeveled, auiFormID);
#endif
}

// GAME - 0x4C8F30
// GECK - 0x52A580
int32_t InventoryChanges::GetObjectCount(const TESBoundObject* apObject) const {
#ifdef GAME
	return ThisCall<int32_t>(0x4C8F30, this, apObject);
#else
	return ThisCall<int32_t>(0x52A580, this, apObject);
#endif
}

#ifdef GAME
// GAME - 0x4C8FD0
int32_t InventoryChanges::GetCount(bool abCountNonPlayable) const {
	return ThisCall<int32_t>(0x4C8FD0, this, abCountNonPlayable);
}

// GAME - 0x4D1960
void InventoryChanges::InitScripts() {
	ThisCall(0x4D1960, this);
}

// GAME - 0x4BF0E0
void InventoryChanges::ResetCachedWeights() {
	ThisCall(0x4BF0E0, this);
}

// GAME - 0x4CB320
int32_t InventoryChanges::GetGoldAmount() const {
	return ThisCall<int32_t>(0x4CB320, this);
}

// GAME - 0x4D0F40
uint32_t InventoryChanges::GetInventoryValue(bool abCountQuestItems, bool abCountGold) const {
	return ThisCall<uint32_t>(0x4D0F40, this, abCountQuestItems, abCountGold);
}

// GAME - 0x4D0900
float InventoryChanges::GetInventoryWeight(bool abHardcore) const {
	return ThisCall<float>(0x4D0900, this, abHardcore);
}

// GAME - 0x4D1180
float InventoryChanges::GetEquippedWeight(const Actor* apOwner) const {
	return ThisCall<float>(0x4D1180, this, apOwner);
}

// GAME - 0x4D4530
int32_t InventoryChanges::IterateInventory(IterateFunc apFunc, void* apUserData, uint32_t auiIterateFlags) const {
	return ThisCall<int32_t>(0x4D4530, this, apFunc, apUserData, auiIterateFlags);
}

// GAME - 0x4D4830
bool InventoryChanges::GetNextItem(InventoryIterator& arIter, ItemChange*& arItem, uint8_t aucFindFlags) {
	return ThisCall<bool>(0x4D4830, this, &arIter, &arItem, aucFindFlags);
}

// GAME - 0x4CA200
FastInventoryIterator* InventoryChanges::StartFastInventoryIteration() const {
	return ThisCall<FastInventoryIterator*>(0x4CA200, this);
}

// GAME - 0x4CA330
ClonedItemChange* InventoryChanges::GetNextFastInventoryItem(FastInventoryIterator* apIter) const {
	return ThisCall<ClonedItemChange*>(0x4CA330, this, apIter);
}

// GAME - 0x4C7300
TESAmmo* InventoryChanges::GetAmmoForWeapon(const TESObjectWEAP* apWeapon, bool& arbHasAmmo) const {
	return ThisCall<TESAmmo*>(0x4C7300, this, apWeapon, &arbHasAmmo);
}

// GAME - 0x4C6BA0
TESBoundObject* InventoryChanges::GetObjectByType(FORM_TYPE aeType, int32_t& ariCount) const {
	return ThisCall<TESBoundObject*>(0x4C6BA0, this, aeType, &ariCount);
}

// GAME - 0x4C6A10
TESBoundObject* InventoryChanges::GetObjectByPackObjType(PACKAGE_OBJECT_TYPE aeType, int32_t& ariCount) const {
	return ThisCall<TESBoundObject*>(0x4C6A10, this, aeType, &ariCount);
}
#endif


#ifdef GAME
// GAME - 0x4CFE20
bool InventoryChanges::HasObjectId(FormID auiFormID) const {
	return ThisCall<bool>(0x4CFE20, this, auiFormID);
}

// GAME - 0x4D0360
bool InventoryChanges::HasQuestObject() const {
	return ThisCall<bool>(0x4D0360, this);
}
#endif

// GAME - 0x4D0490
// GECK - 0x52DA80
bool InventoryChanges::HasScript() const {
#ifdef GAME
	return ThisCall<bool>(0x4D0490, this);
#else
	return ThisCall<bool>(0x52DA80, this);
#endif
}

// GAME - 0x4BFDA0
// GECK - 0x52A400
ExtraDataList* InventoryChanges::WearingObject(const TESBoundObject* apObject, bool abShouldWear) {
#ifdef GAME
	return ThisCall<ExtraDataList*>(0x4BFDA0, this, apObject, abShouldWear);
#else
	return ThisCall<ExtraDataList*>(0x52A400, this, apObject, abShouldWear);
#endif
}

#ifdef GAME
// GAME - 0x4BFC80
bool InventoryChanges::WearingVoiceModulateItem() const {
	return ThisCall<bool>(0x4BFC80, this);
}

// GAME - 0x4C94F0
ClonedItemChange* InventoryChanges::GetItemByIndex(int32_t aiIndex) const {
	return ThisCall<ClonedItemChange*>(0x4C94F0, this, aiIndex);
}

// GAME - 0x4D0650
ClonedItemChange* InventoryChanges::GetInventoryItem(const TESBoundObject* apObject, FormID auiFormID) const {
	return ThisCall<ClonedItemChange*>(0x4D0650, this, apObject, auiFormID);
}
#endif

// GAME - 0x4C8C10
// GECK - 0x52C850
ClonedItemChange* InventoryChanges::GetWornItem(BIPED_OBJECT aeBipedObject, bool abArmorOnly) const {
#ifdef GAME
	return ThisCall<ClonedItemChange*>(0x4C8C10, this, aeBipedObject, abArmorOnly);
#else
	return ThisCall<ClonedItemChange*>(0x52C850, this, aeBipedObject, abArmorOnly);
#endif
}

// GAME - 0x4C7400
// GECK - 0x52CF50
ClonedItemChange* InventoryChanges::GetBestWeapon(const TESActorBase* apActorBase, float& arfValue, COMBAT_WEAPON_TYPE aeType, bool abUseCanNotWear) const {
#ifdef GAME
	return ThisCall<ClonedItemChange*>(0x4C7400, this, apActorBase, &arfValue, aeType, abUseCanNotWear);
#else
	return ThisCall<ClonedItemChange*>(0x52CF50, this, apActorBase, &arfValue, aeType, abUseCanNotWear);
#endif
}

// GAME - 0x4C6F60
// GECK - 0x52C520
ClonedItemChange* InventoryChanges::GetBestAmmo(const TESActorBase* apActorBase, bool abUseCanNotWear) const {
#ifdef GAME
	return ThisCall<ClonedItemChange*>(0x4C6F60, this, apActorBase, abUseCanNotWear);
#else
	return ThisCall<ClonedItemChange*>(0x52C520, this, apActorBase, abUseCanNotWear);
#endif
}

// GAME - 0x4C8220
// GECK - 0x52D400
ClonedItemChange* InventoryChanges::GetBestArmor(const TESActorBase* apActorBase, BIPED_OBJECT aeBipedObject, bool abUseCanNotWear) const {
#ifdef GAME
	return ThisCall<ClonedItemChange*>(0x4C8220, this, apActorBase, aeBipedObject, abUseCanNotWear);
#else
	return ThisCall<ClonedItemChange*>(0x52D400, this, apActorBase, aeBipedObject, abUseCanNotWear);
#endif
}

#ifdef GAME
// GAME - 0x4CAFE0
ClonedItemChange* InventoryChanges::GetBestFood() const {
	return ThisCall<ClonedItemChange*>(0x4CAFE0, this);
}

// GAME - 0x4BF4B0
ClonedItemChange* InventoryChanges::GetHotkeyItem(int32_t aiHotkey) const {
	return ThisCall<ClonedItemChange*>(0x4BF4B0, this, aiHotkey);
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