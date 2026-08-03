#pragma once

#include "AttachDistant3DTask.hpp"
#include "IOManager.hpp"
#include "LoadedFile.hpp"
#include "LockFreeCaseInsensitiveStringMap.hpp"
#include "QueuedAnimIdle.hpp"
#include "QueuedHelmet.hpp"
#include "QueuedReference.hpp"
#include "QueuedReplacementKFList.hpp"
#include "QueuedTexture.hpp"

class Animation;
class AnimIdle;
class BSFileEntry;
class KFModel;
class Model;
class TESObjectREFR;
class BackgroundCloneThread;
class TESModel;
class TESBoundObject;

class ModelLoader {
public:
	ModelLoader();
	~ModelLoader();

	LockFreeCaseInsensitiveStringMap<Model*>*						pModelMap;
	LockFreeCaseInsensitiveStringMap<KFModel*>*						pKFModelMap;
	LockFreeMap<TESObjectREFR*, NiPointer<QueuedReference>>*		pQueuedReferences;
	LockFreeMap<TESObjectREFR*, NiPointer<QueuedReference>>*		pDelayedQueue;
	LockFreeMap<AnimIdle*, NiPointer<QueuedAnimIdle>>*				pQueuedAnimIdles;
	LockFreeMap<Animation*, NiPointer<QueuedReplacementKFList>>*	pQueuedReplacementKFLists;
	LockFreeMap<TESObjectREFR*, NiPointer<QueuedHelmet>>*			pQueuedHelmets;
	LockFreeQueue<NiPointer<AttachDistant3DTask>>*					pAttachDistant3DTaskQueue;
	LockFreeMap<BSFileEntry*, NiPointer<QueuedTexture>>*			pQueuedTextures;
	LockFreeCaseInsensitiveStringMap<LoadedFile*>*					pLoadingFileMap;
	BackgroundCloneThread*											pBackgroundCloneThread;
	bool															bHasDelayedFree;

	static ModelLoader* GetSingleton();

	bool TryLockModelMap();
	void UnlockModelMap();

	uint32_t GetReferenceCount() const;
	uint32_t GetBackgroundCloningCount() const;

	TESModel* GetModelForBoundObject(TESBoundObject* apBoundObject, TESObjectREFR* apRef) const;

	NiNode* LoadFile(const char* apPath, LOD_MULT aeLODFadeMult = LOD_MULT::NONE, bool abAssignShaders = true, bool abSuppressWarning = false, bool abKeepUV = false, bool abNoUseCountIncrease = false);
	KFModel* LoadKF(const char* apPath);

	bool LookupModel(const char* apPath, NiPointer<Model>& arOut);

	void ReleaseFile(const char* apPath);
	void ReleaseModel(const char* apPath, bool abDeleteIfUnreferenced, int32_t aiNumDecrements);

	void QueueReference(TESObjectREFR* apRefr, IO_TASK_PRIORITY aePriority, bool abAllowQueueReferenceQueuing);

	bool QueueTexture(const char* apPath, IO_TASK_PRIORITY aePriority, QueuedFile* apFile);
	bool QueueTexture(BSFileEntry* apFileEntry, IO_TASK_PRIORITY aePriority, QueuedFile* apFile);

	void QueueModel(const char* apSource, IO_TASK_PRIORITY aePriority, QueuedFile* apParent, LOD_MULT aeLODFadeMult = LOD_MULT::NONE, bool abAssignShaders = true, bool abIncreaseCounter = false, bool abKeepUV = false);
	void QueueModel(TESModel* apModel, IO_TASK_PRIORITY aePriority, QueuedFile* apParent, LOD_MULT aeLODFadeMult = LOD_MULT::NONE, bool abAssignShaders = true, bool abIncreaseCounter = false, bool abKeepUV = false);
	void QueueModel(TESModel* apModel, NiPointer<IOTask>& arTask, IO_TASK_PRIORITY aePriority, QueuedFile* apParent, LOD_MULT aeLODFadeMult = LOD_MULT::NONE, bool abAssignShaders = true, bool abIncreaseCounter = false, bool abKeepUV = false, float afOverriddenVisualDistance = 0.f);

	void LoadAddons(NiNode* apNode);
};

ASSERT_SIZE(ModelLoader, 0x30)