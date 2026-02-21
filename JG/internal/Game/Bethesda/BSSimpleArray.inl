#pragma once

#include "BSSimpleArray.hpp"

// GAME - 0x438660
template<typename T, uint32_t RESIZE_SIZE>
inline BSSimpleArray<T, RESIZE_SIZE>::BSSimpleArray() {
	InitialSetup(0, 0);
}

// GAME - 0x709E80
template<typename T, uint32_t RESIZE_SIZE>
inline BSSimpleArray<T, RESIZE_SIZE>::BSSimpleArray(uint32_t auiReserveSize, uint32_t auiSize) {
	InitialSetup(auiReserveSize, auiSize);
}

// GAME - 0x438690
template<typename T, uint32_t RESIZE_SIZE>
inline BSSimpleArray<T, RESIZE_SIZE>::~BSSimpleArray() {
	Clear();
}

// GAME - 0x8225D0
template<typename T, uint32_t RESIZE_SIZE>
SPEC_RESTRICT inline T* BSSimpleArray<T, RESIZE_SIZE>::Allocate(uint32_t auiCount) {
	return BSMemory::malloc<T>(auiCount); 
};

// GAME - 0x6DB090
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::Deallocate(T* apData) { 
	BSMemory::free(apData); 
};

// GAME - 0x84B630
template<typename T, uint32_t RESIZE_SIZE>
SPEC_RESTRICT inline T* BSSimpleArray<T, RESIZE_SIZE>::Reallocate(T* apData, uint32_t auiCount) {
	return static_cast<T*>(BSMemory::realloc(apData, sizeof(T) * auiCount)); 
};

template<typename T, uint32_t RESIZE_SIZE>
inline uint32_t BSSimpleArray<T, RESIZE_SIZE>::GetSize() const {
	return uiSize;
}

template<typename T, uint32_t RESIZE_SIZE>
inline uint32_t BSSimpleArray<T, RESIZE_SIZE>::GetReservedSize() const {
	return uiReservedSize;
}

// GAME - 0x76B610
template<typename T, uint32_t RESIZE_SIZE>
inline bool BSSimpleArray<T, RESIZE_SIZE>::IsEmpty() const {
	return uiSize == 0;
}

// GAME - 0x877A30
template<typename T, uint32_t RESIZE_SIZE>
inline T& BSSimpleArray<T, RESIZE_SIZE>::GetAt(const uint32_t auiIndex) const {
	assert(auiIndex >= 0);
	assert(auiIndex < uiSize);
	return pBuffer[auiIndex]; 
}

template<typename T, uint32_t RESIZE_SIZE>
inline T& BSSimpleArray<T, RESIZE_SIZE>::GetFirst() const {
	return GetAt(0);
}

// GAME - 0x6B3140, 0x6CED90
template<typename T, uint32_t RESIZE_SIZE>
inline T& BSSimpleArray<T, RESIZE_SIZE>::GetLast() const {
	return GetAt(uiSize - 1);
}

// GAME - 0x6A7AD0
template<typename T, uint32_t RESIZE_SIZE>
inline T& BSSimpleArray<T, RESIZE_SIZE>::operator[](uint32_t auiIndex) const {
	return GetAt(auiIndex);
}

// GAME - 0x822780
template<typename T, uint32_t RESIZE_SIZE>
void BSSimpleArray<T, RESIZE_SIZE>::ConstructItems(T* apData, uint32_t auiCount) {
	for (uint32_t i = 0; i < auiCount; i++)
		new (&apData[i]) T;
}

// GAME - 0x822820
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::DestructItems(T* apData, uint32_t auiCount) {
	for (uint32_t i = 0; i < auiCount; ++i)
		apData[i].~T();
}

// GAME - 0x6B3EB0
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::InitialSetup(uint32_t auiReserveSize, uint32_t auiSize) {
	pBuffer = nullptr;
	uiSize = 0;
	uiReservedSize = 0;

	if (auiSize > auiReserveSize)
		auiReserveSize = auiSize;

	if (auiReserveSize) {
		pBuffer = Allocate(auiReserveSize);
		uiReservedSize = auiReserveSize;
	}

	if (auiSize) {
		ConstructItems(pBuffer, auiSize);
		uiSize = auiSize;
	}
}

// GAME - 0x6A8500
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::DeallocateBuffer() {
	Deallocate(pBuffer);
	pBuffer = nullptr;
}

// GAME - 0x6C6200
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::Clear(bool abFree) {
	if (!pBuffer)
		return;

	DestructItems(pBuffer, uiSize);

	if (abFree) {
		DeallocateBuffer();
		pBuffer = nullptr;
		uiReservedSize = 0;
	}

	uiSize = 0;
}

