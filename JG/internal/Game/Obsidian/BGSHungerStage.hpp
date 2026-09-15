#pragma once

#include "Bethesda/TESForm.hpp"

class SpellItem;

class BGSHungerStage : public TESForm {
public:
	BGSHungerStage();
	~BGSHungerStage();

	struct Data {
		uint32_t	uiThreshold;
		SpellItem*	pEffect;
	};

	Data kData;

	TESFORM_TYPE(BGSHungerStage);
};

#ifdef GAME
ASSERT_SIZE(BGSHungerStage, 0x20);
#else
ASSERT_SIZE(BGSHungerStage, 0x34);
#endif