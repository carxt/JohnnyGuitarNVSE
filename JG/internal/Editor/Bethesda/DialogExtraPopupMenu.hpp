#pragma once

#include "Bethesda/BSExtraData.hpp"

class DialogExtraPopupMenu : public BSExtraData {
public:
	HMENU hMenu;
	HMENU hSubMenu;
	DWORD dword14;
	DWORD dword18;

	BSEXTRA_TYPE(DialogExtraPopupMenu);
};

ASSERT_SIZE(DialogExtraPopupMenu, 0x1C);