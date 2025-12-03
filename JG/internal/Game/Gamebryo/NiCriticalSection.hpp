#pragma once

class __declspec(align(128)) NiCriticalSection {
public:
	NiCriticalSection() {
		InitializeCriticalSection(&m_kCriticalSection);
		m_ulThreadOwner = 0;
		m_uiLockCount = 0;
	}

	~NiCriticalSection() {
		DeleteCriticalSection(&m_kCriticalSection);
	}

	CRITICAL_SECTION	m_kCriticalSection;
	uint32_t			m_ulThreadOwner;
	uint32_t			m_uiLockCount;

	void Lock() {
		EnterCriticalSection(&m_kCriticalSection); 
	}

	void Unlock() {
		LeaveCriticalSection(&m_kCriticalSection);
	}

	bool TryLock() {
		return TryEnterCriticalSection(&m_kCriticalSection);
	}
};

ASSERT_SIZE(NiCriticalSection, 0x80);

struct NiCriticalSectionScope {
	NiCriticalSectionScope(NiCriticalSection& aCriticalSection) : rCriticalSection(aCriticalSection) {
		rCriticalSection.Lock();
	}

	NiCriticalSectionScope(NiCriticalSection* apCriticalSection) : rCriticalSection(*apCriticalSection) {
		rCriticalSection.Lock();
	}

	~NiCriticalSectionScope() {
		rCriticalSection.Unlock();
	}

	NiCriticalSection& rCriticalSection;
};