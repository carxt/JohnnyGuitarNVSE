#pragma once

#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "TESDescription.hpp"

class TESLoadScreenType;

class TESLoadScreen : public TESForm, public TESTexture, public TESDescription {
public:
	TESLoadScreen();
	~TESLoadScreen();

	struct LoadForm {
		uint32_t uiFormID;
		uint32_t uiWorldID;
		uint32_t uiCellKey;
	};

	BSSimpleList<LoadForm*> kLoadForms;
	TESLoadScreenType*		pType;
	BSString				strScreenText;

	TESFORM_TYPE(TESLoadScreen);

	bool GetDisplaysOnMainMenu() const;
	void SetDisplaysOnMainMenu(bool abVal);

	TESLoadScreenType* GetLoadScreenType() const;
	void SetLoadScreenType(TESLoadScreenType* apType);

	bool CanDisplayForForm(TESForm* apLoadingForm) const;

	bool IsDefaultLoadScreen() const;
};

ASSERT_SIZE(TESLoadScreen, 0x40);