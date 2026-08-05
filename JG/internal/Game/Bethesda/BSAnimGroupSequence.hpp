#pragma once

#include "Gamebryo/NiControllerSequence.hpp"

class TESAnimGroup;
class TESObjectREFR;

class BSAnimGroupSequence : public NiControllerSequence {
public:
	BSAnimGroupSequence();
	virtual ~BSAnimGroupSequence();

	NiPointer<TESAnimGroup> spAnimGroup;

	TESAnimGroup* GetAnimGroup() const;

	float GetScaledTime(float afTime);

	static bool PlaySounds(NiControllerSequence* apSequence, TESObjectREFR* apRef);
};

ASSERT_SIZE(BSAnimGroupSequence, 0x78);