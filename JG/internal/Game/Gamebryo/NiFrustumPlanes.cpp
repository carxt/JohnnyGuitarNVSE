#include "NiFrustumPlanes.hpp"

// GAME - 0xA74E10
// GECK - 0x82CE10
void NiFrustumPlanes::Set(const NiFrustum& arFrustum, const NiTransform& arTransform) {
#ifdef GAME
	ThisCall(0xA74E10, this, &arFrustum, &arTransform);
#else
	ThisCall(0x82CE10, this, &arFrustum, &arTransform);
#endif
}

// GAME - 0xA755D0
// GECK - 0x82D5D0
void NiFrustumPlanes::Set(const NiCamera* apCamera) {
#ifdef GAME
	ThisCall(0xA755D0, this, apCamera);
#else
	ThisCall(0x82D5D0, this, apCamera);
#endif
}

void NiFrustumPlanes::SetPlane(uint32_t aePlane, const NiPlane& arPlane) {
	m_akCullingPlanes[aePlane] = arPlane;
}

// GAME - 0x4B4CF0
const NiPlane& NiFrustumPlanes::GetPlane(uint32_t ePlane) const {
	return m_akCullingPlanes[ePlane];
}

bool NiFrustumPlanes::IsPlaneActive(uint32_t ePlane) const {
	return (m_uiActivePlanes & (1 << ePlane)) ? true : false;
}

bool NiFrustumPlanes::IsAnyPlaneActive() const {
	return m_uiActivePlanes ? true : false;
}

void NiFrustumPlanes::EnablePlane(uint32_t ePlane) {
	m_uiActivePlanes = m_uiActivePlanes | (1 << ePlane);
}

void NiFrustumPlanes::DisablePlane(uint32_t ePlane) {
	m_uiActivePlanes = m_uiActivePlanes & ~(1 << ePlane);
}

void NiFrustumPlanes::SetActivePlaneState(uint32_t uiState) {
	m_uiActivePlanes = uiState;
}
