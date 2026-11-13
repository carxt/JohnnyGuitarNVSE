#pragma once

#include "Bethesda/TESForm.hpp"
#include "Bethesda/TESFullName.hpp"

class TESCaravanCard;

class TESCaravanDeck : public TESForm, public TESFullName {
public:
	TESCaravanDeck();
	~TESCaravanDeck();

	struct Data {
		int32_t iDeckSize;
	};

	BSSimpleList<TESCaravanCard*>*	pDeck;
	Data							kData;

	TESFORM_TYPE(TESCaravanDeck);

	BSSimpleList<TESCaravanCard*>* GetCaravanDeck() const;
};

#ifdef GAME
ASSERT_SIZE(TESCaravanDeck, 0x2C);
#else
ASSERT_SIZE(TESCaravanDeck, 0x40);
#endif