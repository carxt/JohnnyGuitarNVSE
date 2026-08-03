#include "NiTriShapeData.hpp"

// GAME - 0xA7B630
// GECK - 0x82D8B0
NiTriShapeData* NiTriShapeData::Create(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, uint32_t aeNBTMethod, uint16_t ausTriangles, uint16_t* apTriList) {
#ifdef GAME
    return NiCreate<NiTriShapeData, 0xA7B630>(ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod, ausTriangles, apTriList);
#else
	return NiCreate<NiTriShapeData, 0x82D8B0>(ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod, ausTriangles, apTriList);
#endif
}

uint32_t NiTriShapeData::GetTriListLength() const {
    return m_uiTriListLength;
}

uint16_t* NiTriShapeData::GetTriList() const {
    return m_pusTriList;
}

void NiTriShapeData::SetTriangleIndices(uint16_t ausTriangle, uint16_t ausIndex0, uint16_t ausIndex1, uint16_t ausIndex2) {
    m_pusTriList[3 * ausTriangle + 0] = ausIndex0;
    m_pusTriList[3 * ausTriangle + 1] = ausIndex1;
    m_pusTriList[3 * ausTriangle + 2] = ausIndex2;
}

// GAME - 0xA7B6C0
// GECK - 0x82D940
void NiTriShapeData::Replace(uint16_t ausTriangles, uint16_t* apTriList) {
#ifdef GAME
    ThisCall(0xA7B6C0, this, ausTriangles, apTriList);
#else
    ThisCall(0x82D940, this, ausTriangles, apTriList);
#endif
}
