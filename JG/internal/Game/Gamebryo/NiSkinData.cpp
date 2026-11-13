#include "NiSkinData.hpp"

// GAME - 0xA854C0
// GECK - 0x8377C0
NiSkinData* NiSkinData::Create(uint32_t auiBones, BoneData* apBoneData, const NiTransform& arRootParentToSkin, const NiPoint3* apVerts) {
#ifdef GAME
    return NiCreate<NiSkinData, 0xA854C0>(auiBones, apBoneData, &arRootParentToSkin, apVerts);
#else
	return NiCreate<NiSkinData, 0x8377C0>(auiBones, apBoneData, &arRootParentToSkin, apVerts);
#endif
}
