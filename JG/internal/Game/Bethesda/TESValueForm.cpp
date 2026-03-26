#include "TESValueForm.hpp"

// GAME - 0x726070
uint32_t TESValueForm::GetFormValue() const {
	return uiValue;
}

// GAME - 0x48E960
void TESValueForm::SetFormValue(uint32_t auiValue) {
	ThisCall(0x48E960, this, auiValue);
}

// GAME - 0x48E8A0
uint32_t TESValueForm::GetFormValue(TESForm* apForm) {
	return CdeclCall<uint32_t>(0x48E8A0, apForm);
}
