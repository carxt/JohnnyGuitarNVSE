#pragma once

class CombatTimeStamp {
public:
	CombatTimeStamp() = default;
	CombatTimeStamp(float afTimeStamp) : fTimeStamp(afTimeStamp) {}

	float fTimeStamp = 0.f;

	float GetElapsedTime() const;
	float DisplayElapsedTime() const;
};

ASSERT_SIZE(CombatTimeStamp, 0x4);