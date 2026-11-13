#pragma once

#include "Bethesda/BSExtraData.hpp"

class DialogExtraFactionData : public BSExtraData {
public:
	DWORD dwordC;
	DWORD dword10;

	BSEXTRA_TYPE(DialogExtraFactionData);
};

ASSERT_SIZE(DialogExtraFactionData, 0x14);