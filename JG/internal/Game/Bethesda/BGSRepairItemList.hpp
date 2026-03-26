#pragma once

#include "BaseFormComponent.hpp"

class BGSListForm;
class TESForm;

class BGSRepairItemList : public BaseFormComponent {
public:
	BGSRepairItemList();
	~BGSRepairItemList();

	BGSListForm* pRepairList;

	BGSListForm* GetRepairItemList() const;
	void SetRepairItemList(BGSListForm* apRepairList);

	bool HasRepairItem(TESForm* apForm) const;

	static BGSRepairItemList* GetFormAsRepairItemList(TESForm* apForm);

	static bool CanItemRepairForm(TESForm* apRepairItem, TESForm* apForm);
};

ASSERT_SIZE(BGSRepairItemList, 0x8);