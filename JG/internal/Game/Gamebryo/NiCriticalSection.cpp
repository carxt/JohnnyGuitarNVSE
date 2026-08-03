#include "NiCriticalSection.hpp"

NiCriticalSection::NiCriticalSection() {
	InitializeCriticalSection(&m_kCriticalSection);
}

NiCriticalSection::~NiCriticalSection() {
	DeleteCriticalSection(&m_kCriticalSection);
}

// GAME - 0x82F1B0
void NiCriticalSection::Lock() {
	EnterCriticalSection(&m_kCriticalSection);
}

bool NiCriticalSection::TryLock() {
	return TryEnterCriticalSection(&m_kCriticalSection);
}

// GAME - 0x82F1F0
void NiCriticalSection::Unlock() {
	LeaveCriticalSection(&m_kCriticalSection);
}