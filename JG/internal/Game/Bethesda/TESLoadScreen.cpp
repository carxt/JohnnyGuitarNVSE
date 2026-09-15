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

// GAME - 0x78BC60
TESLoadScreenType::Data* TESLoadScreen::GetLoadScreenTypeData() const {
#ifdef GAME
    return ThisCall<TESLoadScreenType::Data*>(0x78BC60, this);
#else
    return &pType->kData;
#endif
}

// GAME - 0x5A7130
TESLoadScreenType::Type TESLoadScreen::GetLoadScreenTypeDataType() const {
#ifdef GAME
    return ThisCall<TESLoadScreenType::Type>(0x5A7130, this);
#else
    if (pType)
        return pType->kData.eType;
    return TESLoadScreenType::Type::NONE;
#endif
}

#ifdef GAME
// GAME - 0x5A6EC0
bool TESLoadScreen::CanDisplayForForm(TESForm* apLoadingForm) const {
    return ThisCall<bool>(0x5A6EC0, this, apLoadingForm);
}
#endif

// GAME - 0x5A7110
bool TESLoadScreen::IsDefaultLoadScreen() const {
#ifdef GAME
    return ThisCall<bool>(0x5A7110, this);
#else
    return kLoadForms.IsEmpty();
#endif
}

#ifdef GAME
// GAME - 0x78A930
bool TESLoadScreen::GetUseLocationSpecificScreensOnly() {
    return CdeclCall<bool>(0x78A930);
}

// GAME - 0x5C25E0
void TESLoadScreen::SetUseLocationSpecificScreensOnly(bool abVal) {
    CdeclCall(0x5C25E0, abVal);
}
#endif