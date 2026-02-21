#pragma once

#include "NiTListBase.hpp"
#include "NiTObjectAllocator.hpp"

// Possibly unused
template <class T_Data>
class NiTObjectList : public NiTListBase <NiTObjectAllocator<T_Data>, T_Data> {
public:
    ~NiTObjectList() { RemoveAll(); };

    T_Data* GetNext(NiTListIterator& kPos) const {
        if (kPos == 0)
            return nullptr;

        T_Data* element = &((NiTListItem<T_Data>*) kPos)->m_element;
        kPos = static_cast<NiTListItem<T_Data>*>(kPos)->m_pkNext;
        return element;
    }

    // 0xB71300
    void RemoveAll() {
        NiTListItem<T_Data>* pCurr = NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_pkHead;
        while (pCurr) {
            NiTListItem<T_Data>* pDel = pCurr;
            pCurr = pCurr->m_pkNext;
            DeleteItem(pDel);
        }

        NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_kAllocator.m_uiCount = 0;
        NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_pkHead = 0;
        NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_pkTail = 0;
    };

    template <typename FUNC>
    void ForEach(FUNC func) {
        uint32_t i = 0;
        NiTListIterator kPos = NiTObjectList<T_Data>::GetHeadPos();
        while (kPos) {
            func(GetNext(kPos), i++);
        }
    };

protected:
	// 0x49FA80
	NiTListItem<T_Data>* NewItem() {
		return (NiTListItem<T_Data>*)NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_kAllocator.Allocate();
	};
	// 0xE6E8A0
	void DeleteItem(NiTListItem<T_Data>* pkItem) {
		NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_kAllocator.Deallocate(pkItem);
	}
};