#pragma once

class CombatTimer {
public:
	float fStartTime	= 0.f;
	float fTargetTime	= 0.f;

	static float GetGlobalTimer();

	void Reset(float afTargetTime);

	void ForceTrigger();

	float GetElapsedTime() const;

	bool Check() const;
};

ASSERT_SIZE(CombatTimer, 0x8);