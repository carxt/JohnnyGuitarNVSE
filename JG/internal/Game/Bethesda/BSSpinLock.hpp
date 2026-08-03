#pragma once

class alignas(32) BSSpinLock {
public:
	BSSpinLock() noexcept;
	~BSSpinLock() noexcept;

	volatile uint32_t	uiOwningThread;
	uint32_t			uiLockCount;

	void Lock(const char* apName = nullptr) noexcept;
	bool TryLock() noexcept;
	void Unlock() noexcept;

	bool IsLocked() const noexcept;

	// STL compatibility
	inline void lock() noexcept		{ Lock(); };
	inline void try_lock() noexcept { TryLock(); };
	inline void unlock() noexcept	{ Unlock(); };
};

ASSERT_SIZE(BSSpinLock, 0x20);