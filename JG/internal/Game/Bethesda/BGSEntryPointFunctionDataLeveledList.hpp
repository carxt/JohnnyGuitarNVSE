#pragma once

#include "BGSEntryPointFunctionData.hpp"

class TESLevItem;

class BGSEntryPointFunctionDataLeveledList : public BGSEntryPointFunctionData {
public:
	BGSEntryPointFunctionDataLeveledList();
	~BGSEntryPointFunctionDataLeveledList();

	TESLevItem* pList;
};

ASSERT_SIZE(BGSEntryPointFunctionDataLeveledList, 0x8);