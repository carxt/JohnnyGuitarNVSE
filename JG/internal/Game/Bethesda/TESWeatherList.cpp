#include "TESWeatherList.hpp"

// GAME - 0x5822C0
// GECK - 0x664A80
TESWeatherList::TESWeatherList() {
#ifdef GAME
	ThisCall(0x5822C0, this);
#else
	ThisCall(0x664A80, this);
#endif
}

// GAME - 0x582320
// GECK - 0x664B10
TESWeatherList::~TESWeatherList() {
#ifdef GAME
	ThisCall(0x582320, this);
#else
	ThisCall(0x664B10, this);
#endif
}

// GAME - 0x5827D0
// GECK - 0x664280
TESWeather* TESWeatherList::GetRandomWeather() const {
#ifdef GAME
	return ThisCall<TESWeather*>(0x5827D0, this);
#else
	return ThisCall<TESWeather*>(0x664280, this);
#endif
}

// GAME - 0x582780
// GECK - 0x664250
void TESWeatherList::FlushList() {
#ifdef GAME
	ThisCall(0x582780, this);
#else
	ThisCall(0x664250, this);
#endif
}
