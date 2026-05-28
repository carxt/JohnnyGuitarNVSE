#pragma once

class BSDegradePriority {
public:
	enum State : uint8_t {
		NONE		= 0,
		DEGRADING	= 1,
		UPGRADING	= 2,
		DEGRADED	= 3,
		UPGRADED	= 4,
	};

	uint8_t ucPriorityL;
	uint8_t ucPriorityH;
	uint8_t ucPriorityC;
	uint8_t ucState;
};

ASSERT_SIZE(BSDegradePriority, 0x4);