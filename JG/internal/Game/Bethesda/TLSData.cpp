#include "TLSData.hpp"

struct _TEB {
	uint32_t		 padding[11];
	struct TLSData** ThreadLocalStoragePointer;
};

TLSData* TLSData::Get() {
#ifdef GAME
	return NtCurrentTeb()->ThreadLocalStoragePointer[*reinterpret_cast<uint32_t*>(0x126FD98)];
#else
	return NtCurrentTeb()->ThreadLocalStoragePointer[*reinterpret_cast<uint32_t*>(0xF9879C)];
#endif
}

// GAME - 0x404F50
uint32_t TLSData::GetMemContext() {
	return Get()->eMemContext;
}

// GAME - 0x404F30
void TLSData::SetMemContext(uint32_t index) {
	Get()->eMemContext = index;
}

uint32_t TLSData::GetBatchRendererIndex() {
	return Get()->iBatchRendererIndex;
}