#include "BGSPickupPutdownSounds.hpp"

// GAME - 0x726070
TESSound* BGSPickupPutdownSounds::GetPickupSound() const {
	return pPickupSound;
}

// GAME - 0x6ECD40
void BGSPickupPutdownSounds::SetPickupSound(TESSound* apSound) {
	pPickupSound = apSound;
}

// GAME - 0x44DDC0
TESSound* BGSPickupPutdownSounds::GetPutdownSound() const {
	return pPutdownSound;
}

// GAME - 0x403550
void BGSPickupPutdownSounds::SetPutdownSound(TESSound* apSound) {
	pPickupSound = apSound;
}
