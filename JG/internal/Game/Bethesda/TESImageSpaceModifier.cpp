#include "TESImageSpaceModifier.hpp"

// GAME - 0x441110
TESSound* TESImageSpaceModifier::GetIntroSound() const {
	return pIntroSound;
}

void TESImageSpaceModifier::SetIntroSound(TESSound* apSound) {
	pIntroSound = apSound;
}

// GAME - 0x9611E0
TESSound* TESImageSpaceModifier::GetOutroSound() const {
	return pOutroSound;
}

void TESImageSpaceModifier::SetOutroSound(TESSound* apSound) {
	pOutroSound = apSound;
}

// GAME - 0x529EA0
bool TESImageSpaceModifier::GetAnimatable() const {
	return kData.bAnimatable;
}

void TESImageSpaceModifier::SetAnimatable(bool abVal) {
	kData.bAnimatable = abVal;
}

#ifdef GAME
// GAME - 0x80BFA0
TESImageSpaceModifier* TESImageSpaceModifier::GetConcussion() {
	return CdeclCall<TESImageSpaceModifier*>(0x80BFA0);
}

// GAME - 0x9AD630
TESImageSpaceModifier* TESImageSpaceModifier::GetExplosionInFace() {
	return CdeclCall<TESImageSpaceModifier*>(0x9AD630);
}

// GAME - 0x5D2860
TESImageSpaceModifier* TESImageSpaceModifier::GetGetHit() {
	return CdeclCall<TESImageSpaceModifier*>(0x5D2860);
}
#endif