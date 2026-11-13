#pragma once

#include "Bethesda/BSExtraData.hpp"

class TESConditionItem;

class DialogExtraCurrCondItem : public BSExtraData {
public:
	TESConditionItem* pItem;

	BSEXTRA_TYPE(DialogExtraCurrCondItem);
};