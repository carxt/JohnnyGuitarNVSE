#include "TESClimate.hpp"

// GAME - 0x63CFE0
const char* TESClimate::GetNightSkyModel() const {
#ifdef GAME
	return ThisCall<const char*>(0x63CFE0, this);
#else
	return kNightSky.GetModel();
#endif
}

void TESClimate::SetNightSkyModel(const char* apPath) {
	kNightSky.SetModel(apPath);
}

// GAME - 0x63CFA0
const TESTexture* TESClimate::GetTexture(TextureType aeType) const {
#ifdef GAME
	return ThisCall<TESTexture*>(0x63CFA0, this, aeType);
#else
	if (aeType >= TextureType::COUNT)
		return nullptr;
	return &kSkyObjects[aeType];
#endif
}

// GAME - 0x63CFA0
TESTexture* TESClimate::GetTexture(TextureType aeType) {
#ifdef GAME
	return ThisCall<TESTexture*>(0x63CFA0, this, aeType);
#else
	if (aeType >= TextureType::COUNT)
		return nullptr;
	return &kSkyObjects[aeType];
#endif
}

// GAME - 0x595F10
uint8_t TESClimate::GetTransTime(TransTime aeType) const {
#ifdef GAME
	return ThisCall<uint8_t>(0x595F10, this, aeType);
#else
	if (aeType >= TransTime::COUNT)
		return 0;
	return ucData[aeType];
#endif
}

void TESClimate::SetTransTime(TransTime aeType, uint8_t aucVal) {
	if (aeType < TransTime::COUNT)
		ucData[aeType] = aucVal;
}

// GAME - 0x451CD0
uint8_t TESClimate::GetVolatilityIndex() const {
#ifdef GAME
	return ThisCall<uint8_t>(0x451CD0, this);
#else
	return ucVolatility;
#endif
}

void TESClimate::SetVolatilityIndex(uint8_t aucVal) {
	ucVolatility = aucVal;
}

// GAME - 0x636980
uint8_t TESClimate::GetMoonPhaseDays() const {
#ifdef GAME
	return ThisCall<uint8_t>(0x636980, this);
#else
	return ucMoonData.ucDays;
#endif
}

// GAME - 0x52AC50
void TESClimate::SetMoonPhaseDays(uint32_t auiDays) {
#ifdef GAME
	ThisCall(0x52AC50, this, auiDays);
#else
	ucMoonData.ucDays = std::min<uint32_t>(auiDays, MoonData::MOON_PHASE_DAYS_MASK);
#endif
}

// GAME - 0x63D020
bool TESClimate::GetUsesSecunda() const {
#ifdef GAME
	return ThisCall<bool>(0x63D020, this);
#else
	return ucMoonData.bUsesSecunda;
#endif
}

// GAME - 0x52B2C0
void TESClimate::SetUsesSecunda(bool abVal) {
#ifdef GAME
	ThisCall(0x52B2C0, this, abVal);
#else
	ucMoonData.bUsesSecunda = abVal;
#endif
}

// GAME - 0x63D000
bool TESClimate::GetUsesMasser() const {
#ifdef GAME
	return ThisCall<bool>(0x63D000, this);
#else
	return ucMoonData.bUsesMasser;
#endif
}

// GAME - 0x52B260
void TESClimate::SetUsesMasser(bool abVal) {
#ifdef GAME
	ThisCall(0x52B260, this, abVal);
#else
	ucMoonData.bUsesMasser = abVal;
#endif
}

// GAME - 0x63D5C0
TESWeather* TESClimate::GetRandomWeather() const {
#ifdef GAME
	return ThisCall<TESWeather*>(0x63D5C0, this);
#else
	return kWeatherList.GetRandomWeather();
#endif
}
