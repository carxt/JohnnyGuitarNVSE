#pragma once

#include "BaseFormComponent.hpp"

class EnchantmentItem;

class TESEnchantableForm : public BaseFormComponent {
public:
	TESEnchantableForm();
	~TESEnchantableForm();

	virtual uint32_t	GetCastingType() const;

	EnchantmentItem*	pEnchanting;
	uint16_t			usAnimation;
	uint32_t			eCastingType;
};

ASSERT_SIZE(TESEnchantableForm, 0x10);