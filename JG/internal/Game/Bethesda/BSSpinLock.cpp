#include "BSSpinLock.hpp"

// GAME - 0x40FBF0
// GECK - 0x411D40
void BSSpinLock::Lock(const char* apName) {
#ifdef GAME
    ThisCall(0x40FBF0, this, apName);
#else
    ThisCall(0x411D40, this, apName);
#endif
}

// GAME - 0x78D200
// GECK - 0x9DF6B0
bool BSSpinLock::TryLock() {
#ifdef GAME
	return ThisCall<bool>(0x78D200, this);
#else
	return ThisCall<bool>(0x9DF6B0, this);
#endif
}

// GAME - 0x40FBA0
void BSSpinLock::Unlock() {
#ifdef GAME
    ThisCall(0x40FBA0, this);
#else
    if (--uiLockCount == 0)
        uiOwningThread = 0;
#endif
}
