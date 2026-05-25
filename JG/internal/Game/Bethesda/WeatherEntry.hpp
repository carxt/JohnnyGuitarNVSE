#pragma once

class TESWeather;
class TESGlobal;

struct WeatherEntry {
	TESWeather* pWeather;
	uint32_t	uiChance;
	TESGlobal*	pChanceVar;

	void Set(TESWeather* pWtr, uint32_t pChn, TESGlobal* pGlb) {
		pWeather	= pWtr;
		uiChance	= pChn;
		pChanceVar	= pGlb;
	}
};