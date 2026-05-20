#pragma once

#include "NiObject.hpp"
#include "NiFixedString.hpp"

class NiParticleSystem;
class NiPSysData;

NiSmartPointer(NiPSysModifier);

class NiPSysModifier : public NiObject {
public:
	NiPSysModifier();
	virtual ~NiPSysModifier();

	virtual void Update(float afTime, NiPSysData* apData);
	virtual void Initialize(NiPSysData* apData, uint16_t ausNewParticle);
	virtual void HandleReset();
	virtual void SetActive(bool abActive);
	virtual void SetSystemPointer(NiParticleSystem* apTarget);
	virtual bool IsDeferred() const;

	NiFixedString		m_kName;
	uint32_t			m_uiOrder;
	NiParticleSystem*	m_pkTarget;
	bool				m_bActive;

	NIRTTI_ADDRESS(0x12027D0);

	const char* GetName() const {
		return m_kName.c_str();
	}
};

ASSERT_SIZE(NiPSysModifier, 0x18)