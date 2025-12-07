#include "NiMemObject.hpp"

// GAME - 0xAA13E0
void* NiMemObject::operator new(size_t stSize) {
	return CdeclCall<void*>(0xAA13E0, stSize);
}

// GAME - 0xAA1420
void* NiMemObject::operator new[](size_t stSize) {
	return CdeclCall<void*>(0xAA1420, stSize);
}

// GAME - 0xAA1460
void NiMemObject::operator delete(void* pvMem, size_t stElementSize) {
	CdeclCall<void>(0xAA1460, pvMem, stElementSize);
}

// GAME - 0xAA1490
void NiMemObject::operator delete[](void* pvMem, size_t stElementSize) {
	CdeclCall<void>(0xAA1490, pvMem, stElementSize);
}
