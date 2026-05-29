#pragma once

#include "ExtraDataList.hpp"

class Actor;
class ActorValueOwner;
class TESBoundObject;
class TESForm;
class AlchemyItem;
class Script;
class InventoryChanges;

class ItemChange {
public:
	ItemChange();
	ItemChange(const ItemChange& arOther);
	ItemChange(ItemChange&& arOther);
	ItemChange(TESBoundObject* apObject, int32_t aiNumber = 0);
	~ItemChange();

	BSSimpleList<ExtraDataList*>*	pExtraLists;
	int32_t							iNumber;
	TESBoundObject*					pObject;

	BSSimpleList<ExtraDataList*>* GetExtraDataList() const;

	int32_t GetCount() const;
	void SetCount(int32_t aiNumber);

	TESBoundObject* GetContainerObject() const;

	const char* GetFullName() const;

	void DeleteAllExtra();

	void Copy(ItemChange* apSource);

	uint32_t GetAmountNonDefaultExtra() const;

	uint32_t GetExtraTotalCount(bool abWornIgnore) const;

	uint32_t GetExtraTotalDefaultCount() const;

	bool HasLeveledExtra() const;

	bool HasStolenData() const;

	bool HasModEffectActive(uint8_t aeEffect) const;
	bool HasModEffectActive(uint8_t aeEffect, float& arDamage) const;

	float GetItemHealth(bool abPercentage) const;
	void SetItemHealth(float afValue, InventoryChanges* apInventory, ExtraDataList* apExtra, bool abDelete);

	float GetItemValue() const;

	bool GetWorn(bool abLeftOnly) const;
	void SetWorn(bool abEquip, bool abLeft, bool abDelete);

	AlchemyItem* GetPoison() const;
	void SetPoison(AlchemyItem* apPoison);
	void RemovePoison();

	Script* GetScript() const;

	TESForm* GetItemOwnership() const;

	float GetModifiedArmorRating(ActorValueOwner* apActor) const;

	float GetModifiedDamageThreshold(ActorValueOwner* apActor) const;

	float GetModifiedAttackDamage(ActorValueOwner* apActor, float afDamageMult, bool abIgnoreExplosion) const;
};

ASSERT_SIZE(ItemChange, 0xC);