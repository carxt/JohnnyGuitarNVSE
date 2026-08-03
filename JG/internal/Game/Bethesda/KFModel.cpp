#include "KFModel.hpp"
#include "BSAnimGroupSequence.hpp"
#include "TESAnimGroup.hpp"

// GAME - 0x43B640
// GECK - 0x4C1790
KFModel::KFModel(const char* apFileName, BSStream* apStream) {
#ifdef GAME
	ThisCall(0x43B640, this, apFileName, apStream);
#else
	ThisCall(0x4C1790, this, apFileName, apStream);
#endif
}

// GAME - 0x43B750
// GECK - 0x4BC270
KFModel::~KFModel() {
#ifdef GAME
	ThisCall(0x43B750, this);
#else
	ThisCall(0x4BC270, this);
#endif
}

// GAME - 0x559450
const char* KFModel::GetFileName() const {
	return pFileName;
}

// GAME - 0x7FA950
BSAnimGroupSequence* KFModel::GetSequence() const {
	return spControllerSequence;
}

// GAME - 0x5585E0
TESAnimGroup* KFModel::GetAnimGroup() const {
	return spAnimGroup;
}

// GAME - 0x44B010
void KFModel::IncRefCount() {
	InterlockedIncrement(&reinterpret_cast<uint32_t&>(iRefCount));
}

// GAME - 0x44B050
void KFModel::DecRefCount() {
	InterlockedDecrement(&reinterpret_cast<uint32_t&>(iRefCount));
}

// GAME - 0x43BE10
void KFModel::IncManualRefCount() {
	InterlockedIncrement(&reinterpret_cast<uint32_t&>(iManualRefCount));

}

// GAME - 0x43BAC0
// GECK - 0x4BB420
void KFModel::DecManualRefCount() {
	if (iManualRefCount > 0)
		InterlockedIncrement(&reinterpret_cast<uint32_t&>(iManualRefCount));
}

// GAME - 0x4431B0
int32_t KFModel::GetRefCount() const {
	return iRefCount + iManualRefCount;
}

// GAME - 0x84E3A0
int32_t KFModel::GetActualRefCount() const {
	return iRefCount;
}

// GAME - 0x44EDB0
int32_t KFModel::GetManualRefCount() const {
	return iManualRefCount;
}