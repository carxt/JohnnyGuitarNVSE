#pragma once

#include "Bethesda/BSExtraData.hpp"

class TESForm;

class DialogExtraParam : public BSExtraData {
public:
	uint32_t	dwordC;
	TESForm*	pForm;
	DWORD		dword14;

	BSEXTRA_TYPE(DialogExtraParam);
};

ASSERT_SIZE(DialogExtraParam, 0x18);