#include "BSNonReentrantSpinLock.hpp"

BSNonReentrantSpinLock::BSNonReentrantSpinLock() {
	uiLock = 0;
}

BSNonReentrantSpinLock::~BSNonReentrantSpinLock() {
};

void BSNonReentrantSpinLock::Lock() {
	while (InterlockedCompareExchange(&uiLock, 1, 0))
		Sleep(0);
}

bool BSNonReentrantSpinLock::TryLock() {
	return InterlockedCompareExchange(&uiLock, 1, 0) == 0;
}

void BSNonReentrantSpinLock::Unlock() {
	uiLock = 0;
}