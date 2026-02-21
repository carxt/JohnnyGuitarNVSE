#pragma once

#include "NiTListBase.hpp"

// GAME - 0xB998E0
template<class Allocator, class T_Data>
inline NiTListBase<Allocator, T_Data>::NiTListBase() : m_pkHead(0), m_pkTail(0) { 
	m_kAllocator.m_uiCount = 0; 
}

template<class Allocator, class T_Data>
inline NiTListBase<Allocator, T_Data>::~NiTListBase() {
}

template<class Allocator, class T_Data>
inline uint32_t NiTListBase<Allocator, T_Data>::GetSize() const {
	return m_kAllocator.m_uiCount;
}

template<class Allocator, class T_Data>
inline bool NiTListBase<Allocator, T_Data>::IsEmpty() const { 
	return m_kAllocator.m_uiCount == 0; 
}

// GAME - 0x559450
template<class Allocator, class T_Data>
inline NiTListIterator NiTListBase<Allocator, T_Data>::GetHeadPos() const {
	return m_pkHead;
}

template<class Allocator, class T_Data>
inline NiTListIterator NiTListBase<Allocator, T_Data>::GetTailPos() const {
	return m_pkTail;
}

// GAME - 0x7B52D0
template<class Allocator, class T_Data>
inline NiTListIterator NiTListBase<Allocator, T_Data>::GetNextPos(NiTListIterator akPos) const {
	return akPos ? static_cast<NiTListItem<T_Data>*>(akPos)->m_pkNext : 0;
}

template<class Allocator, class T_Data>
inline NiTListIterator NiTListBase<Allocator, T_Data>::GetPrevPos(NiTListIterator akPos) const {
	return akPos ? static_cast<NiTListItem<T_Data>*>(akPos)->m_pkPrev : 0;
}

// GAME - 0x49FA20
template<class Allocator, class T_Data>
inline void NiTListBase<Allocator, T_Data>::AddNodeHead(NiTListItem<T_Data>* apNode) {
    apNode->m_pkPrev = nullptr;
    apNode->m_pkNext = m_pkHead;

    if (m_pkHead)
        m_pkHead->m_pkPrev = apNode;
    else
        m_pkTail = apNode;

    m_pkHead = apNode;
    m_kAllocator.m_uiCount++;
}

// GAME - 0xB5A9A0
template<class Allocator, class T_Data>
inline void NiTListBase<Allocator, T_Data>::AddNodeTail(NiTListItem<T_Data>* apNode) {
    apNode->m_pkNext = nullptr;
    apNode->m_pkPrev = m_pkTail;

    if (m_pkTail)
        m_pkTail->m_pkNext = apNode;
    else
        m_pkHead = apNode;

    m_pkTail = apNode;
    m_kAllocator.m_uiCount++;
}

template<class Allocator, class T_Data>
inline NiTListIterator NiTListBase<Allocator, T_Data>::AddNodeAfter(NiTListIterator akPos, NiTListItem<T_Data>* apNode) {
    NiTListItem<T_Data>* pPrev = static_cast<NiTListItem<T_Data>*>(akPos);

    apNode->m_pkPrev = pPrev;
    apNode->m_pkNext = pPrev->m_pkNext;

    if (pPrev->m_pkNext)
        pPrev->m_pkNext->m_pkPrev = apNode;
    else
        m_pkTail = apNode;

    pPrev->m_pkNext = apNode;

    m_kAllocator.m_uiCount++;
    return apNode;
}

template<class Allocator, class T_Data>
inline NiTListIterator NiTListBase<Allocator, T_Data>::AddNodeBefore(NiTListIterator akPos, NiTListItem<T_Data>* apNode) {
    NiTListItem<T_Data>* pPrev = static_cast<NiTListItem<T_Data>*>(akPos);

    apNode->m_pkNext = pPrev;
    apNode->m_pkPrev = pPrev->m_pkPrev;

    if (pPrev->m_pkPrev)
        pPrev->m_pkPrev->m_pkNext = apNode;
    else
        m_pkHead = apNode;

    pPrev->m_pkPrev = apNode;

    m_kAllocator.m_uiCount++;
    return apNode;
}

// GAME - 0xB702E0
template<class Allocator, class T_Data>
inline void NiTListBase<Allocator, T_Data>::MoveToBefore(NiTListIterator akObjectToMove, NiTListIterator akDestination) {
    NiTListItem<T_Data>* pToMove = static_cast<NiTListItem<T_Data>*>(akObjectToMove);
    NiTListItem<T_Data>* pDestination = static_cast<NiTListItem<T_Data>*>(akDestination);

    if (pToMove != pDestination) {
        if (m_pkHead == pToMove)
            m_pkHead = pToMove->m_pkNext;
        if (m_pkHead == pDestination)
            m_pkHead = pToMove;
        if (m_pkTail == pToMove)
            m_pkTail = pToMove->m_pkPrev;

        if (pToMove->m_pkNext)
            pToMove->m_pkNext->m_pkPrev = pToMove->m_pkPrev;

        if (pToMove->m_pkPrev)
            pToMove->m_pkPrev->m_pkNext = pToMove->m_pkNext;

        pToMove->m_pkPrev = pDestination->m_pkPrev;
        pToMove->m_pkNext = pDestination;

        if (pDestination->m_pkPrev)
            pDestination->m_pkPrev->m_pkNext = pToMove;

        pDestination->m_pkPrev = pToMove;
    }
}