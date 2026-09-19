#pragma once

#include "BaseExtraList.hpp"
#include "BSSimpleList.hpp"
#include "BSStringT.hpp"

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

	void SetLock(LockData* apLock);
	LockData* GetLock() const;
};

ASSERT_SIZE(ExtraDataList, 0x20);