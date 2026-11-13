#include "BGSImpactData.hpp"

// GAME - 0x508100
float BGSImpactData::GetEffectDuration() const {
    return kData.fEffectDuration;
}

void BGSImpactData::SetEffectDuration(float afDuration){
    kData.fEffectDuration = afDuration;
}

// GAME - 0x5F36F0
BGSImpactData::Orientation BGSImpactData::GetImpactOrientation() const {
    return kData.eOrient;
}

void BGSImpactData::SetImpactOrientation(Orientation aeOrientation){
    kData.eOrient = aeOrientation;
}

// GAME - 0x9A9350
float BGSImpactData::GetDecalAngleThreshold() const {
    return kData.fAngleThreshold;
}

void BGSImpactData::SetDecalAngleThreshold(float afThreshold) {
    kData.fAngleThreshold = afThreshold;
}

// GAME - 0x598040
float BGSImpactData::GetPlacementRadius() const {
    return kData.fPlacementRadius;
}

void BGSImpactData::SetPlacementRadius(float afRadius) {
    kData.fPlacementRadius = afRadius;
}

SOUND_LEVEL BGSImpactData::GetSoundLevel() const {
    return kData.eSoundLevel;
}

void BGSImpactData::SetSoundLevel(SOUND_LEVEL aeLevel) {
    kData.eSoundLevel = aeLevel;
}

#ifdef GAME
int32_t BGSImpactData::GetSoundLevelValue() const {
    return ThisCall<int32_t>(0x58E790, this);
}
#endif

// GAME - 0x58DE80
bool BGSImpactData::GetUseTextureSetDecalData() const {
#ifdef GAME
    return ThisCall<bool>(0x58DE80, this);
#else
    return kData.ucFlags.bUseTextureSetDecalData;
#endif
}

void BGSImpactData::SetUseTextureSetDecalData(bool abVal) {
    kData.ucFlags.bUseTextureSetDecalData = abVal;
}

// GAME - 0x6733E0
BGSTextureSet* BGSImpactData::GetDecalTextureSet() const {
    return pTextureSet;
}

// GAME - 0x673400
void BGSImpactData::SetDecalTextureSet(BGSTextureSet* apTextureSet) {
    pTextureSet = apTextureSet;
}

// GAME - 0x68A810
TESSound* BGSImpactData::GetSoundA() const {
    return pSoundA;
}

// GAME - 0x589F50
void BGSImpactData::SetSoundA(TESSound* apSound) {
    pSoundA = apSound;
}

// GAME - 0x68A830
TESSound* BGSImpactData::GetSoundB() const {
    return pSoundB;
}

// GAME - 0x58E430
void BGSImpactData::SetSoundB(TESSound* apSound) {
    pSoundB = apSound;
}


// GAME - 0x4A40A0
float BGSImpactData::GetDecalMinWidth() const {
#ifdef GAME
    return ThisCall<float>(0x4A40A0, this);
#else
    return kDecalData.GetDecalMinWidth();
#endif
}

// GAME - 0x4A40C0
float BGSImpactData::GetDecalMaxWidth() const {
#ifdef GAME
    return ThisCall<float>(0x4A40C0, this);
#else
    return kDecalData.GetDecalMaxWidth();
#endif
}

float BGSImpactData::GetDecalMinHeight() const {
    return kDecalData.GetDecalMinHeight();
}

float BGSImpactData::GetDecalMaxHeight() const {
    return kDecalData.GetDecalMaxHeight();
}

// GAME - 0x8AFF10
float BGSImpactData::GetDecalDepth() const {
#ifdef GAME
    return ThisCall<float>(0x8AFF10, this);
#else
    return kDecalData.GetDecalDepth();
#endif
}

// GAME - 0x4A40E0
float BGSImpactData::GetDecalShininess() const {
#ifdef GAME
    return ThisCall<float>(0x4A40E0, this);
#else
    return kDecalData.GetDecalShininess();
#endif
}

// GAME - 0x4A41C0
float BGSImpactData::GetDecalParallaxScale() const {
#ifdef GAME
    return ThisCall<float>(0x4A41C0, this);
#else
    return kDecalData.GetDecalParallaxScale();
#endif
}

// GAME - 0x4A41E0
uint16_t BGSImpactData::GetDecalParallaxPasses() const {
#ifdef GAME
    return ThisCall<uint16_t>(0x4A41E0, this);
#else
    return kDecalData.GetDecalParallaxPasses();
#endif
}

// GAME - 0x4A4100
bool BGSImpactData::GetIsParallax() const {
#ifdef GAME
    return ThisCall<bool>(0x4A4100, this);
#else
    return kDecalData.GetIsParallax();
#endif
}

// GAME - 0x4A4140
bool BGSImpactData::GetAlphaBlending() const {
#ifdef GAME
    return ThisCall<bool>(0x4A4140, this);
#else
    return kDecalData.GetAlphaBlending();
#endif
}

// GAME - 0x4A4180
bool BGSImpactData::GetAlphaTesting() const {
#ifdef GAME
    return ThisCall<bool>(0x4A4180, this);
#else
    return kDecalData.GetAlphaTesting();
#endif
}

// GAME - 0x4A4220
uint32_t BGSImpactData::GetDecalColor() const {
#ifdef GAME
    return ThisCall<uint32_t>(0x4A4220, this);
#else
    return kDecalData.GetDecalColor();
#endif
}