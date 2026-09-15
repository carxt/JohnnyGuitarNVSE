#include "BGSPerk.hpp"
#include "BGSPerkEntry.hpp"

// GAME - 0x5D4EE0
uint8_t BGSPerk::GetNumRanks() const {
	return kData.ucNumRanks;
}

// GAME - 0x6AABF0
int8_t BGSPerk::GetLevel() const {
	return kData.cLevel;
}

// GAME - 0x7A9280
bool BGSPerk::GetIsTrait() const {
	return kData.bTrait;
}

// GAME - 0x5EB5E0
bool BGSPerk::GetIsPlayable() const {
#ifdef GAME
    return ThisCall<bool>(0x5EB5E0, this);
#else
	return kData.bPlayable;
#endif
}

// GAME - 0x7DD8A0
bool BGSPerk::IsPerkHidden() const {
	return kData.bHidden;
}

#ifdef GAME
// GAME - 0x785150
bool BGSPerk::IsPerkAvailable(TESObjectREFR* apActionRef) const {
	return ThisCall<bool>(0x785150, this, apActionRef);
}

// GAME - 0x5EBA00
bool BGSPerk::IsPerkAttainable(TESObjectREFR* apActionRef) const {
	return ThisCall<bool>(0x5EBA00, this, apActionRef);
}

// GAME - 0x5EB900
BGSPerkEntry* BGSPerk::GetPerkEntryByRank(uint8_t aucRank) const {
	return ThisCall<BGSPerkEntry*>(0x5EB900, this, aucRank);
}
#endif

// GAME - 0x5EB410
// GECK - 0x5507F0
bool BGSPerk::AddPerkEntry(BGSPerkEntry* apEntry) {
#ifdef GAME
	return ThisCall<bool>(0x5EB410, this, apEntry);
#else
	return ThisCall<bool>(0x5507F0, this, apEntry);
#endif
}

// GECK - 0x550E30
void BGSPerk::RemovePerkEntry(BGSPerkEntry* apEntry) {
#ifdef GAME
	kPerkEntries.Remove(apEntry);
	delete apEntry;
#else
	ThisCall(0x550E30, this, apEntry);
#endif
}

#ifdef GAME
// GAME - 0x5EB980
void BGSPerk::AddPerkEntryPoints(Actor* apActor, uint8_t aucRank, bool abAlt) {
	ThisCall(0x5EB980, this, apActor, aucRank, abAlt);
}

// GAME - 0x5EB6A0
void BGSPerk::ApplyPerk(Actor* apActor, uint8_t aucOldRank, uint8_t aucNewRank, bool abAlt) {
	ThisCall(0x5EB6A0, this, apActor, aucOldRank, aucNewRank, abAlt);
}

// GAME - 0x5EB800
void BGSPerk::RemovePerk(Actor* apActor, bool abAlt) {
	ThisCall(0x5EB800, this, apActor, abAlt);
}

// GAME - 0x5EBAC0
void BGSPerk::BuildDescriptionString(char* apBuffer, uint32_t auiBufferSize) {
	ThisCall(0x5EBAC0, this, apBuffer, auiBufferSize);
}
#endif