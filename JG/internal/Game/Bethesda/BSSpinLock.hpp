#pragma once

#include "BSMemObject.hpp"

class BSSpinLock {
public:
	BSSpinLock() {
		memset(this, 0, sizeof(BSSpinLock));
	}

	volatile uint32_t	uiOwningThread;
	uint32_t			uiLockCount;
	uint32_t			unk08[6];

	void Lock(const char* apName = nullptr);
	bool TryLock();
	void Unlock();
};

ASSERT_SIZE(BSSpinLock, 0x20);

class BSSpinLockScope {
public:
	explicit BSSpinLockScope(const BSSpinLock& arLock) {
		pLock = const_cast<BSSpinLock*>(&arLock);
		pLock->Lock();
	}

	explicit BSSpinLockScope(const BSSpinLock* apLock) {
		pLock = const_cast<BSSpinLock*>(apLock);
		pLock->Lock();
	}

	~BSSpinLockScope() {
		pLock->Unlock();
	}

protected:
	BSSpinLock* pLock;
};