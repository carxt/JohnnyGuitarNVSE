#pragma once

#include "BSExtraData.hpp"

class TESObjectREFR;

class ExtraItemDropper : public BSExtraData {
public:
	ExtraItemDropper();
	~ExtraItemDropper();

	TESObjectREFR *pDropper;

	BSEXTRA_TYPE(ExtraItemDropper);
};

ASSERT_SIZE(ExtraItemDropper, 0x10);