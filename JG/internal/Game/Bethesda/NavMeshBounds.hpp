#pragma once

#include "BSSimpleArray.hpp"
#include "Gamebryo/NiPoint3.hpp"

class NavMeshBounds {
public:
	struct NavMeshBoundsTriangle {
		uint16_t	usVertices[3];
	};

	NiPoint3								kMin;
	NiPoint3								kMax;
	BSSimpleArray<NavMeshBoundsTriangle>	kBoundTriangles;
	BSSimpleArray<NiPoint3>					kPoints;
};

ASSERT_SIZE(NavMeshBounds, 0x38);
ASSERT_SIZE(NavMeshBounds::NavMeshBoundsTriangle, 0x6);