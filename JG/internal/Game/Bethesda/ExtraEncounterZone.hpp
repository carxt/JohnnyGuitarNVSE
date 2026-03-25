#pragma once

#include "BSExtraData.hpp"

class BGSEncounterZone;

class ExtraEncounterZone : public BSExtraData {
public:
	ExtraEncounterZone();
	~ExtraEncounterZone();

	BGSEncounterZone *pZone;

	BSEXTRA_TYPE(ExtraEncounterZone);
};

ASSERT_SIZE(ExtraEncounterZone, 0x10);