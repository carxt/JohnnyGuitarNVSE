#pragma once

#include "NiTPointerAllocator.hpp"

inline SPEC_RESTRICT void* NiTPointerAllocator<size_t>::Allocate() {
#ifdef GAME
    return ThisCall<void*>(0x43A010, this);
#else
    return ThisCall<void*>(0x4120F0, this);
#endif
}

inline void NiTPointerAllocator<size_t>::Deallocate(void* apData) {
#ifdef GAME
    ThisCall(0x45CEE0, this, apData);
#else
    ThisCall(0x42E570, this, apData);
#endif
}