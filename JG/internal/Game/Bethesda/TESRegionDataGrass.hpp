#pragma once

#include "TESRegionData.hpp"

class TESRegionGrassObjectList;

class TESRegionDataGrass : public TESRegionData {
public:
	TESRegionDataGrass();
	~TESRegionDataGrass();

	TESRegionGrassObjectList* pObjects;
};

ASSERT_SIZE(TESRegionDataGrass, 0xC)