#include "BGSMovableStatic.hpp"

// GAME - 0x5E3FA0
TESSound* BGSMovableStatic::GetLoopingSound() const {
    return pLoopSound;
}

// GAME - 0x4FBF00
void BGSMovableStatic::SetLoopingSound(TESSound* apSound) {
	pLoopSound = apSound;
}
