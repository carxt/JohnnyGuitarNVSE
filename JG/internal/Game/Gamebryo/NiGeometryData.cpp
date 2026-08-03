#include "NiGeometryData.hpp"
#include "NiColorA.hpp"
#include "NiPoint2.hpp"

// GAME - 0x460140
const NiBound& NiGeometryData::GetBound() const {
	return m_kBound;
}

// GAME - 0x7AF430
NiPoint3* NiGeometryData::GetVertices() const {
	return m_pkVertex;
}

// GAME - 0x59BB30
NiPoint3* NiGeometryData::GetNormals() const {
	return m_pkNormal;
}

NiPoint3* NiGeometryData::GetBinormals() const {
    return m_pkNormal + m_usVertices;
}

NiPoint3* NiGeometryData::GetTangents() const {
    return m_pkNormal + (2 * m_usVertices);
}

// GAME - 0x45CD60
NiColorA* NiGeometryData::GetColors() const {
	return m_pkColor;
}

// GAME - 0x55B980
NiPoint2* NiGeometryData::GetTextures() const {
	return m_pkTexture;
}

uint16_t NiGeometryData::GetTextureSets() const {
	return m_usDataFlags.Get(1);
}

// GAME - 0xA66960
NiPoint2* NiGeometryData::GetTextureSet(uint16_t ausSet) {
	return m_pkTexture;
}

// GAME - 0xA669E0
uint16_t NiGeometryData::GetVertexCount() const {
	return m_usVertices;
}

void NiGeometryData::SetNormalBinormalTangentMethod(NiGeometryData::DataFlags aeNBTMethod) {
	m_usDataFlags = m_usDataFlags & ~NBT_METHOD_MASK | aeNBTMethod;
}

NiGeometryData::DataFlags NiGeometryData::GetNormalBinormalTangentMethod() const {
    return static_cast<DataFlags>(m_usDataFlags.Get(NBT_METHOD_MASK));
}

// GAME - 0x4410D0
void NiGeometryData::SetKeepFlags(uint32_t aeFlags) {
	m_ucKeepFlags = static_cast<KeepFlags>(aeFlags);
}

// GAME - 0x4410F0
void NiGeometryData::SetCompressFlags(uint32_t aeFlags) {
	m_ucCompressFlags = static_cast<Compression>(aeFlags);
}

// GAME - 0x457B80
NiGeometryData::Consistency NiGeometryData::GetConsistency() const {
	return static_cast<Consistency>(m_usDirtyFlags.Get(CONSISTENCY_MASK));
}

// GAME - 0xA67050
// GECK - 0x80C1C0
void NiGeometryData::SetConsistency(Consistency aeConsistency) {
#ifdef GAME
	ThisCall(0xA67050, this, aeConsistency);
#else
	ThisCall(0x80C1C0, this, aeConsistency);
#endif
}

// GAME - 0xA67360
// GECK - 0x80C4D0
bool NiGeometryData::LockPackedVertexData(bool abWriteAccess) {
#ifdef GAME
    return ThisCall<bool>(0xA67360, this, abWriteAccess);
#else
    return ThisCall<bool>(0x80C4D0, this, abWriteAccess);
#endif
}

// GAME - 0xA673D0
// GECK - 0x80C540
void NiGeometryData::UnlockPackedVertexData() {
#ifdef GAME
	ThisCall(0xA673D0, this);
#else
	ThisCall(0x80C540, this);
#endif
}

// GAME - 0x4A8A90
NiAdditionalGeometryData* NiGeometryData::GetAdditionalGeomData() const {
    return m_spAdditionalGeomData;
}

// GAME - 0xA67260
void NiGeometryData::SetAdditionalGeomData(NiAdditionalGeometryData* apData) {
	m_spAdditionalGeomData = apData;
}

// GAME - 0xA67090
// GECK - 0x80C200
void NiGeometryData::MarkAsChanged(uint32_t auiFlags) {
#ifdef GAME
    ThisCall(0xA67090, this, auiFlags);
#else
    ThisCall(0x80C200, this, auiFlags);
#endif
}

void NiGeometryData::ClearRevisionID() {
    m_usDirtyFlags.Clear(DIRTY_MASK);
}

// GAME - 0xA670C0
// GECK - 0x80C230
void NiGeometryData::Replace(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, NiGeometryData::DataFlags aeNBTMethod) {
#ifdef GAME
    ThisCall(0xA670C0, this, ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod);
#else
    ThisCall(0x80C230, this, ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod);
#endif
}

// GAME - 0xA66BB0
// GECK - 0x80BCC0
void NiGeometryData::ReplaceData(uint16_t ausVertices, NiPoint3* apVertex, NiPoint3* apNormal, NiColorA* apColor, NiPoint2* apTexture, uint16_t ausNumTextureSets, NiGeometryData::DataFlags aeNBTMethod) {
#ifdef GAME
    ThisCall(0xA66BB0, this, ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod);
#else
    ThisCall(0x80BCC0, this, ausVertices, apVertex, apNormal, apColor, apTexture, ausNumTextureSets, aeNBTMethod);
#endif
}