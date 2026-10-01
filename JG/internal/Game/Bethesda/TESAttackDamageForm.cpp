#include "TESAttackDamageForm.hpp"

// GAME - 0x47FF50
// GECK - 0x4F11E0
void TESAttackDamageForm::SetAttackDamage(uint16_t ausDamage) {
	usAttackDamage = ausDamage;
}

// GAME - 0x47FEF0
// GECK - 0x4F11A0
uint16_t TESAttackDamageForm::GetAttackDamage(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<uint16_t>(0x47FEF0, apForm);
#else
	return CdeclCall<uint16_t>(0x4F11A0, apForm);
#endif
}
