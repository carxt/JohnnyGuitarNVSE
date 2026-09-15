#include "TESObjectMISC.hpp"

// GAME - 0x8CDD90
TESSound* TESObjectMISC::GetLoopingSound() const {
    return pLoopingSound;
}

// GAME - 0x9DB930
void TESObjectMISC::SetLoopingSound(TESSound* apSound) {
    pLoopingSound = apSound;
}