#include "Setting.hpp"

// GAME - 0xC33090
// GECK - 0x9D19D0
Setting::Type Setting::DataType(const char* apKey) {
#ifdef GAME
	return CdeclCall<Type>(0xC33090, apKey);
#else
	return CdeclCall<Type>(0x9D19D0, apKey);
#endif
}