// GAME - 0x42FB60
template<typename T, uint32_t RESIZE_SIZE>
SPEC_NOALIAS inline void BSSimpleArray<T, RESIZE_SIZE>::MoveItems(T* apNewBuffer, T* apOldBuffer, uint32_t auiSize) {
	if (!auiSize)
		return;

	if (apNewBuffer < apOldBuffer) {
		for (uint32_t i = 0; i < auiSize; ++i)
			memcpy(&apNewBuffer[i], &apOldBuffer[i], sizeof(T));
	}
	else if (apNewBuffer > apOldBuffer) {
		for (int32_t i = static_cast<int32_t>(auiSize) - 1; i >= 0; --i)
			memcpy(&apNewBuffer[i], &apOldBuffer[i], sizeof(T));
	}
}

// GAME - 0x42FC00
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::ReallocateBuffer(uint32_t auiNewSize, uint32_t auiSize) {
	if (!pBuffer) {
		pBuffer = Allocate(auiNewSize);
		uiReservedSize = auiNewSize;
	}
	else if (auiSize == uiReservedSize) {
		pBuffer = Reallocate(pBuffer, auiNewSize);
	}
	else {
		T* pNewBuffer = Allocate(auiNewSize);
		MoveItems(pNewBuffer, pBuffer, auiSize);
		DeallocateBuffer();
		pBuffer = pNewBuffer;
	}
}

// GAME - 0x695230
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::SetSize(uint32_t auiSize, bool abFree) {
	if (!auiSize) {
		Clear(abFree);
	}
	else if (auiSize > uiReservedSize) {
		if (uiReservedSize)
			ReallocateBuffer(auiSize, uiSize);
		else
			pBuffer = Allocate(auiSize);

		uiReservedSize = auiSize;
		ConstructItems(&pBuffer[uiSize], auiSize - uiSize);
		uiSize = auiSize;
	}
	else if (auiSize >= uiSize) {
		ConstructItems(&pBuffer[uiSize], auiSize - uiSize);
		uiSize = auiSize;
	}
	else {
		DestructItems(&pBuffer[auiSize], uiSize - auiSize);
		uiSize = auiSize;
		if (abFree && auiSize <= uiReservedSize >> 2) {
			ReallocateBuffer(auiSize, auiSize);
			uiReservedSize = auiSize;
		}
	}
}

// GAME - 0x6F9790
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::SetReservedSize(uint32_t auiAllocSize) {
	if (auiAllocSize == uiReservedSize)
		return;

	if (auiAllocSize < uiSize)
		uiSize = auiAllocSize;

	ReallocateBuffer(auiAllocSize, uiSize);
	uiReservedSize = auiAllocSize;
}

// GAME - 0x761540, 0xB5C360
template<typename T, uint32_t RESIZE_SIZE>
inline uint32_t BSSimpleArray<T, RESIZE_SIZE>::AddUninitialized() {
	if (!ShouldGrow())
		return uiSize++;

	if (uiReservedSize) {
		uint32_t uiResizeSize = GetNewSizeForGrow();
		ReallocateBuffer(uiResizeSize, uiSize);
		uiReservedSize = uiResizeSize;
	}
	else {
		constexpr uint32_t DEFAULT_ALLOC_SIZE = 4;
		pBuffer = Allocate(DEFAULT_ALLOC_SIZE);
		uiReservedSize = DEFAULT_ALLOC_SIZE;
	}

	return uiSize++;
}

// GAME - 0x7CB2E0
template<typename T, uint32_t RESIZE_SIZE>
inline uint32_t BSSimpleArray<T, RESIZE_SIZE>::Add(const T& aItem) {
	uint32_t uiNext = AddUninitialized();
	ConstructItems(&pBuffer[uiNext], 1);
	pBuffer[uiNext] = aItem;
	return uiNext;
}

// GAME - 0x6DB540
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::SetAt(uint32_t auiIndex, const T& aItem) {
	if (auiIndex == uiSize) {
		Add(aItem);
	}
	else if (ShouldGrow()) {
		uint32_t uiResizeSize = GetNewSizeForGrow();
		T* pNewBuffer = Allocate(uiResizeSize);
		MoveItems(pNewBuffer, pBuffer, auiIndex);
		ConstructItems(&pBuffer[auiIndex], 1);
		MoveItems(&pNewBuffer[auiIndex + 1], &pBuffer[auiIndex], uiSize - auiIndex);
		DeallocateBuffer();
		pBuffer = pNewBuffer;
		uiReservedSize = uiResizeSize;
	}
	else {
		MoveItems(&pBuffer[auiIndex + 1], &pBuffer[auiIndex], uiSize - auiIndex);
		ConstructItems(&pBuffer[auiIndex], 1);
	}
	++uiSize;
	pBuffer[auiIndex] = aItem;
}

// GAME - 0x438B90
template<typename T, uint32_t RESIZE_SIZE>
inline bool BSSimpleArray<T, RESIZE_SIZE>::ShouldGrow() const {
	return uiSize == uiReservedSize;
}

