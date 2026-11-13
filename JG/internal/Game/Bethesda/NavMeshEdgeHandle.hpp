#pragma once

#include "NavmeshTriHandle.hpp"

class NavMeshEdgeHandle : public NavmeshTriHandle {
public:
	int32_t iEdgeIndex;
};

ASSERT_SIZE(NavMeshEdgeHandle, 0xC);