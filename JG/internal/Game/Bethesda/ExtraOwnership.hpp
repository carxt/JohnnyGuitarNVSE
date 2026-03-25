#pragma once

#include "BSExtraData.hpp"

class TESForm;

class ExtraOwnership : public BSExtraData {
public:
	ExtraOwnership();
	~ExtraOwnership();

	TESForm *pOwner;

	BSEXTRA_TYPE(ExtraOwnership);
};

ASSERT_SIZE(ExtraOwnership, 0x10);