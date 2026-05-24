#pragma once

class BSNonReentrantSpinLock {
public:
	BSNonReentrantSpinLock();
	~BSNonReentrantSpinLock();

	uint32_t uiLock;

	void Lock();
	
	bool TryLock();

	void Unlock();
};

ASSERT_SIZE(BSNonReentrantSpinLock, 0x4);