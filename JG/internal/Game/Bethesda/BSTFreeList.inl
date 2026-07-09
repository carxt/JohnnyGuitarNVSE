#pragma once

#include "BSTFreeList.hpp"

template<typename T>
inline BSTFreeListElem<T>::BSTFreeListElem() : pNext(nullptr) {
}

template<typename T>
inline BSTFreeListElem<T>::~BSTFreeListElem() {
}

template <typename T>
inline void BSTFreeListElem<T>::ConstructElem(const T& arItem) {
	new (reinterpret_cast<T*>(&kRawElem)) T();
	*reinterpret_cast<T*>(&kRawElem) = arItem;
}

template <typename T>
inline void BSTFreeListElem<T>::DestructElem() {
	reinterpret_cast<T*>(&kRawElem)->~T();
}

template<typename T>
inline BSTFreeList<T>::BSTFreeList() : uiLock(0), pFree(nullptr) {
}

template<typename T>
inline BSTFreeList<T>::~BSTFreeList() {
}

template<typename T>
inline bool BSTFreeList<T>::Allocate(BSTFreeListElem<T>*& apElement, const T& arItem) {
	if (!DoAllocate(apElement))
		return false;
	apElement->ConstructElem(arItem);
	return true;
}

template<typename T>
inline void BSTFreeList<T>::Deallocate(BSTFreeListElem<T>*& apElement) {
	apElement->DestructElem();
	DoDeallocate(apElement);
}

template<typename T>
inline void BSTFreeList<T>::Lock() {
	while (InterlockedCompareExchange(&uiLock, 0u, 1u));
	_mm_mfence();
}

template<typename T>
inline void BSTFreeList<T>::Unlock() {
	_mm_mfence();
	InterlockedCompareExchange(&uiLock, 1u, 0u);
}

template<typename T>
inline void BSTFreeList<T>::Init(uint32_t auiCount, BSTFreeListElem<T>* apElements) {
	pFree = apElements;

	Lock();

	uint32_t i = 0;
	BSTFreeListElem<T>* pIter = apElements;
	while (i < auiCount - 1) {
		pIter->pNext = pIter + 1;
		++i;
		++pIter;
	}
	pIter->pNext = nullptr;

	Unlock();
}

// GAME - 0x6ECD60
template<typename T>
inline bool BSTFreeList<T>::DoAllocate(BSTFreeListElem<T>*& apElement) {
	Lock();

	bool bResult;
	if (pFree) {
		apElement = pFree;
		pFree = apElement->pNext;
		apElement->pNext = nullptr;
		bResult = true;
	}
	else {
		apElement = nullptr;
		bResult = false;
	}

	Unlock();

	return bResult;
}

// GAME - 0x6ECC70
template<typename T>
inline void BSTFreeList<T>::DoDeallocate(BSTFreeListElem<T>*& apElement) {
	Lock();

	apElement->pNext = pFree;
	pFree = apElement;
	apElement = nullptr;

	Unlock();
}