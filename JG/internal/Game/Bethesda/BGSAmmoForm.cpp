#include "BGSAmmoForm.hpp"
#include "TESForm.hpp"

// GAME - 0x474A00
TESAmmo* BGSAmmoForm::GetAmmoForm() const {
    if (pAmmo && pAmmo->GetFormType() == FORM_TYPE::TESAmmo)
        return reinterpret_cast<TESAmmo*>(pAmmo);
    return nullptr;
}

// GAME - 0x474A40
BGSListForm* BGSAmmoForm::GetAmmoFormList() const {
    if (pAmmo && pAmmo->GetFormType() == FORM_TYPE::BGSListForm)
        return reinterpret_cast<BGSListForm*>(pAmmo);
    return nullptr;
}

// GAME - 0x6ECD40
void BGSAmmoForm::SetFormAmmo(TESForm* apAmmo) {
    pAmmo = apAmmo;
}

// GECK - 0x4E2F30
const char* BGSAmmoForm::GetAmmoFormEditorID() const {
#ifdef GAME
    return pAmmo ? pAmmo->GetFormEditorID() : "";
#else
    return ThisCall<const char*>(0x4E2F30, this);
#endif
}

// GAME - 0x474920
// GECK - 0x4E30D0
TESAmmo* BGSAmmoForm::GetAmmoHelper() const {
#ifdef GAME
    return ThisCall<TESAmmo*>(0x474920, this);
#else
    return ThisCall<TESAmmo*>(0x4E30D0, this);
#endif
}

#ifdef GAME
// GAME - 0x474A80
bool BGSAmmoForm::IsRockItLauncher() const {
    return ThisCall<bool>(0x474A80, this);
}
#endif