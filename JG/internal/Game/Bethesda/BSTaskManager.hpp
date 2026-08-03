#pragma once

#include "BSTask.hpp"
#include "BSTaskManagerThread.hpp"
#include "Gamebryo/NiSmartPointer.hpp"
#include "LockFreeMap.hpp"

template <typename T>
class BSTaskManager : public LockFreeMap<T, NiPointer<BSTask<T>>> {
public:
	virtual bool	    AddTask(BSTask<T>* apTask);
	virtual void	    RunTask(BSTask<T>* apTask);
	virtual bool	    FinishTask(BSTask<T>* apTask);
	virtual void	    CancelAllTasks();
	virtual uint32_t	GetThreadForTask(BSTask<T>* apTask);

	bool						bExit;
	uint32_t					uiSleepingThreads;
	uint32_t					uiSleepLock;
	uint32_t					uiThreadCount;
	BSTaskManagerThread<T>**	ppThreads;
	uint32_t*					pBucketCounts;
	DWORD						uiBucketCountTotal;

	bool RemoveTask(BSTask<T>* apTask);
	void CancelTask(BSTask<T>* apTask, BSTask<T>* apTaskOwner = nullptr);
};

ASSERT_SIZE(BSTaskManager<int64_t>, 0x60);

// GAME - 0x44E050
// GECK - 0x4BBB90
inline bool BSTaskManager<int64_t>::RemoveTask(BSTask<int64_t>* apTask) {
#ifdef GAME
    return ThisCall<bool>(0x44E050, this, apTask);
#else
    return ThisCall<bool>(0x4BBB90, this, apTask);
#endif
}

// GAME - 0x44AC40
// GECK - 0x4BDA90
inline void BSTaskManager<int64_t>::CancelTask(BSTask<int64_t>* apTask, BSTask<int64_t>* apTaskOwner) {
#ifdef GAME
	ThisCall(0x44AC40, this, apTask, apTaskOwner);
#else
	ThisCall(0x4BDA90, this, apTask, apTaskOwner);
#endif
}
