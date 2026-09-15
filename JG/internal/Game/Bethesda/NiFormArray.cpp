#include "NiFormArray.hpp"

// GAME - 0x4D6170
// GECK - 0x52E9A0
TESForm* NiFormArray::GetFormAt(uint32_t auiIndex) const {
#ifdef GAME
	return ThisCall<TESForm*>(0x4D6170, this, auiIndex);
#else
	return ThisCall<TESForm*>(0x52E9A0, this, auiIndex);
#endif
}

// GAME - 0x61BC10
// GECK - 0x5945E0
void NiFormArray::InsertFormAt(uint32_t auiIndex, TESForm* apForm) {
#ifdef GAME
	ThisCall(0x61BC10, this, auiIndex, apForm);
#else
	ThisCall(0x5945E0, this, auiIndex, apForm);
#endif
}

// GAME - 0x4D6100
// GECK - 0x52E960
uint32_t NiFormArray::GetIndexForForm(const TESForm* apForm) const {
#ifdef GAME
	return ThisCall<uint32_t>(0x4D6100, this, apForm);
#else
	return ThisCall<uint32_t>(0x52E960, this, apForm);
#endif
}
