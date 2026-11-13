#pragma once

#include "TESTextureList.hpp"

class TESTextureListArray {
public:
	uint32_t		 uiTextureCount;
	TESTextureList** ppTextures;

	TESTextureList* GetAt(uint32_t auiIndex) const;
};

ASSERT_SIZE(TESTextureListArray, 0x8);