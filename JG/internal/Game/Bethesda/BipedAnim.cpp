#include "BipedAnim.hpp"

// GAME - 0x4AB230
// GECK - 0x51F8C0
NiNode* BipedAnim::GetParentBone(BIPED_BONE aeBone) const {
	return kBones[aeBone].pParent;
}

// GAME - 0x4AB5B0
// GECK - 0x5201C0
void BipedAnim::RemoveBipedWeapon() {
#ifdef GAME
	ThisCall(0x4AB5B0, this);
#else
	ThisCall(0x5201C0, this);
#endif
}

#ifdef GAME
// GAME - 0x4AAFF0
void BipedAnim::RemovePart(BIPED_OBJECT aeObject, bool abClear, void* apClearValue) {
	ThisCall(0x4AAFF0, this, aeObject, abClear, apClearValue);
}

// GAME - 0x4AB0C0
void BipedAnim::RunBiped3DDetach(NiAVObject* apObject) {
	CdeclCall(0x4AB0C0, apObject);
}
#endif

// GAME - 0x4ADE40
// GECK - 0x521640
void BipedAnim::AttachToSkeleton(NiNode* apSkeleton, NiAVObject* apSkin, NiNode* apParentNode, bool abShowWarnings) {
#ifdef GAME
	CdeclCall(0x4ADE40, apSkeleton, apSkin, apParentNode, abShowWarnings);
#else
	CdeclCall(0x521640, apSkeleton, apSkin, apParentNode, abShowWarnings);
#endif
}