#include "TimeGlobal.hpp"

TimeGlobal* TimeGlobal::GetSingleton() {
#ifdef GAME
	return reinterpret_cast<TimeGlobal*>(0x11F6394);
#else
	return reinterpret_cast<TimeGlobal*>(0xF21CB8);
#endif
}