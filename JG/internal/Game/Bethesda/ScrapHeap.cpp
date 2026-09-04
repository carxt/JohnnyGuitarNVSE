#include "ScrapHeap.hpp"

// GAME - 0xAA53F0
// GECK - 0x855910
ScrapHeap::ScrapHeap() noexcept {
#ifdef GAME
	ThisCall(0xAA53F0, this);
#else
	ThisCall(0x855910, this);
#endif
}

// GAME - 0xAA5410
// GECK - 0x855930
ScrapHeap::ScrapHeap(uint32_t auiReserveSize) noexcept {
#ifdef GAME
	ThisCall(0xAA5410, this, auiReserveSize);
#else
	ThisCall(0x855930, this, auiReserveSize);
#endif
}

// GAME - 0xAA5460
// GECK - 0x855980
ScrapHeap::~ScrapHeap() noexcept {
#ifdef GAME
	ThisCall(0xAA5460, this);
#else
	ThisCall(0x855980, this);
#endif
}

// GAME - 0xAA54A0
// GECK - 0x8559C0
__declspec(restrict) __declspec(allocator) void* ScrapHeap::Allocate(uint32_t auiSize, uint32_t auiAlignment) noexcept {
#ifdef GAME
	return ThisCall<void*>(0xAA54A0, this, auiSize, auiAlignment);
#else
	return ThisCall<void*>(0x8559C0, this, auiSize, auiAlignment);
#endif
}

// GAME - 0xAA5610
// GECK - 0x855B30
void ScrapHeap::Deallocate(void* apMem) noexcept {
#ifdef GAME
	ThisCall(0xAA5610, this, apMem);
#else
	ThisCall(0x855B30, this, apMem);
#endif
}

bool ScrapHeap::IsOwner(const void* apMem) const noexcept {
	return apMem >= pMemHeap && apMem < pEndHeap;
}

uint32_t ScrapHeap::GetAllocatedMemory() const noexcept {
	return pCurrentStackLoc - pMemHeap;
}

// GAME - 0xAA5710
// GECK - 0x855C30
uint32_t ScrapHeap::Size(const void* apMem) const noexcept {
#ifdef GAME
	return ThisCall<uint32_t>(0xAA5710, this, apMem);
#else
	return ThisCall<uint32_t>(0x855C30, this, apMem);
#endif
}

// GAME - 0xAA5800
// GECK - 0x855D20
uint32_t ScrapHeap::GetAllocationCount() const noexcept {
#ifdef GAME
	return ThisCall<uint32_t>(0xAA5800, this);
#else
	return ThisCall<uint32_t>(0x855D20, this);
#endif
}
