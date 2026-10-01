#pragma once

#include "Bethesda/BSExtraData.hpp"

class ColorControlData;

class DialogExtraColorControl : public BSExtraData {
public:
	ColorControlData*	pData;
	uint32_t			uiDialogID;

	BSEXTRA_TYPE(DialogExtraColorControl);
};

ASSERT_SIZE(DialogExtraColorControl, 0x14);

class ColorControlData {
public:
	HWND		hWindow;
	uint32_t	uiDialogIDs[8];
	bool		byte24;
};

ASSERT_SIZE(ColorControlData, 0x28u);