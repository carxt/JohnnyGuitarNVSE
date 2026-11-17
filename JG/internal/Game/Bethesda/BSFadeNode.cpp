#include "BSFadeNode.hpp"

#ifdef EDITOR
constexpr inline AddressPtr<bool, 0xEB874C> bFadeEnabled;
constexpr inline AddressPtr<float, 0xEB8750, LOD_MULT_TYPE::COUNT> fFadeOutMultipliers;
#endif

// GAME - 0xB4DFD0
// GECK - 0x8F6FF0
void BSFadeNode::SetRange(float afNearDist, float afFarDist) {
#ifdef GAME
    ThisCall(0xB4DFD0, this, afNearDist, afFarDist);
#else
    ThisCall(0x8F6FF0, this, afNearDist, afFarDist);
#endif
}

// GAME - 0x6D2C20
float BSFadeNode::GetFarDistanceSqr() const {
    return fFarDistSqr;
}

// GAME - 0x6D2C40
float BSFadeNode::GetLastFadePercent() const {
    return fLastFadePct;
}

// GAME - 0x99E040
float BSFadeNode::GetBoundRadius() const {
    return fBoundRadius;
}

// GAME - 0x7058C0
LOD_MULT_TYPE BSFadeNode::GetLODMultType() const {
    return eLODMultType;
}

// GAME - 0xB4DEC0
// GECK - 0x8F6F40
void BSFadeNode::SetLODMultType(LOD_MULT_TYPE aeType) {
	eLODMultType = aeType;
}

// GAME - 0x9AD610
TESObjectREFR* BSFadeNode::GetReference() const {
    return pReference;
}

// GAME - 0x56C7D0
void BSFadeNode::SetReference(TESObjectREFR* apRef) {
    pReference = apRef;
}

// GAME - 0xB4DF80
// GECK - 0x8F6FC0
float BSFadeNode::GetMaxAlpha() {
#ifdef GAME
	return ThisCall<float>(0xB4DF80, this);
#else
    return ThisCall<float>(0x8F6FC0, this);
#endif
}

// GAME - 0x5AA8C0
bool BSFadeNode::IsVisible() const {
#ifdef GAME
    return ThisCall<bool>(0x5AA8C0, this);
#else
    return GetIgnoreFade() || !bFadeEnabled || fCurrentFade > 0.f;
#endif
}

// GAME - 0x476AB0
void BSFadeNode::TurnFadeNodeOn() {
#ifdef GAME
    ThisCall(0x476AB0, this);
#else
    fCurrentFade = 1.f;
    fLastFadePct = 1.f;
    SetFadedIn(true);
#endif
}

// GAME - 0x54B800
void BSFadeNode::TurnFadeNodeOff() {
#ifdef GAME
    ThisCall(0x54B800, this);
#else
    fCurrentFade = 0.f;
    fLastFadePct = 0.f;
    SetFadedIn(false);
#endif
}

// GAME - 0x7D1D00
float BSFadeNode::GetFadeOutMultiplier(LOD_MULT_TYPE aeType) {
#ifdef GAME
    return CdeclCall<float>(0x7D1D00, aeType);
#else
    return fFadeOutMultipliers[aeType];
#endif
}

// GAME - 0x4504F0
void BSFadeNode::SetFadeOutMultiplier(LOD_MULT_TYPE aeType, float afMult) {
#ifdef GAME
	CdeclCall(0x4504F0, aeType, afMult);
#else
    fFadeOutMultipliers[aeType] = afMult;
#endif
}

// GAME - 0x54F4B0
bool BSFadeNode::GetFadeEnabled() {
#ifdef GAME
    return CdeclCall<bool>(0x54F4B0);
#else
    return bFadeEnabled;
#endif
}

// GAME - 0x4E20B0
void BSFadeNode::SetFadeEnabled(bool abVal) {
#ifdef GAME
    CdeclCall(0x4E20B0, abVal);
#else
    bFadeEnabled = abVal;
#endif
}