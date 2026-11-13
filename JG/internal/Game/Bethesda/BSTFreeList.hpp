#pragma once

template <typename T>
class BSTFreeListElem {
public:
	BSTFreeListElem();
	~BSTFreeListElem();

	uint8_t						kRawElem[sizeof(T)];
	BSTFreeListElem<T>*	pNext;

	void ConstructElem(const T& arItem);
	void DestructElem();

	T& Elem() {
		return *reinterpret_cast<T*>(&kRawElem);
	}
};

template <typename T>
class BSTFreeList {
public:
	BSTFreeList();
	virtual ~BSTFreeList();

	uint32_t			uiLock;
	BSTFreeListElem<T>*	pFree;

	bool Allocate(BSTFreeListElem<T>*& apElement, const T& arItem);
	void Deallocate(BSTFreeListElem<T>*& apElement);

	void Lock();
	void Unlock();

protected:
	void Init(uint32_t auiCount, BSTFreeListElem<T>* apElements);

private:
	bool DoAllocate(BSTFreeListElem<T>*& apElement);
	void DoDeallocate(BSTFreeListElem<T>*& apElement);
};

#include "BSTFreeList.inl"