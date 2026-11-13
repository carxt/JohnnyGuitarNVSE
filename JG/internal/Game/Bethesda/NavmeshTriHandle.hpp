#pragma once

class NavMeshInfo;

class NavmeshTriHandle {
public:
	NavMeshInfo*	pNavMeshInfo	= nullptr;
	uint16_t		usTriangle		= UINT16_MAX;
};

ASSERT_SIZE(NavmeshTriHandle, 0x8);