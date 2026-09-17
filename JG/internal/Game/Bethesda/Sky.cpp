#include "Sky.hpp"
#include "TESClimate.hpp"

Sky* Sky::GetSingleton() {
#ifdef GAME
	return *reinterpret_cast<Sky**>(0x11DEA20);
#else
	return *reinterpret_cast<Sky**>(0xEDF1DC);
#endif
}

Sun* Sky::GetSun() const {
	return pSun;
}

#ifdef GAME
// GAME - 0x59E950
bool Sky::IsRaining() const {
	return ThisCall<bool>(0x59E950, this);
}

// GAME - 0x59EA80
bool Sky::IsSnowing() const {
	return ThisCall<bool>(0x59EA80, this);
}
#endif

// GAME - 0x63D0E0
// GECK - 0x683310
void Sky::ForceWeather(TESWeather* apWeather, bool abOverride) {
#ifdef GAME
	ThisCall(0x63D0E0, this, apWeather, abOverride);
#else
	ThisCall(0x683310, this, apWeather, abOverride);
#endif
}

// GAME - 0x63C8F0
// GECK - 0x6837F0
void Sky::SetCurrentClimate(TESClimate* apClimate, bool abForce) {
#ifdef GAME
	ThisCall(0x63C8F0, this, apClimate, abForce);
#else
	ThisCall(0x6837F0, this, apClimate, abForce);
#endif
}

// GAME - 0x595EA0
// GECK - 0x6803A0
float Sky::GetSunriseBegin() {
#ifdef GAME
	return ThisCall<float>(0x595EA0, this);
#else
	return ThisCall<float>(0x6803A0, this);
#endif
}

// GAME - 0x595F50
// GECK - 0x6803E0
float Sky::GetSunriseEnd() {
#ifdef GAME
	return ThisCall<float>(0x595F50, this);
#else
	return ThisCall<float>(0x6803E0, this);
#endif
}

// GAME - 0x595FC0
// GECK - 0x680420
float Sky::GetSunsetBegin() {
#ifdef GAME
	return ThisCall<float>(0x595FC0, this);
#else
	return ThisCall<float>(0x680420, this);
#endif
}

// GAME - 0x596030
// GECK - 0x680460
float Sky::GetSunsetEnd() {
#ifdef GAME
	return ThisCall<float>(0x596030, this);
#else
	return ThisCall<float>(0x680460, this);
#endif
}

// GAME - 0x63D060
// GECK - 0x6832B0
void Sky::ResetWeather() {
#ifdef GAME
	ThisCall(0x63D060, this);
#else
	ThisCall(0x6832B0, this);
#endif
}

float Sky::CalculateMoonPhase(float afDayPassed) const {
	return (fmodf(afDayPassed, pCurrentClimate->GetMoonPhaseDays() * 8)) / (pCurrentClimate->GetMoonPhaseDays());
}

#ifdef GAME
// GAME - 0x63DDB0
void Sky::ActivateWeatherSounds(TESWeather* apWeather) {
	ThisCall(0x63DDB0, this, apWeather);
}
#endif

// GAME - 0x63E2F0
// GECK - 0x6824E0
void Sky::ReloadAllTextures() {
#ifdef GAME
	ThisCall(0x63E2F0, this);
#else
	ThisCall(0x6824E0, this);
#endif
}

// GAME - 0x63E210
// GECK - 0x681030
void Sky::UnloadAllTextures() {
#ifdef GAME
	ThisCall(0x63E210, this);
#else
	ThisCall(0x681030, this);
#endif
}

// GAME - 0x63AC70
// GECK - 0x683620
void Sky::Update(float afDelta) {
#ifdef GAME
	ThisCall(0x63AC70, this, afDelta);
#else
	ThisCall(0x683620, this, afDelta);
#endif
}

// GAME - 0x63EF20
// GECK - 0x682AD0
void Sky::UpdateHDRValues() {
#ifdef GAME
	ThisCall(0x63EF20, this);
#else
	ThisCall(0x682AD0, this);
#endif
}

const NiColorA& Sky::GetBlendColor(uint32_t auiID) {
	return kBlendColors[auiID];
}