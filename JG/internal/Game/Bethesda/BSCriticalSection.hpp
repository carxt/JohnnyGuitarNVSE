#pragma once

class BSCriticalSection {
public:
	BSCriticalSection() noexcept;
	~BSCriticalSection() noexcept;
	BSCriticalSection(const BSCriticalSection&) = delete;
	BSCriticalSection& operator=(const BSCriticalSection&) = delete;

	CRITICAL_SECTION	kCriticalSection;

	void Lock(const char* apName = nullptr) noexcept;
	[[nodiscard]] bool TryLock() noexcept;
	void Unlock() noexcept;

	void Enter(const char* apName = nullptr) noexcept;
	void Leave() noexcept;

	// STL compatibility
	inline void lock() noexcept	{ Lock(); };
	[[nodiscard]] inline bool try_lock() noexcept { return TryLock(); };
	inline void unlock() noexcept { Unlock(); };
};

ASSERT_SIZE(BSCriticalSection, 0x18);