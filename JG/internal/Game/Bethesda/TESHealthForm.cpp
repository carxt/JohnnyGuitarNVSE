#include "TESHealthForm.hpp"

// GAME - 0x4873D0
// GECK - 0x4FE6E0
uint32_t TESHealthForm::GetFormHealth(TESForm* apForm) {
#ifdef GAME
	return CdeclCall<uint32_t>(0x4873D0, apForm);
#else
	return CdeclCall<uint32_t>(0x4FE6E0, apForm);
#endif
}

// GAME - 0x4872E0
// GECK - 0x4FE680
TESHealthForm* TESHealthForm::GetFormAsHealthForm(TESForm* apForm) {
#ifdef GAME
	return CdeclCall<TESHealthForm*>(0x4872E0, apForm);
#else
	return CdeclCall<TESHealthForm*>(0x4FE680, apForm);
#endif
}
