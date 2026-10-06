#include "TESEnchantableForm.hpp"
#include "EnchantmentItem.hpp"

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

const char* TESEnchantableForm::GetFormEnchantingEditorID() const {
	return pEnchanting ? pEnchanting->GetFormEditorID() : "";
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

// GECK - 0x4F70F0
const char* TESEnchantableForm::GetFormEnchantingEditorID(const TESForm* apForm) {
#ifdef GAME
	const EnchantmentItem* pEnchanting = GetFormEnchanting(apForm);
	return pEnchanting ? pEnchanting->GetFormEditorID() : "";
#else
	return CdeclCall<const char*>(0x4F70F0, apForm);
#endif
}
