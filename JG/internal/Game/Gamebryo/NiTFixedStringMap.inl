#pragma once

#include "NiTFixedStringMap.hpp"

template<class T_Data>
inline NiTFixedStringMap<T_Data>::NiTFixedStringMap(uint32_t auiHashSize) : NiTFixedStringMapBase<NiTDefaultAllocator<T_Data>, T_Data>(auiHashSize) {
}

// GAME - 0xA2EB40
template<class T_Data>
inline NiTFixedStringMap<T_Data>::~NiTFixedStringMap() {
	this->RemoveAll();
}

// GAME - 0xA6EF50
template<class T_Data>
inline NiTMapItem<NiFixedString, T_Data>* NiTFixedStringMap<T_Data>::NewItem() {
	NiTMapItem<NiFixedString, T_Data>* pItem = static_cast<NiTMapItem<NiFixedString, T_Data>*>(this->m_kAllocator.Allocate());
	ZeroMemory(&pItem->m_key, sizeof(pItem->m_key));
	return pItem;
}

// GAME - 0xAA0330
template<class T_Data>
inline void NiTFixedStringMap<T_Data>::DeleteItem(NiTMapItem<NiFixedString, T_Data>* apItem) {
	apItem->m_key = 0;
	apItem->m_val = 0;
	this->m_kAllocator.Deallocate(apItem);
}