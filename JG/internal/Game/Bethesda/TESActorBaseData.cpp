#include "TESActorBaseData.hpp"
#ifdef EDITOR
#include "TESFaction.hpp"
#endif

// GAME - 0x47DD30
// GECK - 0x4EA630
void TESActorBaseData::SetFlags(uint32_t auiFlags) {
#ifdef GAME
	ThisCall(0x47DD30, this, auiFlags);
#else
	ThisCall(0x4EA630, this, auiFlags);
#endif
}

// GAME - 0x461580
bool TESActorBaseData::GetFlag(ActorBaseFlags aeFlag) const {
	return kActorData.uiFlags.Get(aeFlag);
}

// GAME - 0x47DD50
// GECK - 0x4EA640
void TESActorBaseData::SetFlag(ActorBaseFlags aeFlag, bool abVal, bool abAddChange) {
#ifdef GAME
	ThisCall(0x47DD50, this, aeFlag, abVal, abAddChange);
#else
	ThisCall(0x4EA640, this, aeFlag, abVal, abAddChange);
#endif
}


// GAME - 0x87F480
bool TESActorBaseData::GetEssential() const {
#ifdef GAME
	return ThisCall<bool>(0x87F480, this);
#else
	return GetFlag(ActorBaseFlags::ESSENTIAL);
#endif
}

// GAME - 0x5CD8F0
void TESActorBaseData::SetEssential(bool abVal) {
#ifdef GAME
	ThisCall(0x5CD8F0, this, abVal);
#else
	SetFlag(ActorBaseFlags::ESSENTIAL, abVal, true);
#endif
}

// GAME - 0x56AF00
bool TESActorBaseData::GetRespawn() const {
#ifdef GAME
	return ThisCall<bool>(0x56AF00, this);
#else
	return GetFlag(ActorBaseFlags::RESPAWN);
#endif
}

// GAME - 0x461560
bool TESActorBaseData::GetMatchesPCLevel() const {
#ifdef GAME
	return ThisCall<bool>(0x461560, this);
#else
	return GetFlag(ActorBaseFlags::PC_LEVEL_MULT);
#endif
}

// GAME - 0x5D1070
void TESActorBaseData::SetMatchesPCLevel(bool abVal) {
#ifdef GAME
	ThisCall(0x5D1070, this, abVal);
#else
	SetFlag(ActorBaseFlags::ESSENTIAL, abVal, true);
#endif
}

// GAME - 0x55E200
bool TESActorBaseData::GetRunsInLow() const {
#ifdef GAME
	return ThisCall<bool>(0x55E200, this);
#else
	return !GetFlag(ActorBaseFlags::NO_LOWLEVEL_PROCESSING);
#endif
}

// GAME - 0x5F7B50
void TESActorBaseData::SetRunsInLow(bool abVal, bool abAddChange) {
#ifdef GAME
	ThisCall(0x5D1070, this, abVal);
#else
	SetFlag(ActorBaseFlags::NO_LOWLEVEL_PROCESSING, !abVal, abAddChange);
#endif
}

// GAME - 0x5D2780
bool TESActorBaseData::GetNoRumors() const {
#ifdef GAME
	return ThisCall<bool>(0x5D2780, this);
#else
	return GetFlag(ActorBaseFlags::NO_RUMORS);
#endif
}

// GAME - 0x884690
bool TESActorBaseData::GetKnockedDowns() const {
#ifdef GAME
	return ThisCall<bool>(0x884690, this);
#else
	return !GetFlag(ActorBaseFlags::NO_KNOCKDOWNS);
#endif
}

// GAME - 0x89D5E0
bool TESActorBaseData::GetNotPushable() const {
#ifdef GAME
	return ThisCall<bool>(0x89D5E0, this);
#else
	return GetFlag(ActorBaseFlags::NOT_PUSHABLE);
#endif
}

