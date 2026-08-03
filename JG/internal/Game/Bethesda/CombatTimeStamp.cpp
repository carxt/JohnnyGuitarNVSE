#include "CombatTimeStamp.hpp"
#ifdef GAME
#include "CombatTimer.hpp"

// GAME - 0x435E00
float CombatTimeStamp::GetElapsedTime() const {
	return CombatTimer::GetGlobalTimer() - fTimeStamp;
}

// GAME - 0x97FA90
float CombatTimeStamp::DisplayElapsedTime() const {
	float fElapsedTime = GetElapsedTime();
	if (fElapsedTime <= 1000.f)
		return fElapsedTime;
	else
		return 1000.f;
}
#endif