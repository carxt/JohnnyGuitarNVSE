#pragma once

#include "NiDynamicEffect.hpp"
#include "NiColor.hpp"

class TESObjectLIGH;

NiSmartPointer(NiLight);

class NiLight : public NiDynamicEffect {
public:
	NiLight();
	virtual ~NiLight();

	float	m_fDimmer;
	NiColor m_kAmb;
	NiColor m_kDiff;
	union { // Bethesda reuses red specular color for light radius, JIP adds a pointer to the light object
		NiColor	 m_kSpec;
		struct {
			float			m_fRadius;
			float			_empty;
#if JIP_LIGHTS
			TESObjectLIGH*	pLightForm;
#else
			float			_empty2;
#endif
		};
	};

	void* m_pvRendererData;

	NIRTTI_ADDRESS(0x11F4A28);

	float GetDimmer() const;
	void SetDimmer(float afDimmer);

	const NiColor& GetAmbientColor() const;
	void SetAmbientColor(const NiColor& arColor);

	const NiColor& GetDiffuseColor() const;
	void SetDiffuseColor(const NiColor& arColor);

	const NiColor& GetSpecularColor() const;
	void SetSpecularColor(const NiColor& arColor);

	float GetLightRadius() const;
	void SetLightRadius(float afRadius);
};

ASSERT_SIZE(NiLight, 0xF0)