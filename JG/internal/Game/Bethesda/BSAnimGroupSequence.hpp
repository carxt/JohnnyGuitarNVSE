#pragma once

#include "Gamebryo/NiControllerSequence.hpp"

class TESAnimGroup;

class BSAnimGroupSequence : public NiControllerSequence {
public:
	BSAnimGroupSequence();
	virtual ~BSAnimGroupSequence();

	NiPointer<TESAnimGroup> spAnimGroup;

	TESAnimGroup* GetAnimGroup() const;

	void CopyMembers(BSAnimGroupSequence* apOther, NiCloningProcess* apCloning);

	float GetScaledTime(float afTime);
};

ASSERT_SIZE(BSAnimGroupSequence, 0x78);