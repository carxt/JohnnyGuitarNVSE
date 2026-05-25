#pragma once

#include "TESForm.hpp"
#include "TESModel.hpp"
#include "TESWeather.hpp"
#include "TESTexture.hpp"
#include "TESWeatherList.hpp"

struct WeatherEntry;

class TESClimate : public TESForm {
public:
	TESClimate();
	~TESClimate();

	enum Data {
		SUNRISE_BEGIN = 0,
		SUNRISE_END,
		SUNSET_BEGIN,
		SUNSET_END,
		VOLATILITY,
		PHASE_LENGTH
	};

	TESModel		kNightSky;
	TESWeatherList	kWeatherList;
	TESTexture		kSkyObjects[2];
	uint8_t			ucData[6];

	TESFORM_TYPE(TESClimate);	

	uint8_t GetTransTime(uint32_t auiType) const;
	uint8_t GetMoonPhaseDays() const;
};

ASSERT_SIZE(TESClimate, 0x58);