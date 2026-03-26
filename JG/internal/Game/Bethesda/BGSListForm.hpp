#pragma once

#include "TESForm.hpp"

class BGSListForm : public TESForm {
public:
	BGSListForm();
	~BGSListForm();

	BSSimpleList<TESForm*>	kList;
	uint32_t				uiNumAddedObjects;

	TESFORM_TYPE(BGSListForm);

	BSSimpleList<TESForm*>* GetFormList();
	const BSSimpleList<TESForm*>* GetFormList() const;

	int32_t GetItemIndex(const TESForm* apForm) const;
};

ASSERT_SIZE(BGSListForm, 0x24);