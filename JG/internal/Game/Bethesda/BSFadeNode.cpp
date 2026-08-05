#include "BSFadeNode.hpp"

// GAME - 0xB4DFD0
void BSFadeNode::SetRange(float afNearDist, float afFarDist) {
	ThisCall(0xB4DFD0, this, afNearDist, afFarDist);
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
    return ThisCall<bool>(0x5AA8C0, this);
}

// GAME - 0x476AB0
void BSFadeNode::TurnFadeNodeOn() {
    ThisCall(0x476AB0, this);
}

// GAME - 0x54B800
void BSFadeNode::TurnFadeNodeOff() {
    ThisCall(0x54B800, this);
}

// GAME - 0x7D1D00
float BSFadeNode::GetFadeOutMultiplier(LOD_MULT_TYPE aeType) {
    return CdeclCall<float>(0x7D1D00, aeType);
}

// GAME - 0x4504F0
void BSFadeNode::SetFadeOutMultiplier(LOD_MULT_TYPE aeType, float afMult) {
	CdeclCall(0x4504F0, aeType, afMult);
}

// GAME - 0x54F4B0
bool BSFadeNode::GetFadeEnabled() {
    return CdeclCall<bool>(0x54F4B0);
}

// GAME - 0x4E20B0
void BSFadeNode::SetFadeEnabled(bool abVal) {
    CdeclCall(0x4E20B0, abVal);
}