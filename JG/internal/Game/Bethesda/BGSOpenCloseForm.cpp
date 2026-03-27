#include "BGSOpenCloseForm.hpp"

#ifdef GAME
// GAME - 0x47A3A0
BGSOpenCloseForm* BGSOpenCloseForm::GetAsOpenCloseForm(const TESForm* apForm) {
	return CdeclCall<BGSOpenCloseForm*>(0x47A3A0, apForm);
}

// GAME - 0x47A490
bool BGSOpenCloseForm::IsOpenCloseForm(const TESForm* apForm) {
	return CdeclCall<bool>(0x47A490, apForm);
}

// GAME - 0x47A560
void BGSOpenCloseForm::HandleActivate(TESObjectREFR* apItemActivated, TESObjectREFR* apActionRef, BGSOpenCloseForm* apDoor) {
	CdeclCall(0x47A560, apItemActivated, apActionRef, apDoor);
}

// GAME - 0x47B250
BGSOpenCloseForm::OpenCloseState BGSOpenCloseForm::GetOpenState(TESObjectREFR* apRef) {
	return CdeclCall<BGSOpenCloseForm::OpenCloseState>(0x47B250, apRef);
}

// GAME - 0x47AEC0
bool BGSOpenCloseForm::SetOpenState(TESObjectREFR* apRef, bool abOpen, bool abSnap) {
	return CdeclCall<bool>(0x47AEC0, apRef, abOpen, abSnap);
}
#endif