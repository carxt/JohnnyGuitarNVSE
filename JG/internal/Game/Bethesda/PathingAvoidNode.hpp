#pragma once

#include "Gamebryo/NiPoint3.hpp"

class PathingAvoidNode {
public:
    enum Type {
        SPHERE          = 0,
        CYLINDER        = 1,
        SPHERE_ACTOR    = 2,
        SPHERE_TARGET   = 3,
        SPHERE_THREAT   = 4,
        SPHERE_OBSTACLE = 5
    };

	NiPoint3    kPoint1;
	NiPoint3    kPoint2;
	float       fRadius;
	float       fCost;
    Type        eType;
};

ASSERT_SIZE(PathingAvoidNode, 0x24);