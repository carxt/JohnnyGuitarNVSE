#pragma once

#include "Bethesda/BSExtraData.hpp"

class DialogExtraDialogData : public BSExtraData {
public:
	void* pData;

	BSEXTRA_TYPE(DialogExtraDialogData);
};

ASSERT_SIZE(DialogExtraDialogData, 0x10);