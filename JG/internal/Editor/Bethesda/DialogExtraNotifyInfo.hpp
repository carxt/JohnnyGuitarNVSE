#pragma once

#include "Bethesda/BSExtraData.hpp"

class TESForm;

class DialogExtraNotifyInfo : public BSExtraData {
public:
	HWND		hDialog;
	TESForm*	pOwner;

	BSEXTRA_TYPE(DialogExtraNotifyInfo);
};

ASSERT_SIZE(DialogExtraNotifyInfo, 0x14);