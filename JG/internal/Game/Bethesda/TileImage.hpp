#pragma once

#include "Tile.hpp"

class NiTexture;
class TileShaderProperty;

class TileImage : public Tile {
public:
	float							fScale;
	NiPointer<NiTexture>			spTexture;
	NiPointer<TileShaderProperty>	spShaderProp;
	bool							bIsScissor;
};

ASSERT_SIZE(TileImage, 0x48);