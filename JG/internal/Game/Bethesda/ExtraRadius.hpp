#pragma once

#include "BSExtraData.hpp"

class ExtraRadius : public BSExtraData {
public:
	ExtraRadius();
	~ExtraRadius();

	float fRadius;

	BSEXTRA_TYPE(ExtraRadius);
};

ASSERT_SIZE(ExtraRadius, 0x10);