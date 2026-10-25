#pragma once

#include "Bethesda/BSMemObject.hpp"

template <class T>
class NiTDefaultAllocator {
protected:
    class SPEC_EMPTY_BASES AllocNode : public BSMemObject {
    public:
        T           m_element;
    };

public:
    SPEC_RESTRICT void* Allocate();
    void Deallocate(void* apData);
};

#include "NiTDefaultAllocator.inl"