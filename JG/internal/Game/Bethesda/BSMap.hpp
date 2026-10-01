#pragma once

#include "BSMapBase.hpp"

template<class T_Key, class T_Data>
class BSMap : public BSMapBase<T_Key, T_Data> {
public:
	BSMap(uint32_t auiHashSize = 37);
	~BSMap();

	BSMapItem<T_Key, T_Data>* NewItem() override;
	void DeleteItem(BSMapItem<T_Key, T_Data>* apItem) override;
};

#include "BSMap.inl"