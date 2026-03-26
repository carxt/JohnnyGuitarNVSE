#pragma once

#include "BaseFormComponent.hpp"

class TESForm;

class TESAttackDamageForm : public BaseFormComponent {
public:
	TESAttackDamageForm();
	~TESAttackDamageForm();

	virtual uint16_t	GetAttackDamage() const;

	uint16_t	usAttackDamage;

	void SetDamage(uint16_t ausDamage);

	static uint16_t GetAttackDamage(const TESForm* apForm);
};

ASSERT_SIZE(TESAttackDamageForm, 0x8);