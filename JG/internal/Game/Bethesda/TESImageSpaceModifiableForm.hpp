#pragma once

#include "BaseFormComponent.hpp"

class TESImageSpaceModifier;

class TESImageSpaceModifiableForm : public BaseFormComponent {
public:
	TESImageSpaceModifiableForm();
	~TESImageSpaceModifiableForm();

	TESImageSpaceModifier* pImageSpaceModifier;

	TESImageSpaceModifier* GetFormImageSpaceModifier() const;
	void SetFormImageSpaceModifier(TESImageSpaceModifier* apModifier);
};

ASSERT_SIZE(TESImageSpaceModifiableForm, 0x8);