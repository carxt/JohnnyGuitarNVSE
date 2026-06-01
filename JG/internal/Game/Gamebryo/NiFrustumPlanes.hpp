#pragma once

#include "NiPlane.hpp"
#include "NiTransform.hpp"
#include "NiFrustum.hpp"

class NiCamera;

class NiFrustumPlanes {
public:
	NiFrustumPlanes() {
		m_uiActivePlanes = 63;
	}

	enum ActivePlanes {
		NEAR_PLANE		= 0,
		FAR_PLANE		= 1,
		LEFT_PLANE		= 2,
		RIGHT_PLANE		= 3,
		TOP_PLANE		= 4,
		BOTTOM_PLANE	= 5,
		MAX_PLANES		= 6
	};

	NiPlane		m_akCullingPlanes[MAX_PLANES];
	uint32_t	m_uiActivePlanes;

	void Set(const NiFrustum& arFrustum, const NiTransform& arTransform);

	void Set(const NiCamera* apCamera);

	void SetPlane(uint32_t aePlane, const NiPlane& arPlane);

	const NiPlane& GetPlane(uint32_t ePlane) const;
	bool IsPlaneActive(uint32_t ePlane) const;
	bool IsAnyPlaneActive() const;
	void EnablePlane(uint32_t ePlane);
	void DisablePlane(uint32_t ePlane);
	void SetActivePlaneState(uint32_t uiState);
};

ASSERT_SIZE(NiFrustumPlanes, 0x64);