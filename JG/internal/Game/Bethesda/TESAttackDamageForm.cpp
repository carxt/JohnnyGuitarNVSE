#include "TESAttackDamageForm.hpp"

// GAME - 0x47FF50
void TESAttackDamageForm::SetDamage(uint16_t ausDamage) {
	usAttackDamage = ausDamage;
}

// GAME - 0x47FEF0
uint16_t TESAttackDamageForm::GetAttackDamage(const TESForm* apForm) {
	return CdeclCall<uint16_t>(0x47FEF0, apForm);
}
