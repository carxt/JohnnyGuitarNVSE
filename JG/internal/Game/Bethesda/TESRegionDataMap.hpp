#pragma once

#include "TESRegionData.hpp"
#include "BSStringT.hpp"

class TESRegionDataMap : public TESRegionData {
public:
	TESRegionDataMap();
	~TESRegionDataMap();

	BSString strMapName;
};

ASSERT_SIZE(TESRegionDataMap, 0x10)