#include "ItemChange.hpp"

// GAME - 0x76B630
ItemChange::ItemChange() : pObject(nullptr), pExtraLists(nullptr), iNumber(0) {
}

// GAME - 0x4BC550
ItemChange::ItemChange(TESBoundObject* apObject, int32_t aiNumber) {
	pObject = apObject;
	pExtraLists = new BSSimpleList<ExtraDataList*>();
	iNumber = aiNumber;
}

// GAME - 0x4BC5F0
ItemChange::~ItemChange() {
	delete pExtraLists;
	pExtraLists = nullptr;
}

// GAME - 0x559450
BSSimpleList<ExtraDataList*>* ItemChange::GetExtraDataList() const {
	return pExtraLists;
}

// GAME - 0x4BC780
void ItemChange::DeleteAllExtra() {
	ThisCall(0x4BC780, this);
}

bool ItemChange::HasLeveledExtra() const {
	return ThisCall<bool>(0x4BCB70, this);
}

// GAME - 0x4BCDB0
float ItemChange::GetItemHealth(bool abPercentage) const {
	return ThisCall<float>(0x4BCDB0, this, abPercentage);
}

// GAME - 0x4BDDD0
bool ItemChange::GetWorn(bool abLeftOnly) const {
	return ThisCall<bool>(0x4BDDD0, this, abLeftOnly);
}