#pragma once

#include "BaseFormComponent.hpp"

class TESForm;

class TESHealthForm : public BaseFormComponent {
public:
	TESHealthForm();
	~TESHealthForm();

	virtual uint32_t GetFormHealth() const;

	uint32_t	uiHealth;

	void SetFormHealth(uint32_t auiHealth);

	static uint32_t GetFormHealth(const TESForm* apForm);

	static TESHealthForm* GetFormAsHealthForm(const TESForm* apForm);
};

ASSERT_SIZE(TESHealthForm, 0x8);