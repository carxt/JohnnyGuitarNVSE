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

	void SetAmmo(TESForm* apAmmo);

	TESAmmo* GetAmmoForm() const;
	BGSListForm* GetAmmoFormList() const;

	bool IsRockItLauncher() const;
};

ASSERT_SIZE(BGSAmmoForm, 0x8);