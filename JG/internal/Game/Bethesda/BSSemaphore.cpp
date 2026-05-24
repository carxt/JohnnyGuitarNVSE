#include "BSSemaphore.hpp"

// GAME - 0x78D3B0
BSSemaphore::BSSemaphore() {
	uiCount		= 0;
	uiMaxCount	= 0;
	hSemaphore	= CreateSemaphore(0, 0, 1, 0);
}

// GAME - 0x54AD60
BSSemaphore::BSSemaphore(uint32_t auiCount) {
	uiCount		= auiCount;
	uiMaxCount	= auiCount + 1;
	hSemaphore	= CreateSemaphore(0, uiCount, uiMaxCount, 0);
}

// GAME - 0x86C6A0
BSSemaphore::BSSemaphore(uint32_t auiCount, uint32_t auiMaxCount) {
	uiCount		= auiCount;
	uiMaxCount	= auiMaxCount;
	hSemaphore	= CreateSemaphore(0, uiCount, uiMaxCount, 0);
}

// GAME - 0x55A2D0
BSSemaphore::~BSSemaphore() {
	CloseHandle(hSemaphore);
}

// GAME - 0x442550
void BSSemaphore::Signal() {
	ReleaseSemaphore(hSemaphore, 1, 0);
	InterlockedIncrement(&uiCount);
}

// GAME - 0x4424E0
void BSSemaphore::Wait() {
	WaitForSingleObject(hSemaphore, INFINITE);
	InterlockedDecrement(&uiCount);
}

bool BSSemaphore::Test() {
	return WaitForSingleObject(hSemaphore, 0) == 258;
}
