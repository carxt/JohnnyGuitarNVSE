#include "ExtraDataList.hpp"
#ifdef EDITOR
#include "ExtraLeveledCreature.hpp"
#include "ExtraActivateRef.hpp"
#include "ExtraActivateRefChildren.hpp"
#endif

ExtraDataList* ExtraDataList::Create() {
#ifdef GAME
	return BSMemory::create<ExtraDataList, 0x410360>();
#else
	return BSMemory::create<ExtraDataList, 0x4AC340>();
#endif
}

// GAME - 0x411EC0
// GECK - 0x4B1CB0
void ExtraDataList::CopyList(ExtraDataList* apCopy) {
#ifdef GAME
	ThisCall(0x411EC0, this, apCopy);
#else
	ThisCall(0x4B1CB0, this, apCopy);
#endif
}

#ifdef GAME
// GAME - 0x4121E0
void ExtraDataList::CopyListForContainer(ExtraDataList* apCopy, bool abDontRemove) {
	ThisCall(0x4121E0, this, apCopy, abDontRemove);
}
#endif

// GAME - 0x412490
// GECK - 0x4B1D10
void ExtraDataList::CopyListForReference(ExtraDataList* apCopy, bool abRemove) {
#ifdef GAME
	ThisCall(0x412490, this, apCopy, abRemove);
#else
	ThisCall(0x4B1D10, this, apCopy, abRemove);
#endif
}

// GAME - 0x4216F0
// GECK - 0x4AB720
TESActorBase* ExtraDataList::GetLevCreaOriginalBase() const {
#ifdef GAME
	return ThisCall<TESActorBase*>(0x4216F0, this);
#else
	return ThisCall<TESActorBase*>(0x4AB720, this);
#endif
}

// GAME - 0x421720
TESActorBase* ExtraDataList::GetLevCreaTemplate() const {
#ifdef GAME
	return ThisCall<TESActorBase*>(0x421720, this);
#else
	const ExtraLeveledCreature* pData = GetExtraData<ExtraLeveledCreature>();
	return pData ? pData->pTemplate : nullptr;
#endif
}

// GAME - 0x419D10
// GECK - 0x4AA130
void ExtraDataList::SetPoison(AlchemyItem* apPoison) {
#ifdef GAME
	ThisCall(0x419D10, this, apPoison);
#else
	ThisCall(0x4AA130, this, apPoison);
#endif
}

// GAME - 0x41AF30
void ExtraDataList::RemovePoison() {
#ifdef GAME
	ThisCall(0x41AF30, this);
#else
	RemoveExtra(EXTRA_DATA_TYPE::ExtraPoison);
#endif
}

// GAME - 0x421D20
// GECK - 0x4AB920
TESForm* ExtraDataList::GetEmittanceSource() const {
#ifdef GAME
	return ThisCall<TESForm*>(0x421D20, this);
#else
	return ThisCall<TESForm*>(0x4AB920, this);
#endif
}

// GAME - 0x421D50
// GECK - 0x4AB940
void ExtraDataList::SetEmittanceSource(TESForm* apSource) {
#ifdef GAME
	ThisCall(0x421D50, this, apSource);
#else
	ThisCall(0x4AB940, this, apSource);
#endif
}

// GAME - 0x421C30
// GECK - 0x4AB830
BGSEncounterZone* ExtraDataList::GetEncounterZone() const {
#ifdef GAME
	return ThisCall<BGSEncounterZone*>(0x421C30, this);
#else
	return ThisCall<BGSEncounterZone*>(0x4AB830, this);
#endif
}

// GAME - 0x421C60
// GECK - 0x4AB850
void ExtraDataList::SetEncounterZone(BGSEncounterZone* apEncounterZone) {
#ifdef GAME
	ThisCall(0x421C60, this, apEncounterZone);
#else
	ThisCall(0x4AB850, this, apEncounterZone);
#endif
}

// GAME - 0x41C160
// GECK - 0x4AA600
BGSAcousticSpace* ExtraDataList::GetAcousticSpace() const {
#ifdef GAME 
	return ThisCall<BGSAcousticSpace*>(0x41C160, this);
#else
	return ThisCall<BGSAcousticSpace*>(0x4AA600, this);
#endif
}

// GAME - 0x41C090
// GECK - 0x4AD6E0
void ExtraDataList::SetAcousticSpace(BGSAcousticSpace* apSpace) {
#ifdef GAME
	ThisCall(0x41C090, this, apSpace);
#else
	ThisCall(0x4AD6E0, this, apSpace);
#endif
}

