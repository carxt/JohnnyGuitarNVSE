#pragma once

#include "Tile.hpp"

class TileText : public Tile {
public:
	float		fTextWidth;
	NiPoint3	kOffset;
	bool		bIsHyper;
};

ASSERT_SIZE(TileText, 0x4C);