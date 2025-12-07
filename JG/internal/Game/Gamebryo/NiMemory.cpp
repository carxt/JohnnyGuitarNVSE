#include "NiMemory.hpp"

// GAME - 0xAA13E0
void* NiNew(size_t stSize) {
    return CdeclCall<void*>(0xAA13E0, stSize);
}

// GAME - 0xAA1070
void* NiAlloc(size_t stSize) {
	return CdeclCall<void*>(0xAA1070, stSize);
}

// GAME - 0xAA10B0
void* NiAlignedAlloc(size_t stSize, size_t stAlignment) {
	return CdeclCall<void*>(0xAA10B0, stSize, stAlignment);
}

// GAME - 0xAA10F0
void NiFree(void* pvMem) {
	CdeclCall<void>(0xAA10F0, pvMem);
}

// GAME - 0xAA1110
void NiAlignedFree(void* pvMem) {
	CdeclCall<void>(0xAA1110, pvMem);
}

// GAME - 0xAA1460
void NiDelete(void* pvMem, size_t stElementSize) {
	CdeclCall<void>(0xAA1460, pvMem, stElementSize);
}
