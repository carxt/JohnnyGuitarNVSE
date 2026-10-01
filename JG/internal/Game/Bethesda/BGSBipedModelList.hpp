#pragma once

#include "BaseFormComponent.hpp"

class BGSListForm;
class TESForm;

class BGSBipedModelList : public BaseFormComponent {
public:
	BGSBipedModelList();
	~BGSBipedModelList();

	BGSListForm* pModelList;

	BGSListForm* GetBipedModelList() const;
	void SetBipedModelList(BGSListForm* apModelList);

	static BGSBipedModelList* GetFormAsBipedModelList(const TESForm* apForm);
};

ASSERT_SIZE(BGSBipedModelList, 0x8);