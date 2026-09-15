#include "TESObjectLIGH.hpp"

int32_t TESObjectLIGH::GetTime() const {
    return kData.iTime;
}

void TESObjectLIGH::SetTime(int32_t aiTime) {
    kData.iTime = aiTime;
}

// GAME - 0x4FD400
uint32_t TESObjectLIGH::GetRadius() const {
    return kData.uiRadius;
}

void TESObjectLIGH::SetRadius(uint32_t auiRadius) {
    kData.uiRadius = auiRadius;
}

float TESObjectLIGH::GetFalloffExponent() const {
    return kData.fFalloffExponent;
}

void TESObjectLIGH::SetFalloffExponent(float afExponent) {
    kData.fFalloffExponent = afExponent;
}

float TESObjectLIGH::GetFOV() const {
    return kData.fFOV;
}

void TESObjectLIGH::SetFOV(float afFOV) {
    kData.fFOV = afFOV;
}

// GAME - 0x50DD90
bool TESObjectLIGH::GetDynamic() const {
    return kData.uiFlags.bDynamic;
}

// GAME - 0x50DDB0
void TESObjectLIGH::SetDynamic(bool abVal) {
    kData.uiFlags.bDynamic;
}

// GAME - 0x46F070
bool TESObjectLIGH::GetCanCarry() const {
    return kData.uiFlags.bCanCarry;
}

bool TESObjectLIGH::GetNegative() const {
	return kData.uiFlags.bNegative;
}

// GAME - 0x50D1D0
bool TESObjectLIGH::GetFlicker() const {
	return kData.uiFlags.bFlicker;
}

bool TESObjectLIGH::GetDeepCopy() const {
	return kData.uiFlags.bDeepCopy;
}

// GAME - 0x46A060
bool TESObjectLIGH::GetOffByDefault() const {
	return kData.uiFlags.bOffByDefault;
}

// GAME - 0x50D1F0
bool TESObjectLIGH::GetFlickerSlow() const {
    return kData.uiFlags.bFlickerSlow;
}

// GAME - 0x50D210
bool TESObjectLIGH::GetPulse() const {
    return kData.uiFlags.bPulse;
}

// GAME - GetPulseSlow
bool TESObjectLIGH::GetPulseSlow() const {
    return kData.uiFlags.bPulseSlow;
}

bool TESObjectLIGH::GetSpotlight() const {
    return kData.uiFlags.bSpotlight;
}

bool TESObjectLIGH::GetSpotShadow() const {
    return kData.uiFlags.bSpotShadow;
}

#if USE_MODDED_CHANGES // JIP
bool TESObjectLIGH::GetColorShift() const {
	return kData.uiFlags.bColorShift;
}

bool TESObjectLIGH::GetColorShiftSlow() const {
	return kData.uiFlags.bColorShiftSlow;
}
#endif

// GAME - 0x6D2C40
float TESObjectLIGH::GetFade() const {
    return fFade;
}

// GAME - 0x6E5EE0
void TESObjectLIGH::SetFade(float afFade) {
    fFade = afFade;
}

// GAME - 0x4036B0
TESSound* TESObjectLIGH::GetSound() const {
    return pSound;
}

// GAME - 0x50C9E0
void TESObjectLIGH::SetSound(TESSound* apSound) {
    pSound = apSound;
}

// GAME - 0x50D810
// GECK - 0x5EDA80
NiLight* TESObjectLIGH::GenDynamic(TESObjectREFR* apRequester, NiNode* apScene, bool abForceDynamic) {
#ifdef GAME
    return ThisCall<NiLight*>(0x50D810, this, apRequester, apScene, abForceDynamic);
#else
    return ThisCall<NiLight*>(0x5EDA80, this, apRequester, apScene, abForceDynamic);
#endif
}
