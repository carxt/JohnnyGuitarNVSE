#pragma once

#include "BSTaskThread.hpp"
#include "LockFreeQueue.hpp"
#include "QueuedReference.hpp"
#include "Gamebryo/NiSmartPointer.hpp"

class BackgroundCloneThread : public BSTaskThread {
public:
	bool										bExit;
	uint32_t									uiRunningCount;
	LockFreeQueue<NiPointer<QueuedReference>>*	pProcessTaskQueue;

	uint32_t GetQueuedCount() const;
};

ASSERT_SIZE(BackgroundCloneThread, 0x3C);