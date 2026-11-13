#pragma once

#include "BSMemObject.hpp"
#include "Gamebryo/NiSmartPointer.hpp"

class NiAVObject;

NiSmartPointer(BSCloneReserver);

class SPEC_EMPTY_BASES BSCloneReserver : public BSMemObject {
public:
	BSCloneReserver(NiAVObject* apObject, uint32_t auiCount);
	~BSCloneReserver();

	NiAVObject*	pModel;
	uint32_t	uiCloneCount;
	uint32_t	uiRefCount;

	void MakeClones();
	void KillClones();

	void IncRefCount();
	void DecRefCount();
};

ASSERT_SIZE(BSCloneReserver, 0xC);