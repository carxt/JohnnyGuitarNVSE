#pragma once

#include "TESRegionData.hpp"
#include "TESWeatherList.hpp"

class TESRegionDataWeather : public TESRegionData {
public:
	TESRegionDataWeather();
	~TESRegionDataWeather();

	TESWeatherList	kWeatherList;
};

#ifdef GAME
ASSERT_SIZE(TESRegionDataWeather, 0x10)
#else
ASSERT_SIZE(TESRegionDataWeather, 0x2C)
#endif