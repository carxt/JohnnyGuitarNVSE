#include "Menu.hpp"

// GAME - 0x726070
TileMenu* Menu::GetMenuTile() const {
	return pMenu;
}

// GAME - 0xA1DC70
void Menu::SetMenuTile(TileMenu* apMenu, bool abDontAddToStack) {
	ThisCall(0xA1DC70, this, apMenu, abDontAddToStack);
}

// GAME - 0xA1DDB0
Tile* Menu::RenderTemplate(Tile* apParent, const char* apName, Tile* apLastTile) {
	return ThisCall<Tile*>(0xA1DDB0, this, apParent, apName, apLastTile);
}

// GAME - 0xA1DC20
void Menu::PrepForVisibility(bool abStayHidden) {
	ThisCall(0xA1DC20, this, abStayHidden);
}

// GAME - 0xA1DB20
void Menu::StartFadeIn() {
	ThisCall(0xA1DB20, this);
}

// GAME - 0xA1DBA0
void Menu::CancelFadeIn() {
	ThisCall(0xA1DBA0, this);
}

// GAME - 0xA1D910
void Menu::StartFadeOut() {
	ThisCall(0xA1D910, this);
}

// GAME - 0xA1DAA0
void Menu::CancelFadeOut() {
	ThisCall(0xA1DAA0, this);
}

// GAME - 0xA1D9E0
void Menu::InstantFadeOut() {
	ThisCall(0xA1D9E0, this);
}

// GAME - 0x7027B0
bool Menu::IsMenuVisible(Interface::MenuID aeMenu) {
	return CdeclCall<bool>(0x7027B0, aeMenu);
}

// GAME - 0xA09030
Menu* Menu::GetMenuByID(Interface::MenuID aeMenu) {
	return CdeclCall<Menu*>(0xA09030, aeMenu);
}
