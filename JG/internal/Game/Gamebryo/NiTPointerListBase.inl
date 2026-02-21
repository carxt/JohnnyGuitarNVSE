#pragma once

#include "NiTPointerListBase.hpp"

template<class Allocator, class T_Data>
inline NiTPointerListBase<Allocator, T_Data>::~NiTPointerListBase() {
    RemoveAll();
}

// GAME - 0xB71300
template<class Allocator, class T_Data>
inline void NiTPointerListBase<Allocator, T_Data>::RemoveAll() {
    NiTListItem<T_Data>* pCurr = this->m_pkHead;
    while (pCurr) {
        NiTListItem<T_Data>* pDel = pCurr;
        pCurr = pCurr->m_pkNext;
        DeleteItem(pDel);
    }

    this->m_kAllocator.m_uiCount = 0;
    this->m_pkHead = 0;
    this->m_pkTail = 0;
}

// GAME - 0x76B660
template<class Allocator, class T_Data>
inline void NiTPointerListBase<Allocator, T_Data>::AddHead(const T_Data& arElement) {
    NiTListItem<T_Data>* pNode = static_cast<NiTListItem<T_Data>*>(NewItem());
    pNode->m_element = arElement;
    this->AddNodeHead(pNode);
}

// GAME - 0xB58570
template<class Allocator, class T_Data>
inline void NiTPointerListBase<Allocator, T_Data>::AddTail(const T_Data& arElement) {
    NiTListItem<T_Data>* pNode = static_cast<NiTListItem<T_Data>*>(NewItem());
    pNode->m_element = arElement;
    this->AddNodeTail(pNode);
}

// GAME - 0xB713C0
template<class Allocator, class T_Data>
inline NiTListIterator NiTPointerListBase<Allocator, T_Data>::InsertBefore(NiTListIterator akPos, const T_Data& arElement) {
    NiTListItem<T_Data>* pNode = static_cast<NiTListItem<T_Data>*>(NewItem());
    pNode->m_element = arElement;
    return this->AddNodeBefore(akPos, pNode);
}

template<class Allocator, class T_Data>
inline NiTListIterator NiTPointerListBase<Allocator, T_Data>::InsertAfter(NiTListIterator akPos, const T_Data& arElement) {
    NiTListItem<T_Data>* pNode = static_cast<NiTListItem<T_Data>*>(NewItem());
    pNode->m_element = arElement;
    return this->AddNodeAfter(akPos, pNode);
};

template<class Allocator, class T_Data>
inline const T_Data& NiTPointerListBase<Allocator, T_Data>::GetHead() const {
    return this->m_pkHead->m_element;
}

template<class Allocator, class T_Data>
inline T_Data& NiTPointerListBase<Allocator, T_Data>::GetHead() {
    return this->m_pkHead->m_element;
}

template<class Allocator, class T_Data>
inline const T_Data& NiTPointerListBase<Allocator, T_Data>::GetTail() const {
    return this->m_pkTail->m_element;
}

template<class Allocator, class T_Data>
inline T_Data& NiTPointerListBase<Allocator, T_Data>::GetTail() {
	return this->m_pkTail->m_element;
}

// GAME - 0x6317A0
template<class Allocator, class T_Data>
inline const T_Data& NiTPointerListBase<Allocator, T_Data>::Get(NiTListIterator akPos) const {
    return static_cast<NiTListItem<T_Data>*>(akPos)->m_element;
};

template<class Allocator, class T_Data>
inline const T_Data& NiTPointerListBase<Allocator, T_Data>::GetNext(NiTListIterator& arPos) const {
    const T_Data& rElement = static_cast<NiTListItem<T_Data>*>(arPos)->m_element;
    arPos = static_cast<NiTListItem<T_Data>*>(arPos)->m_pkNext;
    return rElement;
}

template<class Allocator, class T_Data>
inline T_Data& NiTPointerListBase<Allocator, T_Data>::GetNext(NiTListIterator& arPos) {
    T_Data& rElement = static_cast<NiTListItem<T_Data>*>(arPos)->m_element;
    arPos = static_cast<NiTListItem<T_Data>*>(arPos)->m_pkNext;
    return rElement;
}

