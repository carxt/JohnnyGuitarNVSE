#pragma once

#include "Tile.hpp"

class TileRect : public Tile {
public:
	bool bIsScissor;
};

ASSERT_SIZE(TileRect, 0x3C);