#include "TESEffectShader.hpp"

// GAME - 0x500940
const TESEffectShader::Data* TESEffectShader::GetData() const {
    return &kData;
}

// GAME - 0x500940
TESEffectShader::Data* TESEffectShader::GetData() {
    return &kData;
}

// GAME - 0x5A29B0
BGSDebris* TESEffectShader::GetAddonModels() const {
    return kData.pAddonModels;
}

// GAME - 0x505E50
void TESEffectShader::SetAddonModels(BGSDebris* apModels) {
    kData.pAddonModels = apModels;
}

// GAME - 0x506370
const TESTexture* TESEffectShader::GetFillTexture() const {
    return &kFillTexture;
}

// GAME - 0x506370
TESTexture* TESEffectShader::GetFillTexture() {
    return &kFillTexture;
}

void TESEffectShader::SetFillTexture(const char* apPath) {
    kFillTexture.SetTextureName(apPath);
}

// GAME - 0x506390
const TESTexture* TESEffectShader::GetParticleTexture() const {
    return &kParticleTexture;
}

// GAME - 0x506390
TESTexture* TESEffectShader::GetParticleTexture() {
    return &kParticleTexture;
}

void TESEffectShader::SetParticleTexture(const char* apPath) {
    kParticleTexture.SetTextureName(apPath);
}

// GAME - 0x5063B0
const TESTexture* TESEffectShader::GetHolesTexture() const {
    return &kHolesTexture;
}

// GAME - 0x5063B0
TESTexture* TESEffectShader::GetHolesTexture() {
    return &kHolesTexture;
}

void TESEffectShader::SetHolesTexture(const char* apPath) {
    kHolesTexture.SetTextureName(apPath);
}
