#pragma once

#include "BSTask.hpp"

enum IO_TASK_PRIORITY {
	IO_TASK_PRIORITY_CRITICAL	= 0,
	IO_TASK_PRIORITY_VERY_HIGH	= 1,
	IO_TASK_PRIORITY_HIGH		= 2,
	IO_TASK_PRIORITY_MID		= 3,
	IO_TASK_PRIORITY_LOW		= 4,
	IO_TASK_PRIORITY_VERY_LOW	= 5,
	IO_TASK_PRIORITY_COUNT		= 6,
	IO_TASK_PRIORITY_INVALID	= 7,
	IO_TASK_PRIORITY_HIGHEST	= IO_TASK_PRIORITY_CRITICAL,
	IO_TASK_PRIORITY_LOWEST		= IO_TASK_PRIORITY_VERY_LOW,
};

class IOTask : public BSTask<int64_t> {
public:
	IOTask(IO_TASK_PRIORITY aePriority);
	virtual ~IOTask();

	virtual void PostProcess();
	virtual void GenerateKey();
	virtual void Requeue(IO_TASK_PRIORITY aeNewPriority);

	void SetIOTaskPriority(IO_TASK_PRIORITY aePriority);

	uint8_t GetPriority() const;
	void SetPriority(uint8_t aePriority);

	void SetKey(uint8_t aeFileIndex, uint32_t auiOffset, uint8_t aePriority, uint16_t ausCounter);

	void AddToPostProcessQueue();

	static uint8_t GetPriorityFromKey(int64_t& arKey);

	static uint32_t GetNextCounter();

	static uint32_t GetNextOffset();

private:
	static constexpr AddressPtr<uint32_t, 0x1202D9C> iStaticCounter;
	static constexpr AddressPtr<uint32_t, 0x1202DA0> iStaticOffset;
};

ASSERT_SIZE(IOTask, 0x18);