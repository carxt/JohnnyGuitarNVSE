#pragma once

#include "MobileObjectTaskletData.hpp"

// Unused
class MovementTaskData : public MobileObjectTaskletData {
public:
	uint32_t uiRunCount;
};

ASSERT_SIZE(MovementTaskData, 0x3C);