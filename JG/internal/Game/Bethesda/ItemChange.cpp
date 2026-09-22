#include "ItemChange.hpp"
#ifdef EDITOR
#include "ExtraDataList.hpp"
#endif

// GAME - 0x76B630
ItemChange::ItemChange() {
#ifdef GAME
	ThisCall(0x76B630, this);
#else
	pObject = nullptr;
	pExtraLists = nullptr;
	iNumber = 0;
#endif
}

#ifdef GAME
// GAME - 0x4BC650
ItemChange::ItemChange(const ItemChange& arOther) {
	ThisCall(0x4BC650, this, &arOther);
}
#endif

// GAME - 0x4BC550
// GECK - 0x529F60
ItemChange::ItemChange(TESBoundObject* apObject, int32_t aiNumber) {
#ifdef GAME
	ThisCall(0x4BC550, this, apObject, aiNumber);
#else
	ThisCall(0x529F60, this, apObject, aiNumber);
#endif
}

// GAME - 0x4BC5F0
// GECK - 0x52A6D0
ItemChange::~ItemChange() {
#ifdef GAME
	ThisCall(0x4BC5F0, this);
#else
	ThisCall(0x52A6D0, this);
#endif
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
TESBoundObject* ItemChange::GetItemObject() const {
	return pObject;
}

#ifdef GAME
// GAME - 0x4BE2D0
const char* ItemChange::GetFullName() const {
	return ThisCall<const char*>(0x4BE2D0, this);
}
#endif

// GAME - 0x4BC780
// GECK - 0x52A700
void ItemChange::DeleteAllExtra() {
#ifdef GAME
	ThisCall(0x4BC780, this);
#else
	ThisCall(0x52A700, this);
#endif
}

// GAME - 0x4BC810
void ItemChange::Copy(ItemChange* apSource) {
#ifdef GAME
	ThisCall(0x4BC810, this, apSource);
#else
	if (!apSource)
		return;

	pObject = apSource->pObject;
	pExtraLists = new BSSimpleList<ExtraDataList*>();
	for (auto i = apSource->GetExtraDataList(); i && i->GetItem(); i = i->GetNext()) {
		GetExtraDataList()->AddHead(i->GetItem());
	}
#endif
}

#ifdef GAME
// GAME - 0x4BCA80
uint32_t ItemChange::GetAmountNonDefaultExtra() const {
	return ThisCall<uint32_t>(0x4BCA80, this);
}
#endif

// GAME - 0x4BC8F0
// GECK - 0x529FB0
uint32_t ItemChange::GetExtraTotalCount(bool abWornIgnore) const {
#ifdef GAME
	return ThisCall<uint32_t>(0x4BC8F0, this, abWornIgnore);
#else
	return ThisCall<uint32_t>(0x529FB0, this, abWornIgnore);
#endif
}

// GAME - 0x4BC980
// GECK - 0x52A750
uint32_t ItemChange::GetExtraTotalDefaultCount() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x4BC980, this);
#else
	return ThisCall<uint32_t>(0x52A750, this);
#endif
}

// GAME - 0x4BCB70
// GECK - 0x5CA000 (stub)
bool ItemChange::HasLeveledExtra() const {
#ifdef GAME
	return ThisCall<bool>(0x4BCB70, this);
#else
	return true;
#endif
}

#ifdef GAME
// GAME - 0x4BCCB0
bool ItemChange::HasStolenData() const {
	return ThisCall<bool>(0x4BCCB0, this);
}

// GAME - 0x4BD820
uint8_t ItemChange::GetModSlots() const {
	return ThisCall<uint8_t>(0x4BD820, this);
}

// GAME - 0x4BDA70
bool ItemChange::HasModEffectActive(uint8_t aeEffect) const {
	return ThisCall<bool>(0x4BDA70, this, aeEffect);
}
#endif

// GAME - 0x4BD8D0
// GECK - 0x52A080
bool ItemChange::HasModEffectActive(uint8_t aeEffect, float& arDamage) const {
#ifdef GAME
	return ThisCall<bool>(0x4BD8D0, this, aeEffect, &arDamage);
#else
	return ThisCall<bool>(0x52A080, this, aeEffect);
#endif
}


#ifdef GAME
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
#endif

// GAME - 0x4BDDD0
// GECK - 0x52A130
bool ItemChange::GetWorn(bool abLeftOnly) const {
#ifdef GAME
	return ThisCall<bool>(0x4BDDD0, this, abLeftOnly);
#else
	return ThisCall<bool>(0x52A130, this, abLeftOnly);
#endif
}

// GAME - 0x4BE3D0
// GECK - 0x52A7B0
void ItemChange::SetWorn(bool abEquip, bool abLeft, bool abDelete) {
#ifdef GAME
	ThisCall(0x4BE3D0, this, abEquip, abLeft, abDelete);
#else
	ThisCall(0x52A7B0, this, abEquip, abLeft, abDelete);
#endif
}

#ifdef GAME
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
#endif

// GAME - 0x4BDE40
// GECK - 0x52A170
Script* ItemChange::GetScript() const {
#ifdef GAME
	return ThisCall<Script*>(0x4BDE40, this);
#else
	return ThisCall<Script*>(0x52A170, this);
#endif
}

// GAME - 0x4BD740
TESForm* ItemChange::GetItemOwnership() const {
#ifdef GAME
	return ThisCall<TESForm*>(0x4BD740, this);
#else
	if (pExtraLists && pExtraLists->GetItem())
		return pExtraLists->GetItem()->GetOwner();
	return nullptr;
#endif
}

#ifdef GAME
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