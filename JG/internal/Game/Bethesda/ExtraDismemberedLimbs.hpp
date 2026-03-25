#pragma once

#include "BSExtraData.hpp"
#include "DismemberedLimb.hpp"

class TESForm;

class ExtraDismemberedLimbs : public BSExtraData {
public:
	ExtraDismemberedLimbs();
	~ExtraDismemberedLimbs();

	uint16_t						usLimbs;
	int								eCauseOfDeath;
	TESForm*						pDeathObject;
	int								eKillingBlowLimb;
	bool							bEaten;
	BSSimpleArray<DismemberedLimb*>	kDismemberedLimbs;

	BSEXTRA_TYPE(ExtraDismemberedLimbs);
};

ASSERT_SIZE(ExtraDismemberedLimbs, 0x30);