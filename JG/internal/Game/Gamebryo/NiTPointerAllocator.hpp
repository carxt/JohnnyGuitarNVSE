#pragma once

#include "NiTAbstractPoolAllocator.hpp"

template <class T_Data>
class NiTPointerAllocator : public NiTAbstractPoolAllocator<T_Data> {
public:
    // 0x43A080
    static void CreateFreeMem() {
        CdeclCall(0x43A080);
    }

    __declspec(restrict) void* Allocate() {
        NiTAbstractPoolAllocator<T_Data>::LockCriticalSection();

        if (!NiTAbstractPoolAllocator<T_Data>::GetFreeMem())
            NiTPointerAllocator<T_Data>::CreateFreeMem();

        typename NiTAbstractPoolAllocator<T_Data>::AllocNode* pTmp = NiTAbstractPoolAllocator<T_Data>::GetFreeMem();
        NiTAbstractPoolAllocator<T_Data>::SetFreeMem(NiTAbstractPoolAllocator<T_Data>::GetFreeMem()->m_pkNext);
        pTmp->m_element = 0;
        pTmp->m_pkNext = 0;
        pTmp->m_pkData = 0;
        NiTAbstractPoolAllocator<T_Data>::UnlockCriticalSection();
        return pTmp;
    };

	void Deallocate(void* apData) {
        NiTAbstractPoolAllocator<T_Data>::LockCriticalSection();

        typename NiTAbstractPoolAllocator<T_Data>::AllocNode* pDel = (typename NiTAbstractPoolAllocator<T_Data>::AllocNode*)apData;

        pDel->m_pkData = 0;
        pDel->m_pkNext = NiTAbstractPoolAllocator<T_Data>::GetFreeMem();
        NiTAbstractPoolAllocator<T_Data>::SetFreeMem(pDel);
        NiTAbstractPoolAllocator<T_Data>::UnlockCriticalSection();
    };
};