// GAME - 0x41C260
// GECK - 0x4AA620
TESClimate* ExtraDataList::GetClimate() const {
#ifdef GAME 
	return ThisCall<TESClimate*>(0x41C260, this);
#else
	return ThisCall<TESClimate*>(0x4AA620, this);
#endif
}

// GAME - 0x41C190
// GECK - 0x4AD7C0
void ExtraDataList::SetClimate(TESClimate* apClimate) {
#ifdef GAME
	ThisCall(0x41C190, this, apClimate);
#else
	ThisCall(0x4AD7C0, this, apClimate);
#endif
}

// GAME - 0x41E130
// GECK - 0x4AACF0
TESWaterForm* ExtraDataList::GetWaterType() const {
#ifdef GAME 
	return ThisCall<TESWaterForm*>(0x41E130, this);
#else
	return ThisCall<TESWaterForm*>(0x4AACF0, this);
#endif
}

// GAME - 0x41E160
// GECK - 0x4AAD10
void ExtraDataList::SetWaterType(TESWaterForm* apWater) {
#ifdef GAME
	ThisCall(0x41E160, this, apWater);
#else
	ThisCall(0x4AAD10, this, apWater);
#endif
}

// GAME - 0x41C460
// GECK - 0x4AA640
ImpactSwap* ExtraDataList::GetImpactSwap() const {
#ifdef GAME 
	return ThisCall<ImpactSwap*>(0x41E130, this);
#else
	return ThisCall<ImpactSwap*>(0x4AA640, this);
#endif
}

// GAME - 0x41C390
// GECK - 0x4AD980
void ExtraDataList::SetImpactSwap(ImpactSwap* apSwap) {
#ifdef GAME
	ThisCall(0x41C390, this, apSwap);
#else
	ThisCall(0x4AD980, this, apSwap);
#endif
}

// GAME - 0x41BDE0
// GECK - 0x4AA5D0
BGSMusicType* ExtraDataList::GetMusicType() const {
#ifdef GAME 
	return ThisCall<BGSMusicType*>(0x41BDE0, this);
#else
	return ThisCall<BGSMusicType*>(0x4AA5D0, this);
#endif
}

// GAME - 0x41BD10
// GECK - 0x4AD600
void ExtraDataList::SetMusicType(BGSMusicType* aeType) {
#ifdef GAME
	ThisCall(0x41BD10, this, aeType);
#else
	ThisCall(0x4AD600, this, aeType);
#endif
}

// GAME - 0x418690
// GECK - 0x4A9B20
TESGlobal* ExtraDataList::GetGlobal() const {
#ifdef GAME 
	return ThisCall<TESGlobal*>(0x418690, this);
#else
	return ThisCall<TESGlobal*>(0x4A9B20, this);
#endif
}

// GAME - 0x4197D0
// GECK - 0x4ACA70
void ExtraDataList::SetGlobal(TESGlobal* apGlobal) {
#ifdef GAME
	ThisCall(0x4197D0, this, apGlobal);
#else
	ThisCall(0x4ACA70, this, apGlobal);
#endif
}

// GAME - 0x4186C0
// GECK - 0x4A9B40
int32_t ExtraDataList::GetRank() const {
#ifdef GAME 
	return ThisCall<int32_t>(0x4186C0, this);
#else
	return ThisCall<int32_t>(0x4A9B40, this);
#endif
}

// GAME - 0x4198A0
// GECK - 0x4ACB30
void ExtraDataList::SetRank(int32_t aiRank) {
#ifdef GAME
	ThisCall(0x4198A0, this, aiRank);
#else
	ThisCall(0x4ACB30, this, aiRank);
#endif
}

// GAME - 0x418660
// GECK - 0x4A9B00
TESForm* ExtraDataList::GetOwner() const {
#ifdef GAME 
	return ThisCall<TESForm*>(0x418660, this);
#else
	return ThisCall<TESForm*>(0x4A9B00, this);
#endif
}

// GAME - 0x419700
// GECK - 0x4AC9B0
void ExtraDataList::SetOwnership(TESForm* apOwner) {
#ifdef GAME
	ThisCall(0x419700, this, apOwner);
#else
	ThisCall(0x4AC9B0, this, apOwner);
#endif
}

// GAME - 0x41C360
// GECK - 0x4AA630
TESImageSpace* ExtraDataList::GetImageSpace() const {
#ifdef GAME 
	return ThisCall<TESImageSpace*>(0x41C360, this);
#else
	return ThisCall<TESImageSpace*>(0x4AA630, this);
#endif
}

