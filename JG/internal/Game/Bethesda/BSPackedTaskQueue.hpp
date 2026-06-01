#pragma once

#include "BSTCommonScrapHeapMessageQueue.hpp"
#include "BSPackedTask.hpp"
#include "BSSemaphore.hpp"

class BSPackedTaskQueue {
public:
	BSTCommonScrapHeapMessageQueue<BSPackedTask>	kQueue;
	BSSemaphore										kSemaphore;
	void(__cdecl*									pUnpackFunc)(BSPackedTask*);
	bool											bProcessing;

	bool AddTask(BSPackedTask& arTask);

	void Wait();
};

ASSERT_SIZE(BSPackedTaskQueue, 0x28);