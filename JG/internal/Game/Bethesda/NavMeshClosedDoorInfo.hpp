#pragma once

#include "BSEnums.hpp"

class NavMeshClosedDoorInfo {
public:
	FormID		uiDoorFormID	= 0;
	uint16_t	usTriangleIndex = UINT16_MAX;
};

ASSERT_SIZE(NavMeshClosedDoorInfo, 0x8);