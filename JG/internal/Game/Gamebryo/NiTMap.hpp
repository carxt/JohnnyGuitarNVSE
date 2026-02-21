#pragma once

#include "NiTMapBase.hpp"
#include "NiTDefaultAllocator.hpp"

template <class T_Key, class T_Data>
class NiTMap : public NiTMapBase<NiTDefaultAllocator<T_Data>, T_Key, T_Data> {
public:
	NiTMap(uint32_t auiHashSize = 37);
	~NiTMap();

	virtual NiTMapItem<T_Key, T_Data>* NewItem() override;
	virtual void DeleteItem(NiTMapItem<T_Key, T_Data>* apItem) override;
};

#include "NiTMap.inl"

static_assert(sizeof(NiTMap<uint32_t, uint32_t>) == 0x10, "Wrong structure size!");