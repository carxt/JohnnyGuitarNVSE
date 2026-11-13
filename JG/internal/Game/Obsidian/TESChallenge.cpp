#include "TESChallenge.hpp"

// GAME - 0x6A1B60
TESChallenge::Type TESChallenge::GetChallengeType() const {
    return kData.eType;
}

void TESChallenge::SetChallengeType(Type aeType) {
    kData.eType = aeType;
}

// GAME - 0x6286D0
int32_t TESChallenge::GetThreshold() const {
    return kData.iThreshold;
}

void TESChallenge::SetThreshold(int32_t aiVal) {
    kData.iThreshold = aiVal;
}

// GAME - 0x5F5930
bool TESChallenge::GetStartsLocked() const {
    return kData.uiFlags.bStartLocked;
}

void TESChallenge::SetStartsLocked(bool abVal) {
    kData.uiFlags.bStartLocked = abVal;
}

// GAME - 0x5F5F60
bool TESChallenge::GetRecurring() const {
    return kData.uiFlags.bRecurring;
}

void TESChallenge::SetRecurring(bool abVal) {
    kData.uiFlags.bRecurring = abVal;
}

// GAME - 0x79B800
bool TESChallenge::GetShowZeroProgress() const {
    return kData.uiFlags.bShowZeroProgress;
}

// GAME - 0x5F5020
void TESChallenge::SetShowZeroProgress(bool abVal) {
    kData.uiFlags.bShowZeroProgress = abVal;
}

// GAME - 0x5F5F80
int32_t TESChallenge::GetInterval() const {
    return kData.iInterval;
}

void TESChallenge::SetInterval(int32_t aiVal) {
    kData.iInterval = aiVal;
}

// GAME - 0x5F5FA0
uint32_t TESChallenge::GetSpecialA() const {
    return kData.usSpecialA;
}

void TESChallenge::SetSpecialA(uint16_t ausVal) {
    kData.usSpecialA = ausVal;
}

// GAME - 0x5F5FC0
uint32_t TESChallenge::GetSpecialB() const {
    return kData.usSpecialB;
}

void TESChallenge::SetSpecialB(uint16_t ausVal) {
    kData.usSpecialB = ausVal;
}

// GAME - 0x5F5FE0
uint32_t TESChallenge::GetSpecialC() const {
    return kData.usSpecialC;
}

void TESChallenge::SetSpecialC(uint16_t ausVal) {
    kData.usSpecialC = ausVal;
}

// GAME - 0x5E3FA0
int32_t TESChallenge::GetProgress() const {
    return kProgressData.iProgress;
}

// GAME - 0x5F60E0
void TESChallenge::IncrementProgress(int32_t aiVal) {
#ifdef GAME
    ThisCall(0x5F60E0, this, aiVal);
#else
    kProgressData.iProgress += aiVal;
#endif
}

// GAME - 0x5A60D0
int32_t TESChallenge::GetUnlocked() const {
    return kProgressData.uiFlags.bUnlocked;
}

// GAME - 0x5F6570
void TESChallenge::SetUnlocked(bool abVal) {
#ifdef GAME
    ThisCall(0x5F6570, this, abVal);
#else
    kProgressData.uiFlags.bUnlocked = abVal;
#endif
}

// GAME - 0x5A6150
int32_t TESChallenge::GetCompleted() const {
    return kProgressData.uiFlags.bCompleted;
}

// GAME - 0x5F6000
void TESChallenge::SetCompleted(bool abVal) {
#ifdef GAME
    ThisCall(0x5F6000, this, abVal);
#else
    kProgressData.uiFlags.bCompleted = abVal;
#endif
}

// GAME - 0x5DEF70
int32_t TESChallenge::GetCompletedRecurring() const {
    return kProgressData.uiFlags.bCompletedRecurring;
}

// GAME - 0x5F6000
void TESChallenge::SetCompletedRecurring(bool abVal) {
#ifdef GAME
    ThisCall(0x5F6060, this, abVal);
#else
    kProgressData.uiFlags.bCompletedRecurring = abVal;
#endif
}

// GAME - 0x5F60C0
int32_t TESChallenge::GetRemovedRecurring() const {
    return kProgressData.uiFlags.bRemovedRecurring;
}

// GAME - 0x5DEFE0
void TESChallenge::SetRemovedRecurring(bool abVal) {
#ifdef GAME
    ThisCall(0x5DEFE0, this, abVal);
#else
    kProgressData.uiFlags.bRemovedRecurring = abVal;
#endif
}

// GAME - 0x4FD3A0
TESForm* TESChallenge::GetFormA() const {
    return pFormA;
}

// GAME - 0x4FEBB0
void TESChallenge::SetFormA(TESForm* apForm) {
    pFormA = apForm;
}

// GAME - 0x407820
TESForm* TESChallenge::GetFormB() const {
    return pFormB;
}

// GAME - 0x442A80
void TESChallenge::SetFormB(TESForm* apForm) {
    pFormB = apForm;
}