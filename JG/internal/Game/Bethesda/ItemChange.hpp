#pragma once

#include "BSSimpleList.hpp"

class Actor;
class TESBoundObject;
class ExtraDataList;
class InventoryChanges;
class AlchemyItem;
class Script;
class TESForm;
class ActorValueOwner;

class ItemChange {
public:
	ItemChange();
#ifdef GAME
	ItemChange(const ItemChange& arOther);
#endif
	ItemChange(TESBoundObject* apObject, int32_t aiNumber);
	~ItemChange();

	BSSimpleList<ExtraDataList*>*	pExtraLists;
	int32_t							iNumber;
	TESBoundObject*					pObject;

	BSSimpleList<ExtraDataList*>* GetExtraDataList() const;

	int32_t GetCount() const;
	void SetCount(int32_t aiNumber);

	TESBoundObject* GetItemObject() const;

#ifdef GAME
	const char* GetFullName() const;
#endif

	void DeleteAllExtra();

	void Copy(ItemChange* apSource);

#ifdef GAME
	uint32_t GetAmountNonDefaultExtra() const;
#endif

	uint32_t GetExtraTotalCount(bool abWornIgnore) const;

	uint32_t GetExtraTotalDefaultCount() const;

	bool HasLeveledExtra() const;

#ifdef GAME
	bool HasStolenData() const;

	uint8_t	GetModSlots() const;

	bool HasModEffectActive(uint8_t aeEffect) const;
#endif

	bool HasModEffectActive(uint8_t aeEffect, float& arDamage) const;

#ifdef GAME
	float GetItemHealth(bool abPercentage) const;
	void SetItemHealth(float afValue, InventoryChanges* apInventory, ExtraDataList* apExtra, bool abDelete);

	float GetItemValue() const;
#endif

	bool GetWorn(bool abLeftOnly) const;
	void SetWorn(bool abEquip, bool abLeft, bool abDelete);

#ifdef GAME
	AlchemyItem* GetPoison() const;
	void SetPoison(AlchemyItem* apPoison);
	void RemovePoison();
#endif

	Script* GetScript() const;

	TESForm* GetItemOwnership() const;

#ifdef GAME
	float GetModifiedArmorRating(ActorValueOwner* apActor) const;

	float GetModifiedDamageThreshold(ActorValueOwner* apActor) const;

	float GetModifiedAttackDamage(ActorValueOwner* apActor, float afDamageMult, bool abIgnoreExplosion) const;
#endif
};

ASSERT_SIZE(ItemChange, 0xC);

// Cloned from the original, delete after use
using ClonedItemChange = ItemChange;