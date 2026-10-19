#pragma once

#include "NiTMallocInterface.hpp"
#include "NiMemory.hpp"

// GAME - 0x96AFC0
template<class T_Data>
inline SPEC_RESTRICT T_Data* NiTMallocInterface<T_Data>::Allocate(uint32_t auiNumElements) {
    return NiAlloc<T_Data>(auiNumElements);
}

// GAME - 0x4EDE70
template<class T_Data>
inline void NiTMallocInterface<T_Data>::Deallocate(T_Data* apData) {
    NiFree(apData);
};