#pragma once

#include "NiMemObject.hpp"

template <class T_Data, class Allocator>
class SPEC_EMPTY_BASES NiTLargeArray : public NiMemObject {
public:
	NiTLargeArray(uint32_t auiMaxSize = 0, uint32_t auiGrowBy = 1);
	virtual ~NiTLargeArray();
	NiTLargeArray(const NiTLargeArray&) = delete;
	NiTLargeArray& operator=(const NiTLargeArray&) = delete;

	T_Data*	 m_pBase;
	uint32_t m_uiMaxSize;
	uint32_t m_uiSize;
	uint32_t m_uiESize;
	uint32_t m_uiGrowBy;

	// Array size, including empty elements
	uint32_t GetSize() const;
	// Array size, excluding empty elements
	uint32_t GetEffectiveSize() const;
	// Total allocated size
	uint32_t GetAllocatedSize() const;

	bool IsEmpty() const;

	void SetSize(uint32_t auiMaxSize);
	void SetGrowBy(uint32_t auiGrowBy);

	T_Data& GetAt(uint32_t auiIndex) const;
	void SetAt(uint32_t auiIndex, const T_Data& arData);
	uint32_t SetAtGrow(uint32_t auiIndex, const T_Data& arData);

	uint32_t Add(const T_Data& arData);
	uint32_t AddFirstEmpty(const T_Data& arData);

	T_Data RemoveAt(uint32_t auiIndex);
	T_Data RemoveAtAndFill(uint32_t auiIndex);

	T_Data RemoveEnd();

	void RemoveAll();

	uint32_t Remove(const T_Data& arData);

	void Compact();

	void UpdateSize();
};

#include "NiTLargeArray.inl"