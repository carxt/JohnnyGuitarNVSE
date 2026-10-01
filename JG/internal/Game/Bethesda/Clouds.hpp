#pragma once

#include "SkyObject.hpp"
#include "Gamebryo/NiColor.hpp"

class NiGeometry;
class NiTexture;

class Clouds : public SkyObject {
public:
	NiPointer<NiGeometry>	spClouds[4];
	NiPointer<NiTexture>	spTransTexture[4];
	NiColor					kColors[4];
	uint16_t				usNumLayers;
	bool					bForceTransTextureUpdate;

	void ForceTransTextureUpdate();

	void ClearTransTextures();

	void RemoveTextures();
};

ASSERT_SIZE(Clouds, 0x5C);