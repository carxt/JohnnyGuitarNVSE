#pragma once

#include "MobileObjectTaskletData.hpp"

// Unused
class DetectionTaskData : public MobileObjectTaskletData {
public:
	float		fNumber;
	int32_t		iUpdated;
};

ASSERT_SIZE(DetectionTaskData, 0x40);