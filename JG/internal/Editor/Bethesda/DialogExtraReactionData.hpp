#pragma once

#include "Bethesda/BSExtraData.hpp"

class DialogExtraReactionData : public BSExtraData {
public:
	DWORD dwordC;
	DWORD dword10;

	BSEXTRA_TYPE(DialogExtraReactionData);
};

ASSERT_SIZE(DialogExtraReactionData, 0x14);