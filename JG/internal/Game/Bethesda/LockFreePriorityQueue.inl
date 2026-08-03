#pragma once

#include "LockFreePriorityQueue.hpp"

template<typename T>
inline LockFreePriorityQueue<T>::LockFreePriorityQueue(uint32_t auiSize, uint32_t auiMaxThreads, uint32_t auiDeleteBatchSize) {
	AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
	uiCount = 0;
	uiSize = auiSize;
	ppQueues = new LockFreeQueue<T>*[auiSize];
	for (uint32_t i = 0; i < uiSize; i++) {
		ppQueues[i] = new LockFreeQueue<T>(auiMaxThreads, auiDeleteBatchSize);
	}
}

template<typename T>
inline LockFreePriorityQueue<T>::~LockFreePriorityQueue() {
	for (uint32_t i = 0; i < uiSize; i++) {
		if (ppQueues[i])
			delete ppQueues[i];
	}

	delete[] ppQueues;
}

template<typename T>
inline void LockFreePriorityQueue<T>::IncrementCount() {
	InterlockedIncrement(&uiCount);
}

template<typename T>
inline void LockFreePriorityQueue<T>::DecrementCount() {
	InterlockedDecrement(&uiCount);
}

template<typename T>
inline uint32_t LockFreePriorityQueue<T>::GetCount() const {
	return uiCount;
}

// GAME - 0xC3E420
// GECK - 0x9DA060
template<typename T>
inline bool LockFreePriorityQueue<T>::Pop(T& aData) {
	for (uint32_t i = 0; i < uiSize; ++i) {
		if (ppQueues[i]->Pop(aData)) {
			DecrementCount();
			return true;
		}
	}
	return false;
}