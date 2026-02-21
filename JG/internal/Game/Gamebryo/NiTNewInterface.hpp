#pragma once

#include "Bethesda/BSMemObject.hpp"

template <class T_Data>
class NiTNewInterface {
public:
    BS_ALLOCATORS;

    // 0x869840
    static T_Data* Allocate(uint32_t uiNumElements) {
        return new T_Data[uiNumElements];
    };

    // 0x8696C0
    static void Deallocate(T_Data* pArray) {
        delete[] pArray;
    };
};