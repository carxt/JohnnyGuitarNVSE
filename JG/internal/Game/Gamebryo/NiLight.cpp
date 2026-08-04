#include "NiLight.hpp"

float NiLight::GetDimmer() const { 
	return m_fDimmer; 
};

// GAME - 0x50DD20
void NiLight::SetDimmer(float afDimmer) {
	m_fDimmer = afDimmer;
	IncRevisionID();
}

const NiColor& NiLight::GetAmbientColor() const {
	return m_kAmb;
};

// GAME - 0x4BC280
void NiLight::SetAmbientColor(const NiColor& arColor) {
	m_kAmb = arColor;
	IncRevisionID();
}

const NiColor& NiLight::GetDiffuseColor() const {
	return m_kDiff;
};

// GAME - 0x4BC2E0
void NiLight::SetDiffuseColor(const NiColor& arColor) {
	m_kDiff = arColor;
	IncRevisionID();
}

const NiColor& NiLight::GetSpecularColor() const {
	return m_kSpec;
};

// GAME - 0x50DD50
void NiLight::SetSpecularColor(const NiColor& arColor) {
	m_kSpec = arColor;
	IncRevisionID();
}

float NiLight::GetLightRadius() const {
	return m_fRadius; 
};

void NiLight::SetLightRadius(float afRadius) {
	m_fRadius = afRadius;
	IncRevisionID();
}
