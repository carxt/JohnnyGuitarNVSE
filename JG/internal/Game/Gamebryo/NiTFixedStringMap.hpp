#pragma once

#include "NiTFixedStringMapBase.hpp"

template <class T_Data>
class NiTFixedStringMap : public NiTFixedStringMapBase<NiTDefaultAllocator<T_Data>, T_Data> {
public:
	NiTFixedStringMap(uint32_t auiHashSize = 37);
	~NiTFixedStringMap() override;

	NiTMapItem<NiFixedString, T_Data>* NewItem() override;
	void DeleteItem(NiTMapItem<NiFixedString, T_Data>* apItem) override;
};

#include "NiTFixedStringMap.inl"

ASSERT_SIZE(NiTFixedStringMap<uint32_t>, 0x10);