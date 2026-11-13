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

#ifdef GAME
	bool HasRepairItem(const TESForm* apForm) const;

	static BGSRepairItemList* GetFormAsRepairItemList(const TESForm* apForm);

	static bool CanItemRepairForm(const TESForm* apRepairItem, const TESForm* apForm);
#endif
};

ASSERT_SIZE(BGSRepairItemList, 0x8);