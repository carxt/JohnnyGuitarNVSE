#pragma once

#include "NiInterpController.hpp"
#include "NiInterpolator.hpp"

NiSmartPointer(NiSingleInterpController);

class NiSingleInterpController : public NiInterpController {
public:
	NiSingleInterpController();
	virtual ~NiSingleInterpController();

	virtual bool InterpTargetIsCorrectType(NiObjectNET* apObject) const;

	NiInterpolatorPtr m_spInterpolator;

	CREATE_OBJECT(NiSingleInterpController, 0xC5C9D0);
	NIRTTI_ADDRESS(0x11F3714);
};

ASSERT_SIZE(NiSingleInterpController, 0x38);