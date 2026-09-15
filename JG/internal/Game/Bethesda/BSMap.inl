#pragma once

#include "BSMap.hpp"

// GAME - 0x4383E0
template<class T_Key, class T_Data>
inline BSMap<T_Key, T_Data>::BSMap(uint32_t auiHashSize) : BSMapBase<T_Key, T_Data>(auiHashSize) {
}

// GAME - 0x4388A0
template<class T_Key, class T_Data>
inline BSMap<T_Key, T_Data>::~BSMap() {
	BSMapBase<T_Key, T_Data>::RemoveAll();
}

// GAME - 0x6F99E0
template<class T_Key, class T_Data>
inline BSMapItem<T_Key, T_Data>* BSMap<T_Key, T_Data>::NewItem() {
	return BSMemory::malloc<BSMapItem<T_Key, T_Data>>();
}

// GAME - 0x438940
template<class T_Key, class T_Data>
inline void BSMap<T_Key, T_Data>::DeleteItem(BSMapItem<T_Key, T_Data>* apItem) {
	apItem->m_val = 0;
	BSMemory::free(apItem);
}
