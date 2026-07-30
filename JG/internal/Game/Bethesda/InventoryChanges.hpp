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

	int32_t GetObjectCount(TESBoundObject* apObject) const;
	
	typedef bool(* IterateFunc)(ItemChange*, void*);
	int32_t IterateInventory(IterateFunc apFunc, void* apArgument, uint32_t auiIterateFlags) const;

	bool GetNextItem(InventoryIterator& arIter, ItemChange*& arItem, uint8_t aucFindFlags);

	TESAmmo* GetAmmoForWeapon(TESObjectWEAP* apWeapon, bool& arbHasAmmo) const;

	void ResetCachedWeights();

	ItemChange* GetHotkeyItem(int32_t aiHotkey) const;
	void RemoveHotkeyItem(ItemChange* apItem, int32_t aiHotkey) const;
	void SetHotkeyItem(ItemChange* apItem, ExtraDataList* apExtra, int32_t aiHotkey) const;
};

ASSERT_SIZE(InventoryChanges, 0x14);