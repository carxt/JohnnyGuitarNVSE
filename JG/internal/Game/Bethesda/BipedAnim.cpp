#include "BipedAnim.hpp"

// GAME - 0x4AB230
NiNode* BipedAnim::GetParentBone(BIPED_BONE aeBone) const {
	return kBones[aeBone].pParent;
}

void BipedAnim::RemoveBipedWeapon() {
	ThisCall(0x4AB5B0, this);
}

void BipedAnim::RemovePart(uint32_t aeObject, bool abClear, void* apClearValue) {
	ThisCall(0x4AAFF0, this, aeObject, abClear, apClearValue);
}