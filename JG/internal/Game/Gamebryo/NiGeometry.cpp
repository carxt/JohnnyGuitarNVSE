#include "NiGeometry.hpp"

// GAME - 0x5495F0
NiGeometryData* NiGeometry::GetModelData() const {
	return m_spModelData;
}

// GAME - 0x43FAD0
NiSkinInstance* NiGeometry::GetSkinInstance() const {
	return m_spSkinInstance;
}

// GAME - 0x4ADDE0
void NiGeometry::SetSkinInstance(NiSkinInstance* apSkinInstance) {
	m_spSkinInstance = apSkinInstance;
}

// GAME - 0x4030B0
NiShader* NiGeometry::GetShader() const {
	return m_pShader;
}

// GAME - 0x874460
void NiGeometry::SetShader(NiShader* apShader) {
	m_pShader = apShader;
}

// GAME - 0x49EC60
NiPoint3* NiGeometry::GetVertices() const {
	return GetModelData()->GetVertices();
}

// GAME - 0x4A8030
NiPoint3* NiGeometry::GetNormals() const {
	return GetModelData()->GetNormals();
}

// GAME - 0x4A8050
NiColorA* NiGeometry::GetColors() const {
	return GetModelData()->GetColors();
}

// GAME - 0x4A8070
NiPoint2* NiGeometry::GetTextures() const {
	return GetModelData()->GetTextures();
}

// GAME - 0x456650
uint16_t NiGeometry::GetVertexCount() const {
	return GetModelData()->GetVertexCount();
}

uint16_t NiGeometry::GetTextureSets() const {
	return GetModelData()->GetTextureSets();
}

NiPoint2* NiGeometry::GetTextureSet(uint16_t ausSet) const {
	return GetModelData()->GetTextureSet(ausSet);
}

// GAME - 0x537B10
const NiBound& NiGeometry::GetModelBound() const {
	return GetModelData()->GetBound();
}