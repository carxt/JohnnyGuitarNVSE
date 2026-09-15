#include "PackageSchedule.hpp"

// GAME - 0x67FCB0
// GECK - 0x49FF60
PackageSchedule::PackageSchedule() {
#ifdef GAME
	ThisCall(0x67FCB0, this);
#else
	ThisCall(0x49FF60, this);
#endif
}

// GAME - 0x483710
// GECK - 0x846650
PackageSchedule::~PackageSchedule() {
}

// GAME - 0x678CC0
PackageSchedule::WeekDay PackageSchedule::GetStartDayOfWeek() const {
	return WeekDay(eDayOfWeek);
}

// GAME - 0x67FDB0
void PackageSchedule::SetStartDayOfWeek(WeekDay aeDay) {
	eDayOfWeek = aeDay;
}

// GAME - 0x678CA0
PackageSchedule::Month PackageSchedule::GetStartMonth() const {
	return Month(eMonth);
}

// GAME - 0x5407B0
void PackageSchedule::SetStartMonth(Month aeMonth) {
	eMonth = aeMonth;
}

// GAME - 0x678CE0
int8_t PackageSchedule::GetStartDate() const {
	return cDate;
}

// GAME - 0x67FDD0
void PackageSchedule::SetStartDate(int8_t acDate) {
	cDate = acDate;
}

// GAME - 0x86A460
int8_t PackageSchedule::GetStartTime() const {
	return cTime;
}

// GAME - 0x67FDF0
void PackageSchedule::SetStartTime(int8_t acHour) {
	cTime = acHour;
}

// GAME - 0x726070
int32_t PackageSchedule::GetDuration() const {
	return iDuration;
}

// GAME - 0x6ECD40
void PackageSchedule::SetDuration(int32_t aiDuration) {
	iDuration = aiDuration;
}

// GAME - 0x67FD40
// GECK - 0x49FFB0
void PackageSchedule::Copy(PackageSchedule* apSource) {
#ifdef GAME
	ThisCall(0x67FD40, this, apSource);
#else
	ThisCall(0x49FFB0, this, apSource);
#endif
}

// GECK - 0x4A0060
const char* PackageSchedule::GetDayOfWeekName() const {
#ifdef GAME
	const WeekDay eDay = GetStartDayOfWeek();
	if (eDay < WeekDay::SUNDAY || eDay >= WeekDay::COUNT)
		return "Any";
	else
		return pDayOfWeekNames[eDay];
#else
	return ThisCall<const char*>(0x4A0060, this);
#endif
}

// GECK - 0x4A0080
const char* PackageSchedule::GetMonthName() const {
#ifdef GAME
	const Month eMonth = GetStartMonth();
	if (eMonth < Month::JANUARY || eMonth >= Month::COUNT)
		return "Any";
	else
		return pMonthNames[eMonth];
#else
	return ThisCall<const char*>(0x4A0080, this);
#endif
}