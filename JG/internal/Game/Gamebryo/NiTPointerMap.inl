#pragma once

#include "NiTPointerMap.hpp"

// GAME - 0x4744A0
template<class T_Key, class T_Data>
inline NiTPointerMap<T_Key, T_Data>::NiTPointerMap(uint32_t auiHashSize) : NiTMapBase<NiTPointerAllocator<size_t>, T_Key, T_Data>(auiHashSize) {
}

// GAME - 0x4745D0
template<class T_Key, class T_Data>
inline NiTPointerMap<T_Key, T_Data>::~NiTPointerMap() {
	NiTMapBase<NiTPointerAllocator<size_t>, T_Key, T_Data>::RemoveAll();
};


// GAME - 0x486A90
template<class T_Key, class T_Data>
inline NiTMapItem<T_Key, T_Data>* NiTPointerMap<T_Key, T_Data>::NewItem() {
    return static_cast<NiTMapItem<T_Key, T_Data>*>(this->m_kAllocator.Allocate());
}

// GAME - 0x666050
template<class T_Key, class T_Data>
inline void NiTPointerMap<T_Key, T_Data>::DeleteItem(NiTMapItem<T_Key, T_Data>* apItem) {
    apItem->m_val = 0;
    this->m_kAllocator.Deallocate(apItem);
}
