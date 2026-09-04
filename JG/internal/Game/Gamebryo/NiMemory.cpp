#include "NiMemory.hpp"

// GAME - 0xAA13E0
// GECK - 0x851B00
void* NiNew(size_t stSize) {
#ifdef GAME
	return CdeclCall<void*>(0xAA13E0, stSize);
#else
	return CdeclCall<void*>(0x851B00, stSize);
#endif
}

// GAME - 0xAA1070
// GECK - 0x851790
void* NiAlloc(size_t stSize) {
#ifdef GAME
	return CdeclCall<void*>(0xAA1070, stSize);
#else
	return CdeclCall<void*>(0x851790, stSize);
#endif
}

// GAME - 0xAA10B0
// GECK - 0x8517D0
void* NiAlignedAlloc(size_t stSize, size_t stAlignment) {
#ifdef GAME
	return CdeclCall<void*>(0xAA10B0, stSize, stAlignment);
#else
	return CdeclCall<void*>(0x8517D0, stSize, stAlignment);
#endif
}

// GAME - 0xAA10F0
// GECK - 0x851810
void NiFree(void* pvMem) {
#ifdef GAME
	CdeclCall<void>(0xAA10F0, pvMem);
#else
	CdeclCall<void>(0x851810, pvMem);
#endif
}

// GAME - 0xAA1110
// GECK - 0x851830
void NiAlignedFree(void* pvMem) {
#ifdef GAME
	CdeclCall<void>(0xAA1110, pvMem);
#else
	CdeclCall<void>(0x851830, pvMem);
#endif
}

// GAME - 0xAA1460
// GECK - 0x851B80
void NiDelete(void* pvMem, size_t stElementSize) {
#ifdef GAME
	CdeclCall<void>(0xAA1460, pvMem, stElementSize);
#else
	CdeclCall<void>(0x851830, pvMem, stElementSize);
#endif
}
