#pragma once

#include "Bethesda/BSExtraData.hpp"

class TESForm;

class DialogExtraLocalCopy : public BSExtraData {
public:
	TESForm* pCopiedForm;

	BSEXTRA_TYPE(DialogExtraLocalCopy);
};

ASSERT_SIZE(DialogExtraLocalCopy, 0x10);