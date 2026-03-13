#pragma once

#include "NiMemObject.hpp"
#include "NiTMallocInterface.hpp"
#include "NiTNewInterface.hpp"

template <class T_Data, class Allocator>
class SPEC_EMPTY_BASES NiTSet : public NiMemObject {
public:
	NiTSet(uint32_t auiInitialSize) {
		if (auiInitialSize > 0) {
			m_pBase = Allocator::Allocate(auiInitialSize);
		}
		else {
			m_pBase = nullptr;
		}
		m_uiAlloced = auiInitialSize;
		m_uiUsed = 0;
	}
	~NiTSet() {
		Allocator::Deallocate(m_pBase);
	}

	NiTSet(const NiTSet&) = delete;
	NiTSet& operator=(const NiTSet&) = delete;

	T_Data*		m_pBase;
	uint32_t	m_uiAlloced;
	uint32_t	m_uiUsed;

	uint32_t GetSize() const { return m_uiUsed; }
	T_Data* GetBase() const { return m_pBase; }
	const T_Data& GetAt(uint32_t auiIndex) const { return m_pBase[auiIndex]; }
	T_Data& GetAt(uint32_t auiIndex) { return m_pBase[auiIndex]; }

	void RemoveAll() {
		m_uiUsed = 0;
	}

	// GAME - 0xA311E0
	void Realloc(uint32_t uiNewSize) {
		if (uiNewSize != m_uiAlloced) {
			T_Data* pNewBase;
			uint32_t i;

			if (uiNewSize > 0) {
				pNewBase = Allocator::Allocate(uiNewSize);

				for (i = 0; i < m_uiUsed; i++) {
					pNewBase[i] = m_pBase[i];
				}
			}
			else {
				pNewBase = nullptr;
			}

			Allocator::Deallocate(m_pBase);
			m_pBase = pNewBase;
			m_uiAlloced = uiNewSize;
		}
	}

	// GAME - 0xA543B0
	void Add(const T_Data& element) {
		if (m_uiUsed == m_uiAlloced) {
			Realloc(m_uiAlloced > 0 ? (2 * m_uiAlloced) : 1);
		}

		m_pBase[m_uiUsed++] = element;
	}


	struct Iterator
	{
		friend NiTSet;

		uint32_t index;
		NiTSet* set;

		T_Data& operator*() const { return set->m_pBase[index]; }

		Iterator& operator++() {
			index++;
			return *this;
		}

		bool operator!=(const Iterator& other) {
			return index != other.index;
		}
	};

	Iterator begin() {
		return Iterator{ 0, this };
	}

	Iterator end() {
		return Iterator{ m_uiUsed, this };
	}
};