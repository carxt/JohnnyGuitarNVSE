#pragma once

class ThreadSafeStructures {
public:
	// GAME - 0x43B460
	static inline bool CompareExchange(void* destination, void* exchange, void* compare) {
		return InterlockedCompareExchange(reinterpret_cast<LONG*>(destination), reinterpret_cast<LONG>(exchange), reinterpret_cast<LONG>(compare)) == reinterpret_cast<LONG>(compare);
	}
};