#include "ItemChange.hpp"

// GAME - 0x76B630
ItemChange::ItemChange() {
	ThisCall(0x76B630, this);
}

// GAME - 0x4BC650
ItemChange::ItemChange(const ItemChange& arOther) {
	ThisCall(0x4BC650, this, &arOther);
}

// GAME - 0x4BC550
ItemChange::ItemChange(TESBoundObject* apObject, int32_t aiNumber) {
	ThisCall(0x4BC550, this, apObject, aiNumber);
}

// GAME - 0x4BC5F0
ItemChange::~ItemChange() {
	ThisCall(0x4BC5F0, this);
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

// GAME - 0x4BD820
uint8_t ItemChange::GetModSlots() const {
	return ThisCall<uint8_t>(0x4BD820, this);
}
