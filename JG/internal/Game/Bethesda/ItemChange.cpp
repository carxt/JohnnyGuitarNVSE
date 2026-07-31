#include "ItemChange.hpp"

// GAME - 0x76B630
ItemChange::ItemChange() {
	ThisCall(0x76B630, this);
}

// GAME - 0x4BC650
ItemChange::ItemChange(const ItemChange& arOther) {
	ThisCall(0x4BC650, this, &arOther);
}

ItemChange::ItemChange(ItemChange&& arOther) : pObject(arOther.pObject), pExtraLists(arOther.pExtraLists), iNumber(arOther.iNumber) {
	arOther.pObject = nullptr;
	arOther.pExtraLists = nullptr;
	arOther.iNumber = 0;
}

// GAME - 0x4BC550
ItemChange::ItemChange(TESBoundObject* apObject, int32_t aiNumber) {
	ThisCall(0x4BC550, this, apObject, aiNumber);
}

// GAME - 0x4BC5F0
ItemChange::~ItemChange() {
	ThisCall(0x4BC5F0, this);
}

// GAME - 0x559450
BSSimpleList<ExtraDataList*>* ItemChange::GetExtraDataList() const {
	return pExtraLists;
}

// GAME - 0x726070
int32_t ItemChange::GetCount() const {
	return iNumber;
}

// GAME - 0x6ECD40
void ItemChange::SetCount(int32_t aiNumber) {
	iNumber = aiNumber;
}

// GAME - 0x44DDC0
TESBoundObject* ItemChange::GetContainerObject() const {
	return pObject;
}

// GAME - 0x4BE2D0
const char* ItemChange::GetFullName() const {
	return ThisCall<const char*>(0x4BE2D0, this);
}

// GAME - 0x4BC780
void ItemChange::DeleteAllExtra() {
	ThisCall(0x4BC780, this);
}

// GAME - 0x4BC810
void ItemChange::Copy(ItemChange* apSource) {
	ThisCall(0x4BC810, this, apSource);
}

// GAME - 0x4BCA80
uint32_t ItemChange::GetAmountNonDefaultExtra() const {
	return ThisCall<uint32_t>(0x4BCA80, this);
}

// GAME - 0x4BC8F0
uint32_t ItemChange::GetExtraTotalCount(bool abWornIgnore) const {
	return ThisCall<uint32_t>(0x4BC8F0, this, abWornIgnore);
}

// GAME - 0x4BC980
uint32_t ItemChange::GetExtraTotalDefaultCount() const {
	return ThisCall<uint32_t>(0x4BC980, this);
}


#ifdef GAME
// GAME - 0x4BCB70
bool ItemChange::HasLeveledExtra() const {
	return ThisCall<bool>(0x4BCB70, this);
}

// GAME - 0x4BCCB0
bool ItemChange::HasStolenData() const {
	return ThisCall<bool>(0x4BCCB0, this);
}

// GAME - 0x4BDA70
bool ItemChange::HasModEffectActive(uint8_t aeEffect) const {
	return ThisCall<bool>(0x4BDA70, this, aeEffect);
}

// GAME - 0x4BD8D0
bool ItemChange::HasModEffectActive(uint8_t aeEffect, float& arDamage) const {
	return ThisCall<bool>(0x4BD8D0, this, aeEffect, &arDamage);
}

// GAME - 0x4BCDB0
float ItemChange::GetItemHealth(bool abPercentage) const {
	return ThisCall<float>(0x4BCDB0, this, abPercentage);
}

// GAME - 0x4BD030
void ItemChange::SetItemHealth(float afValue, InventoryChanges* apInventory, ExtraDataList* apExtra, bool abDelete) {
	ThisCall(0x4BD030, this, afValue, apInventory, apExtra, abDelete);
}

// GAME - 0x4BD400
float ItemChange::GetItemValue() const {
	return ThisCall<float>(0x4BD400, this);
}

// GAME - 0x4BDDD0
bool ItemChange::GetWorn(bool abLeftOnly) const {
	return ThisCall<bool>(0x4BDDD0, this, abLeftOnly);
}

// GAME - 0x4BE3D0
void ItemChange::SetWorn(bool abEquip, bool abLeft, bool abDelete) {
	ThisCall(0x4BE3D0, this, abEquip, abLeft, abDelete);
}

// GAME - 0x4BDCC0
AlchemyItem* ItemChange::GetPoison() const {
	return ThisCall<AlchemyItem*>(0x4BDCC0, this);
}

// GAME - 0x4BDD20
void ItemChange::SetPoison(AlchemyItem* apPoison) {
	ThisCall(0x4BDD20, this, apPoison);
}

// GAME - 0x4BDD80
void ItemChange::RemovePoison() {
	ThisCall(0x4BDD80, this);
}

// GAME - 0x4BDE40
Script* ItemChange::GetScript() const {
	return ThisCall<Script*>(0x4BDE40, this);
}

// GAME - 0x4BD740
TESForm* ItemChange::GetItemOwnership() const {
	return ThisCall<TESForm*>(0x4BD740, this);
}

// GAME - 0x4BDF90
float ItemChange::GetModifiedArmorRating(ActorValueOwner* apActor) const {
	return ThisCall<float>(0x4BDF90, this, apActor);
}

// GAME - 0x4BE0B0
float ItemChange::GetModifiedDamageThreshold(ActorValueOwner* apActor) const {
	return ThisCall<float>(0x4BE0B0, this, apActor);
}

// GAME - 0x4BDF00
float ItemChange::GetModifiedAttackDamage(ActorValueOwner* apActor, float afDamageMult, bool abIgnoreExplosion) const {
	return ThisCall<float>(0x4BDF00, this, apActor, afDamageMult, abIgnoreExplosion);
}
#endif

// GAME - 0x4BD820
uint8_t ItemChange::GetModSlots() const {
	return ThisCall<uint8_t>(0x4BD820, this);
}
