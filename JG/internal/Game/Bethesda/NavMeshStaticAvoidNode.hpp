#pragma once

#include "PathingAvoidNode.hpp"

class NavMeshStaticAvoidNode : public PathingAvoidNode {
public:
	uint16_t usTriangle = UINT16_MAX;
};

ASSERT_SIZE(NavMeshStaticAvoidNode, 0x28);