// GAME - 0x41C290
// GECK - 0x4AD8A0
void ExtraDataList::SetImageSpace(TESImageSpace* apImageSpace) {
#ifdef GAME
	ThisCall(0x41C290, this, apImageSpace);
#else
	ThisCall(0x4AD8A0, this, apImageSpace);
#endif
}

// GAME - 0x42F2D0
// GECK - 0x4ABF90
bool ExtraDataList::GetIgnoredBySandbox() const {
#ifdef GAME
	return ThisCall<bool>(0x42F2D0, this);
#else
	return ThisCall<bool>(0x4ABF90, this);
#endif
}

// GAME - 0x42F200
// GECK - 0x4AE8C0
void ExtraDataList::SetIgnoredBySandbox(bool abIgnored) {
#ifdef GAME
	ThisCall(0x42F200, this, abIgnored);
#else
	ThisCall(0x4AE8C0, this, abIgnored);
#endif
}

// GAME - 0x418520
// GECK - 0x4A9A60
InventoryChanges* ExtraDataList::GetContainerChanges() const {
#ifdef GAME
	return ThisCall<InventoryChanges*>(0x418520, this);
#else
	return ThisCall<InventoryChanges*>(0x4A9A60, this);
#endif
}

// GAME - 0x419650
// GECK - 0x4A9E20
void ExtraDataList::SetContainerChanges(InventoryChanges* apChanges) {
#ifdef GAME
	ThisCall(0x419650, this, apChanges);
#else
	ThisCall(0x4A9E20, this, apChanges);
#endif
}

// GAME - 0x4182B0
// GECK - 0x4A9910
LockData* ExtraDataList::GetLock() const {
#ifdef GAME
	return ThisCall<LockData*>(0x4182B0, this);
#else
	return ThisCall<LockData*>(0x4A9910, this);
#endif
}

// GAME - 0x419050
// GECK - 0x4A9D20
void ExtraDataList::SetLock(LockData* apLock) {
#ifdef GAME
	ThisCall(0x419050, this, apLock);
#else
	ThisCall(0x4A9D20, this, apLock);
#endif
}

// GAME - 0x41E7B0
// GECK - 0x4AB0A0
RefActivateData* ExtraDataList::GetActivateData(TESObjectREFR* apRef) const {
#ifdef GAME
	return ThisCall<RefActivateData*>(0x41E7B0, this, apRef);
#else
	return ThisCall<RefActivateData*>(0x4AB0A0, this, apRef);
#endif
}

// GAME - 0x41E9E0
float ExtraDataList::GetActivateDelay(TESObjectREFR* apRef) const {
#ifdef GAME
	return ThisCall<float>(0x41E9E0, this, apRef);
#else
	const ExtraActivateRef* pData = GetExtraData<ExtraActivateRef>();
	if (pData) {
		const RefActivateData* pActivateData = pData->GetData(apRef);
		if (pActivateData)
			return pActivateData->fActivateDelay;
	}
	return 0.f;
#endif
}

// GAME - 0x41EA30
// GECK - 0x4AEE50
void ExtraDataList::SetActivateDelay(TESObjectREFR* apRef, float afDelay) {
#ifdef GAME
	ThisCall(0x41EA30, this, apRef, afDelay);
#else
	ThisCall(0x4AEE50, this, apRef, afDelay);
#endif
}

// GAME - 0x41EC80
// GECK - 0x4B0900
BSString ExtraDataList::GetActivateTextOverride() const {
#ifdef GAME
	return ThisCall<BSString>(0x41EC80, this);
#else
	return ThisCall<BSString>(0x4B0900, this);
#endif
}

// GAME - 0x41ECE0
// GECK - 0x4AEF30
void ExtraDataList::SetActivateTextOverride(const char* apText) {
#ifdef GAME
	ThisCall(0x41ECE0, this, apText);
#else
	ThisCall(0x4AEF30, this, apText);
#endif
}

// GAME - 0x41E780
// GECK - 0x4AB080
BSSimpleList<RefActivateData*>* ExtraDataList::GetActivateParentList() const {
#ifdef GAME
	return ThisCall<BSSimpleList<RefActivateData*>*>(0x41E780, this);
#else
	return ThisCall<BSSimpleList<RefActivateData*>*>(0x4AB080, this);
#endif
}

// GAME - 0x41E7F0
// GECK - 0x4AED40
void ExtraDataList::AddActivateParent(TESObjectREFR* apRef) {
#ifdef GAME
	ThisCall(0x41E7F0, this, apRef);
#else
	ThisCall(0x4AED40, this, apRef);
#endif
}

