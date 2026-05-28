#include "TESWaterForm.hpp"
#include "BGSPlaceableWater.hpp"

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

// GAME - 0x5800E0
void TESWaterForm::GetNoiseTexture(NiTexturePtr& arTexture) {
    arTexture = spNoiseTexture;
}

// GAME - 0x5800C0
void TESWaterForm::SetNoiseTexture(NiTexture* apTexture) {
    spNoiseTexture = apTexture;
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
    return pConsumeSpell;
}

// GAME - 0x57F890
void TESWaterForm::GetSpellItem(SpellItem* apSpell) {
    pConsumeSpell = apSpell;
}

// GAME - 0x57FDA0
const char* TESWaterForm::GetMaterialName() const {
    return ThisCall<const char*>(0x57FDA0, this);
}

// GAME - 0x57FEF0
void TESWaterForm::SetMaterialName(const char* apMaterial) {
    ThisCall(0x57FEF0, this, apMaterial);
}

#ifdef GAME
// GAME - 0x580130
BGSPlaceableWater* TESWaterForm::GetPlaceableAutoWater() {
    return ThisCall<BGSPlaceableWater*>(0x580130, this);
}
// GAME - 0x580330
BGSPlaceableWater* TESWaterForm::GetPlaceableLODWater() {
    return ThisCall<BGSPlaceableWater*>(0x580330, this);
}
#endif