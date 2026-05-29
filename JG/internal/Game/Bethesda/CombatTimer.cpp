#include "CombatTimer.hpp"

float CombatTimer::GetGlobalTimer() {
#ifdef GAME
    return *reinterpret_cast<float*>(0x11F1BF0);
#else
	FUNCTION_NOT_IMPLEMENTED
#endif
}

// GAME - 0x8D7F40
void CombatTimer::Reset(float afTargetTime) {
#ifdef GAME
	fStartTime = GetGlobalTimer();
	fTargetTime = afTargetTime;
#else
	FUNCTION_NOT_IMPLEMENTED
#endif
}

// GAME - 0x97F220
void CombatTimer::ForceTrigger() {
#ifdef GAME
	fTargetTime = -1.f;
#else
	FUNCTION_NOT_IMPLEMENTED
#endif
}

float CombatTimer::GetElapsedTime() const {
#ifdef GAME
	return GetGlobalTimer() - fStartTime;
#else
	FUNCTION_NOT_IMPLEMENTED
#endif
}

// GAME - 0x8D7F80
bool CombatTimer::Check() const {
#ifdef GAME
	return fTargetTime < GetElapsedTime();
#else
	FUNCTION_NOT_IMPLEMENTED
#endif
}
