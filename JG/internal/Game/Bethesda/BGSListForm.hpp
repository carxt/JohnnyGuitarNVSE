#pragma once

#include "TESForm.hpp"

class BGSListForm : public TESForm {
public:
	BGSListForm();
	~BGSListForm();

	BSSimpleList<TESForm*>	kList;
#ifdef GAME
	uint32_t				uiNumAddedObjects;
#endif

	BSSimpleList<TESForm*>* GetFormList();
	const BSSimpleList<TESForm*>* GetFormList() const;

	int32_t GetItemIndex(const TESForm* apForm) const;
};

#ifdef GAME
ASSERT_SIZE(BGSListForm, 0x24);
#else
ASSERT_SIZE(BGSListForm, 0x34);
#endif