#pragma once

#include "BSTFreeList.hpp"

template <typename T_Data, uint32_t uiCount>
class BSTStaticFreeList : public BSTFreeList<T_Data> {
public:
	BSTStaticFreeList();
	virtual ~BSTStaticFreeList() override;

	BSTFreeListElem<T_Data> kElems[uiCount];
};

#include "BSTStaticFreeList.inl"