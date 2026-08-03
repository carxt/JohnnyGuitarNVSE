#pragma once

#include "LockFreeQueue.hpp"

template <typename T>
class LockFreePriorityQueue {
public:
	LockFreePriorityQueue(uint32_t auiSize, uint32_t auiMaxThreads, uint32_t auiDeleteBatchSize);
	virtual				~LockFreePriorityQueue();
	virtual void		IncrementCount();
	virtual void		DecrementCount();
	virtual uint32_t	GetCount() const;

	LockFreeQueue<T>**	ppQueues;
	uint32_t			uiSize;
	uint32_t			uiCount;

	bool Pop(T& aData);
};

#include "LockFreePriorityQueue.inl"

ASSERT_SIZE(LockFreePriorityQueue<uint32_t>, 0x10);