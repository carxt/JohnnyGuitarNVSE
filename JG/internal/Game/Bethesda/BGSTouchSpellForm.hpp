#pragma once

#include "BaseFormComponent.hpp"

class MagicItemForm;

class BGSTouchSpellForm : public BaseFormComponent {
public:
	BGSTouchSpellForm();
	~BGSTouchSpellForm();

	MagicItemForm*	pFormTouchSpell;
	uint16_t		usTouchSpellAnimation;

	MagicItemForm* GetFormTouchSpell() const;
	void SetFormTouchSpell(MagicItemForm* apSpell);

	uint16_t GetFormTouchSpellAnimation() const;
	void SetFormTouchSpellAnimation(uint16_t ausAnimation);
};

ASSERT_SIZE(BGSTouchSpellForm, 0xC);