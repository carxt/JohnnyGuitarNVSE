#pragma once

#include "NiLight.hpp"

NiSmartPointer(NiDirectionalLight)

class NiDirectionalLight : public NiLight {
public:
	NiDirectionalLight();
	virtual ~NiDirectionalLight();

	NiPoint3 m_kWorldDir;

	CREATE_OBJECT(NiDirectionalLight, 0xA75D50);
	NIRTTI_ADDRESS(0x11F4A68);

	const NiPoint3& GetWorldDirection() const;
};

ASSERT_SIZE(NiDirectionalLight, 0xFC);