#pragma once

class alignas(32) BSSpinLock {
public:
	BSSpinLock() noexcept;
	~BSSpinLock() noexcept;
	BSSpinLock(const BSSpinLock&) = delete;
	BSSpinLock& operator=(const BSSpinLock&) = delete;

	volatile uint32_t	uiOwningThread;
	uint32_t			uiLockCount;

	void Lock(const char* apName = nullptr) noexcept;
	[[nodiscard]] bool TryLock() noexcept;
	void Unlock() noexcept;

	bool IsLocked() const noexcept;

	// STL compatibility
	inline void lock() noexcept	{ Lock(); };
	[[nodiscard]] inline bool try_lock() noexcept { return TryLock(); };
	inline void unlock() noexcept { Unlock(); };
};

ASSERT_SIZE(BSSpinLock, 0x20);