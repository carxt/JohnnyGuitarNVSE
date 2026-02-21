#pragma once

#include "NiTLargeArray.hpp"

// GAME - 0x864160
template<class T_Data, class Allocator>
inline NiTLargeArray<T_Data, Allocator>::NiTLargeArray(uint32_t auiMaxSize, uint32_t auiGrowBy) {
	m_uiMaxSize = auiMaxSize;
	m_uiGrowBy = auiGrowBy;
	m_uiSize = 0;
	m_uiESize = 0;

	if (m_uiMaxSize > 0)
		m_pBase = Allocator::Allocate(m_uiMaxSize);
	else
		m_pBase = 0;
}

// GAME - 0x864100
template<class T_Data, class Allocator>
inline NiTLargeArray<T_Data, Allocator>::~NiTLargeArray() {
	Allocator::Deallocate(m_pBase);
}

template<class T_Data, class Allocator>
inline uint32_t NiTLargeArray<T_Data, Allocator>::GetSize() const {
	return m_uiSize;
}

template<class T_Data, class Allocator>
inline uint32_t NiTLargeArray<T_Data, Allocator>::GetEffectiveSize() const {
	return m_uiESize;
}

template<class T_Data, class Allocator>
inline uint32_t NiTLargeArray<T_Data, Allocator>::GetAllocatedSize() const {
	return m_uiMaxSize;
}

template <class T_Data, class Allocator>
inline bool NiTLargeArray<T_Data, Allocator>::IsEmpty() const {
	return m_uiESize == 0;
}

// GAME - 0x864280
template<class T_Data, class Allocator>
inline void NiTLargeArray<T_Data, Allocator>::SetSize(uint32_t auiMaxSize) {
	const uint32_t usMaxSize = static_cast<uint32_t>(auiMaxSize);

	if (usMaxSize == m_uiMaxSize)
		return;

	uint32_t i;
	if (usMaxSize < m_uiSize) {
		for (i = usMaxSize; i < m_uiSize; i++) {
			if (m_pBase[i] != T_Data(0)) {
				m_pBase[i] = T_Data(0);
				m_uiESize--;
			}
		}
		m_uiSize = usMaxSize;
	}

	T_Data* pSaveBase = m_pBase;
	m_uiMaxSize = usMaxSize;
	if (usMaxSize > 0) {
		m_pBase = Allocator::Allocate(m_uiMaxSize);
		for (i = 0; i < m_uiSize; i++) {
			m_pBase[i] = pSaveBase[i];
		}
		for (i = m_uiSize; i < m_uiMaxSize; i++) {
			m_pBase[i] = T_Data(0);
		}
	}
	else {
		m_pBase = 0;
	}
	Allocator::Deallocate(pSaveBase);
}

template<class T_Data, class Allocator>
inline void NiTLargeArray<T_Data, Allocator>::SetGrowBy(uint32_t auiGrowBy) {
	m_uiGrowBy = static_cast<uint32_t>(auiGrowBy);
}

template<class T_Data, class Allocator>
inline T_Data& NiTLargeArray<T_Data, Allocator>::GetAt(uint32_t auiIndex) const {
	return m_pBase[auiIndex];
}

// GAME - 0x61BD20
template<class T_Data, class Allocator>
inline void NiTLargeArray<T_Data, Allocator>::SetAt(uint32_t auiIndex, const T_Data& arData) {
	ASSUME_ASSERT(auiIndex <= m_uiMaxSize);
	if (auiIndex >= m_uiSize) {
		m_uiSize = auiIndex + 1;
		if (arData != T_Data(0))
			m_uiESize++;
	}
	else {
		if (arData != T_Data(0)) {
			if (m_pBase[auiIndex] == T_Data(0))
				m_uiESize++;
		}
		else if (m_pBase[auiIndex] != T_Data(0))
			m_uiESize--;
	}

	m_pBase[auiIndex] = arData;
}

// GAME - 0x864240
template<class T_Data, class Allocator>
inline uint32_t NiTLargeArray<T_Data, Allocator>::SetAtGrow(uint32_t auiIndex, const T_Data& arData) {
	if (auiIndex >= m_uiMaxSize)
		SetSize(auiIndex + m_uiGrowBy);

	SetAt(auiIndex, arData);
	return auiIndex;
}

