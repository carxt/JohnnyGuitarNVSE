#pragma once

#include "Bethesda/TESForm.hpp"

class SpellItem;

class BGSDehydrationStage : public TESFormBase {
public:
	BGSDehydrationStage();
	~BGSDehydrationStage();

	struct Data {
		uint32_t	uiThreshold;
		SpellItem*	pEffect;
	};

	Data kData;

	TESFORM_TYPE(BGSDehydrationStage);
};

#ifdef GAME
ASSERT_SIZE(BGSDehydrationStage, 0x20);
#else
ASSERT_SIZE(BGSDehydrationStage, 0x34);
#endif