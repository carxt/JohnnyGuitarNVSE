#pragma once

#include "Bethesda/BSSimpleList.hpp"

class TESCellUse;

class TESCellUseList : public BSSimpleList<TESCellUse*> {
public:
};

ASSERT_SIZE(TESCellUseList, 0x8);

class TESObjectCELL;

class TESCellUse {
public:
	TESObjectCELL*	pCell;
	uint32_t		uiUses;
};

ASSERT_SIZE(TESCellUse, 0x8);