#pragma once

#include "Gamebryo/NiObject.hpp"
#include "Gamebryo/NiPoint2.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "Gamebryo/NiColorA.hpp"
#include "Gamebryo/NiMatrix3.hpp"
#include "Gamebryo/NiFrustumPlanes.hpp"
#include "BSMultiBoundShape.hpp"

class BSOcclusionPlane : public NiObject {
public:
	virtual uint32_t	GetDebugGeomLineSize() const;
	virtual uint32_t	GetDebugGeomShapeSize() const;

	NiPoint3				kCenter;
	NiPoint2				kHalfExtents;
	NiMatrix3				kRotation;
	BS_CULL_RESULT			eCullResult;
	NiFrustumPlanes			kCachedPlanes;
	NiPoint3				kCachedVertices[4];
	NiPoint3				kViewPoint;
	bool					bDirtyVertices;
	bool					bDirtyPlanes;
	bool					bDisabledPlanes[4];
	bool					bTwoSided;
	BSOcclusionPlane*		pLinkedPlanes[4];

	NIRTTI_ADDRESS(0x1202804);
};

ASSERT_SIZE(BSOcclusionPlane, 0xFC)