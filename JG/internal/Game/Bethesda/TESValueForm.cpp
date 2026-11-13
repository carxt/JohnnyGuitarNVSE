#include "TESValueForm.hpp"

// GAME - 0x726070
uint32_t TESValueForm::GetFormValue() const {
	return uiValue;
}

// GAME - 0x48E960
// GECK - 0x4EA630
void TESValueForm::SetFormValue(uint32_t auiValue) {
#ifdef GAME
	ThisCall(0x48E960, this, auiValue);
#else
	ThisCall(0x4EA630, this, auiValue);
#endif
}

// GAME - 0x48E8A0
// GECK - 0x50CF40
uint32_t TESValueForm::GetFormValue(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<uint32_t>(0x48E8A0, apForm);
#else
	return CdeclCall<uint32_t>(0x50CF40, apForm);
#endif
}
