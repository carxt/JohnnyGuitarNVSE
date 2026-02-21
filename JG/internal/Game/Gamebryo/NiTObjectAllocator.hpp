#pragma once

#include "NiTAbstractPoolAllocator.hpp"

template <class T_Data>
class NiTObjectAllocator : public NiTAbstractPoolAllocator<T_Data> {
    // 0x43A080
    static void CreateFreeMem() {
        CdeclCall(0x43A080);
    }

    // 0x43A010
    void* Allocate() {
        NiTAbstractPoolAllocator<T_Data>::LockCriticalSection();


        typename NiTAbstractPoolAllocator<T_Data>::AllocNode* pTmp = NiTAbstractPoolAllocator<T_Data>::GetFreeMem();
        NiTAbstractPoolAllocator<T_Data>::SetFreeMem(NiTAbstractPoolAllocator<T_Data>::GetFreeMem()->m_pkNext);
        pTmp->m_pkNext = 0;
        pTmp->m_pkData = 0;
        NiTAbstractPoolAllocator<T_Data>::UnlockCriticalSection();
        return pTmp;
    };

    // 0x45CEE0
    void Deallocate(void* apData) {
        NiTAbstractPoolAllocator<T_Data>::LockCriticalSection();

        typename NiTAbstractPoolAllocator<T_Data>::AllocNode* pDel = (typename NiTAbstractPoolAllocator<T_Data>::AllocNode*)apData;

        pDel->m_pkNext = NiTAbstractPoolAllocator<T_Data>::GetFreeMem();
        NiTAbstractPoolAllocator<T_Data>::SetFreeMem(pDel);
        NiTAbstractPoolAllocator<T_Data>::UnlockCriticalSection();
    };
};