#pragma once

#include "TESRegionData.hpp"
#include "TESRegionGrassObjectList.hpp"

class TESRegionDataGrass : public TESRegionData {
public:
	TESRegionDataGrass();
	~TESRegionDataGrass();

	TESRegionGrassObjectList* pObjects;
};

ASSERT_SIZE(TESRegionDataGrass, 0xC)