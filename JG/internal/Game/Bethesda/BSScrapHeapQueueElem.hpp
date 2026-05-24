#pragma once

template <class T_Data>
struct BSScrapHeapQueueElem {
	BSScrapHeapQueueElem<T_Data>* pNext;
	T_Data Elem;
};