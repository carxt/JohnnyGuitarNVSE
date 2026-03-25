#pragma once

#include "ItemChange.hpp"
#include "ContainerObject.hpp"

class InventoryIterator {
public:
	InventoryIterator();
	~InventoryIterator();

	ItemChange						kTempItemChange;
	BSSimpleList<ContainerObject*>* pContainerObjects;
	BSSimpleList<ItemChange*>*		pItemChanges;
	bool							bFinished;

	void Reset();
};

ASSERT_SIZE(InventoryIterator, 0x18);