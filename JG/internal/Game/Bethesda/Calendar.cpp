#include "Calendar.hpp"

Calendar* Calendar::GetSingleton() {
    return reinterpret_cast<Calendar*>(0x11DE7B8);
}

// GAME - 0x867C60
uint32_t Calendar::GetYear() const {
	return ThisCall<float>(0x867C60, this);
}

// GAME - 0x867D20
uint32_t Calendar::GetMonth() const {
	return ThisCall<float>(0x867D20, this);
}

// GAME - 0x867D60
uint32_t Calendar::GetDay() const {
	return ThisCall<float>(0x867D60, this);
}

// GAME - 0x867DA0
float Calendar::GetHour() const {
	return ThisCall<float>(0x867DA0, this);
}

// GAME - 0x867EA0
float Calendar::GetMinutesPassed() const {
	return ThisCall<float>(0x867EA0, this);
}

// GAME - 0x867E30
uint32_t Calendar::GetHoursPassed() const {
	return ThisCall<float>(0x867E30, this);
}

// GAME - 0x867DE0
float Calendar::GetGameDaysPassed() const {
	return ThisCall<float>(0x867DE0, this);
}

// GAME - 0x867CA0
Calendar::Season Calendar::GetSeason() const {
	return ThisCall<Season>(0x867CA0, this);
}

// GAME - 0x867950
float Calendar::GetTimeScale() const {
	return ThisCall<float>(0x867950, this);
}
