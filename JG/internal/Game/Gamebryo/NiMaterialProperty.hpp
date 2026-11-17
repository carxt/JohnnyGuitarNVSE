#pragma once

#include "NiProperty.hpp"
#include "NiColor.hpp"

NiSmartPointer(NiMaterialProperty);

class NiMaterialProperty : public NiProperty {
public:
	NiMaterialProperty();
	virtual ~NiMaterialProperty();

	int32_t			m_iIndex;
	NiColor			m_kSpec;
	NiColor			m_kEmit;
	const NiColor*	pExternalEmittance;
	float			m_fShine;
	float			m_fAlpha;
	float			m_fEmitMult;
	uint32_t		m_uiRevID;
	void*			m_pvRendererData;

	CREATE_OBJECT(NiMaterialProperty, 0xA756D0);
	NIRTTI_ADDRESS(0x11F4A5C);

	const NiColor& GetSpecularColor() const;
	void SetSpecularColor(const NiColor& arColor);

	const NiColor& GetEmittanceColor() const;
	void SetEmittanceColor(const NiColor& arColor);

	void SetExternalEmittanceSource(const NiColor* apColor);

	float GetShineness() const;
	void SetShineness(float afShine);

	float GetAlpha() const;
	void SetAlpha(float afAlpha);

	float GetEmittanceMult() const;
	void SetEmittanceMult(float afEmitMult);

	const NiColor& GetEmittance() const;

	void SetChanged(bool abChanged = true);
};

ASSERT_SIZE(NiMaterialProperty, 0x4C)