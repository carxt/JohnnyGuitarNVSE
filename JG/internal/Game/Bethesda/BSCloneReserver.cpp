#include "BSCloneReserver.hpp"

// GAME - 0x4B0DA0
BSCloneReserver::BSCloneReserver(NiAVObject* apObject, uint32_t auiCount) {
	ThisCall(0x4B0DA0, this, apObject, auiCount);
}

// GAME - 0x4B0DE0
BSCloneReserver::~BSCloneReserver() {
	ThisCall(0x4B0DE0, this);
}

// GAME - 0x4B0EB0
void BSCloneReserver::MakeClones() {
	ThisCall(0x4B0EB0, this);
}

// GAME - 0x4B0DEA
void BSCloneReserver::KillClones() {
	ThisCall(0x4B0DEA, this);
}

// GAME - 0x92C870
void BSCloneReserver::IncRefCount() {
	InterlockedIncrement(&uiRefCount);
}

// GAME - 0x4B0EF0
void BSCloneReserver::DecRefCount() {
	if (!InterlockedDecrement(&uiRefCount))
		delete this;
}
