#pragma once

#include "TESObject.hpp"

class TESObjectCELL;

class TESObjectList {
public:
	uint32_t		uiCount;
	TESObject*		pHead;
	TESObject*		pTail;
	TESObjectCELL*	pOwner;

	inline uint32_t		GetSize() const;
	inline TESObject*	GetHead() const;
	inline TESObject*	GetTail() const;

	TESObject* GetAt(uint32_t auiIndex) const;

	template <typename Function>
	void ForEach(Function&& fn) const {
		TESObject* pCurrent = GetHead();
		while (pCurrent) {
			fn(pCurrent);
			pCurrent = pCurrent->GetNext();
		}
	}
};

ASSERT_SIZE(TESObjectList, 0x10);