#pragma once

#include "Bethesda/BSExtraData.hpp"

class DialogExtraTimer : public BSExtraData {
public:
	HWND		hWindow;
	UINT_PTR	uiTimer;
	DWORD		dword14;

	BSEXTRA_TYPE(DialogExtraTimer);
};

ASSERT_SIZE(DialogExtraTimer, 0x18);