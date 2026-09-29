#pragma once

#include "MobileObjectTaskletData.hpp"

// Unused
class ActorUpdateTaskData : public MobileObjectTaskletData {
public:
	uint32_t uiRunCount;
};

ASSERT_SIZE(ActorUpdateTaskData, 0x3C);