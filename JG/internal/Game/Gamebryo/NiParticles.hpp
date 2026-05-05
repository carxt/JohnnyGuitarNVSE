#pragma once

#include "netimmerse.h"
#include "NiSmartPointer.hpp"

class NiPSysData;

NiSmartPointer(NiParticles);

class NiParticles : public NiGeometry {
public:
	NiParticles();
	virtual ~NiParticles();

	CREATE_OBJECT(NiParticles, 0x84B290);
	NIRTTI_ADDRESS(0xF2188C);
};

ASSERT_SIZE(NiParticles, 0xC4)