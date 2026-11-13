#pragma once

#include "Bethesda/TESRegionData.hpp"
#include "Bethesda/BSSimpleList.hpp"

class TESObjectREFR;

class TESRegionDataImposter : public TESRegionData {
public:
	TESRegionDataImposter();
	~TESRegionDataImposter();

	BSSimpleList<TESObjectREFR*> kObjects;
};

ASSERT_SIZE(TESRegionDataImposter, 0x10)