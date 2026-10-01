#include "TESCaravanCard.hpp"

#ifdef GAME
// GAME - 0x73CB80
bool TESCaravanCard::GetIsActive() const {
    return bIsActive;
}

// GAME - 0x6E2B50
void TESCaravanCard::SetIsActive(bool abVal) {
    bIsActive = abVal;
}
#endif

// GAME - 0x50D100
TESTexture* TESCaravanCard::GetFaceTexture() {
    return &kFaceTexture;
}

// GAME - 0x50D100
const TESTexture* TESCaravanCard::GetFaceTexture() const {
    return &kFaceTexture;
}

// GAME - 0x503650
TESTexture* TESCaravanCard::GetBackTexture() {
    return &kBackTexture;
}

// GAME - 0x503650
const TESTexture* TESCaravanCard::GetBackTexture() const {
    return &kBackTexture;
}

// GAME - 0x4036B0
TESCaravanCard::CardSuit TESCaravanCard::GetCardSuit() const {
    return kData.eCardSuit;
}

// GAME - 0x8D80E0
TESCaravanCard::CardValue TESCaravanCard::GetFaceValue() const {
    return kData.eFaceValue;
}
