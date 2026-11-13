#pragma once

#include "NiSingleInterpController.hpp"

NiSmartPointer(NiFloatInterpController);

class NiFloatInterpController : public NiSingleInterpController {
public:
	NiFloatInterpController();
	virtual ~NiFloatInterpController();

	virtual void GetTargetFloatValue(float& arValue);

#ifdef GAME
	NIRTTI_ADDRESS(0x11F4220);
#else
	NIRTTI_ADDRESS(0xF1FB98);
#endif
};

ASSERT_SIZE(NiFloatInterpController, 0x38);