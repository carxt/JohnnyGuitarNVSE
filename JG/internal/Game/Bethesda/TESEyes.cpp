#include "TESEyes.hpp"

// GAME - 0x5FC4D0
bool TESEyes::GetPlayable() const {
	return ucEyeFlags.bPlayable;
}

// GAME - 0x5FC4F0
void TESEyes::SetPlayable(bool abVal) {
	ucEyeFlags.bPlayable = abVal;
}

// GAME - 0x5FC530
bool TESEyes::CanBeMale() const {
	return ucEyeFlags.bNotMale == false;
}

// GAME - 0x5FC550
void TESEyes::SetCanBeMale(bool abVal) {
	ucEyeFlags.bNotMale = !abVal;
}

// GAME - 0x5FC590
bool TESEyes::CanBeFemale() const {
	return ucEyeFlags.bNotFemale == false;
}

// GAME - 0x5FC5B0
void TESEyes::SetCanBeFemale(bool abVal) {
	ucEyeFlags.bNotFemale = !abVal;
}

// GAME - 0x5FC5F0
// GECK - 0x567420
bool TESEyes::CanBeEyesForNPC(TESNPC* apNPC) {
#ifdef GAME
	return ThisCall<bool>(0x5FC5F0, this, apNPC);
#else
	return ThisCall<bool>(0x567420, this, apNPC);
#endif
}
