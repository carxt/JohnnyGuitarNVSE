#include "BGSTouchSpellForm.hpp"

// GAME - 0x726070
MagicItemForm* BGSTouchSpellForm::GetFormTouchSpell() const {
	return pFormTouchSpell;
}

// GAME - 0x6ECD40
void BGSTouchSpellForm::SetFormTouchSpell(MagicItemForm* apSpell) {
	pFormTouchSpell = apSpell;
}

// GAME - 0x4A8AE0
uint16_t BGSTouchSpellForm::GetFormTouchSpellAnimation() const {
	return usTouchSpellAnimation;
}

// GAME - 0x483170
void BGSTouchSpellForm::SetFormTouchSpellAnimation(uint16_t ausAnimation) {
	usTouchSpellAnimation = ausAnimation;
}
