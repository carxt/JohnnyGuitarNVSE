#include "BSCriticalSection.hpp"

// GAME - 0x44FAE0
BSCriticalSection::BSCriticalSection() {
#ifdef GAME
	ThisCall(0x44FAE0, this);
#else
	(*reinterpret_cast<decltype(InitializeCriticalSection)**>(0xD23344))(&kCriticalSection);
#endif
}

// GAME - 0x44FB00
BSCriticalSection::~BSCriticalSection() {
#ifdef GAME
	ThisCall(0x44FB00, this);
#else
	(*reinterpret_cast<decltype(DeleteCriticalSection)**>(0xD231F0))(&kCriticalSection);
#endif
}

// GAME - 0x4538E0
void BSCriticalSection::Lock(const char* apName) {
#ifdef GAME
	ThisCall(0x4538E0, this, apName);
#else
	(*reinterpret_cast<decltype(EnterCriticalSection)**>(0xD231CC))(&kCriticalSection);
#endif
}

// GAME - 0x44B130
bool BSCriticalSection::TryLock() {
#ifdef GAME
	return ThisCall<bool>(0x44B130, this);
#else
	return (*reinterpret_cast<decltype(TryEnterCriticalSection)**>(0xD231F4))(&kCriticalSection);
#endif
}

// GAME - 0x82F1F0
void BSCriticalSection::Unlock() {
#ifdef GAME
	ThisCall(0x82F1F0, this);
#else
	(*reinterpret_cast<decltype(LeaveCriticalSection)**>(0xD231D0))(&kCriticalSection);
#endif
}

// GAME - 0x4538A0
void BSCriticalSection::Enter(const char* apName) {
	Lock(apName);
}

// GAME - 0x4538C0
void BSCriticalSection::Leave() {
	Unlock();
}