#include "NiTriStripsData.hpp"

// GAME - 0xA75DC0
// GECK - 0x82E0D0
NiTriStripsData* NiTriStripsData::Create(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, DataFlags aeNBTMethod, uint16_t ausTriangles, uint16_t ausStrips, uint16_t* apusStripLengths, uint16_t* apusStripLists) {
#ifdef GAME
	return NiCreate<NiTriStripsData, 0xA75DC0>(ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod, ausTriangles, ausStrips, apusStripLengths, apusStripLists);
#else
	return NiCreate<NiTriStripsData, 0x82E0D0>(ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod, ausTriangles, ausStrips, apusStripLengths, apusStripLists);
#endif
}

uint16_t NiTriStripsData::GetStripCount() const {
	return m_usStrips;
}

uint16_t* NiTriStripsData::GetStripLengths() const {
	return m_pusStripLengths;
}

uint16_t* NiTriStripsData::GetStripLists() const {
	return m_pusStripLists;
}

uint16_t NiTriStripsData::GetIndexCount(uint32_t auiStrip) const {
	return m_pusStripLengths[auiStrip];
}

uint32_t NiTriStripsData::GetStripLengthSum() const {
	return m_usTriangles + 2 * m_usStrips;
}

// GAME - 0xA760C0
// GECK - 0x82E3B0
void NiTriStripsData::Replace(uint16_t usStrips, uint16_t* apusStripLengths, uint16_t* apusStripLists) {
#ifdef GAME
	ThisCall(0xA760C0, this, usStrips, apusStripLengths, apusStripLists);
#else
	ThisCall(0x82E3B0, this, usStrips, apusStripLengths, apusStripLists);
#endif
}