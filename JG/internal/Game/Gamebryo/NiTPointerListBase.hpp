#pragma once

#include "NiTListBase.hpp"

template <class Allocator, class T_Data>
class NiTPointerListBase : public NiTListBase <Allocator, T_Data> {
public:
    ~NiTPointerListBase();

    void RemoveAll();

    void AddHead(const T_Data& arElement);
    void AddTail(const T_Data& arElement);

    NiTListIterator InsertBefore(NiTListIterator akPos, const T_Data& arElement);
    NiTListIterator InsertAfter(NiTListIterator akPos, const T_Data& arElement);

    const T_Data& GetHead() const;
    T_Data& GetHead();

    const T_Data& GetTail() const;
	T_Data& GetTail();

    const T_Data& Get(NiTListIterator akPos) const;

    const T_Data& GetNext(NiTListIterator& arPos) const;
    T_Data& GetNext(NiTListIterator& arPos);

    const T_Data& GetPrev(NiTListIterator& arPos) const;
    T_Data& GetPrev(NiTListIterator& arPos);

    T_Data RemoveHead();
    T_Data RemoveTail();

    T_Data Remove(const T_Data& arElement);
    T_Data RemovePos(NiTListIterator& arPos);

    NiTListIterator FindPos(const T_Data& arElement, NiTListIterator akStart = 0) const;

    template <typename FUNC>
    void ForEach(FUNC func) {
        uint32_t i = 0;
		NiTListIterator kPos = this->GetHeadPos();
		while (kPos) {
			func(GetNext(kPos), i++);
		}
	};

protected:
    SPEC_RESTRICT NiTListItem<T_Data>* NewItem();

    void DeleteItem(NiTListItem<T_Data>* apItem);
};

#include "NiTPointerListBase.inl"