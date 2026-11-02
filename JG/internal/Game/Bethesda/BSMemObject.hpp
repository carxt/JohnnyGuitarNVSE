#pragma once

#include "shared/BSMemory/BSMemory.hpp"

class BSMemObject {
public:
	BS_ALLOCATORS

    void*    operator new(size_t stSize, void* p) noexcept { return p; }
    void*    operator new[](size_t stSize, void* p) noexcept { return p; }
    void     operator delete(void*, void*) noexcept {}
    void     operator delete[](void*, void*) noexcept {}
};