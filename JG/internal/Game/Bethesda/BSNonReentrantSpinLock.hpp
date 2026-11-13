#pragma once

class BSNonReentrantSpinLock {
public:
	BSNonReentrantSpinLock();
	~BSNonReentrantSpinLock();

	uint32_t uiLock;

	void Lock();
	
	bool TryLock();

	void Unlock();

	bool IsLocked() const noexcept;

	// STL compatibility
	inline void lock() noexcept { Lock(); };
	[[nodiscard]] inline bool try_lock() noexcept { return TryLock(); };
	inline void unlock() noexcept { Unlock(); };
};

ASSERT_SIZE(BSNonReentrantSpinLock, 0x4);