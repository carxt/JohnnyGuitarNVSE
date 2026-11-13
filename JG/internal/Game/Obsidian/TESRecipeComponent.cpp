#include "TESRecipeComponent.hpp"

// GAME - 0x559450
uint32_t TESRecipeComponent::GetQuantity() const {
    return uiQuantity;
}

// GAME - 0x537E90
void TESRecipeComponent::SetQuantity(uint32_t auiQuantity) {
    uiQuantity = auiQuantity;
}

// GAME - 0x726070
TESForm* TESRecipeComponent::GetItem() const {
    return pItem;
}

// GAME - 0x6ECD40
void TESRecipeComponent::SetItem(TESForm* apItem) {
    pItem = apItem;
}
