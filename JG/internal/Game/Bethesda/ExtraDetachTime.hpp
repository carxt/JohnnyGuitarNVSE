#pragma once

#include "BSExtraData.hpp"

class ExtraDetachTime : public BSExtraData {
public:
	ExtraDetachTime();
	~ExtraDetachTime();

	uint32_t uiTime;

	BSEXTRA_TYPE(ExtraDetachTime);
};

ASSERT_SIZE(ExtraDetachTime, 0x10);