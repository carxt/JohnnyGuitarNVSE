#include "TESRaceForm.hpp"
#include "TESRace.hpp"
#include <GameRTTI.h>

// GAME - 0x726070
TESRace* TESRaceForm::GetFormRace() const {
    return pRace;
}

// GAME - 0x6ECD40
void TESRaceForm::SetFormRace(TESRace* apRace) {
	pRace = apRace;
}

const char* TESRaceForm::GetFormRaceEditorID() const {
	return pRace ? pRace->GetFormEditorID() : "";
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

// GECK - 0x508290
const char* TESRaceForm::GetFormRaceEditorID(const TESForm* apForm) {
#ifdef GAME
	const TESRace* pRace = GetFormRace(apForm);
	return pRace ? pRace->GetFormEditorID() : "";
#else
	return CdeclCall<const char*>(0x508290, apForm);
#endif
}