#pragma once

#include "BSMemObject.hpp"

template <typename T, uint32_t RESIZE_SIZE = 1024>
class BSSimpleArray {
public:
	BSSimpleArray();
	BSSimpleArray(uint32_t auiReserveSize, uint32_t auiSize);
	BSSimpleArray(const BSSimpleArray&) = delete;
	BSSimpleArray& operator=(const BSSimpleArray&) = delete;

	virtual							~BSSimpleArray();
	virtual SPEC_RESTRICT T*		Allocate(uint32_t auiCount);
	virtual				  void		Deallocate(T* apData);
	virtual SPEC_RESTRICT T*		Reallocate(T* apData, uint32_t auiCount);

	T*			pBuffer;
	uint32_t	uiSize;
	uint32_t	uiReservedSize;

	uint32_t GetSize() const;
	uint32_t GetReservedSize() const;
	bool IsEmpty() const;
	T& GetAt(const uint32_t auiIndex) const;
	T& GetFirst() const;
	T& GetLast() const;

	T& operator[](uint32_t auiIndex) const;

	void ConstructItems(T* apData, uint32_t auiCount);

	void DestructItems(T* apData, uint32_t auiCount);

	void InitialSetup(uint32_t auiReserveSize, uint32_t auiSize);

	void DeallocateBuffer();

	void Clear(bool abFree = true);

	SPEC_NOALIAS void MoveItems(T* apNewBuffer, T* apOldBuffer, uint32_t auiSize);

	void ReallocateBuffer(uint32_t auiNewSize, uint32_t auiSize);

	void SetSize(uint32_t auiSize, bool abFree = true);

	void SetReservedSize(uint32_t auiAllocSize);

	uint32_t AddUninitialized();

	uint32_t Add(const T& aItem);

	void SetAt(uint32_t auiIndex, const T& aItem);

	bool ShouldGrow() const;

	uint32_t GetNewSizeForGrow() const;

	bool ShouldShrink() const;

	uint32_t GetNewSizeForShrink() const;

	void Remove(uint32_t auiIndex, bool abShrink);

	void RemoveRange(uint32_t auiIndex, uint32_t auiCount, bool abShrink);

	void RemoveFast(uint32_t auiIndex, uint32_t auiCount);

	void RemoveLast();

	int32_t Find(const T& aItem, uint32_t auiStartPosition, bool(__cdecl* apCompareFunc)(const T&, const T&)) const;

	bool IsInArray(const T& aItem) const;

	void QuickSort(_CoreCrtNonSecureSearchSortCompareFunction apCompareFunc);

	// -----------------------------------------------

	class Iterator {
	public:
		Iterator(T* apNode) : pNode(apNode) {}

		T& operator*() { return *pNode; }
		const T& operator*() const { return *pNode; }

		Iterator& operator++() {
			pNode++;
			return *this;
		}

		bool operator!=(const Iterator& arOther) const {
			return pNode != arOther.pNode;
		}

	private:
		T* pNode;
	};

	Iterator begin() { return Iterator(&GetFirst()); }
	Iterator end() { return Iterator(&GetLast()); }

	template <typename FUNC, typename... ARGS>
	void ForEach(FUNC&& func, ARGS... args) {
		for (uint32_t i = 0; i < GetSize(); i++)
			func(GetAt(i), args...);
	}
};

#include "BSSimpleArray.inl"

ASSERT_SIZE(BSSimpleArray<uint32_t>, 0x10);