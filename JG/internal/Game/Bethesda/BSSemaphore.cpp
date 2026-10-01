#include "BSSemaphore.hpp"

// GAME - 0x78D3B0
// GECK - 0x857AD0
BSSemaphore::BSSemaphore() {
#ifdef GAME
	ThisCall(0x78D3B0, this);
#else
	ThisCall(0x857AD0, this);
#endif
}

// GAME - 0x54AD60
BSSemaphore::BSSemaphore(uint32_t auiCount) {
#ifdef GAME
	ThisCall(0x54AD60, this, auiCount);
#else
	uiCount		= auiCount;
	uiMaxCount	= auiCount + 1;
	hSemaphore  = CallImport<CreateSemaphoreA>(0xD2321C, nullptr, uiCount, uiMaxCount, nullptr);
#endif
}

// GAME - 0x86C6A0
BSSemaphore::BSSemaphore(uint32_t auiCount, uint32_t auiMaxCount) {
#ifdef GAME
	ThisCall(0x86C6A0, this, auiCount, auiMaxCount);
#else
	uiCount		= auiCount;
	uiMaxCount	= auiMaxCount;
	hSemaphore  = CallImport<CreateSemaphoreA>(0xD2321C, nullptr, uiCount, uiMaxCount, nullptr);
#endif
}

// GAME - 0x55A2D0
// GECK - 0x857B10
BSSemaphore::~BSSemaphore() {
#ifdef GAME
	ThisCall(0x55A2D0, this);
#else
	ThisCall(0x857B10, this);
#endif
}

// GAME - 0x442550
void BSSemaphore::Signal() {
#ifdef GAME
	ThisCall(0x442550, this);
#else
	CallImport<ReleaseSemaphore>(0xD231E4, hSemaphore, 1, nullptr);
	InterlockedIncrement(&uiCount);
#endif
}

// GAME - 0x4424E0
void BSSemaphore::Wait() {
#ifdef GAME
	ThisCall(0x4424E0, this);
#else
	CallImport<WaitForSingleObject>(0xD231E8, hSemaphore, INFINITE);
	InterlockedDecrement(&uiCount);
#endif
}

bool BSSemaphore::Test() {
#ifdef GAME
	return CallImport<WaitForSingleObject>(0xFDF1C8, hSemaphore, 0) == WAIT_TIMEOUT;
#else
	return CallImport<WaitForSingleObject>(0xD231E8, hSemaphore, 0) == WAIT_TIMEOUT;
#endif
}
