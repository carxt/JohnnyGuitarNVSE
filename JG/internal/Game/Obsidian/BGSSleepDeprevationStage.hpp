#pragma once

#include "Bethesda/TESForm.hpp"

class SpellItem;

// sic!
class BGSSleepDeprevationStage : public TESForm {
public:
	BGSSleepDeprevationStage();
	~BGSSleepDeprevationStage();

	struct Data {
		uint32_t	uiThreshold;
		SpellItem*	pEffect;
	};

	Data kData;

	TESFORM_TYPE(BGSSleepDeprevationStage);
};

ASSERT_SIZE(BGSSleepDeprevationStage, 0x20);