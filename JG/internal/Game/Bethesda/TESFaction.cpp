#include "TESFaction.hpp"
#ifdef GAME
#include "BGSChangeFlags.hpp"
#endif

bool TESFaction::GetFlag(uint32_t auiFlag) const {
    return kData.uiFlags.Get(auiFlag);
}

// GAME - 0x5FC970
void TESFaction::SetFlag(uint32_t auiFlag, bool abVal) {
#ifdef GAME
    ThisCall(0x5FC970, this, auiFlag, abVal);
#else
    kData.uiFlags.Set(auiFlag, abVal);
#endif
}

// GAME - 0x47D7C0
bool TESFaction::GetIsEvil() const {
    return kData.uiFlags.bEvil;
}

void TESFaction::SetIsEvil(bool abVal) {
    SetFlag(FactionFlags::EVIL, abVal);
}

// GAME - 0x47D7E0
bool TESFaction::GetSpecialCombat() const {
    return kData.uiFlags.bSpecialCombat;
}

void TESFaction::SetSpecialCombat(bool abVal) {
    SetFlag(FactionFlags::SPECIAL_COMBAT, abVal);
}

// GAME - 0x47D720
bool TESFaction::GetPCExpelled() const {
    return kData.uiFlags.bPCExpelled;
}

// GAME - 0x5CE040
void TESFaction::SetPCExpelled(bool abVal) {
#ifdef GAME
    ThisCall(0x5CE040, this, abVal);
#else
    SetFlag(FactionFlags::PC_EXPELLED, abVal);
#endif
}

// GAME - 0x5A2270
bool TESFaction::GetPCAnEnemy() const {
    return kData.uiFlags.bPCAnEnemy;
}

// GAME - 0x47EB90
void TESFaction::SetPCAnEnemy(bool abVal) {
#ifdef GAME
    ThisCall(0x47EB90, this, abVal);
#else
    SetFlag(FactionFlags::PC_AN_ENEMY, abVal);
#endif
}

// GAME - 0x5A2310
bool TESFaction::GetPCAttacked() const {
    return kData.uiFlags.bPCAttacked;
}

// GAME - 0x47EBD0
void TESFaction::SetPCAttacked(bool abVal) {
#ifdef GAME
    ThisCall(0x47EBD0, this, abVal);
#else
    SetFlag(FactionFlags::PC_ATTACKED, abVal);
#endif
}

// GAME - 0x5A21D0
bool TESFaction::GetPCMurdered() const {
    return kData.uiFlags.bPCMurdered;
}

// GAME - 0x47EBB0
void TESFaction::SetPCMurdered(bool abVal) {
#ifdef GAME
    ThisCall(0x47EBB0, this, abVal);
#else
    SetFlag(FactionFlags::PC_MURDERED, abVal);
#endif
}

// GAME - 0x8B7D00
bool TESFaction::GetTrackCrime() const {
    return kData.uiFlags.bTrackCrime;
}

void TESFaction::SetTrackCrime(bool abVal) {
    SetFlag(FactionFlags::TRACK_CRIME, abVal);
}

// GAME - 0x578770
bool TESFaction::GetAllowSell() const {
    return kData.uiFlags.bAllowSell;
}

void TESFaction::SetAllowSell(bool abVal) {
    SetFlag(FactionFlags::ALLOW_SELL, abVal);
}

// GAME - 0x9E32D0
TESReputation* TESFaction::GetReputation() const {
    return pReputation;
}

// GAME - 0x40E500
void TESFaction::SetReputation(TESReputation* apReputation) {
    pReputation = apReputation;
}

// GAME - 0x6733E0
int32_t TESFaction::GetMinorCrime() const {
    return iMinorCrime;
}

void TESFaction::SetMinorCrime(int32_t aiCount) {
    iMinorCrime = aiCount;
#ifdef GAME
    AddChange(ChangeFlags::CHANGE_FACTION_CRIME_COUNTS);
#endif
}

// GAME - 0x8041A0
int32_t TESFaction::GetMajorCrime() const {
    return iMajorCrime;
}

void TESFaction::SetMajorCrime(int32_t aiCount) {
    iMajorCrime = aiCount;
#ifdef GAME
    AddChange(ChangeFlags::CHANGE_FACTION_CRIME_COUNTS);
#endif
}

#ifdef GAME
// GAME - 0x5FDA00
void TESFaction::AddMinorCrime(int32_t aiCount, bool abModRep) {
    ThisCall(0x5FDA00, this, aiCount, abModRep);
}

// GAME - 0x5FDA50
void TESFaction::AddMajorCrime(int32_t aiCount, bool abModRep) {
    ThisCall(0x5FDA50, this, aiCount, abModRep);
}

// GAME - 0x5FD3D0
void TESFaction::SetFactionReaction(TESFaction* apFaction, int32_t aiReaction) {
    ThisCall(0x5FD3D0, this, apFaction, aiReaction);
}

// GAME - 0x5FD400
void TESFaction::ModFactionReaction(TESFaction* apFaction, int32_t aiReaction) {
    ThisCall(0x5FD400, this, apFaction, aiReaction);
}
#endif

FIGHT_REACTION TESFaction::GetFactionFightReaction(TESFaction* apFaction) const {
    return GetFactionCombatRelation(apFaction);
}

#ifdef GAME
// GAME - 0x5FD430
void TESFaction::SetFactionFightReaction(TESFaction* apFaction, FIGHT_REACTION aeFightReaction) {
    ThisCall(0x5FD430, this, apFaction, aeFightReaction);
}
#endif