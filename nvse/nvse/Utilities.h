#pragma once

class Script;

//const std::string & GetFalloutDirectory(void);
//std::string GetNVSEConfigOption(const char * section, const char * key);
//bool GetNVSEConfigOption_UInt32(const char * section, const char * key, uint32_t * dataOut);

// this has been tested to work for non-varargs functions
// varargs functions end up with 'this' passed as the last parameter (ie. probably broken)
// do NOT use with classes that have multiple inheritance

// if many member functions are to be declared, use MEMBER_FN_PREFIX to create a type with a known name
// so it doesn't need to be restated throughout the member list

// all of the weirdness with the _GetType function is because you can't declare a static const pointer
// inside the class definition. inlining automatically makes the function call go away since it's a const

#define MEMBER_FN_PREFIX(className)	\
	typedef className _MEMBER_FN_BASE_TYPE

#define DEFINE_MEMBER_FN_LONG(className, functionName, retnType, address, ...)		\
	typedef retnType (className::* _##functionName##_type)(__VA_ARGS__);			\
																					\
	inline _##functionName##_type * _##functionName##_GetPtr(void)					\
	{																				\
		static const uint32_t _address = address;										\
		return (_##functionName##_type *)&_address;									\
	}

#define DEFINE_MEMBER_FN(functionName, retnType, address, ...)	\
	DEFINE_MEMBER_FN_LONG(_MEMBER_FN_BASE_TYPE, functionName, retnType, address, __VA_ARGS__)

#define CALL_MEMBER_FN(obj, fn)	\
	((*(obj)).*(*((obj)->_##fn##_GetPtr())))

// ConsolePrint() limited to 512 chars; use this to print longer strings to console
//void Console_Print_Long(const std::string& str);

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