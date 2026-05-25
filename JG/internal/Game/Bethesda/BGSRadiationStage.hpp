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

ASSERT_SIZE(BGSRadiationStage, 0x20);