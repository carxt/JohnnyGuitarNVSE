#pragma once

#include "SkyObject.hpp"

class Stars : public SkyObject {
public:
	NiPointer<NiNode>	spStars;
	float				fAlpha;
};

ASSERT_SIZE(Stars, 0x10);