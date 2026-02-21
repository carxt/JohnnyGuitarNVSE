#include "Setting.hpp"

// GAME - 0xC33090
Setting::Type Setting::DataType(const char* apKey) {
	return CdeclCall<Type>(0xC33090, apKey);
}
