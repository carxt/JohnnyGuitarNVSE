#pragma once

#include "NiSingleInterpController.hpp"
#include "NiFixedString.hpp"

class NiPSysModifier;

NiSmartPointer(NiPSysModifierCtlr);

class NiPSysModifierCtlr : public NiSingleInterpController {
public:
	NiPSysModifierCtlr();
	virtual ~NiPSysModifierCtlr();

	NiFixedString	m_kModifierName;
	NiPSysModifier* m_pkModifier;

	NIRTTI_ADDRESS(0x12027C8);
};

ASSERT_SIZE(NiPSysModifierCtlr, 0x40)