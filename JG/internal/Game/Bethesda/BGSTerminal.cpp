#include "BGSTerminal.hpp"

// GAME - 0x461150
BSSimpleList<TERMINAL_MENU_ITEM*>* BGSTerminal::GetMenuItemList() {
	return &kMenuItems;
}

// GAME - 0x461150
const BSSimpleList<TERMINAL_MENU_ITEM*>* BGSTerminal::GetMenuItemList() const {
	return &kMenuItems;
}

// GAME - 0x501170
void BGSTerminal::AddMenuItem(TERMINAL_MENU_ITEM* apItem) {
#ifdef GAME
	ThisCall(0x501170, this, apItem);
#else
	if (apItem) {
		kMenuItems.AddTail(apItem);
		apItem->kConditions.RegisterForm(this);
	}
#endif
}

// GECK - 0x5DDEA0
void BGSTerminal::RemoveMenuItem(TERMINAL_MENU_ITEM* apItem) {
#ifdef GAME
	kMenuItems.Remove(apItem);
	if (apItem)
		ThisCall(0x5010C0, apItem, 1); // Destructor
#else
	ThisCall(0x5DDEA0, this, apItem);
#endif
}

// GAME - 0x501050
// GECK - 0x5DE670
void BGSTerminal::ClearMenuItemList() {
#ifdef GAME
	ThisCall(0x501050, this);
#else
	ThisCall(0x5DE670, this);
#endif
}

// GAME - 0x4FD400
BGSNote* BGSTerminal::GetPassword() const {
	return pPassword;
}

// GAME - 0x500A20
void BGSTerminal::SetPassword(BGSNote* apPassword) {
	pPassword = apPassword;
}

#ifdef GAME
// GAME - 0x501A30
LOCK_LEVEL BGSTerminal::GetRawDifficulty(const TESObjectREFR* apRef) const {
	return ThisCall<LOCK_LEVEL>(0x501A30, this, apRef);
}

// GAME - 0x501A80
void BGSTerminal::SetRawDifficulty(TESObjectREFR* apRef, LOCK_LEVEL aeLevel) {
	ThisCall(0x501A80, this, apRef, aeLevel);
}
#endif

// GAME - 0x501250
bool BGSTerminal::IsLeveled() const {
	return kData.ucFlags.bLeveled;
}

void BGSTerminal::SetLeveled(bool abVal) {
	kData.ucFlags.bLeveled = abVal;
}

// GAME - 0x5015D0
bool BGSTerminal::IsUnlocked() const {
	return kData.ucFlags.bUnlocked;
}

#ifdef GAME
// GAME - 0x501AE0
bool BGSTerminal::IsUnlocked(const TESObjectREFR* apRef) const {
	return ThisCall<bool>(0x501AE0, this, apRef);
}

// GAME - 0x501B40
void BGSTerminal::SetUnlocked(TESObjectREFR* apRef) {
	ThisCall(0x501B40, this, apRef);
}
#endif

// GAME - 0x757E80
bool BGSTerminal::UsesAltColor() const {
	return kData.ucFlags.bAltColors;
}

void BGSTerminal::SetUsesAltColor(bool abVal) {
	kData.ucFlags.bAltColors = abVal;
}

// GAME - 0x759540
bool BGSTerminal::HidesWelcomeTextWhenDisplayingImage() const {
	return kData.ucFlags.bHideWelcome;
}

void BGSTerminal::SetHidesWelcomeTextWhenDisplayingImage(bool abVal) {
	kData.ucFlags.bHideWelcome = abVal;
}

#ifdef GAME
// GAME - 0x758FE0
const char* BGSTerminal::GetServerText() const {
	return ThisCall<const char*>(0x758FE0, this);
}

// GAME - 0x5011A0
LOCK_LEVEL BGSTerminal::GetHackDifficultyLockLevel(const TESObjectREFR* apRef) const {
    return ThisCall<LOCK_LEVEL>(0x5011A0, this, apRef);
}

// GAME - 0x501270
uint32_t BGSTerminal::GetHackMiniGameValue(const TESObjectREFR* apRef) const {
	return ThisCall<uint32_t>(0x501270, this, apRef);
}

// GAME - 0x5017A0
float BGSTerminal::GetMinSkillRequiredToHack(const TESObjectREFR* apRef) const {
	return ThisCall<float>(0x5017A0, this, apRef);
}

// GAME - 0x501760
bool BGSTerminal::IsHackEligible(const TESObjectREFR* apRef, float afSkill) const {
	return ThisCall<bool>(0x501760, this, apRef, afSkill);
}

// GAME - 0x501870
bool BGSTerminal::IsHacked(const TESObjectREFR* apRef) {
	return CdeclCall<bool>(0x501870, apRef);
}

// GAME - 0x5018B0
void BGSTerminal::SetHacked(TESObjectREFR* apRef, bool abVal) {
	CdeclCall(0x5018B0, apRef, abVal);
}

// GAME - 0x501990
bool BGSTerminal::IsLockedOut(const TESObjectREFR* apRef) {
	return CdeclCall<bool>(0x501990, apRef);
}

// GAME - 0x501930
void BGSTerminal::LockOut(TESObjectREFR* apRef, bool abVal) {
	CdeclCall(0x501930, apRef, abVal);
}

// GAME - 0x5012C0
bool BGSTerminal::IsTerminalRefInUse(const TESObjectREFR* apRef) {
	return CdeclCall<bool>(0x5012C0, apRef);
}

// GAME - 0x501A10
void BGSTerminal::ResetState(TESObjectREFR* apRef) {
	CdeclCall(0x501A10, apRef);
}
#endif

// GAME - 0x758350
bool TERMINAL_MENU_ITEM::IsAutoAdd() const {
	return pDisplayNote && ucFlags.bAddNote;
}

void TERMINAL_MENU_ITEM::SetAutoAdd(bool abVal) {
	ucFlags.bAddNote = abVal;
}

// GAME - 0x758390
bool TERMINAL_MENU_ITEM::ForcesRedraw() const {
	return ucFlags.bForceRedraw;
}

void TERMINAL_MENU_ITEM::SetForcesRedraw(bool abVal) {
	ucFlags.bForceRedraw = abVal;
}

// GAME - 0x758A60
bool TERMINAL_MENU_ITEM::IsSelected() const {
	return ucFlags.bSelected;
}

// GAME - 0x7583B0
void TERMINAL_MENU_ITEM::SetSelected(bool abVal) {
	ucFlags.bSelected = abVal;
}

#ifdef GAME
// GAME - 0x501830
bool TERMINAL_MENU_ITEM::RunResultScript(TESObjectREFR* apActivator) {
	return ThisCall<bool>(0x501830, this, apActivator);
}
#endif