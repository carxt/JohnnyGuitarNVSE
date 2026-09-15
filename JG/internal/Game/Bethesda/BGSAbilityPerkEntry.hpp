#pragma once

#include "BGSPerkEntry.hpp"

class SpellItem;

class BGSAbilityPerkEntry : public BGSPerkEntry {
public:
	BGSAbilityPerkEntry();
	~BGSAbilityPerkEntry();

	SpellItem* pAbility;
};

ASSERT_SIZE(BGSAbilityPerkEntry, 0xC);