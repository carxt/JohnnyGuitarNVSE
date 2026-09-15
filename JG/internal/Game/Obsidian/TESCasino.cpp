#include "TESCasino.hpp"

// GAME - 0x504E00
const TESModelTextureSwap* TESCasino::GetModel(ModelType aeType) const {
    return &kModels[aeType];
}

// GAME - 0x504E00
TESModelTextureSwap* TESCasino::GetModel(ModelType aeType) {
    return &kModels[aeType];
}

// GAME - 0x504E20
const TESTexture* TESCasino::GetTexture(TextureType aeType) const {
    return &kTextures[aeType];
}

// GAME - 0x504E20
TESTexture* TESCasino::GetTexture(TextureType aeType) {
    return &kTextures[aeType];
}

// GAME - 0x737E30
int32_t TESCasino::GetMaxTotalWinnings() const {
    return kData.iMaxWinnings;
}

// GAME - 0x7316D0
TESCasinoChips* TESCasino::GetChipType() const {
#ifdef GAME
    return ThisCall<TESCasinoChips*>(0x7316D0, this);
#else
    return reinterpret_cast<TESCasinoChips*>(GetFormByNumericID(kData.uiCasinoChipID));
#endif
}

// GAME - 0x504E40
TESQuest* TESCasino::GetQuest() const {
#ifdef GAME
    return ThisCall<TESQuest*>(0x504E40, this);
#else
    return reinterpret_cast<TESQuest*>(GetFormByNumericID(kData.uiQuestID));
#endif
}
