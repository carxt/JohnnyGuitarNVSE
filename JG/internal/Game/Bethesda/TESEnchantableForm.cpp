#include "TESEnchantableForm.hpp"

// GAME - 0x726070
EnchantmentItem* TESEnchantableForm::GetFormEnchanting() const {
	return pEnchanting;
}

// GAME - 0x6ECD40
void TESEnchantableForm::SetFormEnchanting(EnchantmentItem* apItem) {
	pEnchanting = apItem;
}

// GAME - 0x4A8AE0
uint16_t TESEnchantableForm::GetFormEnchantmentAmount() const {
	return usEnchantmentAmount;
}

// GAME - 0x483170
void TESEnchantableForm::SetFormEnchantmentAmount(uint16_t ausAmount) {
	usEnchantmentAmount = ausAmount;
}

// GAME - 0x41FD00
void TESEnchantableForm::SetCastingType(MagicSystem::CastingType aeType) {
	eCastingType = aeType;
}

// GAME - 0x4BE330
// GECK - 0x437440
EnchantmentItem* TESEnchantableForm::GetFormEnchanting(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<EnchantmentItem*>(0x4BE330, apForm);
#else
	return CdeclCall<EnchantmentItem*>(0x437440, apForm);
#endif
}