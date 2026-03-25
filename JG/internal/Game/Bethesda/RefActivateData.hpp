#pragma once

class TESObjectREFR;

class RefActivateData {
public:
	TESObjectREFR*	pActivateRef;
	float			fActivateDelay;
};

ASSERT_SIZE(RefActivateData, 0x8);