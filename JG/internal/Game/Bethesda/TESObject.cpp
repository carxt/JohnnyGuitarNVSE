#include "TESObject.hpp"

TESObject* TESObject::GetNext() const {
    return pNext;
}

TESObject* TESObject::GetPrev() const {
    return pPrev;
}

// GAME - 0x50FD90
// GECK - 0x5EFF20
const char* TESObject::GetModelFileName(const TESObjectREFR* apRef) const {
#ifdef GAME
	return ThisCall<const char*>(0x50FD90, this, apRef);
#else
	return ThisCall<const char*>(0x5EFF20, this, apRef);
#endif
}

// GAME - 0x4873D0
// GECK - 0x4FE6E0
uint32_t TESObject::GetHealth(const TESObject* apObject) {
#ifdef GAME
	return ThisCall<uint32_t>(0x4873D0, apObject);
#else
	return ThisCall<uint32_t>(0x4FE6E0, apObject);
#endif
}
