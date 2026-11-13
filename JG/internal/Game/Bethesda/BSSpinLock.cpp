#include "BSSpinLock.hpp"

// GAME - 0x96A2D0
BSSpinLock::BSSpinLock() noexcept : uiOwningThread(0), uiLockCount(0) {
}

BSSpinLock::~BSSpinLock() noexcept {
}

// GAME - 0x40FBF0
// GECK - 0x411D40
void BSSpinLock::Lock(const char* apName) noexcept {
#ifdef GAME
    ThisCall(0x40FBF0, this, apName);
#else
    ThisCall(0x411D40, this, apName);
#endif
}

// GAME - 0x78D200
// GECK - 0x9DF6B0
bool BSSpinLock::TryLock() noexcept {
#ifdef GAME
	return ThisCall<bool>(0x78D200, this);
#else
	return ThisCall<bool>(0x9DF6B0, this);
#endif
}

// GAME - 0x40FBA0
void BSSpinLock::Unlock() noexcept {
#ifdef GAME
    ThisCall(0x40FBA0, this);
#else
    if (--uiLockCount == 0)
        uiOwningThread = 0;
#endif
}

// GAME - 0x5570B0
bool BSSpinLock::IsLocked() const noexcept {
    return uiLockCount != 0;
}
