#include "TESWeather.hpp"

const Bitfield<TESWeather::_WeatherDataFlags>& TESWeather::GetWeatherFlags() const {
	return *reinterpret_cast<const Bitfield<_WeatherDataFlags>*>(&ucWeatherData[WD_FLAGS]);
}

Bitfield<TESWeather::_WeatherDataFlags>& TESWeather::GetWeatherFlags() {
	return *reinterpret_cast<Bitfield<_WeatherDataFlags>*>(&ucWeatherData[WD_FLAGS]);
}

// GAME - 0x59E7D0
bool TESWeather::IsPleasant() const {
	return GetWeatherFlags().bPleasant;
}

// GAME - 0x59E8C0
bool TESWeather::IsCloudy() const {
	return GetWeatherFlags().bCloudy;
}

// GAME - 0x4ED270
bool TESWeather::IsRainy() const {
	return GetWeatherFlags().bRainy;
}

// GAME - 0x59EB40
bool TESWeather::IsSnowy() const {
	return GetWeatherFlags().bSnowy;
}

// GAME - 0x4ED230
double TESWeather::GetWeatherData(WeatherData aeData, float afMax, float afMin) const {
    return (ucWeatherData[aeData] * (1 / 255) * (afMax - afMin) + afMin);
}

// GAME - 0x63DD50
uint8_t TESWeather::GetWeatherDataRaw(WeatherData aeData) const {
	return ucWeatherData[aeData];
}

// GAME - 0x63BB40
uint32_t TESWeather::GetColor(COLOR_TYPE aeColorType, COLOR_TIME aeColorTime) const {
    return uiColorData[aeColorType][aeColorTime];
}