#include "NiMemObject.hpp"

// GAME - 0xAA13E0
// GECK - 0x851B00
void* NiMemObject::operator new(size_t stSize) {
#ifdef GAME
	return CdeclCall<void*>(0xAA13E0, stSize);
#else
	return CdeclCall<void*>(0x851B00, stSize);
#endif
}

// GAME - 0xAA1420
// GECK - 0x851B40
void* NiMemObject::operator new[](size_t stSize) {
#ifdef GAME
	return CdeclCall<void*>(0xAA1420, stSize);
#else
	return CdeclCall<void*>(0x851B40, stSize);
#endif
}

// GAME - 0xAA1460
// GECK - 0x851B80
void NiMemObject::operator delete(void* pvMem, size_t stElementSize) {
#ifdef GAME
	CdeclCall<void>(0xAA1460, pvMem, stElementSize);
#else
	CdeclCall<void>(0x851B80, pvMem, stElementSize);
#endif
}

// GAME - 0xAA1490
// GECK - 0x851BB0
void NiMemObject::operator delete[](void* pvMem, size_t stElementSize) {
#ifdef GAME
	CdeclCall<void>(0xAA1490, pvMem, stElementSize);
#else
	CdeclCall<void>(0x851BB0, pvMem, stElementSize);
#endif
}
