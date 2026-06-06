#pragma once

#include "InventoryIterator.hpp"

class ExtraDataList;
class TESObjectREFR;
class ItemChange;
class InventoryIterator;
class TESObjectWEAP;
class TESAmmo;

class InventoryChanges {
public:
	InventoryChanges(TESObjectREFR* apOwner);
	~InventoryChanges();

	BSSimpleList<ItemChange*>*	pItems;
	TESObjectREFR*				pOwner;
	float						fCurrentWeight;
	float						fPreviousWeight;
	bool						bChanged;

	static InventoryChanges* GetInventoryChanges(TESObjectREFR* apOwner);

	void InitScripts();

	ItemChange* GetObjectInList(const TESBoundObject* apObject, bool abLeveled, uint32_t auiRefID) const;

	int32_t GetObjectCount(const TESBoundObject* apObject) const;
	
	typedef bool(* IterateFunc)(ItemChange*, void*);
	int32_t IterateInventory(IterateFunc apFunc, void* apArgument, uint32_t auiIterateFlags) const;

	bool GetNextItem(InventoryIterator& arIter, ItemChange*& arItem, uint8_t aucFindFlags);

	TESAmmo* GetAmmoForWeapon(TESObjectWEAP* apWeapon, bool& arbHasAmmo) const;

	void ResetCachedWeights();
};

ASSERT_SIZE(InventoryChanges, 0x14);