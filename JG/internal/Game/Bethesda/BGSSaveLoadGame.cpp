#include "BGSSaveLoadGame.hpp"

BGSSaveLoadGame* BGSSaveLoadGame::GetSingleton() {
    return *reinterpret_cast<BGSSaveLoadGame**>(0x11DDF38);
}

// GAME - 0x570F40
bool BGSSaveLoadGame::GetGlobalAllowChanges() const {
	return uiGlobalFlags.bGlobalBlockChanges == false;
}

// GAME - 0x42CE10
bool BGSSaveLoadGame::GetSaveGameLoading() const {
	return uiGlobalFlags.bSaveGameLoading;
}

// GAME - 0x5621D0
bool BGSSaveLoadGame::GetSaveGameSaving() const {
	return uiGlobalFlags.bSaveGameSaving;
}

// GAME - 0x444D20
bool BGSSaveLoadGame::GetInitingForms() const {
	return uiGlobalFlags.bInitingForms;
}

// GAME - 0x546950
bool BGSSaveLoadGame::GetDeferInitForms() const {
	return uiGlobalFlags.bDeferInitForms;
}

// GAME - 0x452E90
bool BGSSaveLoadGame::GetPositioningPlayerCharacter() const {
	return uiGlobalFlags.bPositioningPlayer;
}

// GAME - 0x63EF00
bool BGSSaveLoadGame::GetPlayerLocationInvalid() const {
	return uiGlobalFlags.bPlayerLocationInvalid;
}

// GAME - 0x848CF0
bool BGSSaveLoadGame::GetSaveLoadFailed() const {
	return uiGlobalFlags.bSaveLoadFailed;
}

// GAME - 0x462480
bool BGSSaveLoadGame::GetThreadAllowChanges() {
	return ThisCall<bool>(0x462480, this);
}

bool BGSSaveLoadGame::SetThreadAllowChanges(bool abEnable) {
	return ThisCall<bool>(0x4623F0, this, abEnable);
}

// GAME - 0x469570
bool BGSSaveLoadGame::GetLoadingMovedRefs() {
	return ThisCall<bool>(0x469570, this);
}

// GAME - 0x4121B0
bool BGSSaveLoadGame::GetReconstructingForms() {
	return ThisCall<bool>(0x4121B0, this);
}

#if ESL_SUPPORT || OVERLAY_SUPPORT
TESFile* BGSSaveLoadGame::GetSaveMod(uint8_t aucIndex) const {
	if (aucIndex >= kFiles.GetSize())
		return nullptr;

	return kFiles.GetAt(aucIndex);
}

#if ESL_SUPPORT
TESFile* BGSSaveLoadGame::GetSmallSaveMod(uint16_t ausIndex) const {
	if (ausIndex >= kSmallFiles.GetSize())
		return nullptr;

	return kSmallFiles.GetAt(ausIndex);
}

bool BGSSaveLoadGame::SupportsSmallPlugins() const {
	return ucCurrentMinorVersion >= 28;
}
#endif

#else
// GAME - 0x846DE0
uint8_t BGSSaveLoadGame::GetSaveMod(uint8_t aucIndex) const {
	return ucSaveMods[aucIndex];
}
#endif

// GAME - 0x8492B0
void BGSSaveLoadGame::InitForms(bool abLowPriority) {
    ThisCall(0x8492B0, this, abLowPriority);
}

void BGSSaveLoadGame::LoadCell(TESObjectCELL* apCell) {
    ThisCall(0x849B10, this, apCell);
}
