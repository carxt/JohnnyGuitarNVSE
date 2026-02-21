#pragma once

#include "NiTMapBase.hpp"
#include "NiTPointerAllocator.hpp"

template <class T_Key, class T_Data>
class NiTPointerMap : public NiTMapBase<NiTPointerAllocator<size_t>, T_Key, T_Data> {
public:
    NiTPointerMap(uint32_t auiHashSize = 37);
    ~NiTPointerMap();

    virtual NiTMapItem<T_Key, T_Data>* NewItem() override;
    virtual void DeleteItem(NiTMapItem<T_Key, T_Data>* apItem) override;
};

#include "NiTPointerMap.inl"