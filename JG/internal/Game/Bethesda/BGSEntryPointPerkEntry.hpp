#pragma once

#include "BGSPerkEntry.hpp"

class BGSEntryPointFunctionData;
class TESCondition;

class BGSEntryPointPerkEntry : public BGSPerkEntry {
public:
	BGSEntryPointPerkEntry();
	~BGSEntryPointPerkEntry();

	uint8_t						ucEntryPoint;
	uint8_t						ucFunction;
	uint8_t						ucNumConditions;
	BGSEntryPointFunctionData*	pFunctionData;
	TESCondition*				pConditionsArray;
};

ASSERT_SIZE(BGSEntryPointPerkEntry, 0x14);