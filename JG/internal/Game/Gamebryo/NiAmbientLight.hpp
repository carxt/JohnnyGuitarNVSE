#pragma once

#include "NiLight.hpp"

NiSmartPointer(NiAmbientLight);

class NiAmbientLight : public NiLight {
public:
	NiAmbientLight();
	virtual ~NiAmbientLight();

	CREATE_OBJECT(NiAmbientLight, 0xA9B330);
	NIRTTI_ADDRESS(0x11F5F6C);
};

ASSERT_SIZE(NiAmbientLight, 0xF0)