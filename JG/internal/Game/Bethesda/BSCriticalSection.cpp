#include "BSCriticalSection.hpp"

// GAME - 0x44FAE0
BSCriticalSection::BSCriticalSection() {
	InitializeCriticalSection(&kCriticalSection);
}

// GAME - 0x44FB00
BSCriticalSection::~BSCriticalSection() {
	DeleteCriticalSection(&kCriticalSection);
}

// GAME - 0x4538E0
void BSCriticalSection::Lock(const char* apName) {
	EnterCriticalSection(&kCriticalSection);
}

// GAME - 0x44B130
bool BSCriticalSection::TryLock() {
	return TryEnterCriticalSection(&kCriticalSection);
}

// GAME - 0x82F1F0
void BSCriticalSection::Unlock() {
	LeaveCriticalSection(&kCriticalSection);
}

// GAME - 0x4538A0
void BSCriticalSection::Enter(const char* apName) {
	Lock(apName);
}

// GAME - 0x4538C0
void BSCriticalSection::Leave() {
	Unlock();
}