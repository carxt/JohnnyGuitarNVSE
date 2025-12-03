#pragma once

#include "NiMemObject.hpp"
#include "NiTMallocInterface.hpp"
#include "NiTNewInterface.hpp"

template <class T_Data, class Allocator>
class NiTArray : public NiMemObject {
public:
	NiTArray(uint32_t uiMaxSize = 0, uint32_t uiGrowBy = 1) {
		m_usMaxSize = (uint16_t)uiMaxSize;
		m_usGrowBy = (uint16_t)uiGrowBy;
		m_usSize = 0;
		m_usESize = 0;

		if (m_usMaxSize > 0)
			m_pBase = Allocator::Allocate(m_usMaxSize);
		else
			m_pBase = 0;
	}
	NiTArray(const NiTArray&) = delete;
	NiTArray& operator=(const NiTArray&) = delete;

	virtual ~NiTArray() {
		Allocator::Deallocate(m_pBase);
	};

	T_Data*		m_pBase;
	uint16_t	m_usMaxSize;
	uint16_t	m_usSize;
	uint16_t	m_usESize;
	uint16_t	m_usGrowBy;

	// Array size, including empty elements
	inline uint16_t GetSize() const { return m_usSize; }
	// Array size, excluding empty elements
	inline uint16_t GetEffectiveSize() const { return m_usESize; }
	// Total allocated size
	inline uint16_t GetAllocatedSize() const { return m_usMaxSize; }
	inline bool IsEmpty() const { return m_usESize == 0; }

	// 0xA5B790, 0xC45B20, 0xA90180, so many I won't bother listing them all
	void SetSize(uint32_t uiMaxSize) {
		if (uiMaxSize == m_usMaxSize)
			return;

		uint16_t i;
		if (uiMaxSize < m_usSize) {
			for (i = (uint16_t)uiMaxSize; i < m_usSize; i++) {
				if (m_pBase[i] != T_Data(0)) {
					m_pBase[i] = T_Data(0);
					m_usESize--;
				}
			}
			m_usSize = uiMaxSize;
		}

		T_Data* pSaveBase = m_pBase;
		m_usMaxSize = uiMaxSize;
		if (uiMaxSize > 0) {
			m_pBase = Allocator::Allocate(m_usMaxSize);
			for (i = 0; i < m_usSize; i++) {
				m_pBase[i] = pSaveBase[i];
			}
			for (i = m_usSize; i < m_usMaxSize; i++) {
				m_pBase[i] = T_Data(0);
			}
		}
		else {
			m_pBase = 0;
		}
		Allocator::Deallocate(pSaveBase);
	}

	// 0xBA3AA0, so many I won't bother listing them all
	void SetAt(uint32_t uiIndex, const T_Data& element) {
		if (uiIndex >= m_usSize) {
			m_usSize = uiIndex + 1;
			if (element != T_Data(0))
				m_usESize++;
		}
		else {
			if (element != T_Data(0)) {
				if (m_pBase[uiIndex] == T_Data(0))
					m_usESize++;
			}
			else if (m_pBase[uiIndex] != T_Data(0))
					m_usESize--;
		}

		m_pBase[uiIndex] = element;
	}

	// 0x470000, 0x869640, 0x60BD90, 0x4B02D0, 0x869680
	uint32_t SetAtGrow(uint32_t uiIndex, const T_Data& element) {
		if (uiIndex >= m_usMaxSize)
			SetSize(uiIndex + m_usGrowBy);

		SetAt(uiIndex, element);
		return uiIndex;
	}

	// 0xC4C8D0
	uint32_t Add(const T_Data& element) {
		return SetAtGrow(m_usSize, element);
	}

	// 0xA5B4B0, 0xA5EB20, 0xC1F420, 0xC1F360
	uint32_t AddFirstEmpty(const T_Data& element) {
		if (element == T_Data(0))
			return 0xffffffff;

		for (uint16_t i = 0; i < m_usSize; i++) {
			if (m_pBase[i] == T_Data(0)) {
				m_pBase[i] = element;
				m_usESize++;
				return i;
			}
		}

		return SetAtGrow(m_usSize, element);
	}

