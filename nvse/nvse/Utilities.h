#pragma once

class Script;

#define SIZEOF_ARRAY(arrayName, elementType) (sizeof(arrayName) / sizeof(elementType))

// this copies the string onto the FormHeap - used to work around alloc/dealloc mismatch when passing
// data between nvse and plugins
char* CopyCString(const char* src);

struct CSLock {
private:
	CRITICAL_SECTION* cs;

public:
	CSLock(CRITICAL_SECTION& _cs) : cs(&_cs) {
		EnterCriticalSection(cs);
	}

	CSLock(CRITICAL_SECTION* _cs) : cs(_cs) {
		EnterCriticalSection(cs);
	}
	~CSLock() {
		LeaveCriticalSection(cs);
	}
};

class SRWSharedLock {
public:
	SRWSharedLock(PSRWLOCK apLock) : pLock(apLock) { AcquireSRWLockShared(pLock); }
	SRWSharedLock(SRWLOCK& arLock) : pLock(&arLock) { AcquireSRWLockShared(pLock); }
	~SRWSharedLock() { ReleaseSRWLockShared(pLock); }
private:
	PSRWLOCK pLock;
};

class SRWUniqueLock {
public:
	SRWUniqueLock(PSRWLOCK apLock) : pLock(apLock) { AcquireSRWLockExclusive(pLock); }
	SRWUniqueLock(SRWLOCK& arLock) : pLock(&arLock) { AcquireSRWLockExclusive(pLock); }
	~SRWUniqueLock() { ReleaseSRWLockExclusive(pLock); }
private:
	PSRWLOCK pLock;
};