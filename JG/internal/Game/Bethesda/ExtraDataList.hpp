#pragma once

#include "BaseExtraList.hpp"
#include "BSSimpleList.hpp"
#include "BSStringT.hpp"

class AlchemyItem;
class TESActorBase;
class InventoryChanges;
class BGSEncounterZone;

class ExtraDataList : public BaseExtraList {
public:
	static ExtraDataList* Create();

	void CopyList(ExtraDataList* apCopy);

#ifdef GAME
	void CopyListForContainer(ExtraDataList* apCopy, bool abDontRemove);
#endif

	void CopyListForReference(ExtraDataList* apCopy, bool abRemove);

	void SetPoison(AlchemyItem* apPoison);
	void RemovePoison();

	TESActorBase* GetLevCreaTemplate() const;
	TESActorBase* GetLevCreaOriginalBase() const;

	bool GetIgnoredBySandbox() const;
	void SetIgnoredBySandbox(bool abVal);

	InventoryChanges* GetContainerChanges() const;
	void SetContainerChanges(InventoryChanges* apChanges);

	BSString GetActivateTextOverride() const;
	void SetActivateTextOverride(const char* apText);

	BGSEncounterZone* GetEncounterZone() const;
	void SetEncounterZone(BGSEncounterZone* apZone);

	float GetRadius() const;
	void SetRadius(float afRadius);
};

ASSERT_SIZE(ExtraDataList, 0x20);