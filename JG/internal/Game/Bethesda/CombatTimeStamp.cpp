#include "CombatTimeStamp.hpp"
#include "CombatTimer.hpp"

// GAME - 0x435E00
float CombatTimeStamp::GetElapsedTime() const {
#ifdef GAME
	return CombatTimer::GetGlobalTimer() - fTimeStamp;
#else
	FUNCTION_NOT_IMPLEMENTED
#endif
}

// GAME - 0x97FA90
float CombatTimeStamp::DisplayElapsedTime() const {
#ifdef GAME
	float fElapsedTime = GetElapsedTime();
	if (fElapsedTime <= 1000.f)
		return fElapsedTime;
	else
		return 1000.f;
#else
	FUNCTION_NOT_IMPLEMENTED
#endif
}
