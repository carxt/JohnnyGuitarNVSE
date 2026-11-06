#include "NiTriStrips.hpp"

// GAME - 0xA71C40
// GECK - 0x82A0F0
NiTriStrips* NiTriStrips::Create(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, NiGeometryData::DataFlags aeNBTMethod, uint16_t ausTriangles, uint16_t ausStrips, uint16_t* apusStripLengths, uint16_t* apusStripLists) {
#ifdef GAME
    return NiCreate<NiTriStrips, 0xA71C40>(ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod, ausTriangles, ausStrips, apusStripLengths, apusStripLists);
#else
	return NiCreate<NiTriStrips, 0x82A0F0>(ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod, ausTriangles, ausStrips, apusStripLengths, apusStripLists);
#endif
}

NiTriStripsData* NiTriStrips::GetModelData() const {
    return static_cast<NiTriStripsData*>(NiTriBasedGeom::GetModelData());
}