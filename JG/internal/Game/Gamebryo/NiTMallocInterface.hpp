#pragma once

template <class T_Data>
class NiTMallocInterface {
public:
    static SPEC_RESTRICT T_Data* Allocate(uint32_t auiNumElements);
    static void Deallocate(T_Data* apData);
};

#include "NiTMallocInterface.inl"