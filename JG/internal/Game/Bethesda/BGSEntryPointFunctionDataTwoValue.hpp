#pragma once

#include "BGSEntryPointFunctionData.hpp"

class BGSEntryPointFunctionDataTwoValue : public BGSEntryPointFunctionData {
public:
	BGSEntryPointFunctionDataTwoValue();
	virtual ~BGSEntryPointFunctionDataTwoValue();

	float fValues[2];
};

ASSERT_SIZE(BGSEntryPointFunctionDataTwoValue, 0xC);