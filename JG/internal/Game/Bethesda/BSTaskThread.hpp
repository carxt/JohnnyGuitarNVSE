#pragma once

#include "BSSemaphore.hpp"
#include "bhkThreadMemoryRouter.hpp"

class BSTaskThread {
public:
	BSTaskThread(const char* apThreadName);
	virtual ~BSTaskThread();
	virtual void ThreadUpdate();

	HANDLE					hThread;
	DWORD					uiThreadID;
	BSSemaphore				kTaskSemaphore;
	BSSemaphore				kPauseSemaphore;
	bhkThreadMemoryRouter	kHavokData;

	void SignalTask();
	void WaitTask();

	void SignalPause();
	void WaitPause();

	bool TestPauseSemaphore();
};

ASSERT_SIZE(BSTaskThread, 0x30);