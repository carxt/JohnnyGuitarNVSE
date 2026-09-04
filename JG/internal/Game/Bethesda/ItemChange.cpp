#include "ItemChange.hpp"

// GAME - 0x76B630
ItemChange::ItemChange() {
#ifdef GAME
	ThisCall(0x76B630, this);
#else
	pObject = nullptr;
	pExtraLists = nullptr;
	iNumber = 0;
#endif
}

#ifdef GAME
// GAME - 0x4BC650
ItemChange::ItemChange(const ItemChange& arOther) {
	ThisCall(0x4BC650, this, &arOther);
}
#endif

// GAME - 0x4BC550
// GECK - 0x529F60
ItemChange::ItemChange(TESBoundObject* apObject, int32_t aiNumber) {
#ifdef GAME
	ThisCall(0x4BC550, this, apObject, aiNumber);
#else
	ThisCall(0x529F60, this, apObject, aiNumber);
#endif
}

// GAME - 0x4BC5F0
// GECK - 0x52A6D0
ItemChange::~ItemChange() {
#ifdef GAME
	ThisCall(0x4BC5F0, this);
#else
	ThisCall(0x52A6D0, this);
#endif
}

// GAME - 0x559450
BSSimpleList<ExtraDataList*>* ItemChange::GetExtraDataList() const {
	return pExtraLists;
}

// GAME - 0x4BC780
// GECK - 0x52A700
void ItemChange::DeleteAllExtra() {
#ifdef GAME
	ThisCall(0x4BC780, this);
#else
	ThisCall(0x52A700, this);
#endif
}

// GAME - 0x4BCB70
// GECK - 0x5CA000 (stub)
bool ItemChange::HasLeveledExtra() const {
#ifdef GAME
	return ThisCall<bool>(0x4BCB70, this);
#else
	return true;
#endif
}

#ifdef GAME
// GAME - 0x4BCDB0
float ItemChange::GetItemHealth(bool abPercentage) const {
	return ThisCall<float>(0x4BCDB0, this, abPercentage);
}
#endif

// GAME - 0x4BDDD0
// GECK - 0x52A130
bool ItemChange::GetWorn(bool abLeftOnly) const {
#ifdef GAME
	return ThisCall<bool>(0x4BDDD0, this, abLeftOnly);
#else
	return ThisCall<bool>(0x52A130, this, abLeftOnly);
#endif
}

#ifdef GAME
// GAME - 0x4BD820
uint8_t ItemChange::GetModSlots() const {
	return ThisCall<uint8_t>(0x4BD820, this);
}
#endif

// GAME - 0x4BDA70
// GECK - 0x52A080
bool ItemChange::HasModEffectActive(uint8_t aeEffect) const {
#ifdef GAME
	return ThisCall<bool>(0x4BDA70, this, aeEffect);
#else
	return ThisCall<bool>(0x52A080, this, aeEffect);
#endif
}
