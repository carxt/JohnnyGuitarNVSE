#pragma once

#include "Bethesda/BSExtraData.hpp"

class RefSelectControl;

class DialogExtraRefSelectControl : public BSExtraData {
public:
	RefSelectControl*	pControl;
	DWORD				dword10;

	BSEXTRA_TYPE(DialogExtraRefSelectControl);
};

ASSERT_SIZE(DialogExtraRefSelectControl, 0x14);