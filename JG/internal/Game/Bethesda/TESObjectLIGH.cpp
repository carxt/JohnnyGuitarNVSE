#include "TESObjectLIGH.hpp"

// GAME - 0x50DD90
bool TESObjectLIGH::GetDynamic() const {
    return kData.uiFlags.bDynamic;
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

#if USE_MODDED_CHANGES
bool TESObjectLIGH::GetColorShift() const {
	return kData.uiFlags.bColorShift;
}

bool TESObjectLIGH::GetColorShiftSlow() const {
	return kData.uiFlags.bColorShiftSlow;
}
#endif