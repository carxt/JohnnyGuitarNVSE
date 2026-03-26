#include "BGSAmmoForm.hpp"
#include "BGSListForm.hpp"
#include "TESAmmo.hpp"

// GAME - 0x6ECD40
void BGSAmmoForm::SetAmmo(TESForm* apAmmo) {
	pAmmo = apAmmo;
}

// GAME - 0x474A00
TESAmmo* BGSAmmoForm::GetAmmoForm() const {
    if (pAmmo && pAmmo->IsType<TESAmmo>())
        return static_cast<TESAmmo*>(pAmmo);
    return nullptr;
}

// GAME - 0x474A40
BGSListForm* BGSAmmoForm::GetAmmoFormList() const {
    if (pAmmo && pAmmo->IsType<BGSListForm>())
        return static_cast<BGSListForm*>(pAmmo);
    return nullptr;
}

// GAME - 0x474A80
bool BGSAmmoForm::IsRockItLauncher() const {
    return ThisCall<bool>(0x474A80, this);
}
