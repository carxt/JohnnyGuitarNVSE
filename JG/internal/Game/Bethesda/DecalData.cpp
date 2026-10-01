#include "DecalData.hpp"

// GAME - 0x6A7F50
float DecalData::GetDecalMinWidth() const {
    return kData.fDecalMinWidth;
}

// GAME - 0x6B9130
float DecalData::GetDecalMaxWidth() const {
    return kData.fDecalMaxWidth;
}

// GAME - 0x488D50
float DecalData::GetDecalMinHeight() const {
    return kData.fDecalMinHeight;
}

// GAME - 0x84D030
float DecalData::GetDecalMaxHeight() const {
    return kData.fDecalMaxHeight;
}

// GAME - 0x621B00
float DecalData::GetDecalDepth() const {
    return kData.fDepth;
}

// GAME - 0x47C860
float DecalData::GetDecalShininess() const {
    return kData.fDepth;
}

// GAME - 0x4A7BD0
float DecalData::GetDecalParallaxScale() const {
    return kData.fParallaxScale;
}

// GAME - 0x4A4200
uint16_t DecalData::GetDecalParallaxPasses() const {
    return kData.ucParallaxPasses;
}

// GAME - 0x4A4120
bool DecalData::GetIsParallax() const {
#ifdef GAME
    return ThisCall<bool>(0x4A4120, this);
#else
    return kData.ucFlags.bParallax;
#endif
}

// GAME - 0x4A4160
bool DecalData::GetAlphaBlending() const {
#ifdef GAME
    return ThisCall<bool>(0x4A4160, this);
#else
    return kData.ucFlags.bAlphaBlend;
#endif
}

// GAME - 0x4A41A0
bool DecalData::GetAlphaTesting() const {
#ifdef GAME
    return ThisCall<bool>(0x4A41A0, this);
#else
    return kData.ucFlags.bAlphaTest;
#endif
}

// GAME - 0x7AF430
uint32_t DecalData::GetDecalColor() const {
    return kData.uiColor;
}

// GAME - 0x56A8C0
DecalData* DecalData::GetDefaultDecalData() {
#ifdef GAME
    return CdeclCall<DecalData*>(0x56A8C0);
#else
    return reinterpret_cast<DecalData*>(0xE9BA70);
#endif
}