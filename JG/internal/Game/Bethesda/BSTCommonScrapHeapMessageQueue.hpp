#pragma once

#include "BSTCommonMessageQueue.hpp"
#include "ScrapHeap.hpp"
#include "BSScrapHeapQueueElem.hpp"

template <class T_Data>
class BSTCommonScrapHeapMessageQueue : public BSTCommonMessageQueue<T_Data> {
public:
	ScrapHeap*						pScrapHeap;
	BSScrapHeapQueueElem<T_Data>*	pHead;
	BSScrapHeapQueueElem<T_Data>**	ppTail;
};

ASSERT_SIZE(BSTCommonScrapHeapMessageQueue<uint32_t>, 0x14);