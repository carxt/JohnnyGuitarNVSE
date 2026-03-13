#pragma once

#include "NiMemObject.hpp"

typedef void* NiTListIterator;

template <class T_Data>
class SPEC_EMPTY_BASES NiTListItem : public NiMemObject {
public:
	NiTListItem* m_pkNext;
	NiTListItem* m_pkPrev;
	T_Data       m_element;
};

template <class Allocator, class T_Data>
class SPEC_EMPTY_BASES NiTListBase : public NiMemObject {
public:
    NiTListBase();
    ~NiTListBase();

    NiTListBase(const NiTListBase&) = delete;
    NiTListBase& operator=(const NiTListBase&) = delete;

    struct AntiBloatAllocator : public Allocator {
        uint32_t m_uiCount;
    };

    NiTListItem<T_Data>* m_pkHead;
    NiTListItem<T_Data>* m_pkTail;
    AntiBloatAllocator   m_kAllocator;

    uint32_t GetSize() const;
    bool IsEmpty() const;

    NiTListIterator GetHeadPos() const;
    NiTListIterator GetTailPos() const;

    NiTListIterator GetNextPos(NiTListIterator akPos) const;
    NiTListIterator GetPrevPos(NiTListIterator akPos) const;

    void AddNodeHead(NiTListItem<T_Data>* apNode);
    void AddNodeTail(NiTListItem<T_Data>* apNode);

    NiTListIterator AddNodeAfter(NiTListIterator akPos, NiTListItem<T_Data>* apNode);
    NiTListIterator AddNodeBefore(NiTListIterator akPos, NiTListItem<T_Data>* apNode);

    void MoveToBefore(NiTListIterator akObjectToMove, NiTListIterator akDestination);
};

#include "NiTListBase.inl"