#include "CombatTimer.hpp"

#ifdef GAME
float CombatTimer::GetGlobalTimer() {
    return *reinterpret_cast<float*>(0x11F1BF0);
}

// GAME - 0x8D7F40
void CombatTimer::Reset(float afTargetTime) {
	fStartTime = GetGlobalTimer();
	fTargetTime = afTargetTime;
}

// GAME - 0x97F220
void CombatTimer::ForceTrigger() {
	fTargetTime = -1.f;
}

float CombatTimer::GetElapsedTime() const {
	return GetGlobalTimer() - fStartTime;
}

// GAME - 0x8D7F80
bool CombatTimer::Check() const {
	return fTargetTime < GetElapsedTime();
}
#endif