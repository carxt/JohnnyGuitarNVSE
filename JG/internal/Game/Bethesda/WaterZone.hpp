#pragma once

#include "ZoneEntry.hpp"

class PlaceableWaterGroup;

class WaterZone : public ZoneEntry {
public:
	float					fWaterHeight;
	PlaceableWaterGroup*	pGroup;
};

ASSERT_SIZE(WaterZone, 0x20);