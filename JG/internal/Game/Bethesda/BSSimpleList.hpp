#pragma once

#include "BSMemObject.hpp"


template <class T>
class SPEC_EMPTY_BASES BSSimpleList : public BSMemObject {
public:
	BSSimpleList();
	BSSimpleList(const T& arItem);
	BSSimpleList(const T& arItem, BSSimpleList<T>* apNext);
	~BSSimpleList();

	T					m_item;
	BSSimpleList<T>*	m_pkNext;

	const T& GetItem() const;
	T& GetItem();
	void SetItem(const T& arItem);

	const BSSimpleList<T>* GetNext() const;
	BSSimpleList<T>* GetNext();
	void SetNext(BSSimpleList<T>* apNext);

	bool IsEmpty() const;

	void AddHead(const T& arItem);

	void AddTail(const T& arItem);

	bool IsInList(const T& arItem) const;

	BSSimpleList<T>* GetPos(const T& arItem) const;

	uint32_t ItemsInList() const;

	void RemoveAll();

	void RemoveHead();

	void RemoveTail();

	void Remove(const T& arItem);

	void Insert(const T& arItem, int32_t(__cdecl* apCompare)(const T& arItem1, const T& arItem2));

	// Custom methods

	const BSSimpleList<T>* GetHead() const { return this; }
	BSSimpleList<T>* GetHead() { return this; }

	BSSimpleList<T>* GetTail() const {
		BSSimpleList<T>* pIter;
		for (pIter = const_cast<BSSimpleList<T>*>(this); pIter->GetNext(); pIter = pIter->GetNext()) {}
		return pIter;
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

	int32_t GetIndexOf(const T& arItem) const {
		int32_t iIndex = 0;
		const BSSimpleList<T>* pIter = this;
		while (pIter) {
			if (pIter->GetItem() == arItem)
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

	BSSimpleList<T>* Find(const T& arItem) const {
		BSSimpleList<T>* pIter = const_cast<BSSimpleList<T>*>(this);
		while (pIter) {
			if (pIter->GetItem() == arItem)
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

	[[nodiscard]] BSSimpleList<T>* ReplaceAt(uint32_t auiIndex, const T& arItem) {
		BSSimpleList<T>* pIter = GetAt(auiIndex);
		BSSimpleList<T>* pReplaced = nullptr;
		if (pIter) {
			pReplaced = new BSSimpleList<T>(pIter->GetItem());
			pIter->SetItem(arItem);
		}
		return pReplaced;
	}

	[[nodiscard]] BSSimpleList<T>* SetAt(uint32_t auiIndex, const T& arItem) {
		BSSimpleList<T>* pIter = GetAt(auiIndex);
		if (pIter)
			pIter->SetItem(arItem);
		else
			AddTail(arItem);
		return pIter;
	}

	BSSimpleList<T>* AddAt(uint32_t auiIndex, const T& arItem) {
		BSSimpleList<T>* pIter = GetAt(auiIndex);
		if (pIter) {
			if (pIter->GetItem()) {
				BSSimpleList<T>* pNewNode = new BSSimpleList<T>(arItem);
				pNewNode->SetNext(pIter->GetNext());
				pIter->SetNext(pNewNode);
			}
			else {
				pIter->SetItem(arItem);
			}
		}
		else {
			AddTail(arItem);
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