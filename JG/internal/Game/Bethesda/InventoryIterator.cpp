#include "InventoryIterator.hpp"

// GAME - 0x527270
InventoryIterator::InventoryIterator() : pContainerObjects(nullptr), pItemChanges(nullptr), bFinished(false) {
}

// GAME - 0x5272B0
InventoryIterator::~InventoryIterator() {
	kTempItemChange.pExtraLists = nullptr;
}

// GAME - 0x527740
void InventoryIterator::Reset() {
	pContainerObjects = 0;
	pItemChanges = 0;
	bFinished = 0;
}
