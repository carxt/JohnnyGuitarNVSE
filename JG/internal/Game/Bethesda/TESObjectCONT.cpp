#include "TESObjectCONT.hpp"

// GAME - 0x8CE390
TESSound* TESObjectCONT::GetOpenSound() const {
    return pOpenSound;
}

// GAME - 0x8CC6D0
void TESObjectCONT::SetOpenSound(TESSound* apSound) {
	pOpenSound = apSound;
}

// GAME - 0x516BF0
TESSound* TESObjectCONT::GetCloseSound() const {
    return pCloseSound;
}

// GAME - 0x4FB0B0
void TESObjectCONT::SetCloseSound(TESSound* apSound) {
    pCloseSound = apSound;
}

// GAME - 0x9185E0
TESSound* TESObjectCONT::GetLoopSound() const {
    return pLoopSound;
}

// GAME - 0x4FEBF0
void TESObjectCONT::SetLoopSound(TESSound* apSound) {
    pLoopSound = apSound;
}

// GAME - 0x56AF20
bool TESObjectCONT::GetRespawn() const {
    return kData.ucFlags.bRespawns;
}

// GAME - 0x516CD0
bool TESObjectCONT::CanActivate(TESObjectREFR* apItemActivated, TESObjectREFR* apActionRef, bool abAllowLockpicing) const {
	return ThisCall<bool>(0x516CD0, this, apItemActivated, apActionRef, abAllowLockpicing);
}
