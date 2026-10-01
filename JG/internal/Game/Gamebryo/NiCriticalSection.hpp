#pragma once

class alignas(128) NiCriticalSection {
public:
	NiCriticalSection() noexcept;
	~NiCriticalSection() noexcept;

	CRITICAL_SECTION	m_kCriticalSection;

	void Lock() noexcept;
	[[nodiscard]] bool TryLock() noexcept;
	void Unlock() noexcept;

	// STL compatibility
	inline void lock() noexcept	{ Lock(); };
	[[nodiscard]] inline bool try_lock() noexcept { return TryLock(); };
	inline void unlock() noexcept { Unlock(); };
};

ASSERT_SIZE(NiCriticalSection, 0x80);