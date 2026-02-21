#pragma once

#include "NiTMap.hpp"

template<class T_Key, class T_Data>
inline NiTMap<T_Key, T_Data>::NiTMap(uint32_t auiHashSize) : NiTMapBase<NiTDefaultAllocator<T_Data>, T_Key, T_Data>(auiHashSize) {
}

template<class T_Key, class T_Data>
inline NiTMap<T_Key, T_Data>::~NiTMap() {
	NiTMapBase<NiTDefaultAllocator<T_Data>, T_Key, T_Data>::RemoveAll();
}

template<class T_Key, class T_Data>
inline NiTMapItem<T_Key, T_Data>* NiTMap<T_Key, T_Data>::NewItem() {
	return static_cast<NiTMapItem<T_Key, T_Data>*>(this->m_kAllocator.Allocate());
}

template<class T_Key, class T_Data>
inline void NiTMap<T_Key, T_Data>::DeleteItem(NiTMapItem<T_Key, T_Data>* apItem) {
	apItem->m_val = T_Data(0);
	this->m_kAllocator.Deallocate(apItem);
}