#pragma once

#include "TESForm.hpp"

class SpellItem;

class BGSRadiationStage : public TESForm {
public:
	BGSRadiationStage();
	~BGSRadiationStage();

	struct Data {
		uint32_t	uiThreshold;
		SpellItem*	pEffect;
	};

	Data kData;

	TESFORM_TYPE(BGSRadiationStage);
};

#ifdef GAME
ASSERT_SIZE(BGSRadiationStage, 0x20);
#else
ASSERT_SIZE(BGSRadiationStage, 0x34);
#endif