// GAME - 0x8A46A0
bool TESActorBaseData::GetNoRotatingToHeadtrack() const {
#ifdef GAME
	return ThisCall<bool>(0x8A46A0, this);
#else
	return GetFlag(ActorBaseFlags::NO_ROTATE_TO_HEADTRACK);
#endif
}

// GAME - 0x47E010
// GECK - 0x4EA750
void TESActorBaseData::SetFatigue(uint16_t ausVal) {
#ifdef GAME
	ThisCall(0x47E010, this, ausVal);
#else
	ThisCall(0x4EA750, this, ausVal);
#endif
}

// GAME - 0x47D3F0
uint16_t TESActorBaseData::GetBarterGold() const {
	return kActorData.usBarterGold;
}

// GAME - 0x47E240
// GECK - 0x4EA800
void TESActorBaseData::SetBarterGold(uint16_t ausVal) {
#ifdef GAME
	ThisCall(0x47E240, this, ausVal);
#else
	ThisCall(0x4EA800, this, ausVal);
#endif
}

// GAME - 0x47D370
uint16_t TESActorBaseData::GetLevelExact() const {
	return kActorData.usLevel;
}

// GAME - 0x47DFE0
// GECK - 0x4EA740
void TESActorBaseData::SetLevel(uint16_t ausVal) {
#ifdef GAME
	ThisCall(0x47DFE0, this, ausVal);
#else
	ThisCall(0x4EA740, this, ausVal);
#endif
}

// GAME - 0x47D390
uint16_t TESActorBaseData::GetCalcLevelMin() const {
	return kActorData.usCalcLevelMin;
}

// GAME - 0x47DE40
// GECK - 0x4EA660
void TESActorBaseData::SetCalcLevelMin(uint16_t ausVal) {
#ifdef GAME
	ThisCall(0x47DE40, this, ausVal);
#else
	ThisCall(0x4EA660, this, ausVal);
#endif
}

// GAME - 0x47D3B0
uint16_t TESActorBaseData::GetCalcLevelMax() const {
	return kActorData.usCalcLevelMax;
}

// GAME - 0x47DE70
// GECK - 0x4EA670
void TESActorBaseData::SetCalcLevelMax(uint16_t ausVal) {
#ifdef GAME
	ThisCall(0x47DE70, this, ausVal);
#else
	ThisCall(0x4EA670, this, ausVal);
#endif
}

// GAME - 0x8F21D0
uint16_t TESActorBaseData::GetSpeedMult() const {
	return kActorData.usSpeedMultiplier;
}

// GAME - 0x47E270
// GECK - 0x4EA810
void TESActorBaseData::SetSpeedMult(uint16_t ausVal) {
#ifdef GAME
	ThisCall(0x47E270, this, ausVal);
#else
	ThisCall(0x4EA810, this, ausVal);
#endif
}

// GAME - 0x47D3D0
uint16_t TESActorBaseData::GetBaseDisposition() const {
	return kActorData.usBaseDisposition;
}

// GAME - 0x47DEA0
// GECK - 0x4EA680
void TESActorBaseData::SetBaseDisposition(uint16_t ausVal) {
#ifdef GAME
	ThisCall(0x47DEA0, this, ausVal);
#else
	ThisCall(0x4EA680, this, ausVal);
#endif
}

// GAME - 0x47E1C0
// GECK - 0x4EA7C0
void TESActorBaseData::SetKarma(float afVal) {
#ifdef GAME
	ThisCall(0x47E1C0, this, afVal);
#else
	ThisCall(0x4EA7C0, this, afVal);
#endif
}

// GAME - 0x441110
TESLevItem* TESActorBaseData::GetDeathItem() const {
	return pDeathItem;
}

// GAME - 0x50F9A0
void TESActorBaseData::SetDeathItem(TESLevItem* apItem) {
	pDeathItem = apItem;
}

// GAME - 0x50F9C0
void TESActorBaseData::SetVoiceType(BGSVoiceType* apVoice) {
	pVoiceType = apVoice;
}

