#pragma once

#include "BaseFormComponent.hpp"

class TESForm;

class TESValueForm : public BaseFormComponent {
public:
	TESValueForm();
	virtual ~TESValueForm();

	virtual uint32_t	GetSaveSize(uint32_t auiChangeFlags) const;
	virtual void		SaveGameTES(uint32_t auiChangeFlags);
	virtual void		LoadGameTES(uint32_t auiChangeFlags, uint32_t);

	uint32_t	uiValue;

	uint32_t GetFormValue() const;
	void SetFormValue(uint32_t auiValue);

	static uint32_t GetFormValue(TESForm* apForm);
};

ASSERT_SIZE(TESValueForm, 0x8);