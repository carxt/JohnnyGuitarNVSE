#pragma once

#include "BaseFormComponent.hpp"
#include "MagicSystem.hpp"

class EnchantmentItem;
class TESForm;

class TESEnchantableForm : public BaseFormComponent {
public:
	TESEnchantableForm();
	~TESEnchantableForm();

	virtual MagicSystem::CastingType	GetCastingType() const;

	EnchantmentItem*			pEnchanting;
	uint16_t					usEnchantmentAmount;
	MagicSystem::CastingType	eCastingType;

	EnchantmentItem* GetFormEnchanting() const;
	void SetFormEnchanting(EnchantmentItem* apItem);

	uint16_t GetFormEnchantmentAmount() const;
	void SetFormEnchantmentAmount(uint16_t ausAmount);

	void SetCastingType(MagicSystem::CastingType aeType);

	const char* GetFormEnchantingEditorID() const;

	static EnchantmentItem* GetFormEnchanting(const TESForm* apForm);
	static const char* GetFormEnchantingEditorID(const TESForm* apForm);
};

ASSERT_SIZE(TESEnchantableForm, 0x10);