#pragma once

#include "NiTMap.hpp"
#include "NiFixedString.hpp"

template <class Allocator, class T_Data>
class SPEC_EMPTY_BASES NiTFixedStringMapBase : public NiMemObject {
public:
	NiTFixedStringMapBase(uint32_t auiHashSize = 37);
	NiTFixedStringMapBase(const NiTFixedStringMapBase&) = delete;
	NiTFixedStringMapBase& operator=(const NiTFixedStringMapBase&) = delete;

	virtual ~NiTFixedStringMapBase();
	virtual NiTMapItem<NiFixedString, T_Data>* NewItem() = 0;
	virtual void DeleteItem(NiTMapItem<NiFixedString, T_Data>* apItem) = 0;

	struct AntiBloatAllocator : public Allocator {
		uint32_t m_uiCount;
	};

	uint32_t							m_uiHashSize;
	NiTMapItem<NiFixedString, T_Data>** m_ppkHashTable;
	AntiBloatAllocator					m_kAllocator;

	uint32_t GetCount() const;
	bool IsEmpty() const;

	uint32_t KeyToHashIndex(const NiFixedString& arString) const;

	bool IsKeysEqual(const NiFixedString& arString1, const NiFixedString& arString2) const;

	void SetValue(NiTMapItem<NiFixedString, T_Data>* apItem, const NiFixedString& arString, T_Data akData);

	void ClearValue(NiTMapItem<NiFixedString, T_Data>* apItem);

	bool GetAt(const NiFixedString& arString, T_Data& arData) const;

	void SetAt(const NiFixedString& arString, T_Data akData);

	NiTMapIterator GetFirstPos() const;

	void GetNext(NiTMapIterator& arPos, NiFixedString& arString, T_Data& arData) const;

	void RemoveAll();

	bool RemoveAt(const NiFixedString& arString);
};

#include "NiTFixedStringMapBase.inl"