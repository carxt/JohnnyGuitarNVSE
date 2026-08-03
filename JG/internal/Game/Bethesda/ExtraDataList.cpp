#include "ExtraDataList.hpp"
#include "ExtraLeveledCreature.hpp"

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

// GAME - 0x42F2D0
bool ExtraDataList::GetIgnoredBySandbox() const {
#ifdef GAME
	return ThisCall<bool>(0x42F2D0, this);
#else
	return GetExtraData(EXTRA_DATA_TYPE::ExtraIgnoredBySandbox) != nullptr;
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

// GAME - 0x422320
// GECK - 0x4ABC90
float ExtraDataList::GetRadius() const {
#ifdef GAME
	return ThisCall<float>(0x422320, this);
#else
	return ThisCall<float>(0x4ABC90, this);
#endif
}

// GAME - 0x422220
// GECK - 0x4ABC10
void ExtraDataList::SetRadius(float afRadius) {
#ifdef GAME
	ThisCall(0x422220, this, afRadius);
#else
	ThisCall(0x4ABC10, this, afRadius);
#endif
}
