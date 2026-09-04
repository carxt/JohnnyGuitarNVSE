#pragma once

#include "TESTexture.hpp"

class TESIcon : public TESTexture {
public:
	TESIcon();
	~TESIcon();
};

#ifdef GAME
ASSERT_SIZE(TESIcon, 0xC);
#else
ASSERT_SIZE(TESIcon, 0x1C);
#endif