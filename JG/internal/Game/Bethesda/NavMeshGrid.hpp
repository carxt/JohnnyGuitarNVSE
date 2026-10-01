#pragma once

#include "Gamebryo/NiPoint3.hpp"
#include "BSSimpleArray.hpp"

class NavMeshGrid {
public:
	uint32_t					uiGridSize;
	float						fColumnSectionLen;
	float						fRowSectionLen;
	NiPoint3					kGridBoundsMin;
	NiPoint3					kGridBoundsMax;
	BSSimpleArray<uint16_t>*	pGridData;
};

ASSERT_SIZE(NavMeshGrid, 0x28);