// GAME - 0x863D90
template<class T_Data, class Allocator>
inline uint32_t NiTLargeArray<T_Data, Allocator>::Add(const T_Data& arData) {
	return SetAtGrow(m_uiSize, arData);
}

// GAME - 0xA65F80
template<class T_Data, class Allocator>
inline uint32_t NiTLargeArray<T_Data, Allocator>::AddFirstEmpty(const T_Data& arData) {
	if (arData == T_Data(0))
		return UINT32_MAX;

	for (uint32_t i = 0; i < m_uiSize; i++) {
		if (m_pBase[i] == T_Data(0)) {
			m_pBase[i] = arData;
			m_uiESize++;
			return i;
		}
	}

	return SetAtGrow(m_uiSize, arData);
}

// GAME - 0x486B80
template<class T_Data, class Allocator>
inline T_Data NiTLargeArray<T_Data, Allocator>::RemoveAt(uint32_t auiIndex) {
	if (auiIndex >= m_uiSize)
		return T_Data(0);

	T_Data kElement = m_pBase[auiIndex];
	m_pBase[auiIndex] = T_Data(0);

	if (kElement != T_Data(0))
		m_uiESize--;

	if (auiIndex == m_uiSize - 1)
		m_uiSize--;

	return kElement;
}

template<class T_Data, class Allocator>
inline T_Data NiTLargeArray<T_Data, Allocator>::RemoveAtAndFill(uint32_t auiIndex) {
	if (auiIndex >= m_uiSize)
		return T_Data(0);

	m_uiSize--;
	T_Data kElement = m_pBase[auiIndex];

	m_pBase[auiIndex] = m_pBase[m_uiSize];
	m_pBase[m_uiSize] = T_Data(0);

	if (kElement != T_Data(0))
		m_uiESize--;

	return kElement;
}

template<class T_Data, class Allocator>
inline T_Data NiTLargeArray<T_Data, Allocator>::RemoveEnd() {
	if (m_uiSize == 0)
		return T_Data(0);

	m_uiSize--;
	T_Data kElement = m_pBase[m_uiSize];
	m_pBase[m_uiSize] = T_Data(0);

	if (kElement != T_Data(0))
		m_uiESize--;

	return kElement;
}

// GAME - 0x863DB0
template<class T_Data, class Allocator>
inline void NiTLargeArray<T_Data, Allocator>::RemoveAll() {
	for (uint32_t i = 0; i < m_uiSize; i++)
		m_pBase[i] = T_Data(0);

	m_uiSize = 0;
	m_uiESize = 0;
}

template<class T_Data, class Allocator>
inline uint32_t NiTLargeArray<T_Data, Allocator>::Remove(const T_Data& arData) {
	if (arData != T_Data(0)) {
		for (uint32_t i = 0; i < m_uiSize; i++) {
			if (m_pBase[i] == arData) {
				m_pBase[i] = T_Data(0);

				m_uiESize--;
				if (i == m_uiSize - 1)
					m_uiSize--;

				return i;
			}
		}
	}

	return UINT32_MAX;
}

// GAME - 0x61BDC0
template<class T_Data, class Allocator>
inline void NiTLargeArray<T_Data, Allocator>::Compact() {
	if (m_uiESize == m_uiSize)
		return;

	if (m_uiESize) {
		for (uint32_t i = 0, j = 0; i < m_uiSize; i++) {
			if (m_pBase[i] != T_Data(0)) {
				if (m_pBase[j] != m_pBase[i])
					m_pBase[j] = m_pBase[i];
				j++;
			}
		}
	}

	T_Data* pSaveBase = m_pBase;
	m_uiSize = m_uiESize;
	m_uiMaxSize = m_uiSize;
	if (m_uiMaxSize > 0) {
		m_pBase = Allocator::Allocate(m_uiMaxSize);

		for (uint32_t i = 0; i < m_uiSize; i++)
			m_pBase[i] = pSaveBase[i];
	}
	else {
		m_pBase = 0;
	}

	Allocator::Deallocate(pSaveBase);
}

template<class T_Data, class Allocator>
inline void NiTLargeArray<T_Data, Allocator>::UpdateSize() {
	while (m_uiSize > 0) {
		if (m_pBase[m_uiSize - 1] != T_Data(0))
			break;

		m_uiSize--;
	}
}