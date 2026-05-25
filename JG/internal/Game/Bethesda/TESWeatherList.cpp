#include "TESWeatherList.hpp"

// GAME - 0x5822C0
TESWeatherList::TESWeatherList() {
	ThisCall(0x5822C0, this);
}

// GAME - 0x582320
TESWeatherList::~TESWeatherList() {
	ThisCall(0x582320, this);
}

// GAME - 0x582780
void TESWeatherList::FlushList() {
	ThisCall(0x582780, this);
}
