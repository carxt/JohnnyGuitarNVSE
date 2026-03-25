#pragma once

#include "BSExtraData.hpp"
#include "ExtraDataList.hpp"
#include "TESForm.hpp"
#include "InventoryChanges.hpp"

class TESObjectREFR;

class ExtraContainerChanges : public BSExtraData {
public:
	ExtraContainerChanges();
	~ExtraContainerChanges();

	InventoryChanges* pChanges;

	BSEXTRA_TYPE(ExtraContainerChanges);
};

ASSERT_SIZE(ExtraContainerChanges, 0x10);