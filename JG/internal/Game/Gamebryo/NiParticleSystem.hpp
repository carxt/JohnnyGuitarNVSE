#pragma once

#include <NiTypes.h>

#include "netimmerse.h"
#include "NiParticles.hpp"
#include "NiTPointerList.hpp"
#include "NiPSysModifier.hpp"

NiSmartPointer(NiParticleSystem);

class NiParticleSystem : public NiParticles {
public:
	NiParticleSystem();
	virtual ~NiParticleSystem();

	virtual void UpdateSystem(float afTime);
	virtual void Do_UpdateSystem(float afTime);

	bool								m_bWorldSpace;
	NiTPointerList<NiPSysModifierPtr>	m_kModifierList;
	float								m_fLastTime;
	bool								m_bResetSystem;
	bool								m_bDynamicBounds;
	NiTransform							m_kUnmodifiedWorld;

	CREATE_OBJECT(NiParticleSystem, 0xC1B7F0);
	NIRTTI_ADDRESS(0x12024E0);

	void UpdateDownwardPassEx(NiUpdateData& arData, uint32_t auiFlags);
	void UpdateWorldDataEx(NiUpdateData& arData);
	void UpdateWorldBoundEx();
	void UpdateSystemEx(float afTime);
	void Do_UpdateSystemEx(float afTime);

	void PerformSystemReset();
};

ASSERT_SIZE(NiParticleSystem, 0x110);