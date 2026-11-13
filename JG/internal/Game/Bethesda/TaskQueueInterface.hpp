#pragma once

class NiAVObject;
class BSPackedTaskQueue;

class TaskQueueInterface {
public:
	BSPackedTaskQueue*	pQueue;
	BSPackedTaskQueue*	pSecondaryQueue;
	BSPackedTaskQueue*	pActiveQueue;
	uint32_t			uiThreadID;

	static TaskQueueInterface* GetSingleton();

	void QueueBiped3DDetach(NiAVObject* apObject);
};

ASSERT_SIZE(TaskQueueInterface, 0x10);