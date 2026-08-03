#pragma once

#include "LockFreeQueue.hpp"
#include "LockFreePriorityQueue.hpp"

template<class T>
inline LockFreeQueue<T>::LockFreeQueueNode* LockFreeQueue<T>::LockFreeQueueNode::GetNextDelete() {
	return *reinterpret_cast<LockFreeQueueNode**>(reinterpret_cast<char*>(this) + sizeof(size_t));
}

template<class T>
inline void LockFreeQueue<T>::LockFreeQueueNode::SetNextDelete(LockFreeQueueNode* apNext) {
	*reinterpret_cast<LockFreeQueueNode**>(reinterpret_cast<char*>(this) + sizeof(size_t)) = apNext;
}

template<class T>
inline LockFreeQueue<T>::LockFreeQueue(uint32_t auiMaxThreads, uint32_t auiDeleteBatchSize) {
	AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
	uiCount = 0;
	pHead = new LockFreeQueueNode;
	pTail = pHead;
	uiDeleteBatchSize = auiDeleteBatchSize;
	pReferencedNodes = new LockFreeQueueNode*[auiMaxThreads * 2];
	pManager = new Manager(auiMaxThreads);
}

template<class T>
inline LockFreeQueue<T>::~LockFreeQueue() {
	RemoveAll(true);
	delete[] pReferencedNodes;
}

template<class T>
inline void* LockFreeQueue<T>::AllocateInterface(uint32_t auiThread) {
	AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
	const uint32_t uiIndex = auiThread * 2;
	return new LockFreeQueueInterface(this, &pReferencedNodes[uiIndex], &pReferencedNodes[uiIndex + 1]);
}	

template<class T>
inline void LockFreeQueue<T>::IncrementCount() {
	InterlockedIncrement(&uiCount);
}

template<class T>
inline void LockFreeQueue<T>::DecrementCount() {
	InterlockedDecrement(&uiCount);
}

template<class T>
inline uint32_t LockFreeQueue<T>::GetCount() const {
	return uiCount;
}

template<class T>
inline uint32_t LockFreeQueue<T>::GetMaxThreads() const {
	return pManager->uiMaxThreads;
}

template<class T>
inline void LockFreeQueue<T>::RemoveAll(bool abNoNewManager) {
	Lock();
	AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
	const uint32_t uiMaxThreads = pManager->uiMaxThreads;
	
	delete pManager;
	pManager = nullptr;
	uiCount = 0;

	while (pHead) {
		auto pNext = pHead->pNext;
		pHead->tData = 0;
		delete pHead;
		pHead = pNext;
	}

	if (!abNoNewManager) {
		pHead = new LockFreeQueueNode;
		pTail = pHead;
		pManager = new Manager(uiMaxThreads);
	}
	Unlock();
}


template<class T>
inline void LockFreeQueue<T>::Push(const T& arData) {
	kLock.Lock();
	GetInterface()->Push(arData);
	kLock.Unlock();
};

template<class T>
inline bool LockFreeQueue<T>::Pop(T& arData) {
	Lock();
	bool bFound = GetInterface()->Pop(arData);
	Unlock();
	return bFound;
};

template<class T>
inline void LockFreeQueue<T>::LockFreeQueueInterface::Push(const T& arData) {
	AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);

	LockFreeQueueNode* pNewNode = new LockFreeQueueNode;
	pNewNode->tData = const_cast<T>(arData);

	LockFreeQueueNode* pIter = nullptr;
	do {
		while (true) {
			do {
				pIter = pOwner->pTail;
				*pReferencedNodes[0] = pIter;
			} while (pIter != pOwner->pTail);

			if (!pIter->pNext)
				break;

			ThreadSafeStructures::CompareExchange(&pOwner->pTail, pIter->pNext, pIter);
		}
	} while (!ThreadSafeStructures::CompareExchange(pIter, pNewNode, nullptr));

	pOwner->IncrementCount();

	ThreadSafeStructures::CompareExchange(&pOwner->pTail, pNewNode, pIter);

	*pReferencedNodes[0] = nullptr;
}

template<class T>
inline bool LockFreeQueue<T>::LockFreeQueueInterface::Pop(T& arData) {
	LockFreeQueueNode* pCurrent = nullptr;
	LockFreeQueueNode* pNext = nullptr;
	LockFreeQueueNode* pLast = nullptr;
	do {
		while (true) {
			do {
				do {
					pCurrent = pOwner->pHead;
					*pReferencedNodes[0] = pCurrent;
				} while (pCurrent != pOwner->pHead);
				pLast = pOwner->pTail;
				pNext = pCurrent->pNext;
				*pReferencedNodes[1] = pCurrent->pNext;
			} while (pCurrent != pOwner->pHead);

			if (!pNext) {
				*pReferencedNodes[0] = 0;
				arData = 0;
				return false;
			}

			if (pCurrent != pLast)
				break;
			ThreadSafeStructures::CompareExchange(&pOwner->pTail, pNext, pLast);
		}
		arData = pNext->tData;
	} while (!ThreadSafeStructures::CompareExchange(&pOwner->pHead, pNext, pCurrent));
	pOwner->DecrementCount();
	pNext->tData = 0;
	*pReferencedNodes[0] = nullptr;
	*pReferencedNodes[1] = nullptr;
	DeleteNode(pCurrent);
	return 1;
}

template<class T>
inline void LockFreeQueue<T>::LockFreeQueueInterface::DeleteNode(LockFreeQueueNode* apNode) {
	apNode->tData = 0;
	apNode->SetNextDelete(pDeleteHead);
	pDeleteHead = apNode;
	++uiDeleteCount;
	if (uiDeleteCount == pOwner->uiDeleteBatchSize)
		ScanForDeletedNodes();
}

template<class T>
inline void LockFreeQueue<T>::LockFreeQueueInterface::ScanForDeletedNodes() {
	AUTO_MEM_CONTEXT(MEM_CONTEXT::THREAD_SAFE_STRUCT);
	uint32_t uiMaxThreads = pOwner->GetMaxThreads();
	uint32_t uiArraySize = 2 * uiMaxThreads;
	LockFreeQueueNode** ppTempNodes = new LockFreeQueueNode*[uiArraySize];
	memcpy(ppTempNodes, pOwner->pReferencedNodes, sizeof(size_t) * uiArraySize);
	LockFreeQueueNode* pCurrentHead = nullptr;
	uint32_t uiCounter = 0;
	while (pDeleteHead) {
		LockFreeQueueNode* pItem = pDeleteHead;
		pDeleteHead = pItem->GetNextDelete();
		bool bFound = false;
		for (uint32_t i = 0; i < uiArraySize; ++i) {
			if (pItem == ppTempNodes[i]) {
				bFound = true;
				break;
			}
		}
		if (bFound) {
			pItem->SetNextDelete(pCurrentHead);
			pCurrentHead = pItem;
			++uiCounter;
		}
		else {
			pItem->SetNextDelete(nullptr);
			if (pItem)
				delete pItem;
		}
	}

	delete[] ppTempNodes;
	pDeleteHead = pCurrentHead;
	uiDeleteCount = uiCounter;
}