#pragma once

#include "TESRegionData.hpp"
#include "TESWeatherList.hpp"

class TESRegionDataWeather : public TESRegionData {
public:
	TESRegionDataWeather();
	~TESRegionDataWeather();

	TESWeatherList	kWeatherList;
};

ASSERT_SIZE(TESRegionDataWeather, 0x10)