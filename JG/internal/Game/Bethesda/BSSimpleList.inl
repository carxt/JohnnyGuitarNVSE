#pragma once

#include "BSSimpleList.hpp"

// GAME - 0x96A2D0
template<class T>
inline BSSimpleList<T>::BSSimpleList() : m_item(0), m_pkNext(nullptr) {
}

// GAME - 0x470440
template<class T>
inline BSSimpleList<T>::BSSimpleList(const T& arItem) : m_item(arItem), m_pkNext(nullptr) {
}

template<class T>
inline BSSimpleList<T>::BSSimpleList(const T& arItem, BSSimpleList<T>* apNext) : m_item(arItem), m_pkNext(apNext) {
}

// GAME - 0x46FFB0
template<class T>
inline BSSimpleList<T>::~BSSimpleList() {
	RemoveAll();
}

// GAME - 0x6815C0
template<class T>
inline const T& BSSimpleList<T>::GetItem() const {
	return m_item;
}

// GAME - 0x6815C0
template<class T>
inline T& BSSimpleList<T>::GetItem() {
	return m_item;
}

// GAME - 0x726C60
template<class T>
inline void BSSimpleList<T>::SetItem(const T& arItem) {
	if (arItem)
		m_item = arItem;
}

// GAME - 0x726070
template<class T>
inline const BSSimpleList<T>* BSSimpleList<T>::GetNext() const {
	return m_pkNext;
}

// GAME - 0x726070
template<class T>
inline BSSimpleList<T>* BSSimpleList<T>::GetNext() {
	return m_pkNext;
}

// GAME - 0x6ECD40
template<class T>
inline void BSSimpleList<T>::SetNext(BSSimpleList<T>* apNext) {
	m_pkNext = apNext;
}

// GAME - 0x8256D0
template<class T>
inline bool BSSimpleList<T>::IsEmpty() const { 
	if (m_pkNext)
		return false;

	return m_item == T(0); 
}

// GAME - 0x631540
template<class T>
inline void BSSimpleList<T>::AddHead(const T& arItem) {
	if (!arItem)
		return;

	if (m_item) {
		BSSimpleList<T>* pNewEntry = new BSSimpleList<T>(m_item);
		pNewEntry->m_pkNext = m_pkNext;
		m_pkNext = pNewEntry;
		m_item = arItem;
	}
	else {
		m_item = arItem;
	}
}

// GAME - 0xAF25B0, 0x905820, 0xB63BF0
template<class T>
inline void BSSimpleList<T>::AddTail(const T& arItem) {
	if (!arItem)
		return;

	BSSimpleList<T>* pTail = GetTail();

	if (pTail->m_item) {
		pTail->m_pkNext = new BSSimpleList<T>(arItem);
	}
	else {
		pTail->m_item = arItem;
	}
}

// GAME - 0x5F65D0
template<class T>
inline bool BSSimpleList<T>::IsInList(const T& arItem) const {
	const BSSimpleList<T>* pIter = this;
	while (pIter && pIter->m_item != arItem)
		pIter = pIter->m_pkNext;
	return pIter != 0;
}

template<class T>
inline BSSimpleList<T>* BSSimpleList<T>::GetPos(const T& arItem) const {
	BSSimpleList<T>* pIter = const_cast<BSSimpleList<T>*>(this);
	while (pIter && pIter->m_item != arItem)
		pIter = pIter->m_pkNext;
	return pIter;
}

// GAME - 0x5AE380
template<class T>
inline uint32_t BSSimpleList<T>::ItemsInList() const {
	uint32_t uiCount = 0;
	const BSSimpleList<T>* pIter = GetHead();
	while (pIter) {
		if (pIter->GetItem())
			++uiCount;

		pIter = pIter->GetNext();
	}
	return uiCount;
}

// GAME - 0xB64EC0
template<class T>
inline void BSSimpleList<T>::RemoveAll() {
	while (m_pkNext) {
		BSSimpleList<T>* pNext = m_pkNext->m_pkNext;
		m_pkNext->m_pkNext = nullptr;
		delete m_pkNext;
		m_pkNext = pNext;
	}
	m_item = T(0);
}

// GAME - 0xB99730
template<class T>
inline void BSSimpleList<T>::RemoveHead() {
	if (m_pkNext) {
		BSSimpleList<T>* pNext = m_pkNext;
		m_pkNext = pNext->m_pkNext;
		m_item = pNext->m_item;
		pNext->m_pkNext = nullptr;
		delete pNext;
	}
	else {
		m_item = T(0);
	}
}

template<class T>
inline void BSSimpleList<T>::RemoveTail() {
	BSSimpleList<T>* pTail = GetTail();
	if (pTail) {
		BSSimpleList<T>* pIter = this;
		while (pIter->m_pkNext != pTail)
			pIter = pIter->m_pkNext;

		pIter->m_pkNext = nullptr;
		delete pTail;
	}
	else {
		m_item = T(0);
	}
}

// GAME - 0x905330
template<class T>
inline void BSSimpleList<T>::Remove(const T& arItem) {
	if (!arItem || IsEmpty())
		return;

	BSSimpleList<T>* pIter = this;
	BSSimpleList<T>* pPrev = this;

	while (pIter && pIter->m_item != arItem) {
		pPrev = pIter;
		pIter = pIter->m_pkNext;
	}

	if (!pIter)
		return;

	if (pIter == this) {
		if (m_pkNext) {
			BSSimpleList<T>* pNext = m_pkNext;
			m_pkNext = pNext->m_pkNext;
			m_item = pNext->m_item;
			pNext->m_pkNext = nullptr;
			delete pNext;
		}
		else {
			m_item = T(0);
		}
	}
	else {
		pPrev->m_pkNext = pIter->m_pkNext;
		pIter->m_pkNext = nullptr;
		delete pIter;
	}
}

// GAME - 0x7A7EB0
template<class T>
inline void BSSimpleList<T>::Insert(const T& arItem, int32_t(__cdecl* apCompare)(const T& arItem1, const T& arItem2)) {
	if (arItem) {
		BSSimpleList<T>* pIter = GetHead();
		BSSimpleList<T>* pPrev = nullptr;
		bool bDone = false;
		while (pIter && !bDone) {
			if (pIter->m_item) {
				if (apCompare(arItem, pIter->m_item) > 0) {
					if (!pIter->m_pkNext) {
						pIter->m_pkNext = new BSSimpleList<T>(arItem);
						bDone = true;
					}
				}
				else {
					if (pPrev) {
						BSSimpleList<T>* pNewEntry = new BSSimpleList<T>(arItem);
						pPrev->m_pkNext = pNewEntry;
						pNewEntry->m_pkNext = pIter;
					}
					else {
						AddHead(arItem);
					}
					bDone = true;
				}
			}
			else {
				pIter->m_item = arItem;
				bDone = true;
			}
			pPrev = pIter;
			pIter = pIter->m_pkNext;
		}
	}
}