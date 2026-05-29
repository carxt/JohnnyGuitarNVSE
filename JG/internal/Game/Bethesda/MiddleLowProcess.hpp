#pragma once

#include "LowProcess.hpp"

class MiddleLowProcess : public LowProcess {
public:
	MiddleLowProcess();
	~MiddleLowProcess();

	virtual bool	ProcessCombatOneHour(Actor* apActor, float);

	int32_t			iHourPackageEvaluated;
	ModifierList	kTemporaryModifiers;
};

ASSERT_SIZE(MiddleLowProcess, 0xC8);