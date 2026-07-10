#include "TESActorBaseData.hpp"

// GAME - 0x47D680
int8_t TESActorBaseData::GetFactionRank(const TESFaction* apFaction, bool abCheckIfExpelled) const {
	return ThisCall<int32_t>(0x47D680, this, apFaction, abCheckIfExpelled);
}

// GAME - 0x5D8A70
const BSSimpleList<FactionRank*>* TESActorBaseData::GetFactionList() const {
	return &kFactions;
}

// GAME - 0x5D8A70
BSSimpleList<FactionRank*>* TESActorBaseData::GetFactionList() {
	return &kFactions;
}

// GAME - 0x47CDB0
bool TESActorBaseData::GetUsesLeveledTemplate() const {
	return ThisCall<bool>(0x47CDB0, this);
}

// GAME - 0x47E040
uint32_t TESActorBaseData::GetAlignmentForKarma(float afKarma) {
	return CdeclCall<uint32_t>(0x47E040, afKarma);
}

// GAME - 0x47E0E0
const char* TESActorBaseData::GetKarmicTitle(Actor* apActor) {
	return CdeclCall<const char*>(0x47E0E0, apActor);
}
