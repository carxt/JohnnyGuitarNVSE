#pragma once

#include "Gamebryo/NiSmartPointer.hpp"
#include "BSTaskManager.hpp"
#include "LockFreePriorityQueue.hpp"
#include "IOTask.hpp"

class IOManager : public BSTaskManager<int64_t> {
public:
	uint32_t									uiTaskManagerThreadID;
	LockFreePriorityQueue<NiPointer<IOTask>>*	pPostProcessQueue;
	IO_TASK_PRIORITY							eLoadingQueuedPriority;
	uint32_t(__thiscall*						pGetExternalCountCallback)();
	void(__thiscall*							pUpdateQueueCallback)();
	bool(__thiscall*							pUpdateSecondaryQueueCallback)();
	void(__thiscall*							pLoadQueuedPriorityCallback)(float);
	void(__thiscall*							pPauseCallback)();
	void(__thiscall*							pResumeCallback)();
	uint32_t									unk084;
	uint32_t									unk088;
	uint32_t									unk08C;
	uint32_t									unk090;
	uint32_t									unk094;
	uint32_t									unk098;
	uint32_t									unk09C;

#ifdef GAME
	static constexpr AddressPtr<uint32_t, 0x1202DD8> bUpdating;
#else
	static constexpr AddressPtr<uint32_t, 0xF2CE04> bUpdating;
#endif

	static IOManager* GetSingleton();
	uint32_t GetPostProcessQueueCount() const;
	void AddPostProcessTask(IOTask* apTask);
	void RequeueTask(IOTask* apTask, IO_TASK_PRIORITY aeNewPriority);
	bool UpdateQueue();
	void Pause();
	void Resume();

	bool IsLoadingQueuedPriority() const;

	uint32_t GetBucketForKey(uint8_t aucPriority, uint8_t aucFileIndex) {
		uint8_t ucPriority = aucPriority;
		uint8_t ucFileIndex = aucFileIndex + 4;
		return ucPriority * (ucFileIndex % 20);
	}
};

ASSERT_SIZE(IOManager, 0xA0);