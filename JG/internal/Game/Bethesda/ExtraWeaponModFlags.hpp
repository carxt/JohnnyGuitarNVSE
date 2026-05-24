#pragma once

#include "BSExtraData.hpp"

class ExtraWeaponModFlags : public BSExtraData {
public:
	ExtraWeaponModFlags();
	~ExtraWeaponModFlags();

	Bitfield8	ucWeaponModsActive;

	BSEXTRA_TYPE(ExtraWeaponModFlags);
};

ASSERT_SIZE(ExtraWeaponModFlags, 0x10);