	// 0xC5BB60, 0xA93C50
	T_Data RemoveAt(uint32_t uiIndex) {
		if (uiIndex >= m_usSize)
			return T_Data(0);

		T_Data element = m_pBase[uiIndex];
		m_pBase[uiIndex] = T_Data(0);

		if (element != T_Data(0))
			m_usESize--;

		if (uiIndex == (uint16_t)(m_usSize - 1))
			m_usSize--;

		return element;
	}

	// 0x877A30
	inline T_Data& GetAt(uint32_t uiIndex) const {
		return m_pBase[uiIndex];
	}

	T_Data RemoveAtAndFill(uint32_t uiIndex)
	{
		if (uiIndex >= m_usSize)
			return T_Data(0);

		m_usSize--;
		T_Data element = m_pBase[uiIndex];

		m_pBase[uiIndex] = m_pBase[m_usSize];
		m_pBase[m_usSize] = T_Data(0);

		if (element != T_Data(0))
			m_usESize--;

		return element;
	}

	T_Data RemoveEnd() {
		if (m_usSize == 0)
			return T_Data(0);

		m_usSize--;
		T_Data element = m_pBase[m_usSize];
		m_pBase[m_usSize] = T_Data(0);

		if (element != T_Data(0))
			m_usESize--;

		return element;
	}

	// 0xC46080, 0xC62F40
	void RemoveAll() {
		for (uint16_t i = 0; i < m_usSize; i++)
			m_pBase[i] = T_Data(0);

		m_usSize = 0;
		m_usESize = 0;
	}

	uint32_t Remove(const T_Data& element) {
		if (element != T_Data(0)) {
			for (uint16_t i = 0; i < m_usSize; i++) {
				if (m_pBase[i] == element) {
					m_pBase[i] = T_Data(0);

					m_usESize--;
					if (i == m_usSize - 1)
						m_usSize--;

					return i;
				}
			}
		}

		return (uint32_t)~0;
	}

	// 0x4AFC80, 0x600BC0
	void Compact() {
		if (m_usESize == m_usSize)
			return;

		if (m_usESize) {
			for (uint16_t i = 0, j = 0; i < m_usSize; i++) {
				if (m_pBase[i] != T_Data(0)) {
					if (m_pBase[j] != m_pBase[i])
						m_pBase[j] = m_pBase[i];
					j++;
				}
			}
		}

		T_Data* pSaveBase = m_pBase;
		m_usSize = m_usESize;
		m_usMaxSize = m_usSize;
		if (m_usMaxSize > 0) {
			m_pBase = Allocator::Allocate(m_usMaxSize);

			for (uint16_t i = 0; i < m_usSize; i++)
				m_pBase[i] = pSaveBase[i];
		}
		else
			m_pBase = 0;

		Allocator::Deallocate(pSaveBase);
	}

	// 0x4AFE50
	void UpdateSize() {
		while (m_usSize > 0) {
			if (m_pBase[m_usSize - 1] != T_Data(0))
				break;

			m_usSize--;
		}
	}
};

template <class T_Data> 
class NiTObjectArray : public NiTArray<T_Data, NiTNewInterface<T_Data>> {
public:
	NiTObjectArray(uint32_t uiMaxSize = 0, uint32_t uiGrowBy = 1) : NiTArray<T_Data, NiTNewInterface<T_Data>>(uiMaxSize, uiGrowBy) {};
};

template <class T_Data> 
class NiTPrimitiveArray : public NiTArray<T_Data, NiTMallocInterface<T_Data>> {
public:
	NiTPrimitiveArray(uint32_t uiMaxSize = 0, uint32_t uiGrowBy = 1) : NiTArray<T_Data, NiTMallocInterface<T_Data>>(uiMaxSize, uiGrowBy) {};
};

ASSERT_SIZE(NiTObjectArray<void*>, 0x10);
ASSERT_SIZE(NiTPrimitiveArray<void*>, 0x10);

typedef NiTPrimitiveArray<const char*> NiViewerStringsArray;