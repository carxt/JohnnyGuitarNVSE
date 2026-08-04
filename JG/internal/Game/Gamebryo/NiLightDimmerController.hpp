#pragma once

#include "NiFloatInterpController.hpp"

class NiLightDimmerController : public NiFloatInterpController {
public:
	CREATE_OBJECT(NiLightDimmerController, 0xA4D0D0);
	NIRTTI_ADDRESS(0x11F3FA0);
};

ASSERT_SIZE(NiLightDimmerController, 0x38);