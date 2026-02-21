#pragma once

#include "NiTMapBase.hpp"

// GAME - 0x405630
template<class Allocator, class T_Key, class T_Data>
inline NiTMapBase<Allocator, T_Key, T_Data>::NiTMapBase(uint32_t auiHashSize) {
    m_uiHashSize = auiHashSize;
    m_kAllocator.m_uiCount = 0;

    m_ppkHashTable = NiAlloc<NiTMapItem<T_Key, T_Data>*>(auiHashSize);
    memset(m_ppkHashTable, 0, auiHashSize * sizeof(NiTMapItem<T_Key, T_Data>*));
}

// GAME - 0x405370
template<class Allocator, class T_Key, class T_Data>
inline NiTMapBase<Allocator, T_Key, T_Data>::~NiTMapBase() {
    RemoveAll();
    NiFree(m_ppkHashTable);
}

// GAME - 0x6C6A60
template<class Allocator, class T_Key, class T_Data>
inline uint32_t NiTMapBase<Allocator, T_Key, T_Data>::KeyToHashIndex(const T_Key aKey) const {
    return uint32_t(size_t(aKey) % m_uiHashSize);
}

// GAME - 0x6B81D0
template<class Allocator, class T_Key, class T_Data>
inline bool NiTMapBase<Allocator, T_Key, T_Data>::IsKeysEqual(const T_Key aKey1, const T_Key aKey2) const {
    return aKey1 == aKey2;
}

// GAME - 0x863840
template<class Allocator, class T_Key, class T_Data>
inline void NiTMapBase<Allocator, T_Key, T_Data>::SetValue(NiTMapItem<T_Key, T_Data>* apItem, T_Key aKey, T_Data aData) {
    apItem->m_key = aKey;
    apItem->m_val = aData;
}

template<class Allocator, class T_Key, class T_Data>
inline void NiTMapBase<Allocator, T_Key, T_Data>::ClearValue(NiTMapItem<T_Key, T_Data>* apItem) {
}

template<class Allocator, class T_Key, class T_Data>
inline uint32_t NiTMapBase<Allocator, T_Key, T_Data>::GetCount() const {
    return m_kAllocator.m_uiCount;
}

template<class Allocator, class T_Key, class T_Data>
inline bool NiTMapBase<Allocator, T_Key, T_Data>::IsEmpty() const {
    return m_kAllocator.m_uiCount == 0;
}

// GAME - 0x57C850
template<class Allocator, class T_Key, class T_Data>
inline bool NiTMapBase<Allocator, T_Key, T_Data>::GetAt(const T_Key aKey, T_Data& arData) const {
    const uint32_t uiHashIndex = KeyToHashIndex(aKey);
    NiTMapItem<T_Key, T_Data>* pItem = m_ppkHashTable[uiHashIndex];
    while (pItem) {
        if (IsKeysEqual(pItem->m_key, aKey)) {
            arData = pItem->m_val;
            return true;
        }
        pItem = pItem->m_pkNext;
    }
    return false;
}

// GAME - 0x844700
template<class Allocator, class T_Key, class T_Data>
inline void NiTMapBase<Allocator, T_Key, T_Data>::SetAt(T_Key aKey, T_Data aData) {
    const uint32_t uiHashIndex = KeyToHashIndex(aKey);
    NiTMapItem<T_Key, T_Data>* pItem = m_ppkHashTable[uiHashIndex];
    while (pItem) {
        if (IsKeysEqual(pItem->m_key, aKey)) {
            pItem->m_val = aData;
            return;
        }
        pItem = pItem->m_pkNext;
    }
    NiTMapItem<T_Key, T_Data>* pNewEntry = NewItem();
    SetValue(pNewEntry, aKey, aData);
    pNewEntry->m_pkNext = m_ppkHashTable[uiHashIndex];
    m_ppkHashTable[uiHashIndex] = pNewEntry;
    m_kAllocator.m_uiCount++;
}

// GAME - 0x405430
template<class Allocator, class T_Key, class T_Data>
inline bool NiTMapBase<Allocator, T_Key, T_Data>::RemoveAt(const T_Key aKey) {
    const uint32_t uiIndex = KeyToHashIndex(aKey);
    NiTMapItem<T_Key, T_Data>* pItem = m_ppkHashTable[uiIndex];

    if (!pItem)
        return false;

    if (IsKeysEqual(aKey, pItem->m_key)) {
        m_ppkHashTable[uiIndex] = pItem->m_pkNext;
        ClearValue(pItem);
        DeleteItem(pItem);
        --m_kAllocator.m_uiCount;
        return true;
    }

    NiTMapItem<T_Key, T_Data>* pPrev = pItem;
    NiTMapItem<T_Key, T_Data>* i = pItem->m_pkNext;

    for (i; i && !IsKeysEqual(aKey, i->m_key); i = i->m_pkNext)
        pPrev = i;

    if (!i)
        return false;

    pPrev->m_pkNext = i->m_pkNext;
    ClearValue(i);
    DeleteItem(i);
    --m_kAllocator.m_uiCount;
    return true;
}

// GAME - 0x438AF0
template<class Allocator, class T_Key, class T_Data>
inline void NiTMapBase<Allocator, T_Key, T_Data>::RemoveAll() {
    for (uint32_t i = 0; i < m_uiHashSize; i++) {
        while (m_ppkHashTable[i]) {
            NiTMapItem<T_Key, T_Data>* pItem = m_ppkHashTable[i];
            m_ppkHashTable[i] = m_ppkHashTable[i]->m_pkNext;
            ClearValue(pItem);
            DeleteItem(pItem);
        }
    }

    m_kAllocator.m_uiCount = 0;
}

// GAME - 0x4B9BA0
template<class Allocator, class T_Key, class T_Data>
inline NiTMapIterator NiTMapBase<Allocator, T_Key, T_Data>::GetFirstPos() const {
    for (uint32_t i = 0; i < m_uiHashSize; i++) {
        if (m_ppkHashTable[i])
            return m_ppkHashTable[i];
    }
    return nullptr;
}

// GAME - 0x6B7F20
template<class Allocator, class T_Key, class T_Data>
inline void NiTMapBase<Allocator, T_Key, T_Data>::GetNext(NiTMapIterator& arPos, T_Key& arKey, T_Data& arData) const {
    NiTMapItem<T_Key, T_Data>* pItem = static_cast<NiTMapItem<T_Key, T_Data>*>(arPos);

    arKey = pItem->m_key;
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

    arPos = nullptr;
}