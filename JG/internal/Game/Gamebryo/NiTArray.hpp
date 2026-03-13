#pragma once

#include "NiMemObject.hpp"

template <class T_Data, class Allocator>
class SPEC_EMPTY_BASES NiTArray : public NiMemObject {
public:
	NiTArray(uint32_t auiMaxSize = 0, uint32_t auiGrowBy = 1);
	virtual ~NiTArray();
	NiTArray(const NiTArray&) = delete;
	NiTArray& operator=(const NiTArray&) = delete;

	T_Data*		m_pBase;
	uint16_t	m_usMaxSize;
	uint16_t	m_usSize;
	uint16_t	m_usESize;
	uint16_t	m_usGrowBy;

	// Array size, including empty elements
	uint16_t GetSize() const;
	// Array size, excluding empty elements
	uint16_t GetEffectiveSize() const;
	// Total allocated size
	uint16_t GetAllocatedSize() const;

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

#include "NiTArray.inl"