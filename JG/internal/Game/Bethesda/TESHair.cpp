#include "TESHair.hpp"

// GAME - 0x5FDF40
bool TESHair::GetPlayable() const {
    return ucHairFlags.bPlayable;
}

void TESHair::SetPlayable(bool abVal) {
	ucHairFlags.bPlayable = abVal;
}

// GAME - 0x5FDF60
bool TESHair::CanBeMale() const {
	return ucHairFlags.bNotMale == false;
}

void TESHair::SetCanBeMale(bool abVal) {
	ucHairFlags.bNotMale = !abVal;
}

// GAME - 0x5FDF80
bool TESHair::CanBeFemale() const {
	return ucHairFlags.bNotFemale == false;
}

void TESHair::SetCanBeFemale(bool abVal) {
	ucHairFlags.bNotFemale = !abVal;
}

bool TESHair::GetFixedColor() const {
	return ucHairFlags.bFixedColor;
}

void TESHair::SetFixedColor(bool abVal) {
	ucHairFlags.bFixedColor = abVal;
}

// GAME - 0x5FDFA0
// GECK - 0x56A310
bool TESHair::CanBeHairForNPC(TESNPC* apNPC) {
#ifdef GAME
	return ThisCall<bool>(0x5FDFA0, this, apNPC);
#else
	return ThisCall<bool>(0x56A310, this, apNPC);
#endif
}
