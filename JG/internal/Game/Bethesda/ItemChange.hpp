#pragma once

#include "BSSimpleList.hpp"

class Actor;
class TESBoundObject;
class ExtraDataList;

class ItemChange {
public:
	ItemChange();
	ItemChange(const ItemChange& arOther);
	ItemChange(TESBoundObject* apObject, int32_t aiNumber);
	~ItemChange();

	BSSimpleList<ExtraDataList*>*	pExtraLists;
	int32_t							iNumber;
	TESBoundObject*					pObject;

	BSSimpleList<ExtraDataList*>*	GetExtraDataList() const;

	void							DeleteAllExtra();

	bool							HasLeveledExtra() const;

	float							GetItemHealth(bool abPercentage) const;

	bool							GetWorn(bool abLeftOnly) const;

	uint8_t							GetModSlots() const;
};

ASSERT_SIZE(ItemChange, 0xC);