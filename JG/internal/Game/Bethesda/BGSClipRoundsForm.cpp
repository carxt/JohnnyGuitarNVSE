#include "BGSClipRoundsForm.hpp"
#include <GameRTTI.h>

// GAME - 0x401170
uint32_t BGSClipRoundsForm::GetFormClipRounds() const {
	return ucClipRounds;
}

// GAME - 0x4F15A0
void BGSClipRoundsForm::SetFormClipRounds(uint32_t auiClipRounds) {
	ucClipRounds = auiClipRounds;
}

// GECK - 0x4E3930
uint32_t BGSClipRoundsForm::GetFormClipRounds(const TESForm* apForm) {
#ifdef GAME
	BGSClipRoundsForm* pClipRounds = DYNAMIC_CAST(apForm, TESForm, BGSClipRoundsForm);
	if (pClipRounds)
		return pClipRounds->GetFormClipRounds();
	return 0;
#else
	return CdeclCall<uint32_t>(0x4E3930, apForm);
#endif
}
