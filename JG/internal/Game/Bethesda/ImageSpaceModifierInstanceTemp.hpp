#pragma once

#include "ImageSpaceModifierInstance.hpp"

class ImageSpaceModifierInstanceTemp : public ImageSpaceModifierInstance {
public:
	ImageSpaceModifierInstanceTemp();
	virtual ~ImageSpaceModifierInstanceTemp();

	float fDuration;
};

ASSERT_SIZE(ImageSpaceModifierInstanceTemp, 0x20);