#pragma once

#include "BGSEntryPointFunctionData.hpp"

class BGSEntryPointFunctionDataOneValue : public BGSEntryPointFunctionData {
public:
	BGSEntryPointFunctionDataOneValue();
	~BGSEntryPointFunctionDataOneValue();

	float	fValue;
};

ASSERT_SIZE(BGSEntryPointFunctionDataOneValue, 0x8);