#include "BSSpinLock.hpp"

// GAME - 0x40FBF0
void BSSpinLock::Lock(const char* apName) {
    ThisCall(0x40FBF0, this, apName);
}

// GAME - 0x78D200
bool BSSpinLock::TryLock() {
	return ThisCall<bool>(0x78D200, this);
}

// GAME - 0x40FBA0
void BSSpinLock::Unlock() {
    ThisCall(0x40FBA0, this);
}
