#include "NiCriticalSection.hpp"

NiCriticalSection::NiCriticalSection() noexcept {
#ifdef GAME
	CallImport<InitializeCriticalSection>(0xFDF054, &m_kCriticalSection);
#else
	CallImport<InitializeCriticalSection>(0xD23344, &m_kCriticalSection);
#endif
}

NiCriticalSection::~NiCriticalSection() noexcept {
#ifdef GAME
	CallImport<DeleteCriticalSection>(0xFDF058, &m_kCriticalSection);
#else
	CallImport<DeleteCriticalSection>(0xD231F0, &m_kCriticalSection);
#endif
}

// GAME - 0x82F1B0
void NiCriticalSection::Lock() noexcept {
#ifdef GAME
	ThisCall(0x82F1B0, this);
#else
	CallImport<EnterCriticalSection>(0xD231CC, &m_kCriticalSection);
#endif
}

// GAME - 0x78D1D0
bool NiCriticalSection::TryLock() noexcept {
#ifdef GAME
	return ThisCall<bool>(0x78D1D0, this);
#else
	return CallImport<TryEnterCriticalSection>(0xD231F4, &m_kCriticalSection);
#endif
}

// GAME - 0x82F1F0
void NiCriticalSection::Unlock() noexcept {
#ifdef GAME
	ThisCall(0x82F1F0, this);
#else
	CallImport<LeaveCriticalSection>(0xD231D0, &m_kCriticalSection);
#endif
}