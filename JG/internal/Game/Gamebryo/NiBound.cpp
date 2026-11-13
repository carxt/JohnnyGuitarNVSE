#include "NiBound.hpp"
#include "NiPlane.hpp"

// GAME - 0x6240D0
NiBound::NiBound() noexcept {}

NiBound::NiBound(const NiPoint3& arCenter, float afRadius) noexcept : m_kCenter(arCenter), m_fRadius(afRadius) {}

// GAME - 0x4A5250
void NiBound::operator=(const NiBound& arOther) noexcept {
	SetCenterAndRadius(arOther.m_kCenter, arOther.m_fRadius);
}

// GAME - 0xA92660
bool NiBound::operator==(const NiBound& arOther) const noexcept {
	return m_kCenter == arOther.m_kCenter && m_fRadius == arOther.m_fRadius;
}

// GAME - 0x6815C0
const NiPoint3& NiBound::GetCenter() const noexcept {
	return m_kCenter;
}

// GAME - 0x6397F0
void NiBound::SetCenter(float afX, float afY, float afZ) noexcept {
	m_kCenter = NiPoint3(afX, afY, afZ);
}

// GAME - 0x98DDD0
void NiBound::SetCenter(const NiPoint3& arCenter) noexcept {
	m_kCenter = arCenter;
}

// GAME - 0x84D030
float NiBound::GetRadius() const noexcept {
	return m_fRadius;
}

// GAME - 0x63F790
void NiBound::SetRadius(float afRadius) noexcept {
	m_fRadius = afRadius;
}

// GAME - 0x4A51D0
void NiBound::SetCenterAndRadius(const NiPoint3& arCenter, float afRadius) noexcept {
	m_kCenter = arCenter;
	m_fRadius = afRadius;
}

// GAME - 0x4B6100
// GECK - 0x523060
uint32_t NiBound::WhichSide(const NiPlane &arPlane) const noexcept {
	float fDistance = arPlane.Distance(m_kCenter);
	return (fDistance > -m_fRadius) ? (m_fRadius <= fDistance) : NiPlane::NEGATIVE_SIDE;
}

// GAME - 0xA7F3F0
// GECK - 0x821410
void NiBound::Merge(const NiBound* apBound) noexcept {
#ifdef GAME
	ThisCall(0xA7F3F0, this, apBound);
#else
	ThisCall(0x821410, this, apBound);
#endif
}

// GAME - 0xA7EE30
// GECK - 0x820E50
void NiBound::ComputeFromData(uint32_t auiVertexCount, const NiPoint3* apVertexArray) noexcept {
#ifdef GAME
	ThisCall(0xA7EE30, this, auiVertexCount, apVertexArray);
#else
	ThisCall(0x820E50, this, auiVertexCount, apVertexArray);
#endif
}

// GAME - 0xA7FEA0
// GECK - 0x830B20
void NiBound::Update(const NiTransform& arTransform) noexcept {
#ifdef GAME
	ThisCall(0xA7FEA0, this, &arTransform);
#else
	ThisCall(0x830B20, this, &arTransform);
#endif
}

// GAME - 0xA7FDD0
// GECK - 0x830AE7
void NiBound::Update(const NiBound& arBound, const NiTransform& arTransform) noexcept {
#ifdef GAME
	ThisCall(0xA7FDD0, this, &arBound, &arTransform);
#else
	ThisCall(0x830AE7, this, &arBound, &arTransform);
#endif
}

bool NiBound::IsPointWithin(const NiPoint3& arPoint) const noexcept {
	float fDistance = m_kCenter.Distance(arPoint);
	return fDistance <= m_fRadius;
}

bool NiBound::IsBoundWithin(const NiBound& arBound) const noexcept {
	float fDistance = m_kCenter.Distance(arBound.m_kCenter) + arBound.m_fRadius;
	return fDistance <= m_fRadius;
}
