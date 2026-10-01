#include "Interface.hpp"

// GAME - 0x702360
bool Interface::IsInMenuMode() {
	return CdeclCall<bool>(0x702360);
}

// GAME - 0x7178A0
bool Interface::IsPipBoyMenuOpen() {
	return CdeclCall<bool>(0x7178A0);
}

// GAME - 0x709BC0
bool Interface::IsPipBoyOpening() {
	return CdeclCall<bool>(0x709BC0);
}

// GAME - 0x709C00
bool Interface::IsPipBoyOpened() {
	return CdeclCall<bool>(0x709C00);
}

// GAME - 0x705A00
bool Interface::IsInPipBoy() {
	return CdeclCall<bool>(0x705A00);
}

// GAME - 0x7079B0
bool Interface::IsInRenderedMenu() {
	return CdeclCall<bool>(0x7079B0);
}

// GAME - 0x7050D0
bool Interface::IsInDialog() {
	return CdeclCall<bool>(0x7050D0);
}

// GAME - 0x702680
bool Interface::IsMenuIDVisible(Menus aeMenu, uint32_t auiFlags) {
	return CdeclCall<bool>(0x702680, aeMenu, auiFlags);
}

// GAME - 0x702FC0
bool Interface::IsDebugTextVisible() {
	return CdeclCall<bool>(0x702FC0);
}

// GAME - 0x703D50
bool Interface::IsConsoleVisible() {
	return CdeclCall<bool>(0x703D50);
}

// GAME - 0x705E80
bool Interface::IsLoadingMenuVisible() {
	return CdeclCall<bool>(0x705E80);
}

// GAME - 0x702450
bool Interface::IsTopMenuID(Menus aeMenu) {
	return CdeclCall<bool>(0x702450, aeMenu);
}

// GAME - 0x7023C0
Interface::Menus Interface::GetTopMenuID() {
	return CdeclCall<Menus>(0x7023C0);
}

// GAME - 0x703350
TESObjectREFR* Interface::GetActivateTarget() {
	return CdeclCall<TESObjectREFR*>(0x703350);
}

// GAME - 0x7624D0
TESObjectREFR* Interface::GetDialogueTarget() {
	return CdeclCall<TESObjectREFR*>(0x7624D0);
}

// GAME - 0x707AD0
FORenderedMenu* Interface::GetCurrentRenderedMenu() {
	return CdeclCall<FORenderedMenu*>(0x707AD0);
}

// GAME - 0x705990
FOPipboyManager* Interface::GetPipboy() {
	return CdeclCall<FOPipboyManager*>(0x705990);
}

// GAME - 0x705910
FOVATSEffectManager* Interface::GetVATSEffect() {
	return CdeclCall<FOVATSEffectManager*>(0x705910);
}

// GAME - 0x709C20
void Interface::InitGunScope(TESModel* apModel) {
	CdeclCall(0x709C20, apModel);
}

// GAME - 0x709C40
void Interface::SetGunScopeVisible(bool abVisible) {
	CdeclCall(0x709C40, abVisible);
}

// GAME - 0x709CA0
void Interface::ClearGunScope() {
	CdeclCall(0x709CA0);
}

// GAME - 0x707870
NiAVObject* Interface::CopyOrDeepCopyNode(NiAVObject* apObject) {
	return CdeclCall<NiAVObject*>(0x707870, apObject);
}

// GAME - 0x705870
void Interface::CreateRaceSexMenu(uint32_t aeType) {
	CdeclCall(0x705870, aeType);
}

// GAME - 0x7052F0
bool Interface::ShowMessage(const char* apText, Emotion aeEmotion, const char* apImagePath, const char* apSoundName, float afTime, bool abInstant) {
	return CdeclCall<bool>(0x7052F0, apText, aeEmotion, apImagePath, apSoundName, afTime, abInstant);
}