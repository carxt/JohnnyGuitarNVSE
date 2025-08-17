#pragma once

template <class T>
class BSSimpleList {
public:
	BSSimpleList();
	BSSimpleList(const T& item);
	BSSimpleList(const T& item, BSSimpleList<T>* apNext);
	BSSimpleList(const BSSimpleList<T>& arEntry);
	~BSSimpleList();

	T					m_item;
	BSSimpleList<T>*	m_pkNext;

	const T GetItem() const;
	T GetItem();
	void SetItem(const T& aItem);

	const BSSimpleList<T>* GetNext() const;
	BSSimpleList<T>* GetNext();
	void SetNext(BSSimpleList<T>* apNext);

	bool IsEmpty() const;

	void AddHead(const T& aItem);

	void AddTail(const T& aItem);

	bool IsInList(const T& aItem) const;

	BSSimpleList<T>* GetPos(const T& aItem) const;

	uint32_t ItemsInList() const;

	void RemoveAll();

	void RemoveHead();

	void RemoveTail();

	void Remove(const T& aItem);

	void InsertSorted(const T& aItem, int32_t(__cdecl* apCompare)(const T& aItem1, const T& aItem2));

	// Custom methods

	const BSSimpleList<T>* GetHead() const { return this; }
	BSSimpleList<T>* GetHead() { return this; }

	BSSimpleList<T>* GetTail() const {
		BSSimpleList<T>* kIter;
		for (kIter = const_cast<BSSimpleList<T>*>(this); kIter->GetNext(); kIter = kIter->GetNext()) {}
		return kIter;
	}

	class Iterator {
	public:
		Iterator(BSSimpleList<T>* node) : m_node(node) {}

		T& operator*() { return m_node->m_item; }
		const T& operator*() const { return m_node->m_item; }

		Iterator& operator++() {
			if (m_node)
				m_node = m_node->m_pkNext;
			return *this;
		}

		bool operator!=(const Iterator& other) const {
			return m_node != other.m_node;
		}

	private:
		BSSimpleList<T>* m_node;
	};

	Iterator begin() { return Iterator(this); }
	Iterator end() { return Iterator(nullptr); }

	BSSimpleList<T>* GetAt(uint32_t auiIndex) const {
		uint32_t i = 0;
		BSSimpleList<T>* pIter = const_cast<BSSimpleList<T>*>(this);
		while (pIter) {
			if (i == auiIndex)
				return pIter;

			pIter = pIter->GetNext();
			++i;
		}
		return nullptr;
	}

	int32_t GetIndexOf(const T& aItem) const {
		int32_t iIndex = 0;
		const BSSimpleList<T>* pIter = this;
		while (pIter) {
			if (pIter->GetItem() == aItem)
				return iIndex;

			pIter = pIter->GetNext();
			++iIndex;
		}
		return -1;
	}

	template <typename FUNC>
	int32_t GetIndexOf(const FUNC&& func) const {
		int32_t iIndex = 0;
		const BSSimpleList<T>* pIter = this;
		while (pIter) {
			if (func(pIter))
				return iIndex;

			pIter = pIter->GetNext();
			++iIndex;
		}
		return -1;
	}

	BSSimpleList<T>* Find(const T& aItem) const {
		BSSimpleList<T>* pIter = const_cast<BSSimpleList<T>*>(this);
		while (pIter) {
			if (pIter->GetItem() == aItem)
				return pIter;

			pIter = pIter->GetNext();
		}
		return nullptr;
	}

	template <typename FUNC>
	BSSimpleList<T>* Find(const FUNC&& func) const {
		BSSimpleList<T>* pIter = const_cast<BSSimpleList<T>*>(this);
		while (pIter) {
			if (func(pIter))
				return pIter;

			pIter = pIter->GetNext();
		}
		return nullptr;
	}

	template <typename FUNC>
	bool IsInList(FUNC&& func) const {
		return Find(func) != nullptr;
	}

	template <typename FUNC, typename... ARGS>
	void ForEach(FUNC&& func, ARGS... args) {
		BSSimpleList<T>* pIter = const_cast<BSSimpleList<T>*>(this);
		while (pIter) {
			func(pIter, args...);
			pIter = pIter->GetNext();
		}
	}

	[[nodiscard]] BSSimpleList<T>* ReplaceAt(uint32_t auiIndex, const T& aItem) {
		BSSimpleList<T>* pIter = GetAt(auiIndex);
		BSSimpleList<T>* pReplaced = nullptr;
		if (pIter) {
			pReplaced = new BSSimpleList<T>(pIter->GetItem());
			pIter->SetItem(aItem);
		}
		return pReplaced;
	}

	[[nodiscard]] BSSimpleList<T>* SetAt(uint32_t auiIndex, const T& aItem) {
		BSSimpleList<T>* pIter = GetAt(auiIndex);
		if (pIter)
			pIter->SetItem(aItem);
		else
			AddTail(aItem);
		return pIter;
	}

	BSSimpleList<T>* AddAt(uint32_t auiIndex, const T& aItem) {
		BSSimpleList<T>* pIter = GetAt(auiIndex);
		if (pIter) {
			if (pIter->GetItem()) {
				BSSimpleList<T>* pNewNode = new BSSimpleList<T>(aItem);
				pNewNode->SetNext(pIter->GetNext());
				pIter->SetNext(pNewNode);
			}
			else {
				pIter->SetItem(aItem);
			}
		}
		else {
			AddTail(aItem);
		}
		return pIter;
	}

	BSSimpleList<T>* RemoveAt(uint32_t auiIndex) {
		BSSimpleList<T>* pIter = GetAt(auiIndex);
		if (pIter)
			Remove(pIter->GetItem());
		return pIter;
	}
};

#include "BSSimpleList.inl"

ASSERT_SIZE(BSSimpleList<uint32_t>, 0x8);