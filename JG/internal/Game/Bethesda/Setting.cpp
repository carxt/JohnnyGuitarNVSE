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

// GAME - 0xC33170
// GECK - 0x9D1AB0
Setting& Setting::operator==(const char* apString) {
#ifdef GAME
	return ThisCall<Setting&>(0xC33170, this, apString);
#else
	return ThisCall<Setting&>(0x9D1AB0, this, apString);
#endif
}
