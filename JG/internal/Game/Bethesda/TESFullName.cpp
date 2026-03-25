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
const char* TESFullName::GetFullName(const TESForm* apForm) {
	return CdeclCall<const char*>(0x482720, apForm);
}

// GAME - 0x48CEE0
uint32_t TESFullName::GetFullNameLength() const {
	return strFullName.GetLength();
}

// GAME - 0x579620
uint32_t TESFullName::GetFullNameLength(const TESForm* apForm) {
	return CdeclCall<uint32_t>(0x579620, apForm);
}
