#include "TESObjectSTAT.hpp"

uint8_t TESObjectSTAT::GetPassThroughSoundType() const {
    return ucPassThroughSoundType;
}

void TESObjectSTAT::SetPassThroughSoundType(uint8_t aucType) {
    ucPassThroughSoundType = aucType;
}

TESSound* TESObjectSTAT::GetSound() const {
    return pSound;
}

void TESObjectSTAT::SetSound(TESSound* apSound) {
    pSound = apSound;
}
