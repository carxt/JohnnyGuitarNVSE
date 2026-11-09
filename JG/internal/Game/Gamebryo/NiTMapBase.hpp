#pragma once

#include "Bethesda/BSMemObject.hpp"
#include "NiConcepts.hpp"

using NiTMapIterator = void*;

template <NiC::NiMapKey T_Key, NiC::NiMapItem T_Data>
class SPEC_EMPTY_BASES NiTMapItem : public BSMemObject {
public:
    NiTMapItem* m_pkNext;
    T_Key       m_key;
    T_Data      m_val;
};

template <class Allocator, NiC::NiMapKey T_Key, NiC::NiMapItem T_Data>
class SPEC_EMPTY_BASES NiTMapBase : public BSMemObject {
protected:
    using _Empty = NiC::PickEmptyType<T_Data>;

public:
    struct AntiBloatAllocator : public Allocator {
        uint32_t m_uiCount;
    };

    NiTMapBase(uint32_t auiHashSize = 37);
	NiTMapBase(const NiTMapBase&) = delete;
	NiTMapBase& operator=(const NiTMapBase&) = delete;

    virtual                             ~NiTMapBase();
    virtual uint32_t                    KeyToHashIndex(const T_Key aKey) const;
    virtual bool                        IsKeysEqual(const T_Key aKey1, const T_Key aKey2) const;
    virtual void                        SetValue(NiTMapItem<T_Key, T_Data>* apItem, T_Key aKey, T_Data aData);
    virtual void                        ClearValue(NiTMapItem<T_Key, T_Data>* apItem);
    virtual NiTMapItem<T_Key, T_Data>*  NewItem() = 0;
    virtual void                        DeleteItem(NiTMapItem<T_Key, T_Data>* apItem) = 0;

    uint32_t                    m_uiHashSize;
    NiTMapItem<T_Key, T_Data>** m_ppkHashTable;
    AntiBloatAllocator          m_kAllocator;

    uint32_t GetCount() const;
    bool IsEmpty() const;

    bool GetAt(const T_Key aKey, T_Data& arData) const;

    void SetAt(T_Key aKey, T_Data aData);

    bool RemoveAt(const T_Key aKey);

    void RemoveAll();

    NiTMapIterator GetFirstPos() const;

    void GetNext(NiTMapIterator& arPos, T_Key& arKey, T_Data& arData) const;
};

#include "NiTMapBase.inl"