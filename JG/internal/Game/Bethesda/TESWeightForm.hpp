#pragma once

#include "BaseFormComponent.hpp"

class TESForm;

class TESWeightForm : public BaseFormComponent {
public:
	TESWeightForm();
	~TESWeightForm();

	float	fWeight;

	float GetFormWeight() const;
	void SetFormWeight(float afWeight);

	static float GetFormWeight(TESForm* apForm, bool abHardcore);
};

ASSERT_SIZE(TESWeightForm, 0x8);