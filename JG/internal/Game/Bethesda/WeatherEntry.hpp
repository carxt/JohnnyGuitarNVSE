#pragma once

class TESWeather;
class TESGlobal;

struct WeatherEntry {
	TESWeather* pWeather;
	uint32_t	uiChance;
	TESGlobal*	pChanceVar;
};

ASSERT_SIZE(WeatherEntry, 0xC);