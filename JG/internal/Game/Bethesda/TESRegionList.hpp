#pragma once

#include "BSSimpleList.hpp"

class TESRegion;

class TESRegionList : public BSSimpleList<TESRegion*> {
public:
	TESRegionList();
	virtual ~TESRegionList();

	bool	bOwnsRegionMemory;
};

ASSERT_SIZE(TESRegionList, 0x10);