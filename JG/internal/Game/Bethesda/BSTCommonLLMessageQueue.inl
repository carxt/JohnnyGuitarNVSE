#pragma once

#include "BSTCommonLLMessageQueue.hpp"

template<class T>
inline BSTCommonLLMessageQueue<T>::BSTCommonLLMessageQueue(BSTFreeList<T>* apList) {
	pFreeList = apList;
	pHead = nullptr;
	ppTail = &pHead;
}

template<class T>
inline BSTCommonLLMessageQueue<T>::~BSTCommonLLMessageQueue() {
	T kMessage{};
	while (BSTCommonMessageQueue<T>::TryPop(kMessage));
}

// GAME - 0x9056F0
template<class T>
inline bool BSTCommonLLMessageQueue<T>::DoTryPush(const T& arMessage) {
	if (!pFreeList)
		return false;

	BSTFreeListElem<T>* pElement;
	if (!pFreeList->Allocate(pElement, arMessage))
		return false;

	if (!pHead)
		ppTail = &pHead;

	*ppTail = pElement;
	pElement->pNext = nullptr;
	ppTail = &pElement->pNext;
	return true;
}

// GAME - 0x6EC2E0
template<class T>
inline bool BSTCommonLLMessageQueue<T>::DoTryPop(T& arMessage) {
	auto pCurrent = pHead;
	if (!pCurrent)
		return false;

	arMessage = pCurrent->Elem();
	pHead = pCurrent->pNext;
	pFreeList->Deallocate(pCurrent);
	return true;
}
