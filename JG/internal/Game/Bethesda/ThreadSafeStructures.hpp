#pragma once


class ThreadSafeStructures {
public:

	static bool CompareExchange(void* destination, void* exchange, void* compare) {
		return InterlockedCompareExchange((LONG*)destination, (LONG)exchange, (LONG)compare) == (LONG)compare;
	}

};