#pragma once

#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "TESDescription.hpp"
#include "Obsidian/TESLoadScreenType.hpp"

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
#ifdef GAME
	BSString				strScreenText;
#endif

	TESFORM_TYPE(TESLoadScreen);

	bool GetDisplaysOnMainMenu() const;
	void SetDisplaysOnMainMenu(bool abVal);

	TESLoadScreenType* GetLoadScreenType() const;
	void SetLoadScreenType(TESLoadScreenType* apType);

	TESLoadScreenType::Data* GetLoadScreenTypeData() const;
	TESLoadScreenType::Type GetLoadScreenTypeDataType() const;

#ifdef GAME
	bool CanDisplayForForm(TESForm* apLoadingForm) const;
#endif

	bool IsDefaultLoadScreen() const;

#ifdef GAME
	static bool GetUseLocationSpecificScreensOnly();
	static void SetUseLocationSpecificScreensOnly(bool abVal);
#endif
};

#ifdef GAME
ASSERT_SIZE(TESLoadScreen, 0x40);
#else
ASSERT_SIZE(TESLoadScreen, 0x64);
#endif