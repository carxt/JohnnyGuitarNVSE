#include "ModelLoader.hpp"
#include "BackgroundCloneThread.hpp"

ModelLoader* ModelLoader::GetSingleton() {
#ifdef GAME
	return *reinterpret_cast<ModelLoader**>(0x011C3B3C);
#else
	return *reinterpret_cast<ModelLoader**>(0xED36A0);
#endif
}

// GAME - 0x868250
bool ModelLoader::TryLockModelMap() {
#ifdef GAME
	return ThisCall<bool>(0x868250, this);
#else
	return pModelMap->TryLock();
#endif
}

// GAME - 0x4AAF10
void ModelLoader::UnlockModelMap() {
#ifdef GAME
	ThisCall(0x4AAF10, this);
#else
	pModelMap->Unlock();
#endif
}

// GAME - 0x446C90
uint32_t ModelLoader::GetReferenceCount() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x446C90, this);
#else
	return pQueuedReferences->GetCount();
#endif
}

// GAME - 0x446DC0
uint32_t ModelLoader::GetBackgroundCloningCount() const {
#ifdef GAME
	return ThisCall<uint32_t>(0x446DC0, this);
#else
	return pBackgroundCloneThread->GetQueuedCount();
#endif
}

// GAME - 0x446A60
// GECK - 0x4BB6D0
TESModel* ModelLoader::GetModelForBoundObject(TESBoundObject* apBoundObject, TESObjectREFR* apRef) const {
#ifdef GAME
	return ThisCall<TESModel*>(0x446A60, this, apBoundObject, apRef);
#else
	return ThisCall<TESModel*>(0x4BB6D0, this, apBoundObject, apRef);
#endif
}

// GAME - 0x447080
// GECK - 0x4C0040
NiNode* ModelLoader::LoadFile(const char* apPath, LOD_MULT_TYPE aeLODFadeMult, bool abAssignShaders, bool abSuppressWarning, bool abKeepUV, bool abNoUseCountIncrease) {
#ifdef GAME
	return ThisCall<NiNode*>(0x447080, this, apPath, aeLODFadeMult, abAssignShaders, abSuppressWarning, abKeepUV, abNoUseCountIncrease);
#else
	return ThisCall<NiNode*>(0x4C0040, this, apPath, aeLODFadeMult, abAssignShaders, abSuppressWarning, abKeepUV, abNoUseCountIncrease);
#endif
}

// GAME - 0x4471C0
// GECK - 0x4C28E0
KFModel* ModelLoader::LoadKF(const char* apPath) {
#ifdef GAME
	return ThisCall<KFModel*>(0x4471C0, this, apPath);
#else
	return ThisCall<KFModel*>(0x4C28E0, this, apPath);
#endif
}

// GAME - 0x4472A0
// GECK - 0x4BD800
bool ModelLoader::LookupModel(const char* apPath, NiPointer<Model>& arOut) {
#ifdef GAME
	return ThisCall<bool>(0x4472A0, this, apPath, &arOut);
#else
	return ThisCall<bool>(0x4BD800, this, apPath, &arOut);
#endif
}

// GAME - 0x45A5E0
void ModelLoader::ReleaseFile(const char* apPath) {
#ifdef GAME
	ThisCall(0x45A5E0, this, apPath);
#else
	ReleaseModel(apPath, true, 1);
#endif
}

// GAME - 0x445300
// GECK - 0x4BFAF0
void ModelLoader::ReleaseModel(const char* apPath, bool abDeleteIfUnreferenced, int32_t aiNumDecrements) {
#ifdef GAME
	ThisCall(0x445300, this, apPath, abDeleteIfUnreferenced, aiNumDecrements);
#else
	ThisCall(0x4BFAF0, this, apPath, abDeleteIfUnreferenced, aiNumDecrements);
#endif
}

// GAME - 0x444850
// GECK - 0x4BF5A0
void ModelLoader::QueueReference(TESObjectREFR* apRefr, IO_TASK_PRIORITY aePriority, bool abAllowQueueReferenceQueuing) {
#ifdef GAME
	ThisCall(0x444850, this, apRefr, aePriority, (uint32_t)abAllowQueueReferenceQueuing);
#else
	ThisCall(0x4BF5A0, this, apRefr, aePriority, (uint32_t)abAllowQueueReferenceQueuing);
#endif
}

// GAME - 0x4436C0
// GECK - 0x4C1E20
bool ModelLoader::QueueTexture(const char* apPath, IO_TASK_PRIORITY aePriority, QueuedFile* apFile) {
#ifdef GAME
	return ThisCall<bool>(0x4436C0, this, apPath, aePriority, apFile);
#else
	return ThisCall<bool>(0x4C1E20, this, apPath, aePriority, apFile);
#endif
}

// GAME - 0x443AF0
#ifdef GAME
bool ModelLoader::QueueTexture(BSFileEntry* apFileEntry, IO_TASK_PRIORITY aePriority, QueuedFile* apFile) {
	return ThisCall<bool>(0x443AF0, this, apFileEntry, aePriority, apFile);
}
#endif

// GAME - 0x444040
// GECK - 0x4C21B0
void ModelLoader::QueueModel(const char* apSource, IO_TASK_PRIORITY aePriority, QueuedFile* apParent, LOD_MULT_TYPE aeLODFadeMult, bool abAssignShaders, bool abIncreaseCounter, bool abKeepUV) {
#ifdef GAME
	ThisCall(0x444040, this, apSource, aePriority, apParent, aeLODFadeMult, abAssignShaders, abIncreaseCounter, abKeepUV);
#else
	ThisCall(0x4C21B0, this, apSource, aePriority, apParent, aeLODFadeMult, abAssignShaders, abIncreaseCounter, abKeepUV);
#endif
}

// GAME - 0x443D30
// GECK - 0x4C2110
void ModelLoader::QueueModel(TESModel* apModel, IO_TASK_PRIORITY aePriority, QueuedFile* apParent, LOD_MULT_TYPE aeLODFadeMult, bool abAssignShaders, bool abIncreaseCounter, bool abKeepUV) {
#ifdef GAME
	ThisCall(0x443D30, this, apModel, aePriority, apParent, aeLODFadeMult, abAssignShaders, abIncreaseCounter, abKeepUV);
#else
	ThisCall(0x4C2110, this, apModel, aePriority, apParent, aeLODFadeMult, abAssignShaders, abIncreaseCounter, abKeepUV);
#endif
}

// GAME - 0x443DC0
// GECK - 0x4BED50
void ModelLoader::QueueModel(TESModel* apModel, NiPointer<IOTask>& arTask, IO_TASK_PRIORITY aePriority, QueuedFile* apParent, LOD_MULT_TYPE aeLODFadeMult, bool abAssignShaders, bool abIncreaseCounter, bool abKeepUV, float afOverriddenVisualDistance) {
#ifdef GAME
	ThisCall(0x443DC0, this, apModel, &arTask, aePriority, apParent, aeLODFadeMult, abAssignShaders, abIncreaseCounter, abKeepUV, afOverriddenVisualDistance);
#else
	ThisCall(0x4BED50, this, apModel, &arTask, aePriority, apParent, aeLODFadeMult, abAssignShaders, abIncreaseCounter, abKeepUV, afOverriddenVisualDistance);
#endif
}

// GAME - 0x448A90
// GECK - 0x4C0200
void ModelLoader::LoadAddons(NiNode* apNode) {
#ifdef GAME
	ThisCall(0x448A90, this, apNode);
#else
	ThisCall(0x4C0200, this, apNode);
#endif
}
