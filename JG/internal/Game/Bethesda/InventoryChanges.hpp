#pragma once

#include "InventoryIterator.hpp"
#include "Obsidian/FastInventoryIterator.hpp"
#include "BSEnums.hpp"

class ExtraDataList;
class TESObjectREFR;
class TESObjectWEAP;
class TESAmmo;
class TESActorBase;

class InventoryChanges {
public:
	InventoryChanges(TESObjectREFR* apOwner);
	~InventoryChanges();

	BSSimpleList<ItemChange*>*	pItems;
	TESObjectREFR*				pOwner;
	float						fCurrentWeight;
	float						fPreviousWeight;
	bool						bChanged;

	static InventoryChanges* GetOrAddInventoryChanges(TESObjectREFR* apOwner);
	static InventoryChanges* GetInventoryChanges(const TESObjectREFR* apOwner);

	TESContainer* GetOriginalContainer() const;

	bool IsEmpty() const;

	ItemChange* GetObjectInList(const TESBoundObject* apObject, bool abLeveled, FormID auiFormID) const;

	int32_t GetObjectCount(const TESBoundObject* apObject) const;

#ifdef GAME
	int32_t GetCount(bool abCountNonPlayable) const;

	void InitScripts();

	void ResetCachedWeights();

	int32_t GetGoldAmount() const;

	uint32_t GetInventoryValue(bool abCountQuestItems, bool abCountGold) const;

	float GetInventoryWeight(bool abHardcore) const;

	float GetEquippedWeight(const Actor* apOwner) const;
	
	using IterateFunc = bool(*__cdecl)(ItemChange* apItemChange, void* apUserData);
	int32_t IterateInventory(IterateFunc apFunc, void* apUserData, uint32_t auiIterateFlags) const;

	bool GetNextItem(InventoryIterator& arIter, ItemChange*& arItem, uint8_t aucFindFlags);

	[[nodiscard]] FastInventoryIterator* StartFastInventoryIteration() const;
	[[nodiscard]] ClonedItemChange* GetNextFastInventoryItem(FastInventoryIterator* apIter) const;

	TESAmmo* GetAmmoForWeapon(const TESObjectWEAP* apWeapon, bool& arbHasAmmo) const;

	TESBoundObject* GetObjectByType(FORM_TYPE aeType, int32_t& ariCount) const;

	TESBoundObject* GetObjectByPackObjType(PACKAGE_OBJECT_TYPE aeType, int32_t& ariCount) const;

	bool HasObjectId(FormID auiFormID) const;

	bool HasQuestObject() const;
#endif

	bool HasScript() const;

	ExtraDataList* WearingObject(const TESBoundObject* apObject, bool abShouldWear);

#ifdef GAME
	bool WearingVoiceModulateItem() const;

	[[nodiscard]] ClonedItemChange* GetItemByIndex(int32_t aiIndex) const;

	[[nodiscard]] ClonedItemChange* GetInventoryItem(const TESBoundObject* apObject, FormID auiFormID) const;
#endif

	[[nodiscard]] ClonedItemChange* GetWornItem(BIPED_OBJECT aeBipedObject, bool abArmorOnly) const;

	[[nodiscard]] ClonedItemChange* GetBestWeapon(const TESActorBase* apActorBase, float& arfValue, COMBAT_WEAPON_TYPE aeType, bool abUseCanNotWear) const;

	[[nodiscard]] ClonedItemChange* GetBestAmmo(const TESActorBase* apActorBase, bool abUseCanNotWear) const;

	[[nodiscard]] ClonedItemChange* GetBestArmor(const TESActorBase* apActorBase, BIPED_OBJECT aeBipedObject, bool abUseCanNotWear) const;

#ifdef GAME
	[[nodiscard]] ClonedItemChange* GetBestFood() const;

	[[nodiscard]] ClonedItemChange* GetHotkeyItem(int32_t aiHotkey) const;
	void RemoveHotkeyItem(ItemChange* apItem, int32_t aiHotkey) const;
	void SetHotkeyItem(ItemChange* apItem, ExtraDataList* apExtra, int32_t aiHotkey) const;
#endif
};

ASSERT_SIZE(InventoryChanges, 0x14);