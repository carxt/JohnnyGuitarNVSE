#pragma once

#include "Bethesda/BSMemObject.hpp"

template <class T_Data>
class NiTNewInterface {
public:
    BS_ALLOCATORS;

    static SPEC_RESTRICT T_Data* Allocate(uint32_t auiNumElements);
    static void Deallocate(T_Data* apData);
};

#include "NiTNewInterface.inl"