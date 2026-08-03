#pragma once

class alignas(128) NiCriticalSection {
public:
	NiCriticalSection();
	~NiCriticalSection();

	CRITICAL_SECTION	m_kCriticalSection;

	void Lock();
	bool TryLock();
	void Unlock();

	// STL compatibility
	inline void lock() noexcept		{ Lock(); };
	inline void try_lock() noexcept { TryLock(); };
	inline void unlock() noexcept	{ Unlock(); };
};

ASSERT_SIZE(NiCriticalSection, 0x80);