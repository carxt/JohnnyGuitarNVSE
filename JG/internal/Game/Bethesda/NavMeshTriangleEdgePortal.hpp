#pragma once

class NavMeshInfo;

class NavMeshTriangleEdgePortal {
public:
	NavMeshInfo*	pNavMeshInfo	= nullptr;
	uint16_t		usTriangleIndex = UINT16_MAX;
};

ASSERT_SIZE(NavMeshTriangleEdgePortal, 0x8);