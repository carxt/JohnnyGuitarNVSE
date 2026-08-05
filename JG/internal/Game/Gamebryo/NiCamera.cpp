#include "NiCamera.hpp"
#include "NiBound.hpp"

// GAME - 0x45BBA0
NiPoint3 NiCamera::GetWorldDirection() const {
    NiPoint3 kVector;
    m_kWorld.m_kRotate.GetCol(0, kVector);
    return kVector;
}

// GAME - 0x4E9C10
NiPoint3 NiCamera::GetWorldUpVector() const {
    NiPoint3 kVector;
    m_kWorld.m_kRotate.GetCol(1, kVector);
    return kVector;
}

// GAME - 0x4E9C50
NiPoint3 NiCamera::GetWorldRightVector() const {
    NiPoint3 kVector;
    m_kWorld.m_kRotate.GetCol(2, kVector);
    return kVector;
}

// GAME - 0x4A0D10
const NiRect<float>& NiCamera::GetViewport() const {
    return m_kPort;
}

// GAME - 0x712E60
void NiCamera::SetViewport(const NiRect<float>& arPort) {
    m_kPort = arPort;
}

// GAME - 0x45BBE0
const NiFrustum& NiCamera::GetViewFrustum() const {
    return m_kViewFrustum;
}

// GAME - 0xA6FAF0
// GECK - 0x816790
void NiCamera::SetViewFrustum(const NiFrustum& arFrustum) {
#ifdef GAME
	ThisCall(0xA6FAF0, this, &arFrustum);
#else
	ThisCall(0x816790, this, &arFrustum);
#endif
}

float NiCamera::GetMinNearPlaneDist() const {
    return m_fMinNearPlaneDist;
}

// GAME - 0x733FD0
void NiCamera::SetMinNearPlaneDist(float afDist) {
    m_fMinNearPlaneDist = afDist;
}

// GAME - 0x6447F0
float NiCamera::GetMaxFarNearRatio() const {
    return m_fMaxFarNearRatio;
}

// GAME - 0x507700
void NiCamera::SetMaxFarNearRatio(float afRatio) {
    m_fMaxFarNearRatio = afRatio;
}

// GAME - 0xA701B0
// GECK - 0x816B00
bool NiCamera::LookAtWorldPoint(const NiPoint3& arWorldPt, const NiPoint3& arWorldUp) {
#ifdef GAME
	return ThisCall<bool>(0xA701B0, this, &arWorldPt, &arWorldUp);
#else
	return ThisCall<bool>(0x816B00, this, &arWorldPt, &arWorldUp);
#endif
}

// GAME - 0xA70080
// GECK - NONE
bool NiCamera::FitNearAndFarToBound(const NiBound& arBound) {
#ifdef GAME
	return ThisCall<bool>(0xA70080, this, &arBound);
#else
    const float fDistToCenter = (arBound.GetCenter() - GetWorldTranslate()) * GetWorldDirection();

    float fMinDist = fDistToCenter - arBound.GetRadius();
    float fMaxDist = fDistToCenter + arBound.GetRadius();

    if (fMaxDist <= 0.f)
        return false;

    const float fMinMinDist = fMaxDist / m_fMaxFarNearRatio;
    if (fMinDist < fMinMinDist)
        fMinDist = fMinMinDist;

    if (fMinDist < m_fMinNearPlaneDist)
        fMinDist = m_fMinNearPlaneDist;

    m_kViewFrustum.m_fNear = fMinDist;
    m_kViewFrustum.m_fFar = fMaxDist;

    NiUpdateData kData;
    UpdateWorldData(kData);
    UpdateWorldBound();

    return true;
#endif
}

// GAME - 0xA6FC50
// GECK - 0x816830
bool NiCamera::WorldPtToScreenPt(const NiPoint3& arPt, float& arfBx, float& arfBy, const float afZeroTolerance) const {
#ifdef GAME
	return ThisCall<bool>(0xA6FC50, this, &arPt, &arfBx, &arfBy, afZeroTolerance);
#else
    return ThisCall<bool>(0x816830, this, &arPt, &arfBx, &arfBy, afZeroTolerance);
#endif
}

// GAME - 0xA6FDB0
bool NiCamera::WorldPtToScreenPt3(const NiPoint3& arPt, float& arfBx, float& arfBy, float& arfBz, const float afZeroTolerance) const {
    return ThisCall<bool>(0xA6FDB0, this, &arPt, &arfBx, &arfBy, &arfBz, afZeroTolerance);
}

// GAME - 0xA70BA0
// GECK - 0x816FA0
void NiCamera::WorldToCameraMatrix() {
#ifdef GAME
    ThisCall(0xA70BA0, this);
#else
    ThisCall(0x816FA0, this);
#endif
}

// GAME - 0xA703A0
// GECK - 0x816CF0
void NiCamera::ViewPointToRay(float afVx, float afVy, NiPoint3& arOrigin, NiPoint3& arDir) const {
#ifdef GAME
	ThisCall(0xA703A0, this, afVx, afVy, &arOrigin, &arDir);
#else
    ThisCall(0x816CF0, this, afVx, afVy, &arOrigin, &arDir);
#endif
}

// GAME - 0xA71080
// GECK - 0x817480
bool NiCamera::WindowPointToRay(uint32_t auiWx, uint32_t auiWy, NiPoint3& arOrigin, NiPoint3& arDir, NiRenderTargetGroup* apTarget) const {
#ifdef GAME
	return ThisCall<bool>(0xA71080, this, auiWx, auiWy, &arOrigin, &arDir, apTarget);
#else
	return ThisCall<bool>(0x817480, this, auiWx, auiWy, &arOrigin, &arDir, apTarget);
#endif
}
