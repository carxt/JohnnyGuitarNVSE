#pragma once

#include "BSSemaphore.hpp"
#include "BSTaskletGroup.hpp"
#include "BSTasklet.hpp"

class BSTaskletManager {
public:
	virtual ~BSTaskletManager();
	virtual void SetTaskletThreadPriority(uint32_t auiCore, int32_t aiPriority);
	virtual void ShutdownAllTasks();
	virtual bool IsTaskletThread(uint32_t auiThreadID);
	virtual bool CreateTaskGroupData(BSTaskletGroupData*& apResult);
	virtual bool OpenTaskGroupData(BSTaskletGroupData* apGroupData);
	virtual bool AttachTaskData(BSTaskletGroupData* apGroupData, BSTaskletData* apTaskData, bool abLastTask);
	virtual bool CloseTaskGroupData(BSTaskletGroupData* apGroupData);
	virtual void DestroyTaskGroupData(BSTaskletGroupData* apGroupData);
	virtual void InstanceAvailable();

	bool		bAvailable;
	bool		bSignaled;
	BSSemaphore kInstanceSemaphore;

	static BSTaskletManager* GetSingleton();

	bool CreateTaskGroup(BSTaskletGroup& arGroup);
	bool OpenTaskGroup(BSTaskletGroup& arGroup);
	bool AttachTask(BSTaskletGroup& arGroup, BSTasklet& arTask, bool abLastTask);
	bool CloseTaskGroup(BSTaskletGroup& arGroup);
	void DestroyTaskGroup(BSTaskletGroup& arGroup);
};

ASSERT_SIZE(BSTaskletManager, 0x14);