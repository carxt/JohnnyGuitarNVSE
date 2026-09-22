#pragma once

#include "Bethesda/BSExtraData.hpp"

class TESPreviewControl;

class DialogExtraPreviewControl : public BSExtraData {
public:
	TESPreviewControl*	pPreviewControl;
	uint32_t			uiUnk10;

	BSEXTRA_TYPE(DialogExtraPreviewControl);
};

ASSERT_SIZE(DialogExtraPreviewControl, 0x14);