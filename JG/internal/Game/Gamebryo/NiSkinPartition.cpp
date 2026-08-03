#include "NiSkinPartition.hpp"

// GAME - 0xA84980
// GECK - 0x836230
bool NiSkinPartition::MakePartitions(const NiTriBasedGeomData* apTriData, const NiSkinData* apSkinData, uint8_t aucBonesPerPartition, uint8_t aucBonesPerVertex, bool abForcePalette, void** a7, uint16_t* a8, bool* a9) {
#ifdef GAME
    return ThisCall<bool>(0xA84980, this, apTriData, apSkinData, aucBonesPerPartition, aucBonesPerVertex, abForcePalette, a7, a8, a9);
#else
	return ThisCall<bool>(0x836230, this, apTriData, apSkinData, aucBonesPerPartition, aucBonesPerVertex, abForcePalette, a7, a8, a9);
#endif
}

// GAME - 0xA84810
// GECK - 0x8360C0
NiSkinPartition::VertexInteractions* NiSkinPartition::CreateVertexInteractions(uint32_t auiVertices, const NiSkinData* apSkinData) {
#ifdef GAME
    return ThisCall<NiSkinPartition::VertexInteractions*>(0xA84810, this, auiVertices, apSkinData);
#else
	return ThisCall<NiSkinPartition::VertexInteractions*>(0x8360C0, this, auiVertices, apSkinData);
#endif
}

// GAME - 0xA833B0
// GECK - 0x834C60
bool NiSkinPartition::RemoveExcessInteractions(NiTriBasedGeomData* apTriData, uint8_t aucBonesPerPartition, uint8_t aucBonesPerVertex, VertexInteractions* apVertexInteraction) {
#ifdef GAME
    return ThisCall<bool>(0xA833B0, this, apTriData, aucBonesPerPartition, aucBonesPerVertex, apVertexInteraction);
#else
	return ThisCall<bool>(0x834C60, this, apTriData, aucBonesPerPartition, aucBonesPerVertex, apVertexInteraction);
#endif
}

// GAME - 0xA84310
// GECK - 0x835BC0
bool NiSkinPartition::MakeBoneSets(const NiTriBasedGeomData* apTriData, const NiSkinData* apSkinData, uint8_t aucBonesPerPartition, NiSkinPartition::VertexInteractions* apVertexInteraction, NiBoneSetCollection& arBoneSets, uint32_t*& apuiTriangleToPartition, uint32_t** apUnk18) {
#ifdef GAME
    return ThisCall<bool>(0xA84310, this, apTriData, apSkinData, aucBonesPerPartition, apVertexInteraction, &arBoneSets, apuiTriangleToPartition, apUnk18);
#else
	return ThisCall<bool>(0x835BC0, this, apTriData, apSkinData, aucBonesPerPartition, apVertexInteraction, &arBoneSets, apuiTriangleToPartition, apUnk18);
#endif
}