// GAME - 0x9A3910
template<typename T, uint32_t RESIZE_SIZE>
inline uint32_t BSSimpleArray<T, RESIZE_SIZE>::GetNewSizeForGrow() const {
	if (uiReservedSize <= RESIZE_SIZE)
		return 2 * uiReservedSize;
	else
		return uiReservedSize + RESIZE_SIZE;
}

// GAME - 0x6F3170
template<typename T, uint32_t RESIZE_SIZE>
inline bool BSSimpleArray<T, RESIZE_SIZE>::ShouldShrink() const {
	if (uiReservedSize <= RESIZE_SIZE) {
		if (uiSize <= uiReservedSize >> 2)
			return true;
	}
	else if (uiSize <= (uiReservedSize - RESIZE_SIZE * 2))
		return true;

	return false;
}

// GAME - 0x869600
template<typename T, uint32_t RESIZE_SIZE>
inline uint32_t BSSimpleArray<T, RESIZE_SIZE>::GetNewSizeForShrink() const {
	if (uiReservedSize <= RESIZE_SIZE * 2)
		return uiReservedSize >> 1;
	else
		return uiReservedSize - RESIZE_SIZE;
}

// GAME - 0x6BF8F0
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::Remove(uint32_t auiIndex, bool abShrink) {
	if (abShrink && ShouldShrink()) {
		uint32_t uiOptimalCapacity = GetNewSizeForShrink();
		T* pNewBuffer = Allocate(uiOptimalCapacity);
		MoveItems(pNewBuffer, pBuffer, auiIndex);
		DestructItems(&pBuffer[auiIndex], 1);
		MoveItems(&pNewBuffer[auiIndex], &pBuffer[auiIndex + 1], uiSize - 1);
		DeallocateBuffer();
		pBuffer = pNewBuffer;
		uiReservedSize = uiOptimalCapacity;
	}
	else
	{
		DestructItems(&pBuffer[auiIndex], 1);
		MoveItems(&pBuffer[auiIndex], &pBuffer[auiIndex + 1], uiSize - auiIndex - 1);
	}
	--uiSize;
}

// GAME - 0x49F3C0
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::RemoveRange(uint32_t auiIndex, uint32_t auiCount, bool abShrink) {
	if (auiCount < uiSize) {
		if (abShrink && ShouldShrink()) {
			uint32_t uiOptimalCapacity = GetNewSizeForShrink();
			T* pNewBuffer = Allocate(uiOptimalCapacity);
			MoveItems(pNewBuffer, pBuffer, auiIndex);
			DestructItems(&pBuffer[auiIndex], auiCount);
			MoveItems(&pNewBuffer[auiIndex], &pBuffer[auiIndex + auiCount], uiSize - auiCount);
			DeallocateBuffer();
			pBuffer = pNewBuffer;
			uiReservedSize = uiOptimalCapacity;
		}
		else {
			DestructItems(&pBuffer[auiIndex], auiCount);
			MoveItems(&pBuffer[auiIndex], &pBuffer[auiIndex + auiCount], uiSize - auiIndex - auiCount);
		}
		--uiSize;
	}
	else {
		Clear(abShrink);
	}
}

// GAME - 0x98F1F0
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::RemoveFast(uint32_t auiIndex, uint32_t auiCount) {
	uint32_t uiToMove = std::min(auiCount, uiSize - auiIndex - auiCount);
	DestructItems(&pBuffer[auiIndex], auiCount);
	MoveItems(&pBuffer[auiIndex], &pBuffer[uiSize - uiToMove], uiToMove);
	uiSize -= auiCount;
}

// GAME - 0x49F510
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::RemoveLast() {
	if (uiSize)	{
		DestructItems(&pBuffer[uiSize - 1], 1);
		--uiSize;
	}
}

// GAME - 0x719B20
template<typename T, uint32_t RESIZE_SIZE>
inline int32_t BSSimpleArray<T, RESIZE_SIZE>::Find(const T& aItem, uint32_t auiStartPosition, bool(__cdecl* apCompareFunc)(const T&, const T&)) const {
	while (auiStartPosition < uiSize) {
		if (pBuffer && apCompareFunc(pBuffer[auiStartPosition], aItem))
			return auiStartPosition;
		++auiStartPosition;
	}
	return -1;
}

// GAME - 0x9962F0
template<typename T, uint32_t RESIZE_SIZE>
inline bool BSSimpleArray<T, RESIZE_SIZE>::IsInArray(const T& aItem) const {
	return Find(aItem, 0, [](const T& left, const T& right) -> bool { return left == right; }) != -1;
}

// GAME - 0x6C8980
template<typename T, uint32_t RESIZE_SIZE>
inline void BSSimpleArray<T, RESIZE_SIZE>::QuickSort(_CoreCrtNonSecureSearchSortCompareFunction apCompareFunc) {
	std::qsort(pBuffer, uiSize, sizeof(T), apCompareFunc);
}