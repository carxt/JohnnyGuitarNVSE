#include "BGSLightingTemplate.hpp"

struct RGBA {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

// GAME - 0x9611E0
// GECK - 0x975470
uint32_t BGSLightingTemplate::GetDataAmbientColor() const {
    return kData.uiAmbientColor;
}

void BGSLightingTemplate::GetDataAmbientColor(NiColor& arColor) const {
    arColor.r = reinterpret_cast<const RGBA&>(kData.uiAmbientColor).r / 255.f;
    arColor.g = reinterpret_cast<const RGBA&>(kData.uiAmbientColor).g / 255.f;
    arColor.b = reinterpret_cast<const RGBA&>(kData.uiAmbientColor).b / 255.f;
}

void BGSLightingTemplate::SetDataAmbientColor(uint32_t auiColor) {
    kData.uiAmbientColor = auiColor;
}

// GAME - 0x441110
// GECK - 0x830800
uint32_t BGSLightingTemplate::GetDataDirectionalColor() const {
    return kData.uiDirectionalColor;
}

void BGSLightingTemplate::GetDataDirectionalColor(NiColor& arColor) const {
    arColor.r = reinterpret_cast<const RGBA&>(kData.uiDirectionalColor).r / 255.f;
    arColor.g = reinterpret_cast<const RGBA&>(kData.uiDirectionalColor).g / 255.f;
    arColor.b = reinterpret_cast<const RGBA&>(kData.uiDirectionalColor).b / 255.f;
}

void BGSLightingTemplate::SetDataDirectionalColor(uint32_t auiColor) {
    kData.uiDirectionalColor = auiColor;
}

// GAME - 0x7AF430
// GECK - 0x608B20
uint32_t BGSLightingTemplate::GetDataFogColor() const {
    return kData.uiFogColor;
}

void BGSLightingTemplate::GetDataFogColor(NiColor& arColor) const {
    arColor.r = reinterpret_cast<const RGBA&>(kData.uiFogColor).r / 255.f;
    arColor.g = reinterpret_cast<const RGBA&>(kData.uiFogColor).g / 255.f;
    arColor.b = reinterpret_cast<const RGBA&>(kData.uiFogColor).b / 255.f;
}

void BGSLightingTemplate::SetDataFogColor(uint32_t auiColor) {
    kData.uiFogColor = auiColor;
}

// GAME - 0x526AC0
// GECK - 0x608B30
float BGSLightingTemplate::GetDataFogNearPlane() const {
    return kData.fFogNear;
}

void BGSLightingTemplate::SetDataFogNearPlane(float afVal) {
    kData.fFogNear = afVal;
}

// GAME - 0x526AE0
// GECK - 0x608B40
float BGSLightingTemplate::GetDataFogFarPlane() const {
    return kData.fFogFar;
}

void BGSLightingTemplate::SetDataFogFarPlane(float afVal) {
    kData.fFogFar = afVal;
}

// GAME - 0x55B980
// GECK - 0xC31C80
int32_t BGSLightingTemplate::GetDataDirectionalXY() const {
    return kData.iDirectionalXY;
}

void BGSLightingTemplate::SetDataDirectionalXY(int32_t aiVal) {
    kData.iDirectionalXY = aiVal;
}

// GAME - 0x671D10
// GECK - 0xC31CF0
int32_t BGSLightingTemplate::GetDataDirectionalZ() const {
    return kData.iDirectionalZ;
}

void BGSLightingTemplate::SetDataDirectionalZ(int32_t aiVal) {
    kData.iDirectionalZ = aiVal;
}

float BGSLightingTemplate::GetDataDirectionalFade() const {
    return kData.fDirectionalFade;
}

void BGSLightingTemplate::SetDataDirectionalFade(float afVal) {
    kData.fDirectionalFade = afVal;
}

// GAME - 0x9A9350
// GECK - 0x608B60
float BGSLightingTemplate::GetDataClipDist() const {
    return kData.fClipDist;
}

void BGSLightingTemplate::SetDataClipDist(float afVal) {
    kData.fClipDist = afVal;
}

// GAME - 0x598040
// GECK - 0x608B50
float BGSLightingTemplate::GetDataFogPower() const {
    return kData.fFogPower;
}

void BGSLightingTemplate::SetDataFogPower(float afVal) {
    kData.fFogPower = afVal;
}