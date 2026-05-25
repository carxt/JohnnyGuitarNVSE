#include "TESLoadScreen.hpp"

// GAME - 0x78ADA0
bool TESLoadScreen::GetDisplaysOnMainMenu() const {
    return uiFormFlags.Get(FormFlags::DISPLAY_ON_MAIN_MENU);
}

void TESLoadScreen::SetDisplaysOnMainMenu(bool abVal) {
    uiFormFlags.Set(FormFlags::DISPLAY_ON_MAIN_MENU, abVal);
}

// GAME - 0x5F36F0
TESLoadScreenType* TESLoadScreen::GetLoadScreenType() const {
    return pType;
}

// GAME - 0x8D7DC0
void TESLoadScreen::SetLoadScreenType(TESLoadScreenType* apType) {
    pType = apType;
}

// GAME - 0x5A6EC0
bool TESLoadScreen::CanDisplayForForm(TESForm* apLoadingForm) const {
    return ThisCall<bool>(0x5A6EC0, this, apLoadingForm);
}

// GAME - 0x5A7110
bool TESLoadScreen::IsDefaultLoadScreen() const {
    return kLoadForms.IsEmpty();
}
