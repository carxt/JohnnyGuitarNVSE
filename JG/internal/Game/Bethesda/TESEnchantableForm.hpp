#pragma once

#include "BaseFormComponent.hpp"

class EnchantmentItem;
class TESForm;

class TESEnchantableForm : public BaseFormComponent {
public:
	TESEnchantableForm();
	~TESEnchantableForm();

	virtual uint32_t	GetCastingType() const;

	EnchantmentItem*	pEnchanting;
	uint16_t			usAnimation;
	uint32_t			eCastingType;

	static EnchantmentItem* GetFormEnchanting(TESForm* apForm);
};

ASSERT_SIZE(TESEnchantableForm, 0x10);