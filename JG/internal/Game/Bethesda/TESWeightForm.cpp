#include "TESWeightForm.hpp"

// GAME - 0x6B9130
float TESWeightForm::GetFormWeight() const {
	return fWeight;
}

// GAME - 0x4F5D90
void TESWeightForm::SetFormWeight(float afWeight) {
	fWeight = afWeight;
}

// GAME - 0x48EBC0
// GECK - 0x50D260
float TESWeightForm::GetFormWeight(TESForm* apForm, bool abHardcore) {
#ifdef GAME
	return CdeclCall<float>(0x48EBC0, apForm, abHardcore);
#else
	return CdeclCall<float>(0x50D260, apForm, abHardcore);
#endif
}
