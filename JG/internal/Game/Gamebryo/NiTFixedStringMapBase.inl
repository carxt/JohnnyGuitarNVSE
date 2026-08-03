#pragma once

#include "NiTFixedStringMapBase.hpp"

template<class Allocator, class T_Data>
inline NiTFixedStringMapBase<Allocator, T_Data>::NiTFixedStringMapBase(uint32_t auiHashSize) {
	m_uiHashSize = auiHashSize;
	m_kAllocator.m_uiCount = 0;

	uint32_t uiSize = sizeof(NiTMapItem<NiFixedString, T_Data>*) * auiHashSize;
	m_ppkHashTable = NiAlloc<NiTMapItem<NiFixedString, T_Data>*>(uiSize);
	memset(m_ppkHashTable, 0, auiHashSize * sizeof(NiTMapItem<NiFixedString, T_Data>*));
}

// GAME - 0xA6EA00
template<class Allocator, class T_Data>
inline NiTFixedStringMapBase<Allocator, T_Data>::~NiTFixedStringMapBase() {
	NiTFixedStringMapBase<Allocator, T_Data>::RemoveAll();
	NiFree(m_ppkHashTable);
}

template<class Allocator, class T_Data>
inline uint32_t NiTFixedStringMapBase<Allocator, T_Data>::GetCount() const {
	return m_kAllocator.m_uiCount;
}

template<class Allocator, class T_Data>
inline bool NiTFixedStringMapBase<Allocator, T_Data>::IsEmpty() const {
	return m_kAllocator.m_uiCount == 0;
}

template<class Allocator, class T_Data>
inline uint32_t NiTFixedStringMapBase<Allocator, T_Data>::KeyToHashIndex(const NiFixedString& arString) const {
	const char* pKey = arString;
	return uint32_t(size_t(pKey) % m_uiHashSize);
}

template<class Allocator, class T_Data>
inline bool NiTFixedStringMapBase<Allocator, T_Data>::IsKeysEqual(const NiFixedString& arString1, const NiFixedString& arString2) const {
	return arString1 == arString2;
}

template<class Allocator, class T_Data>
inline void NiTFixedStringMapBase<Allocator, T_Data>::SetValue(NiTMapItem<NiFixedString, T_Data>* apItem, const NiFixedString& arString, T_Data akData) {
	apItem->m_key = arString;
	apItem->m_val = akData;
}

template<class Allocator, class T_Data>
inline void NiTFixedStringMapBase<Allocator, T_Data>::ClearValue(NiTMapItem<NiFixedString, T_Data>* apItem) {
}

template<class Allocator, class T_Data>
inline bool NiTFixedStringMapBase<Allocator, T_Data>::GetAt(const NiFixedString& arString, T_Data& arData) const {
	uint32_t uiHashIndex = KeyToHashIndex(arString);
	NiTMapItem<NiFixedString, T_Data>* pItem = m_ppkHashTable[uiHashIndex];
	while (pItem) {
		if (IsKeysEqual(pItem->m_key, arString)) {
			arData = pItem->m_val;
			return true;
		}
		pItem = pItem->m_pkNext;
	}
	return false;
}

template<class Allocator, class T_Data>
inline void NiTFixedStringMapBase<Allocator, T_Data>::SetAt(const NiFixedString& arString, T_Data akData) {
	uint32_t uiHashIndex = KeyToHashIndex(arString);
	NiTMapItem<NiFixedString, T_Data>* pItem = m_ppkHashTable[uiHashIndex];
	while (pItem) {
		if (IsKeysEqual(pItem->m_key, arString)) {
			SetValue(pItem, arString, akData);
			return;
		}
		pItem = pItem->m_pkNext;
	}
	NiTMapItem<NiFixedString, T_Data>* pNewEntry = NewItem();
	SetValue(pNewEntry, arString, akData);
	pNewEntry->m_pkNext = m_ppkHashTable[uiHashIndex];
	m_ppkHashTable[uiHashIndex] = pNewEntry;
	m_kAllocator.m_uiCount++;
}

template<class Allocator, class T_Data>
inline NiTMapIterator NiTFixedStringMapBase<Allocator, T_Data>::GetFirstPos() const {
	for (uint32_t i = 0; i < m_uiHashSize; i++) {
		if (m_ppkHashTable[i])
			return m_ppkHashTable[i];
	}
	return nullptr;
}

template<class Allocator, class T_Data>
inline void NiTFixedStringMapBase<Allocator, T_Data>::GetNext(NiTMapIterator& arPos, NiFixedString& arString, T_Data& arData) const {
	NiTMapItem<NiFixedString, T_Data>* pItem = static_cast<NiTMapItem<NiFixedString, T_Data>*>(arPos);

	arString = pItem->m_key;
	arData = pItem->m_val;

	if (pItem->m_pkNext) {
		arPos = pItem->m_pkNext;
		return;
	}

	uint32_t i = KeyToHashIndex(pItem->m_key);
	for (++i; i < m_uiHashSize; i++) {
		pItem = m_ppkHashTable[i];
		if (pItem) {
			arPos = pItem;
			return;
		}
	}

	arPos = 0;
}

template<class Allocator, class T_Data>
inline void NiTFixedStringMapBase<Allocator, T_Data>::RemoveAll() {
	for (uint32_t i = 0; i < m_uiHashSize; i++) {
		while (m_ppkHashTable[i]) {
			NiTMapItem<NiFixedString, T_Data>* pkSave = m_ppkHashTable[i];
			m_ppkHashTable[i] = m_ppkHashTable[i]->m_pkNext;
			ClearValue(pkSave);
			DeleteItem(pkSave);
		}
	}

	m_kAllocator.m_uiCount = 0;
}

template<class Allocator, class T_Data>
inline bool NiTFixedStringMapBase<Allocator, T_Data>::RemoveAt(const NiFixedString& arString) {
	uint32_t uiIndex = KeyToHashIndex(arString);
	NiTMapItem<NiFixedString, T_Data>* apItem = m_ppkHashTable[uiIndex];

	if (apItem) {
		if (IsKeysEqual(arString, apItem->m_key)) {
			m_ppkHashTable[uiIndex] = apItem->m_pkNext;
			ClearValue(apItem);
			DeleteItem(apItem);
			m_kAllocator.m_uiCount--;
			return true;
		}
		else {
			NiTMapItem<NiFixedString, T_Data>* pPrev = apItem;
			NiTMapItem<NiFixedString, T_Data>* pCurr = pPrev->m_pkNext;
			while (pCurr && !IsKeysEqual(arString, pCurr->m_key)) {
				pPrev = pCurr;
				pCurr = pCurr->m_pkNext;
			}
			if (pCurr) {
				pPrev->m_pkNext = pCurr->m_pkNext;
				ClearValue(pCurr);
				DeleteItem(pCurr);
				m_kAllocator.m_uiCount--;
				return true;
			}
		}
	}

	return false;
}
