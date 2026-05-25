#pragma once

#include "BSSimpleList.hpp"
#include "WeatherEntry.hpp"

class TESWeatherList : public BSSimpleList<WeatherEntry*> {
public:
	TESWeatherList();
	~TESWeatherList();

	void FlushList();
};

ASSERT_SIZE(TESWeatherList, 0x8);