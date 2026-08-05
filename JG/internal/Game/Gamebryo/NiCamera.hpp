#pragma once

#include "NiAVObject.hpp"
#include "NiRect.hpp"
#include "NiFrustum.hpp"

NiSmartPointer(NiCamera);

class NiRenderTargetGroup;

class NiCamera : public NiAVObject {
public:
	NiCamera();
	virtual ~NiCamera();

	float			m_aafWorldToCam[4][4];
	NiFrustum		m_kViewFrustum;
	float			m_fMinNearPlaneDist;
	float			m_fMaxFarNearRatio;
	NiRect<float>	m_kPort;
	float			m_fLODAdjust;

	CREATE_OBJECT(NiCamera, 0xA71430);
	NIRTTI_ADDRESS(0x11F4A18);

	NiPoint3 GetWorldDirection() const;
	NiPoint3 GetWorldUpVector() const;
	NiPoint3 GetWorldRightVector() const;

	const NiRect<float>& GetViewport() const;
	void SetViewport(const NiRect<float>& arPort);

	const NiFrustum& GetViewFrustum() const;
	void SetViewFrustum(const NiFrustum& arFrustum);

	float GetMinNearPlaneDist() const;
	void SetMinNearPlaneDist(float afDist);

	float GetMaxFarNearRatio() const;
	void SetMaxFarNearRatio(float afRatio);

	bool LookAtWorldPoint(const NiPoint3& arWorldPt, const NiPoint3& arWorldUp);
	bool FitNearAndFarToBound(const NiBound& arBound);

	bool WorldPtToScreenPt(const NiPoint3& arPt, float& arfBx, float& arfBy, const float afZeroTolerance = 1e-5f) const;
	bool WorldPtToScreenPt3(const NiPoint3& arPt, float& arfBx, float& arfBy, float& arfBz, const float afZeroTolerance = 1e-5f) const;

	void WorldToCameraMatrix();
	void ViewPointToRay(float afVx, float afVy, NiPoint3& arOrigin, NiPoint3& arDir) const;
	bool WindowPointToRay(uint32_t auiWx, uint32_t auiWy, NiPoint3& arOrigin, NiPoint3& arDir, NiRenderTargetGroup* apTarget = nullptr) const;
};

ASSERT_SIZE(NiCamera, 0x114);