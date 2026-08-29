#include "TESFullName.hpp"

const char* TESFullName::c_str() const {
	return strFullName.c_str();
}

// GAME - 0x408DA0
const char* TESFullName::GetFullName() const {
	return ThisCall<const char*>(0x408DA0, this);
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
	ThisCall(0x489100, this, apName);
}

// GAME - 0x48CEE0
uint32_t TESFullName::GetFullNameLength() const {
	return ThisCall<uint32_t>(0x48CEE0, this);
}

// GAME - 0x579620
uint32_t TESFullName::GetFullNameLength(const TESForm* apForm) {
	return CdeclCall<uint32_t>(0x579620, apForm);
}
