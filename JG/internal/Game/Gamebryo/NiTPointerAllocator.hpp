#pragma once

#include "NiTAbstractPoolAllocator.hpp"

template <class T_Data>
class NiTPointerAllocator : public NiTAbstractPoolAllocator<T_Data> {
public:
    SPEC_RESTRICT void* Allocate();
    void Deallocate(void* apData);
};

#include "NiTPointerAllocator.inl"