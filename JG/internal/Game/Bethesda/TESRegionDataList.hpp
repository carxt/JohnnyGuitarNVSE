#pragma once

#include "BSSimpleList.hpp"
#include "TESRegionData.hpp"

class TESRegionDataList : public BSSimpleList<TESRegionData*> {
public:
	bool bOwnsDataMemory;

	bool Add(TESRegionData* apData);

	void Clear();

	TESRegionData* Find(REGION_DATA_ID aeID) const;
};

ASSERT_SIZE(TESRegionDataList, 0xC);