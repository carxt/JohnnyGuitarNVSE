#include "NiFormArray.hpp"

// GAME - 0x4D6170
TESForm* NiFormArray::GetFormAt(uint32_t auiIndex) const {
	return ThisCall<TESForm*>(0x4D6170, this, auiIndex);
}

// GAME - 0x61BC10
void NiFormArray::InsertFormAt(uint32_t auiIndex, TESForm* apForm) {
	ThisCall(0x61BC10, this, auiIndex, apForm);
}

// GAME - 0x4D6100
uint32_t NiFormArray::GetIndexForForm(const TESForm* apForm) const {
	return ThisCall<uint32_t>(0x4D6100, this, apForm);
}
