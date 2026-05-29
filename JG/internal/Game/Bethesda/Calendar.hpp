#pragma once

class TESGlobal;

class Date {
public:
	uint16_t usDate;
	uint16_t usYear;
};

class Calendar {
public:
	enum Season : int32_t {
		NONE	= -1,
		SPRING	= 0,
		SUMMER	= 1,
		FALL	= 2,
		WINTER	= 3,
		COUNT	= 4,
	};

	TESGlobal*	pGameYear;
	TESGlobal*	pGameMonth;
	TESGlobal*	pGameDay;
	TESGlobal*	pGameHour;
	TESGlobal*	pGameDaysPassed;
	TESGlobal*	pTimeScale;
	uint32_t	uiMidnightsPassed;
	bool		bGameLoaded;

	static Calendar* GetSingleton();

	uint32_t GetYear() const;
	uint32_t GetMonth() const;
	uint32_t GetDay() const;
	float GetHour() const;
	float GetMinutesPassed() const;
	uint32_t GetHoursPassed() const;
	float GetGameDaysPassed() const;
	Season GetSeason() const;
	float GetTimeScale() const;
};

ASSERT_SIZE(Date, 0x4);
ASSERT_SIZE(Calendar, 0x20);