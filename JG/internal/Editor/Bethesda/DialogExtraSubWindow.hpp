#pragma once

#include "Bethesda/BSExtraData.hpp"

class SubWindow;

class DialogExtraSubWindow : public BSExtraData {
public:
	SubWindow*	pSubWindow;
	DWORD		dword10;

	BSEXTRA_TYPE(DialogExtraSubWindow);
};

ASSERT_SIZE(DialogExtraSubWindow, 0x14);