#pragma once

#include "NiTDefaultAllocator.hpp"

template<class T>
inline SPEC_RESTRICT void* NiTDefaultAllocator<T>::Allocate() {
    return new AllocNode;
}

template<class T>
inline void NiTDefaultAllocator<T>::Deallocate(void* apData) {
    delete static_cast<AllocNode*>(apData);
}
