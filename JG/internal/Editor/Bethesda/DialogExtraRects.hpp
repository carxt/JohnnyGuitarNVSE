#pragma once

#include "Bethesda/BSExtraData.hpp"

class DialogExtraRects : public BSExtraData {
public:
	RECT		kClientRect;
	RECT		kRect2;
	RECT		kRect3;
	uint32_t	uiWidth;
	uint32_t	uiHeight;

	BSEXTRA_TYPE(DialogExtraRects);
};

ASSERT_SIZE(DialogExtraRects, 0x44);