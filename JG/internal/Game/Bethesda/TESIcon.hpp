#pragma once

#include "TESTexture.hpp"

class TESIcon : public TESTexture {
public:
	TESIcon();
	~TESIcon();
};

ASSERT_SIZE(TESIcon, 0xC);