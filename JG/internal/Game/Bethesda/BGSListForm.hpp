#pragma once

#include "TESForm.hpp"

class BGSListForm : public TESForm {
public:
	BGSListForm();
	~BGSListForm();

	BSSimpleList<TESForm*>	kList;
	uint32_t				uiNumAddedObjects;

	BSSimpleList<TESForm*>* GetFormList();
	const BSSimpleList<TESForm*>* GetFormList() const;

	int32_t GetItemIndex(const TESForm* apForm) const;
};

ASSERT_SIZE(BGSListForm, 0x24);