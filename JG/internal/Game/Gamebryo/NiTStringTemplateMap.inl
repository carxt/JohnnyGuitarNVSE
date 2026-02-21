#pragma once

#include "NiTStringTemplateMap.hpp"

// GAME - 0x4055D0
template<class T_Parent, class T_Data>
inline NiTStringTemplateMap<T_Parent, T_Data>::NiTStringTemplateMap(uint32_t auiHashSize, bool abCopy) : T_Parent(auiHashSize) {
	m_bCopy = abCopy;
}

// GAME - 0x405250
template<class T_Parent, class T_Data>
inline NiTStringTemplateMap<T_Parent, T_Data>::~NiTStringTemplateMap() {
	if (m_bCopy) {
		for (uint32_t i = 0; i < T_Parent::m_uiHashSize; i++) {
			NiTMapItem<const char*, T_Data>* pItem = T_Parent::m_ppkHashTable[i];
			while (pItem) {
				NiTMapItem<const char*, T_Data>* pSave = pItem;
				pSave = pItem->m_pkNext;
				NiFree((char*)pSave->m_key);
			}
		}
	}
}

// GAME - 0x486DF0
template<class T_Parent, class T_Data>
inline uint32_t NiTStringTemplateMap<T_Parent, T_Data>::KeyToHashIndex(const char* apKey) const {
	uint32_t uiHash = 0;

	while (*apKey)
		uiHash = (uiHash << 5) + uiHash + *apKey++;

	return uiHash % T_Parent::m_uiHashSize;
}

// GAME - 0xEC1C90
template<class T_Parent, class T_Data>
inline bool NiTStringTemplateMap<T_Parent, T_Data>::IsKeysEqual(const char* apKey1, const char* apKey2) const {
	return _stricmp(apKey1, apKey2) == 0;
}

// GAME - 0x486AE0
template<class T_Parent, class T_Data>
inline void NiTStringTemplateMap<T_Parent, T_Data>::SetValue(NiTMapItem<const char*, T_Data>* apItem, const char* apKey, T_Data val) {
	if (m_bCopy) {
		uint32_t uiLen = strlen(apKey) + 1;
		apItem->m_key = NiAlloc<char>(uiLen);
		strcpy_s((char*)apItem->m_key, uiLen, apKey);
	}
	else {
		apItem->m_key = apKey;
	}
	apItem->m_val = val;
}

// GAME - 0x658B80
template<class T_Parent, class T_Data>
inline void NiTStringTemplateMap<T_Parent, T_Data>::ClearValue(NiTMapItem<const char*, T_Data>* apItem) {
	if (m_bCopy) {
		NiFree((char*)apItem->m_key);
	}
}

// GAME - 0x470200
template<class T_Parent, class T_Data>
inline void NiTStringTemplateMap<T_Parent, T_Data>::SetAt(const char* apKey, T_Data aData) {
	const uint32_t uiHashIndex = KeyToHashIndex(apKey);
	NiTMapItem<const char*, T_Data>* pItem = T_Parent::m_ppkHashTable[uiHashIndex];
	while (pItem) {
		if (IsKeysEqual(pItem->m_key, apKey)) {
			if (!m_bCopy)
				pItem->m_key = apKey;
			pItem->m_val = aData;
			return;
		}
		pItem = pItem->m_pkNext;
	}
	NiTMapItem<const char*, T_Data>* pNewEntry = T_Parent::NewItem();
	SetValue(pNewEntry, apKey, aData);
	pNewEntry->m_pkNext = T_Parent::m_ppkHashTable[uiHashIndex];
	T_Parent::m_ppkHashTable[uiHashIndex] = pNewEntry;
	T_Parent::m_kAllocator.m_uiCount++;
}