#include "TESWeather.hpp"

const Bitfield<TESWeather::_WeatherDataFlags>& TESWeather::GetWeatherFlags() const {
	return *reinterpret_cast<const Bitfield<_WeatherDataFlags>*>(&ucWeatherData[WeatherData::FLAGS]);
}

Bitfield<TESWeather::_WeatherDataFlags>& TESWeather::GetWeatherFlags() {
	return *reinterpret_cast<Bitfield<_WeatherDataFlags>*>(&ucWeatherData[WeatherData::FLAGS]);
}

// GAME - 0x6347A0
const TESTexture1024* TESWeather::GetCloudTexture(uint32_t auiLayer) const {
#ifdef GAME
	return ThisCall<TESTexture1024*>(0x6347A0, this, auiLayer);
#else
	return &kCloudTexture[auiLayer];
#endif
}

TESTexture1024* TESWeather::GetCloudTexture(uint32_t auiLayer) {
#ifdef GAME
	return ThisCall<TESTexture1024*>(0x6347A0, this, auiLayer);
#else
	return &kCloudTexture[auiLayer];
#endif
}

// GAME - 0x6347C0
float TESWeather::GetCloudLayerSpeed(uint32_t auiLayer, float afMax, float afMin) const {
#ifdef GAME
	return ThisCall<float>(0x6347C0, this, auiLayer, afMax, afMin);
#else
	uint8_t ucSpeed = 51;
	if (iNumCloudLayers > 0) {
		if (auiLayer >= iNumCloudLayers)
			auiLayer = 0;
		ucSpeed = ucCloudSpeed[auiLayer];
	}
	return (ucSpeed * (1.0 / 255.0) * (afMax - afMin) + afMin);
#endif
}

// GAME - 0x63BC60
// GECK - 0x680340
uint32_t TESWeather::GetCloudColor(uint32_t auiLayer, ColorTime aeTime) const {
#ifdef GAME
	return ThisCall<uint32_t>(0x63BC60, this, auiLayer, aeTime);
#else
	return ThisCall<uint32_t>(0x680340, this, auiLayer, aeTime);
#endif
}

// GAME - 0x6377E0
const TESModel* TESWeather::GetPrecipitationModel() const {
#ifdef GAME
	return ThisCall<const TESModel*>(0x6377E0, this);
#else
	return &kPrecipitationModel;
#endif
}

// GAME - 0x6377E0
TESModel* TESWeather::GetPrecipitationModel() {
#ifdef GAME
	return ThisCall<TESModel*>(0x6377E0, this);
#else
	return &kPrecipitationModel;
#endif
}

// GAME - 0x4ED230
float TESWeather::GetWeatherData(WeatherData aeData, float afMax, float afMin) const {
#ifdef GAME
	return ThisCall<float>(0x4ED230, this, aeData, afMax, afMin);
#else
	return (ucWeatherData[aeData] * (1.0 / 255.0) * (afMax - afMin) + afMin);
#endif
}

// GAME - 0x63DD50
uint8_t TESWeather::GetWeatherDataRaw(WeatherData aeData) const {
#ifdef GAME
	return ThisCall<uint8_t>(0x63DD50, this, aeData);
#else
	return ucWeatherData[aeData];
#endif
}

// GAME - 0x59E7D0
bool TESWeather::IsPleasant() const {
#ifdef GAME
	return ThisCall<bool>(0x59E7D0, this);
#else
	return GetWeatherFlags().bPleasant;
#endif
}

// GAME - 0x59E8C0
bool TESWeather::IsCloudy() const {
#ifdef GAME
	return ThisCall<bool>(0x59E8C0, this);
#else
	return GetWeatherFlags().bCloudy;
#endif
}

// GAME - 0x4ED270
bool TESWeather::IsRainy() const {
#ifdef GAME
	return ThisCall<bool>(0x4ED270, this);
#else
	return GetWeatherFlags().bRainy;
#endif
}

// GAME - 0x59EB40
bool TESWeather::IsSnowy() const {
#ifdef GAME
	return ThisCall<bool>(0x59EB40, this);
#else
	return GetWeatherFlags().bSnowy;
#endif
}

// GAME - 0x63C420
float TESWeather::GetFogData(FogData aeData) const {
#ifdef GAME
	return ThisCall<float>(0x63C420, this, aeData);
#else
	return fFogData[aeData];
#endif
}

// GAME - 0x63BB40
uint32_t TESWeather::GetColor(ColorType aeColorType, ColorTime aeColorTime) const {
#ifdef GAME
	return ThisCall<uint32_t>(0x63BB40, this, aeColorType, aeColorTime);
#else
    return uiColorData[aeColorType][aeColorTime];
#endif
}