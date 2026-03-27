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

ASSERT_SIZE(BGSHungerStage, 0x20);