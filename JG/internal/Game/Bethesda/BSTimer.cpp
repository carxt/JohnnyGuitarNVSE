#include "BSTimer.hpp"

// GAME - 0x825C00
uint32_t BSTimer::GetTime() const {
	return uiLastTime;
}

// GAME - 0x7013E0
float BSTimer::GetRealTimeSeconds() const {
	return ThisCall<float>(0x7013E0, this);
}

// GAME - 0xAA4DB0
void BSTimer::SetGlobalTimeMultiplier(float afMult, bool abNow) {
#ifdef GAME
	ThisCall(0xAA4DB0, this, afMult, abNow);
#endif
}

// GAME - 0x716440
float BSTimer::GetGlobalTimeMultiplier() {
#ifdef GAME
	return *reinterpret_cast<float*>(0x11AC3A0);
#else
	return *reinterpret_cast<float*>(0xEB74DC);
#endif
}

// GAME - 0x9443F0
float BSTimer::GetGlobalTimeMultiplierTarget() {
#ifdef GAME
	return *reinterpret_cast<float*>(0x11AC3A4);
#endif
}