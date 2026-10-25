#pragma once

#include "BaseExtraList.hpp"
#include "BSSimpleList.hpp"
#include "BSStringT.hpp"
#include "BSSoundHandle.hpp"

class AlchemyItem;
class TESForm;
class BGSEncounterZone;
class BGSAcousticSpace;
class TESClimate;
class TESWaterForm;
class ImpactSwap;
class BGSMusicType;
class TESGlobal;
class TESImageSpace;
class TESActorBase;
class InventoryChanges;
class LockData;
class TESObjectREFR;
class RefActivateData;

class ExtraDataList : public BaseExtraList {
public:
	static ExtraDataList* Create();

	void CopyList(ExtraDataList* apCopy);

#ifdef GAME
	void CopyListForContainer(ExtraDataList* apCopy, bool abDontRemove);
#endif

	void CopyListForReference(ExtraDataList* apCopy, bool abRemove);

	TESActorBase* GetLevCreaTemplate() const;
	TESActorBase* GetLevCreaOriginalBase() const;

	void SetPoison(AlchemyItem* apPoison);
	void RemovePoison();

	TESForm* GetEmittanceSource() const;
	void SetEmittanceSource(TESForm* apSource);

	BGSEncounterZone* GetEncounterZone() const;
	void SetEncounterZone(BGSEncounterZone* apZone);

	BGSAcousticSpace* GetAcousticSpace() const;
	void SetAcousticSpace(BGSAcousticSpace* apSpace);

	TESClimate* GetClimate() const;
	void SetClimate(TESClimate* apClimate);

	TESWaterForm* GetWaterType() const;
	void SetWaterType(TESWaterForm* apWater);

	ImpactSwap* GetImpactSwap() const;
	void SetImpactSwap(ImpactSwap* apSwap);

	BGSMusicType* GetMusicType() const;
	void SetMusicType(BGSMusicType* aeType);

	TESGlobal* GetGlobal() const;
	void SetGlobal(TESGlobal* apGlobal);

	int32_t GetRank() const;
	void SetRank(int32_t aiRank);

	TESForm* GetOwner() const;
	void SetOwnership(TESForm* apOwner);

	TESImageSpace* GetImageSpace() const;
	void SetImageSpace(TESImageSpace* apImageSpace);

	bool GetIgnoredBySandbox() const;
	void SetIgnoredBySandbox(bool abVal);

	InventoryChanges* GetContainerChanges() const;
	void SetContainerChanges(InventoryChanges* apChanges);

	LockData* GetLock() const;
	void SetLock(LockData* apLock);

	RefActivateData* GetActivateData(TESObjectREFR* apRef) const;

	float GetActivateDelay(TESObjectREFR* apRef) const;
	void SetActivateDelay(TESObjectREFR* apRef, float afDelay);

	BSString GetActivateTextOverride() const;
	void SetActivateTextOverride(const char* apText);

	BSSimpleList<RefActivateData*>* GetActivateParentList() const;
	void AddActivateParent(TESObjectREFR* apRef);
	void RemoveActivateParent(TESObjectREFR* apRef);

	BSSimpleList<RefActivateData*>* GetActivateRefChildren() const;
	void AddActivateRefChild(TESObjectREFR* apRef);
	void RemoveActivateRefChild(TESObjectREFR* apRef);

	float GetActivateChildrenTimer() const;
	void SetActivateChildrenTimer(float afTimer);

#ifdef GAME
	BSSoundHandle GetActivateLoopSound() const;
	void SetActivateLoopSound(BSSoundHandle& arSound);
#endif

	TESObjectREFR* GetEnableStateParent() const;
	void SetEnableStateParent(TESObjectREFR* apRef);

	bool IsEnableStateInverse() const;
	void SetEnableStateParentFlags(uint8_t aucFlags);

	BSSimpleList<TESObjectREFR*>* GetEnableStateChildren() const;
	void AddEnableStateChild(TESObjectREFR* apRef);
	void RemoveEnableStateChild(TESObjectREFR* apRef);

	float GetRadius() const;
	void SetRadius(float afRadius);
};

ASSERT_SIZE(ExtraDataList, 0x20);