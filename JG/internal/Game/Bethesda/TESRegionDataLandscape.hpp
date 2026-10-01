#pragma once

#include "TESRegionData.hpp"

class TESTexture;

class TESRegionDataLandscape : public TESRegionData {
public:
	TESRegionDataLandscape();
	~TESRegionDataLandscape();

	TESTexture* pCanopyShadowTexture;
};

ASSERT_SIZE(TESRegionDataLandscape, 0xC)