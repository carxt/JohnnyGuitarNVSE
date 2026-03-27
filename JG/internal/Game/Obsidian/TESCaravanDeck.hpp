#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"

class TESCaravanCard;

class TESCaravanDeck : public TESForm, public TESFullName {
public:
	TESCaravanDeck();
	~TESCaravanDeck();

	BSSimpleList<TESCaravanCard*>*	pCards;
	uint32_t						uiCount;

	TESFORM_TYPE(TESCaravanDeck);
};

ASSERT_SIZE(TESCaravanDeck, 0x2C);