// GAME - 0x41E960
// GECK - 0x4B08A0
void ExtraDataList::RemoveActivateParent(TESObjectREFR* apRef) {
#ifdef GAME
	ThisCall(0x41E960, this, apRef);
#else
	ThisCall(0x4B08A0, this, apRef);
#endif
}

// GAME - 0x41EDA0
// GECK - 0x4AB190
BSSimpleList<RefActivateData*>* ExtraDataList::GetActivateRefChildren() const {
#ifdef GAME
	return ThisCall<BSSimpleList<RefActivateData*>*>(0x41EDA0, this);
#else
	return ThisCall<BSSimpleList<RefActivateData*>*>(0x4AB190, this);
#endif
}

// GAME - 0x41EDD0
// GECK - 0x4AEFD0
void ExtraDataList::AddActivateRefChild(TESObjectREFR* apRef) {
#ifdef GAME
	ThisCall(0x41EDD0, this, apRef);
#else
	ThisCall(0x4AEFD0, this, apRef);
#endif
}

// GAME - 0x41EF20
// GECK - 0x4B0950
void ExtraDataList::RemoveActivateRefChild(TESObjectREFR* apRef) {
#ifdef GAME
	ThisCall(0x41EF20, this, apRef);
#else
	ThisCall(0x4B0950, this, apRef);
#endif
}

// GAME - 0x41F020
float ExtraDataList::GetActivateChildrenTimer() const {
#ifdef GAME
	return ThisCall<float>(0x41F020, this);
#else
	const ExtraActivateRefChildren* pData = GetExtraData<ExtraActivateRefChildren>();
	return pData ? pData->fActivateTimer : -1.f;
#endif
}

// GAME - 0x41EFF0
void ExtraDataList::SetActivateChildrenTimer(float afTimer) {
#ifdef GAME
	ThisCall(0x41EFF0, this, afTimer);
#else
	ExtraActivateRefChildren* pData = GetExtraData<ExtraActivateRefChildren>();
	if (pData)
		pData->fActivateTimer = afTimer;
#endif
}

#ifdef GAME
// GAME - 0x418A40
BSSoundHandle ExtraDataList::GetActivateLoopSound() const {
	return ThisCall<BSSoundHandle>(0x418A40, this);
}

// GAME - 0x41A6A0
void ExtraDataList::SetActivateLoopSound(BSSoundHandle& arSound) {
	ThisCall(0x41A6A0, this, &arSound);
}
#endif

// GAME - 0x41DA10
// GECK - 0x4AAB00
TESObjectREFR* ExtraDataList::GetEnableStateParent() const {
#ifdef GAME
	return ThisCall<TESObjectREFR*>(0x41DA10, this);
#else
	return ThisCall<TESObjectREFR*>(0x4AAB00, this);
#endif
}

// GAME - 0x41DA40
// GECK - 0x4AAB20
void ExtraDataList::SetEnableStateParent(TESObjectREFR* apRef) {
#ifdef GAME
	ThisCall(0x41DA40, this, apRef);
#else
	ThisCall(0x4AAB20, this, apRef);
#endif
}

// GAME - 0x41DB00
// GECK - 0x4AABF0
bool ExtraDataList::IsEnableStateInverse() const {
#ifdef GAME
	return ThisCall<bool>(0x41DB00, this);
#else
	return ThisCall<bool>(0x4AABF0, this);
#endif
}

// GAME - 0x41DC70
// GECK - 0x4AACB0
void ExtraDataList::SetEnableStateParentFlags(uint8_t aucFlags) {
#ifdef GAME
	ThisCall(0x41DC70, this, aucFlags);
#else
	ThisCall(0x4AACB0, this, aucFlags);
#endif
}

// GAME - 0x41DCA0
// GECK - 0x4AACD0
BSSimpleList<TESObjectREFR*>* ExtraDataList::GetEnableStateChildren() const {
#ifdef GAME
	return ThisCall<BSSimpleList<TESObjectREFR*>*>(0x41DCA0, this);
#else
	return ThisCall<BSSimpleList<TESObjectREFR*>*>(0x4AACD0, this);
#endif
}

// GAME - 0x41DCD0
// GECK - 0x4AEBE0
void ExtraDataList::AddEnableStateChild(TESObjectREFR* apRef) {
#ifdef GAME
	ThisCall(0x41DCD0, this, apRef);
#else
	ThisCall(0x4AEBE0, this, apRef);
#endif
}

// GAME - 0x41DDA0
// GECK - 0x4B0800
void ExtraDataList::RemoveEnableStateChild(TESObjectREFR* apRef) {
#ifdef GAME
	ThisCall(0x41DDA0, this, apRef);
#else
	ThisCall(0x4B0800, this, apRef);
#endif
}
