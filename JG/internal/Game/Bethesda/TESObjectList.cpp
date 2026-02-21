#include "TESObjectList.hpp"
#include "TESObject.hpp"

static uint32_t uiLastIndex = 0;
static TESObject* pLastObject = nullptr;

inline uint32_t TESObjectList::GetSize() const {
	return uiCount;
}

inline TESObject* TESObjectList::GetHead() const {
	return pHead;
}

inline TESObject* TESObjectList::GetTail() const {
	return pTail;
}

TESObject* TESObjectList::GetAt(uint32_t auiIndex) const {
	if (auiIndex == uiLastIndex && pLastObject)
		return pLastObject;

	if (auiIndex >= GetSize())
		return nullptr;

	TESObject* pCurrent = GetHead();
	for (uint32_t i = 0; i < auiIndex; i++)
		pCurrent = pCurrent->GetNext();

	uiLastIndex = auiIndex;
	pLastObject = pCurrent;
	return pCurrent;
}