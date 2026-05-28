#include "TESEnchantableForm.hpp"

// GAME - 0x4BE330
EnchantmentItem* TESEnchantableForm::GetFormEnchanting(TESForm* apForm) {
	return CdeclCall<EnchantmentItem*>(0x4BE330, apForm);
}