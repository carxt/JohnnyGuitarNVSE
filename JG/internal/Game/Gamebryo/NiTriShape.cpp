#include "NiTriShape.hpp"

// GAME - 0x68CA10
// GECK - 0x6A4BB0
NiTriShape* NiTriShape::Create(NiTriShapeData* apData) {
#ifdef GAME
    return CdeclCall<NiTriShape*>(0x68CA10, apData);
#else
	return CdeclCall<NiTriShape*>(0x6A4BB0, apData);
#endif
}

// GAME - 0xA74410
// GECK - 0x82D5F0
NiTriShape* NiTriShape::Create(uint16_t ausVertices, NiPoint3* apkVertex, NiPoint3* apkNormal, NiColorA* apkColor, NiPoint2* apkTexture, uint16_t ausNumTextureSets, uint32_t aeNBTMethod, uint16_t ausTriangles, uint16_t* apusTriList) {
#ifdef GAME
    return NiCreate<NiTriShape, 0xA74410>(ausVertices, apkVertex, apkNormal, apkColor, apkTexture, ausNumTextureSets, aeNBTMethod, ausTriangles, apusTriList);
#else
	return NiCreate<NiTriShape, 0x82D5F0>(ausVertices, apkVertex, apkNormal, apkColor, apkTexture, ausNumTextureSets, aeNBTMethod, ausTriangles, apusTriList);
#endif
}

NiTriShapeData* NiTriShape::GetModelData() const {
    return static_cast<NiTriShapeData*>(NiTriBasedGeom::GetModelData());
}

uint32_t NiTriShape::GetTriListLength() const {
    return GetModelData()->GetTriListLength();
}

uint16_t* NiTriShape::GetTriList() const {
    return GetModelData()->GetTriList();
}