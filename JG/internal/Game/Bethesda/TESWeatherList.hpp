#pragma once

#include "BSSimpleList.hpp"
#include "WeatherEntry.hpp"

class SPEC_NOVTABLE TESWeatherList : public BSSimpleList<WeatherEntry*> {
public:
	TESWeatherList();
	~TESWeatherList();

#ifdef EDITOR
	virtual bool	Func0(HWND, uint32_t, uint16_t, void*, bool&);
	virtual bool	Func1(HWND);
	virtual void	Func2(HWND);
	virtual void	Func3(HWND);
	virtual void*	Func4(HWND);
	virtual void	Func5(HWND);

	uint32_t uiDialogs[6];
#endif

	TESWeather* GetRandomWeather() const;

	void FlushList();
};

#ifdef GAME
ASSERT_SIZE(TESWeatherList, 0x8);
#else
ASSERT_SIZE(TESWeatherList, 0x24);
#endif