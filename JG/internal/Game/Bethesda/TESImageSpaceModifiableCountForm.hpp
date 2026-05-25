#pragma once

#include "BaseFormComponent.hpp"

class TESImageSpaceModifier;

class TESImageSpaceModifiableCountForm : public BaseFormComponent {
public:
	TESImageSpaceModifier* pFormImageSpaceModifying[6];
};

ASSERT_SIZE(TESImageSpaceModifiableCountForm, 0x1C);