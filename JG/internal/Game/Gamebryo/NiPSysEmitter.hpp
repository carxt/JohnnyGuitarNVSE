#pragma once

#include "NiPSysModifier.hpp"

NiSmartPointer(NiPSysEmitter);

class NiPSysEmitter : public NiPSysModifier {
public:
	NiPSysEmitter();
	virtual ~NiPSysEmitter();

	virtual void EmitParticles(float afTime, uint16_t ausNumParticles, const float* apfAges);
	virtual void ComputeInitialPositionAndVelocity(NiPoint3& arPosition, NiPoint3& arVelocity);

	float		m_fSpeed;
	float		m_fSpeedVar;
	float		m_fDeclination;
	float		m_fDeclinationVar;
	float		m_fPlanarAngle;
	float		m_fPlanarAngleVar;
	NiColorA	m_kInitialColor;
	float		m_fInitialRadius;
	float		m_fRadiusVar;
	float		m_fLifeSpan;
	float		m_fLifeSpanVar;
	float		m_fScale;

	NIRTTI_ADDRESS(0x1202540);
};

ASSERT_SIZE(NiPSysEmitter, 0x54);