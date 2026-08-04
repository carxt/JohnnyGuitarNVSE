#pragma once

#include "Gamebryo/NiAVObject.hpp"

NiSmartPointer(BSNodeReferences);

class BSNodeReferences : public NiObject {
public:
	BSNodeReferences();
	~BSNodeReferences();

	NiTPrimitiveArray<NiAVObject*> RefNodes;

	CREATE_OBJECT(BSNodeReferences, 0xC649F0);
	NIRTTI_ADDRESS(0x12043E4);
};

ASSERT_SIZE(BSNodeReferences, 0x18)