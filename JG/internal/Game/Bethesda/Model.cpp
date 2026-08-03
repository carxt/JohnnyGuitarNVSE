#include "Model.hpp"

// GAME - 0x43AAF0
// GECK - 0x4BE160
Model::Model(const char* apFileName, BSStream* apStream, bool abAssignShaders, bool abKeepUV) {
#ifdef GAME
	ThisCall(0x43AAF0, this, apFileName, apStream, abAssignShaders, abKeepUV);
#else
	ThisCall(0x4BE160, this, apFileName, apStream, abAssignShaders, abKeepUV);
#endif
}

// GAME - 0x43ABF0
// GECK - 0x4BBE30
Model::Model(const char* apFileName, NiNode* apNode) {
#ifdef GAME
	ThisCall(0x43ABF0, this, apFileName, apNode);
#else
	ThisCall(0x4BBE30, this, apFileName, apNode);
#endif
}

// GAME - 0x43AB70
// GECK - 0x4BBD90
Model::~Model() {
#ifdef GAME
	ThisCall(0x43AB70, this);
#else
	ThisCall(0x4BBD90, this);
#endif
}

// GAME - 0x559450
const char* Model::GetFileName() const {
	return pFileName;
}

// GAME - 0x40F6E0
void Model::IncRefCount() {
	InterlockedIncrement(&reinterpret_cast<uint32_t&>(iRefCount));
}

// GAME - 0x40C130
void Model::DecRefCount() {
	InterlockedDecrement(&reinterpret_cast<uint32_t&>(iRefCount));
}

// GAME - 0x92C870
void Model::IncManualRefCount() {
	InterlockedIncrement(&reinterpret_cast<uint32_t&>(iManualRefCount));

}

// GAME - 0x43ACB0
// GECK - 0x4BB3C0
void Model::DecManualRefCount() {
	if (iManualRefCount > 0)
		InterlockedIncrement(&reinterpret_cast<uint32_t&>(iManualRefCount));
}

// GAME - 0x43B410
// GECK - 0x4BB3E0
void Model::ModManualRefCount(int32_t aiVal) {
#ifdef GAME
	ThisCall(0x43B410, this, aiVal);
#else
	ThisCall(0x4BB3E0, this, aiVal);
#endif
}

// GAME - 0x443190
int32_t Model::GetRefCount() const {
	return iManualRefCount + iRefCount;
}

// GAME - 0x726070
int32_t Model::GetActualRefCount() const {
	return iRefCount;
}

// GAME - 0x44DDC0
int32_t Model::GetManualRefCount() const {
	return iManualRefCount;
}

// GAME - 0x43B230
NiNode* Model::GetModel() const {
	return spModel;
}