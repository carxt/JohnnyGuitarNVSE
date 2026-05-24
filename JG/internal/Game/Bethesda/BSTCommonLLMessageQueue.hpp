#pragma once

#include "BSTCommonMessageQueue.hpp"
#include "BSTFreeList.hpp"

template <class T>
class BSTCommonLLMessageQueue : public BSTCommonMessageQueue<T> {
public:
	BSTCommonLLMessageQueue(BSTFreeList<T>* apList);
	~BSTCommonLLMessageQueue() override;

	BSTFreeList<T>*			pFreeList;
	BSTFreeListElem<T>*		pHead;
	BSTFreeListElem<T>**	ppTail;

	bool DoTryPush(const T& arMessage) override;
	bool DoTryPop(T& arMessage) override;
};

#include "BSTCommonLLMessageQueue.inl"

//ASSERT_SIZE(BSTCommonLLMessageQueue<uint32_t>, 0x14);