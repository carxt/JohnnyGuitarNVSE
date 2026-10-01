#pragma once

#include "BaseFormComponent.hpp"

class TESForm;
class TESAmmo;
class BGSListForm;

class BGSAmmoForm : public BaseFormComponent {
public:
	BGSAmmoForm();
	~BGSAmmoForm();

	TESForm* pAmmo; // TESAmmo or BGSListForm

	TESAmmo* GetAmmoForm() const;
	BGSListForm* GetAmmoFormList() const;
	void SetFormAmmo(TESForm* apAmmo);

#ifdef GAME
	TESAmmo* GetAmmoHelper() const;

	bool IsRockItLauncher() const;
#endif
};

ASSERT_SIZE(BGSAmmoForm, 0x8);