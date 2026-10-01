#pragma once

#include "BaseFormComponent.hpp"

class TESImageSpaceModifier;

template<uint32_t uiCount = 6>
class TESImageSpaceModifiableCountForm : public BaseFormComponent {
public:
	TESImageSpaceModifier* pFormImageSpaceModifying[uiCount];
};

ASSERT_SIZE(TESImageSpaceModifiableCountForm<6>, 0x1C);