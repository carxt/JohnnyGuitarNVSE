#pragma once

#include "BaseFormComponent.hpp"

class TESForm;

class TESHealthForm : public BaseFormComponent {
public:
	TESHealthForm();
	~TESHealthForm();

	virtual uint32_t GetFormHealth() const;

	uint32_t	uiHealth;

	static uint32_t GetFormHealth(TESForm* apForm);

	static TESHealthForm* GetFormAsHealthForm(TESForm* apForm);
};

ASSERT_SIZE(TESHealthForm, 0x8);