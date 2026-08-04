#pragma once

#include "NiSingleInterpController.hpp"

NiSmartPointer(NiFloatInterpController);

class NiFloatInterpController : public NiSingleInterpController {
public:
	NiFloatInterpController();
	virtual ~NiFloatInterpController();

	virtual void GetTargetFloatValue(float& arValue);

	NIRTTI_ADDRESS(0x11F4220);
};

ASSERT_SIZE(NiFloatInterpController, 0x38);