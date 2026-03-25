#pragma once

#include "BSExtraData.hpp"

class TESCombatStyle;

class ExtraCombatStyle : public BSExtraData {
public:
	ExtraCombatStyle();
	~ExtraCombatStyle();

	TESCombatStyle* pCombatStyle;

	BSEXTRA_TYPE(ExtraCombatStyle);
};

ASSERT_SIZE(ExtraCombatStyle, 0x10);