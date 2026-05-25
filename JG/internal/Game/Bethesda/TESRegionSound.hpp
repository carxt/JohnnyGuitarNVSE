#pragma once

#include "BSMemObject.hpp"

class TESSound;

class TESRegionSound {
public:
	TESSound*	pSound;
	Bitfield32	uiFlags;
	uint32_t	uiChance;
};

ASSERT_SIZE(TESRegionSound, 0xC)