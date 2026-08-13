#include "TESFullName.hpp"

const char* TESFullName::c_str() const {
	return strFullName.c_str();
}

// GAME - 0x408DA0
const char* TESFullName::GetFullName() const {
	if (strFullName.GetString())
		return strFullName.GetString();
	else
		return "";
}

// GAME - 0x482720
// GECK - 0x437DB0
const char* TESFullName::GetFullName(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<const char*>(0x482720, apForm);
#else
	return CdeclCall<const char*>(0x437DB0, apForm);
#endif
}

// GAME - 0x48CEE0
uint32_t TESFullName::GetFullNameLength() const {
	return strFullName.GetLength();
}

// GAME - 0x579620
// GECK - 0x449800
uint32_t TESFullName::GetFullNameLength(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<uint32_t>(0x579620, apForm);
#else
	return CdeclCall<uint32_t>(0x449800, apForm);
#endif
}
