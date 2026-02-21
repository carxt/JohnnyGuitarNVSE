#pragma once

#include "NiMemObject.hpp"

#define NiTDefaultAllocator DFALL

template <class T>
class NiTDefaultAllocator {
protected:
    class AllocNode : public NiMemObject {
    public:
        AllocNode*  m_pkNext = nullptr;
        void*       m_pkData = nullptr;
        T           m_element;
    };

public:
    void* Allocate() {
        AllocNode* pNode = new AllocNode;
        pNode->m_element = T(0);
        return (void*)pNode;
    }

    void Deallocate(void* p) {
        delete (AllocNode*)p;
    }
};