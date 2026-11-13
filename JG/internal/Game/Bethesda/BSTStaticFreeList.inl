#pragma once

#include "BSTStaticFreeList.hpp"

template<typename T_Data, uint32_t uiCount>
inline BSTStaticFreeList<T_Data, uiCount>::BSTStaticFreeList() {
	BSTFreeList<T_Data>::Init(uiCount, kElems);
}

template<typename T_Data, uint32_t uiCount>
inline BSTStaticFreeList<T_Data, uiCount>::~BSTStaticFreeList() {
}
