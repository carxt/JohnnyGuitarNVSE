#pragma once

#include "BSMemObject.hpp"

// Clone of BSMapBase lmao
// Doesn't call RemoveAll in the destructor, can have null hash table, and calls ClearValue and SetValue in SetAt

typedef void* BSMapIterator;

template <class T_Key, class T_Data>
class SPEC_EMPTY_BASES BSMapItem : public BSMemObject {
public:
    BSMapItem*  m_pkNext;
    T_Key       m_key;
    T_Data      m_val;
};

template <class T_Key, class T_Data>
class SPEC_EMPTY_BASES BSMapBase : public BSMemObject {
public:
    BSMapBase(uint32_t auiHashSize = 37);
    BSMapBase(const BSMapBase&) = delete;
    BSMapBase& operator=(const BSMapBase&) = delete;

    virtual                             ~BSMapBase();
    virtual uint32_t                    KeyToHashIndex(const T_Key aKey) const;
    virtual bool                        IsKeysEqual(const T_Key aKey1, const T_Key aKey2) const;
    virtual void                        SetValue(BSMapItem<T_Key, T_Data>* apItem, T_Key aKey, T_Data aData);
    virtual void                        ClearValue(BSMapItem<T_Key, T_Data>* apItem);
    virtual BSMapItem<T_Key, T_Data>*   NewItem() = 0;
    virtual void                        DeleteItem(BSMapItem<T_Key, T_Data>* apItem) = 0;

    uint32_t                    m_uiHashSize;
    BSMapItem<T_Key, T_Data>**  m_ppkHashTable;
    uint32_t                    m_uiCount;

    uint32_t GetCount() const;
    bool IsEmpty() const;

    bool GetAt(const T_Key aKey, T_Data& arData) const;

    void SetAt(T_Key aKey, T_Data aData);

    bool RemoveAt(const T_Key aKey);

    void RemoveAll();

    BSMapIterator GetFirstPos() const;

    void GetNext(BSMapIterator& arPos, T_Key& arKey, T_Data& arData) const;
};

#include "BSMapBase.inl"