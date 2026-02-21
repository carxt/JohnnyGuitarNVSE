#pragma once

#include "NiTArray.hpp"

// GAME - 0x869E90
template<class T_Data, class Allocator>
inline NiTArray<T_Data, Allocator>::NiTArray(uint32_t auiMaxSize, uint32_t auiGrowBy) {
	m_usMaxSize = static_cast<uint16_t>(auiMaxSize);
	m_usGrowBy = static_cast<uint16_t>(auiGrowBy);
	m_usSize = 0;
	m_usESize = 0;

	if (m_usMaxSize > 0)
		m_pBase = Allocator::Allocate(m_usMaxSize);
	else
		m_pBase = 0;
}

// GAME - 0x869E30
template<class T_Data, class Allocator>
inline NiTArray<T_Data, Allocator>::~NiTArray() {
	Allocator::Deallocate(m_pBase);
}

// GAME - 0x658930
template<class T_Data, class Allocator>
inline uint16_t NiTArray<T_Data, Allocator>::GetSize() const {
	return m_usSize;
}

// GAME - 0x9938B0
template<class T_Data, class Allocator>
inline uint16_t NiTArray<T_Data, Allocator>::GetEffectiveSize() const {
	return m_usESize;
}

template<class T_Data, class Allocator>
inline uint16_t NiTArray<T_Data, Allocator>::GetAllocatedSize() const {
	return m_usMaxSize;
}

template <class T_Data, class Allocator>
inline bool NiTArray<T_Data, Allocator>::IsEmpty() const {
	return m_usESize == 0;
}

// GAME - 0x96AD30
template<class T_Data, class Allocator>
inline void NiTArray<T_Data, Allocator>::SetSize(uint32_t auiMaxSize) {
	ASSUME_ASSERT(auiMaxSize <= UINT16_MAX);

	const uint16_t usMaxSize = static_cast<uint16_t>(auiMaxSize);

	if (usMaxSize == m_usMaxSize)
		return;

	uint16_t i;
	if (usMaxSize < m_usSize) {
		for (i = usMaxSize; i < m_usSize; i++) {
			if (m_pBase[i] != T_Data(0)) {
				m_pBase[i] = T_Data(0);
				m_usESize--;
			}
		}
		m_usSize = usMaxSize;
	}

	T_Data* pSaveBase = m_pBase;
	m_usMaxSize = usMaxSize;
	if (usMaxSize > 0) {
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

// GAME - 0x559490
template<class T_Data, class Allocator>
inline void NiTArray<T_Data, Allocator>::SetGrowBy(uint32_t auiGrowBy) {
	ASSUME_ASSERT(auiGrowBy <= UINT16_MAX);
	m_usGrowBy = static_cast<uint16_t>(auiGrowBy);
}

// GAME - 0x877A30
template<class T_Data, class Allocator>
inline T_Data& NiTArray<T_Data, Allocator>::GetAt(uint32_t auiIndex) const {
	ASSUME_ASSERT(auiIndex < m_usSize);
	return m_pBase[auiIndex];
}

// GAME - 0x96AE90
template<class T_Data, class Allocator>
inline void NiTArray<T_Data, Allocator>::SetAt(uint32_t auiIndex, const T_Data& arData) {
	ASSUME_ASSERT(auiIndex <= m_usMaxSize);
	if (auiIndex >= m_usSize) {
		m_usSize = auiIndex + 1;
		if (arData != T_Data(0))
			m_usESize++;
	}
	else {
		if (arData != T_Data(0)) {
			if (m_pBase[auiIndex] == T_Data(0))
				m_usESize++;
		}
		else if (m_pBase[auiIndex] != T_Data(0))
			m_usESize--;
	}

	m_pBase[auiIndex] = arData;
}

// GAME - 0x470000
template<class T_Data, class Allocator>
inline uint32_t NiTArray<T_Data, Allocator>::SetAtGrow(uint32_t auiIndex, const T_Data& arData) {
	if (auiIndex >= m_usMaxSize)
		SetSize(auiIndex + m_usGrowBy);

	SetAt(auiIndex, arData);
	return auiIndex;
}

// GAME - 0x96A610
template<class T_Data, class Allocator>
inline uint32_t NiTArray<T_Data, Allocator>::Add(const T_Data& arData) {
	return SetAtGrow(m_usSize, arData);
}

// GAME - 0xA5B4B0
template<class T_Data, class Allocator>
inline uint32_t NiTArray<T_Data, Allocator>::AddFirstEmpty(const T_Data& arData) {
	if (arData == T_Data(0))
		return UINT32_MAX;

	for (uint16_t i = 0; i < m_usSize; i++) {
		if (m_pBase[i] == T_Data(0)) {
			m_pBase[i] = arData;
			m_usESize++;
			return i;
		}
	}

	return SetAtGrow(m_usSize, arData);
}

// GAME - 0xA93C50
template<class T_Data, class Allocator>
inline T_Data NiTArray<T_Data, Allocator>::RemoveAt(uint32_t auiIndex) {
	if (auiIndex >= m_usSize)
		return T_Data(0);

	T_Data kElement = m_pBase[auiIndex];
	m_pBase[auiIndex] = T_Data(0);

	if (kElement != T_Data(0))
		m_usESize--;

	if (auiIndex == static_cast<uint16_t>(m_usSize - 1))
		m_usSize--;

	return kElement;
}

template<class T_Data, class Allocator>
inline T_Data NiTArray<T_Data, Allocator>::RemoveAtAndFill(uint32_t auiIndex) {
	if (auiIndex >= m_usSize)
		return T_Data(0);

	m_usSize--;
	T_Data kElement = m_pBase[auiIndex];

	m_pBase[auiIndex] = m_pBase[m_usSize];
	m_pBase[m_usSize] = T_Data(0);

	if (kElement != T_Data(0))
		m_usESize--;

	return kElement;
}

// GAME - 0xC20FD0
template<class T_Data, class Allocator>
inline T_Data NiTArray<T_Data, Allocator>::RemoveEnd() {
	if (m_usSize == 0)
		return T_Data(0);

	m_usSize--;
	T_Data kElement = m_pBase[m_usSize];
	m_pBase[m_usSize] = T_Data(0);

	if (kElement != T_Data(0))
		m_usESize--;

	return kElement;
}

// GAME - 0x5E03D0
template<class T_Data, class Allocator>
inline void NiTArray<T_Data, Allocator>::RemoveAll() {
	for (uint16_t i = 0; i < m_usSize; i++)
		m_pBase[i] = T_Data(0);

	m_usSize = 0;
	m_usESize = 0;
}

template<class T_Data, class Allocator>
inline uint32_t NiTArray<T_Data, Allocator>::Remove(const T_Data& arData) {
	if (arData != T_Data(0)) {
		for (uint16_t i = 0; i < m_usSize; i++) {
			if (m_pBase[i] == arData) {
				m_pBase[i] = T_Data(0);

				m_usESize--;
				if (i == m_usSize - 1)
					m_usSize--;

				return i;
			}
		}
	}

	return UINT32_MAX;
}

// GAME - 0x4AFC80
template<class T_Data, class Allocator>
inline void NiTArray<T_Data, Allocator>::Compact() {
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
	else {
		m_pBase = 0;
	}

	Allocator::Deallocate(pSaveBase);
}

// GAME - 0x4AFE50
template<class T_Data, class Allocator>
inline void NiTArray<T_Data, Allocator>::UpdateSize() {
	while (m_usSize > 0) {
		if (m_pBase[m_usSize - 1] != T_Data(0))
			break;

		m_usSize--;
	}
}