#pragma once

#include "NiMemory.hpp"

template <class T_Data>
class NiTMallocInterface {
public:
    // 0x96AFC0
    static T_Data* Allocate(uint32_t uiNumElements) {
        return NiAlloc<T_Data>(uiNumElements);
    };
    // 0x4EDE70
    static void Deallocate(T_Data* pArray) {
        NiFree(pArray);
    };
};