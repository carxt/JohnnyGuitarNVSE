#include "TESRaceForm.hpp"
#include <GameRTTI.h>

// GAME - 0x726070
TESRace* TESRaceForm::GetFormRace() const {
    return pRace;
}

// GAME - 0x6ECD40
void TESRaceForm::SetFormRace(TESRace* apRace) {
	pRace = apRace;
}

// GAME - 0x617270
TESRace* TESRaceForm::GetFormRace(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<TESRace*>(0x617270, apForm);
#else
	TESRaceForm* pRaceForm = DYNAMIC_CAST(apForm, TESForm, TESRaceForm);
	if (pRaceForm)
		return pRaceForm->GetFormRace();
	return nullptr;
#endif
}
