#pragma once

class PackageSchedule {
public:
	struct _Month {
		enum Month {
			NONE = -1,

			JANUARY = 0,
			FEBRUARY,
			MARCH,
			APRIL,
			MAY,
			JUNE,
			JULY,
			AUGUST,
			SEPTEMBER,
			OCTOBER,
			NOVEMBER,
			DECEMBER,

			SPRING,	// March, April, May
			SUMMER,	// June, July, August
			AUTUMN,	// September, October, November
			WINTER,	// December, January, February

			COUNT,
		};
	};
	using Month = _Month::Month;

	struct _WeekDay {
		enum WeekDay {
			NONE = -1,

			SUNDAY = 0,
			MONDAY,
			TUESDAY,
			WEDNESDAY,
			THURSDAY,
			FRIDAY,
			SATURDAY,

			WEEKDAY,
			WEEKEND,

			MWF,
			TT,

			COUNT,
		};
	};
	using WeekDay = _WeekDay::WeekDay;

	PackageSchedule();
	~PackageSchedule();

	int8_t	eMonth;
	int8_t	eDayOfWeek;
	int8_t	cDate;
	int8_t	cTime;
	int32_t	iDuration;

	WeekDay GetStartDayOfWeek() const;
	void SetStartDayOfWeek(WeekDay aeDay);

	Month GetStartMonth() const;
	void SetStartMonth(Month aeMonth);

	int8_t GetStartDate() const;
	void SetStartDate(int8_t acDate);

	int8_t GetStartTime() const;
	void SetStartTime(int8_t acHour);

	int32_t GetDuration() const;
	void SetDuration(int32_t aiDuration);

	void Copy(PackageSchedule* apSource);

	const char* GetDayOfWeekName() const;

	const char* GetMonthName() const;


#ifdef GAME
	static constexpr AddressPtr<const char*, 0x119BF84, 11> pDayOfWeekNames;
	static constexpr AddressPtr<const char*, 0x119BFB0, 16> pMonthNames;
	static constexpr AddressPtr<uint8_t, 0x119BFF0, 16>		ucMonthDayCounts;
#else
	static constexpr AddressPtr<const char*, 0xE917E4, 11>	pDayOfWeekNames;
	static constexpr AddressPtr<const char*, 0xE91810, 16>	pMonthNames;
	static constexpr AddressPtr<uint8_t, 0xE91850, 16>		ucMonthDayCounts;
#endif
};

ASSERT_SIZE(PackageSchedule, 0x8);