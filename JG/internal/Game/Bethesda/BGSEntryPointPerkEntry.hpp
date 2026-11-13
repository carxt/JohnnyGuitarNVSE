#pragma once

#include "BGSPerkEntry.hpp"

class BGSEntryPointFunctionData;
class TESCondition;

class BGSEntryPointPerkEntry : public BGSPerkEntry {
public:
	BGSEntryPointPerkEntry();
	~BGSEntryPointPerkEntry();

	struct Data {
		uint8_t ucEntryPoint;
		uint8_t ucFunction;
		uint8_t ucNumConditions;
	};

	Data						kData;
	BGSEntryPointFunctionData*	pFunctionData;
	TESCondition*				pConditionsArray;
};

ASSERT_SIZE(BGSEntryPointPerkEntry, 0x14);