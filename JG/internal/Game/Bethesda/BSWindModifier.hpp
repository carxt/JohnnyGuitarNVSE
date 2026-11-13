#pragma once

#include "Gamebryo/NiPSysModifier.hpp"
#include "Gamebryo/NiPoint3.hpp"

NiSmartPointer(BSWindModifier);

class BSWindModifier : public NiPSysModifier {
public:
	BSWindModifier();
	~BSWindModifier();

	float fStrength;

	CREATE_OBJECT(BSWindModifier, 0xC46740);
	NIRTTI_ADDRESS(0x1202E60);

	static constexpr AddressPtr<NiPoint3, 0x1202E68> kWindDir;
};

ASSERT_SIZE(BSWindModifier, 0x1C)