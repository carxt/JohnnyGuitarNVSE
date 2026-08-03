#include "BSSemaphore.hpp"

// GAME - 0x78D3B0
BSSemaphore::BSSemaphore() {
	iCount		= 0;
	iMaxCount	= 0;
	hSemaphore	= CreateSemaphore(0, 0, 1, 0);
}

// GAME - 0x54AD60
BSSemaphore::BSSemaphore(int32_t aiCount) {
	iCount		= aiCount;
	iMaxCount	= aiCount + 1;
	hSemaphore	= CreateSemaphore(0, iCount, iMaxCount, 0);
}

// GAME - 0x86C6A0
BSSemaphore::BSSemaphore(int32_t aiCount, int32_t aiMaxCount) {
	iCount		= aiCount;
	iMaxCount	= aiMaxCount;
	hSemaphore	= CreateSemaphore(0, iCount, iMaxCount, 0);
}

// GAME - 0x55A2D0
BSSemaphore::~BSSemaphore() {
	CloseHandle(hSemaphore);
}

int32_t BSSemaphore::GetCount() const {
	return iCount;
}

// GAME - 0x442550
void BSSemaphore::Signal() {
	ReleaseSemaphore(hSemaphore, 1, 0);
	InterlockedIncrement(reinterpret_cast<volatile LONG*>(&iCount));
}

// GAME - 0x4424E0
void BSSemaphore::Wait() {
	WaitForSingleObject(hSemaphore, INFINITE);
	InterlockedDecrement(reinterpret_cast<volatile LONG*>(&iCount));
}

bool BSSemaphore::Test() {
	return WaitForSingleObject(hSemaphore, 0) == 258;
}
