#pragma once

#include "NiPSysModifierCtlr.hpp"
#include "NiTPrimitiveSet.hpp"

NiSmartPointer(NiPSysEmitterCtlr);

class NiFloatInterpolator;

class NiPSysEmitterCtlr : public NiPSysModifierCtlr {
public:
	NiPSysEmitterCtlr();
	virtual ~NiPSysEmitterCtlr();

	NiInterpolatorPtr			m_spEmitterActiveInterpolator;
	NiInterpolator*				m_pkLastBirthRateInterpolator;
	float						m_fLastScaledTime;
	bool						m_bLastActive;
	NiTPrimitiveSet<float>		m_kParticleAges;

	CREATE_OBJECT(NiPSysEmitterCtlr, 0xC1C5E0);
	NIRTTI_ADDRESS(0x12024E8);

	NiFloatInterpolator* GetBirthRateInterpolator() const;
};

ASSERT_SIZE(NiPSysEmitterCtlr, 0x5C)