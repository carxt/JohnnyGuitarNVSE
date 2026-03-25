#pragma once

#include "SeenData.hpp"

class IntSeenData : public SeenData {
public:
	int8_t			cSectionX;
	int8_t			cSectionY;
	bool			bFullySeen;
	IntSeenData*	pNextSection;
};

ASSERT_SIZE(IntSeenData, 0x2C);