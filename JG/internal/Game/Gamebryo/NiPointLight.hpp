#pragma once

#include "NiLight.hpp"
#include "NiPoint4.hpp"

NiSmartPointer(NiPointLight);

#if JIP_LIGHTS
	struct JIPLightData {
		float			flt0FC;
		NiPoint3		kNewPos;
		float			kNewScale;
	};

	#define LIGHT_SIZE 0x110
#else
	#define LIGHT_SIZE 0xFC
#endif

class NiPointLight : public NiLight {
public:
	NiPointLight();
	virtual ~NiPointLight();

	// Bethesda uses these fields for position offset (for flickering lights)
	union {
		struct {
			float m_fAtten0;
			float m_fAtten1;
			float m_fAtten2;
		};
		NiPoint3 m_kLightOffset;
	};

#if JIP_LIGHTS
	JIPLightData		kJIPData;
#endif

	CREATE_OBJECT(NiPointLight, 0xA7D6E0);
	NIRTTI_ADDRESS(0x11F4A98);
};

ASSERT_SIZE(NiPointLight, LIGHT_SIZE);