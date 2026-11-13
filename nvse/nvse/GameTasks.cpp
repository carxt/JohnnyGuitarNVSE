#include "GameTasks.h"

ModelLoader* ModelLoader::GetSingleton() {
	return *(ModelLoader**)0x011C3B3C;
}

void ModelLoader::QueueReference(TESObjectREFR* apRef, IO_TASK_PRIORITY aePriority, bool abAllowQueueReferenceQueuing) {
	ThisCall(0x444850, this, apRef, aePriority, abAllowQueueReferenceQueuing);
}

TESModel* ModelLoader::GetModelForBoundObject(TESBoundObject* apBoundObject, TESObjectREFR* apRef) {
	return ThisCall<TESModel*>(0x446A60, this, apBoundObject, apRef);
}

// GAME - 0x447080
// GECK - 0x4C0040
NiNode* ModelLoader::LoadFile(const char* apPath, uint32_t aeLODFadeMult, bool abAssignShaders, bool abSuppressWarning, bool abKeepUV, bool abNoUseCountIncrease) {
#ifdef GAME
	return ThisCall<NiNode*>(0x447080, this, apPath, aeLODFadeMult, abAssignShaders, abSuppressWarning, abKeepUV, abNoUseCountIncrease);
#else
	return ThisCall<NiNode*>(0x4C0040, this, apPath, aeLODFadeMult, abAssignShaders, abSuppressWarning, abKeepUV, abNoUseCountIncrease);
#endif
}