// GAME - 0x59BB30
// GECK - 0xBF67B0
TESForm* TESActorBaseData::GetTemplateForm() const {
	return pTemplateForm;
}

// GAME - 0x7037C0
void TESActorBaseData::SetTemplateForm(TESForm* apTemplate) {
	pTemplateForm = apTemplate;
}

#ifdef GAME
// GAME- 0x45CD60
uint32_t TESActorBaseData::GetChangeFlags() const {
	return uiChangeFlags;
}
#endif

// GAME - 0x5D8A70
const BSSimpleList<FactionRank*>* TESActorBaseData::GetFactionList() const {
	return &kFactions;
}

// GAME - 0x5D8A70
BSSimpleList<FactionRank*>* TESActorBaseData::GetFactionList() {
	return &kFactions;
}

// GAME - 0x47EBF0
bool TESActorBaseData::IsInFaction(const TESFaction* apFaction) const {
#ifdef GAME
	return ThisCall<bool>(0x47EBF0, this, apFaction);
#else
	auto pIter = GetFactionList();
	while (pIter) {
		const FactionRank* pRank = pIter->GetItem();
		if (pRank && pRank->pFaction == apFaction)
			return true;

		pIter = pIter->GetNext();
	}
	return false;
#endif
}

// GAME - 0x47D740
bool TESActorBaseData::IsInEvilFactionsOnly() const {
#ifdef GAME
	return ThisCall<bool>(0x47D740, this);
#else
	auto pIter = GetFactionList();
	bool bIsEvil = !pIter->IsEmpty();
	while (pIter && bIsEvil) {
		const FactionRank* pRank = pIter->GetItem();
		if (pRank && !pRank->pFaction->GetIsEvil())
			bIsEvil = false;

		pIter = pIter->GetNext();
	}
	return bIsEvil;
#endif
}

// GAME - 0x47D680
// GECK - 0x4EAF70
int32_t TESActorBaseData::GetFactionRank(const TESFaction* apFaction, bool abPlayer) const {
#ifdef GAME
	return ThisCall<int32_t>(0x47D680, this, apFaction, abPlayer);
#else
	return ThisCall<int32_t>(0x4EAF70, this, apFaction, abPlayer);
#endif
}

// GAME - 0x47DED0
// GAME - 0x4EA690
uint16_t TESActorBaseData::GetLevel() const {
#ifdef GAME
	return ThisCall<uint16_t>(0x47DED0, this);
#else
	return ThisCall<uint16_t>(0x4EA690, this);
#endif
}

// GAME - 0x47CDB0
// GECK - 0x4EAF20
bool TESActorBaseData::GetUsesLeveledTemplate() const {
#ifdef GAME
	return ThisCall<bool>(0x47CDB0, this);
#else
	return ThisCall<bool>(0x4EAF20, this);
#endif
}

// GAME - 0x47D1A0
// GECK - 0x4EA5E0
TESActorBase* TESActorBaseData::GetLeveledTemplateInHierarchy(TESActorBase* apBase, uint16_t& arFlags) {
#ifdef GAME
	return CdeclCall<TESActorBase*>(0x47D1A0, apBase, &arFlags);
#else
	return CdeclCall<TESActorBase*>(0x4EA5E0, apBase, &arFlags);
#endif
}

// GAME - 0x47E040
// GECK - 0x4EA760
uint32_t TESActorBaseData::GetAlignmentForKarma(float afKarma) {
#ifdef GAME
	return CdeclCall<uint32_t>(0x47E040, afKarma);
#else
	return CdeclCall<uint32_t>(0x4EA760, afKarma);
#endif
}

#ifdef GAME
// GAME - 0x47E0E0
const char* TESActorBaseData::GetKarmicTitle(Actor* apActor) {
	return CdeclCall<const char*>(0x47E0E0, apActor);
}
#endif
