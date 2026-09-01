#pragma once

class BSCriticalSection {
public:
	BSCriticalSection();
	~BSCriticalSection();

	CRITICAL_SECTION	kCriticalSection;

	void Lock(const char* apName = nullptr);
	bool TryLock();
	void Unlock();

	void Enter(const char* apName = nullptr);
	void Leave();

	// STL compatibility
	inline void lock() noexcept		{ Lock(); };
	inline void try_lock() noexcept { TryLock(); };
	inline void unlock() noexcept	{ Unlock(); };
};

ASSERT_SIZE(BSCriticalSection, 0x18);