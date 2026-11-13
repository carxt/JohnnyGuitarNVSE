#include "TESWaterForm.hpp"

// GAME - 0x5800A0
const char* TESWaterForm::GetNoiseTextureName() const {
    return kNoiseTexture.GetTextureName();
}

void TESWaterForm::SetNoiseTextureName(const char* apTexture) {
    kNoiseTexture.SetTextureName(apTexture);
}

// GAME - 0x580080
uint32_t TESWaterForm::GetNoiseTextureNameLength() const {
    return kNoiseTexture.GetTextureNameLength();
}

// GANE - 0x580060
bool TESWaterForm::GetIsDangerousWater() const {
#ifdef GAME
    return ThisCall<bool>(0x580060, this);
#else
    return ucFlags.bDangerous;
#endif
}

void TESWaterForm::SetIsDangerousWater(bool abVal) {
    ucFlags.bDangerous = abVal;
}

// GAME - 0x57FDA0
const char* TESWaterForm::GetMaterialName() const {
#ifdef GAME
    return ThisCall<const char*>(0x57FDA0, this);
#else
    return strMaterialID.c_str();
#endif
}

// GAME - 0x57FEF0
void TESWaterForm::SetMaterialName(const char* apMaterial) {
#ifdef GAME
    ThisCall(0x57FEF0, this, apMaterial);
#else
    strMaterialID.Set(apMaterial);
#endif
}

// GAME - 0x407840
TESSound* TESWaterForm::GetWaterSound() const {
    return pWaterSound;
}

// GAME - 0x4FEBD0
void TESWaterForm::SetWaterSound(TESSound* apSound) {
    pWaterSound = apSound;
}

// GAME - 0x57FED0
SpellItem* TESWaterForm::GetSpellItem() const {
    return pSpellItem;
}

// GAME - 0x57F890
void TESWaterForm::GetSpellItem(SpellItem* apSpell) {
    pSpellItem = apSpell;
}

// GAME - 0x5800E0
void TESWaterForm::GetNoiseTexture(NiTexturePtr& arTexture) {
    arTexture = spNoiseTexture;
}

// GAME - 0x5800C0
void TESWaterForm::SetNoiseTexture(NiTexture* apTexture) {
    spNoiseTexture = apTexture;
}