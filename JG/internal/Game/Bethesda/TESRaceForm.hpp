#pragma once

#include "BaseFormComponent.hpp"

class TESRace;
class TESForm;

class TESRaceForm : public BaseFormComponent {
public:
	TESRaceForm();
	~TESRaceForm();

	TESRace* pRace;

	TESRace* GetFormRace() const;
	void SetFormRace(TESRace* apRace);

	static TESRace* GetFormRace(const TESForm* apForm);
};

ASSERT_SIZE(TESRaceForm, 0x8);