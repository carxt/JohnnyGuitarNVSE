#include "BGSOpenCloseForm.hpp"

// GAME - 0x47A3A0
// GECK - 0x4E7BD0
BGSOpenCloseForm* BGSOpenCloseForm::GetAsOpenCloseForm(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<BGSOpenCloseForm*>(0x47A3A0, apForm);
#else
	return CdeclCall<BGSOpenCloseForm*>(0x4E7BD0, apForm);
#endif
}

// GAME - 0x47A490
// GECK - 0x4E7B50
bool BGSOpenCloseForm::IsOpenCloseForm(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<bool>(0x47A490, apForm);
#else
	return CdeclCall<bool>(0x4E7B50, apForm);
#endif
}

#ifdef GAME
// GAME - 0x47A560
void BGSOpenCloseForm::HandleActivate(TESObjectREFR* apItemActivated, TESObjectREFR* apActionRef, BGSOpenCloseForm* apDoor) {
	CdeclCall(0x47A560, apItemActivated, apActionRef, apDoor);
}

// GAME - 0x47B250
BGSOpenCloseForm::OpenCloseState BGSOpenCloseForm::GetOpenState(TESObjectREFR* apRef) {
	return CdeclCall<BGSOpenCloseForm::OpenCloseState>(0x47B250, apRef);
}
#endif

// GAME - 0x47AEC0
// GECK - 0x4E7D50
bool BGSOpenCloseForm::SetOpenState(TESObjectREFR* apRef, bool abOpen, bool abSnap) {
#ifdef GAME
	return CdeclCall<bool>(0x47AEC0, apRef, abOpen, abSnap);
#else
	return CdeclCall<bool>(0x4E7D50, apRef, abOpen, abSnap);
#endif
}