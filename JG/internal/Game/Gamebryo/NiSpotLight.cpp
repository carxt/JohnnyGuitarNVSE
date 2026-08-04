#include "NiSpotLight.hpp"

const NiPoint3& NiSpotLight::GetWorldDirection() const {
	return m_kWorldDir;
}

float NiSpotLight::GetOuterSpotAngle() const {
	return m_fOuterSpotAngle; 
}

void NiSpotLight::SetOuterSpotAngle(float afAngle) {
	m_fOuterSpotAngle = afAngle;
	IncRevisionID();
}

float NiSpotLight::GetInnerSpotAngle() const {
	return m_fInnerSpotAngle;
}

void NiSpotLight::SetInnerSpotAngle(float afAngle) {
	m_fInnerSpotAngle = afAngle;
	IncRevisionID();
}

float NiSpotLight::GetSpotExponent() const { 
	return m_fSpotExponent;
}

void NiSpotLight::SetSpotExponent(float afExponent) {
	m_fSpotExponent = afExponent;
	IncRevisionID();
}
