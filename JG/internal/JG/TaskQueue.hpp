#pragma once
#include <queue>

typedef void (*TaskFunction)(const class QueuedTask& arTask);

class ALIGN16 QueuedTask {
public:
	QueuedTask() noexcept;
	QueuedTask(const QueuedTask& arOther) noexcept;
	QueuedTask(QueuedTask&& arOther) noexcept;

	union Item {
		bool		b[4];
		uint8_t		uc[4];
		int8_t 		c[4];

		uint16_t	us[2];
		int16_t		s[2];

		void*		p;
		uint32_t	ui;
		int32_t		i;
		float		f;
	};

	TaskFunction	pFunction;
	Item			kItems[7];
};

#define QUEUED_TASK [](const QueuedTask& arTask)

class TaskQueue {
public:
	static SPEC_NOINLINE void __fastcall QueueTask(const QueuedTask& arTask) noexcept;
	
	static SPEC_NOINLINE void __fastcall ExecuteTasks() noexcept;
private:
	SRWLOCK					kQueueLock = SRWLOCK_INIT;
	std::queue<QueuedTask>	kTaskQueue;

	static TaskQueue kSingleton;
};