template<class Allocator, class T_Data>
inline const T_Data& NiTPointerListBase<Allocator, T_Data>::GetPrev(NiTListIterator& arPos) const {
    const T_Data& rElement = static_cast<NiTListItem<T_Data>*>(arPos)->m_element;
    arPos = static_cast<NiTListItem<T_Data>*>(arPos)->m_pkPrev;
    return rElement;
}

template<class Allocator, class T_Data>
inline T_Data& NiTPointerListBase<Allocator, T_Data>::GetPrev(NiTListIterator& arPos) {
    T_Data& rElement = static_cast<NiTListItem<T_Data>*>(arPos)->m_element;
    arPos = static_cast<NiTListItem<T_Data>*>(arPos)->m_pkPrev;
    return rElement;
}

// GAME - 0xB602D0
template<class Allocator, class T_Data>
inline T_Data NiTPointerListBase<Allocator, T_Data>::RemoveHead() {
    NiTListItem<T_Data>* pNode = this->m_pkHead;

    this->m_pkHead = this->m_pkHead->m_pkNext;

    if (this->m_pkHead)
        this->m_pkHead->m_pkPrev = 0;
    else
        this->m_pkTail = 0;

    T_Data kElement = pNode->m_element;

    DeleteItem(pNode);

    this->m_kAllocator.m_uiCount--;

    return kElement;
};

// GAME - 0xE7D5B0
template<class Allocator, class T_Data>
inline T_Data NiTPointerListBase<Allocator, T_Data>::RemoveTail() {
    NiTListItem<T_Data>* pNode = this->m_pkTail;

    this->m_pkTail = this->m_pkTail->m_pkPrev;

    if (this->m_pkTail)
        this->m_pkTail->m_pkNext = 0;
    else
        this->m_pkHead = 0;

    T_Data kElement = pNode->m_element;

    DeleteItem(pNode);

    this->m_kAllocator.m_uiCount--;

    return kElement;
};

// GAME - 0xE7DB70
template<class Allocator, class T_Data>
inline T_Data NiTPointerListBase<Allocator, T_Data>::Remove(const T_Data& arElement) {
    NiTListIterator kPos = NiTPointerListBase<Allocator, T_Data>::FindPos(arElement);
    return kPos ? RemovePos(kPos) : arElement;
}

// GAME - 0xE7D7F0
template<class Allocator, class T_Data>
inline T_Data NiTPointerListBase<Allocator, T_Data>::RemovePos(NiTListIterator& arPos) {
    NiTListItem<T_Data>* pNode = static_cast<NiTListItem<T_Data>*>(arPos);

    if (pNode == this->m_pkHead) {
        arPos = pNode->m_pkNext;
        return RemoveHead();
    }
    if (pNode == this->m_pkTail) {
        arPos = 0;
        return RemoveTail();
    }

    NiTListItem<T_Data>* pPrev = pNode->m_pkPrev;
    NiTListItem<T_Data>* pNext = pNode->m_pkNext;

    arPos = pNext;

    if (pPrev)
        pPrev->m_pkNext = pNext;
    if (pNext)
        pNext->m_pkPrev = pPrev;

    T_Data kElement = pNode->m_element;

    DeleteItem(pNode);

    this->m_kAllocator.m_uiCount--;

    return kElement;
}

// GAME - 0xE7DB70
template<class Allocator, class T_Data>
inline NiTListIterator NiTPointerListBase<Allocator, T_Data>::FindPos(const T_Data& arElement, NiTListIterator akStart) const {
    if (akStart == 0)
        akStart = this->GetHeadPos();

    while (akStart) {
        NiTListIterator kPos = akStart;
        if (arElement == GetNext(akStart))
            return kPos;
    }
    return 0;
};

// GAME - 0x49FA80
template<class Allocator, class T_Data>
SPEC_RESTRICT inline NiTListItem<T_Data>* NiTPointerListBase<Allocator, T_Data>::NewItem() {
    return static_cast<NiTListItem<T_Data>*>(this->m_kAllocator.Allocate());
};

// GAME - 0xE6E8A0
template<class Allocator, class T_Data>
inline void NiTPointerListBase<Allocator, T_Data>::DeleteItem(NiTListItem<T_Data>* apItem) {
    apItem->m_element = 0;
    this->m_kAllocator.Deallocate(apItem);
}