#include "TESFullName.hpp"

const char* TESFullName::c_str() const {
	return strFullName.c_str();
}

// GAME - 0x408DA0
const char* TESFullName::GetFullName() const {
#ifdef GAME
	return ThisCall<const char*>(0x408DA0, this);
#else
	return strFullName.c_str();
#endif
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

// GAME - 0x489100
void TESFullName::SetFullName(const char* apName) {
#ifdef GAME
	ThisCall(0x489100, this, apName);
#else
	strFullName.Set(apName);
#endif
}

// GAME - 0x48CEE0
uint32_t TESFullName::GetFullNameLength() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x48CEE0, this);
#else
	return strFullName.GetLength();
#endif
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
