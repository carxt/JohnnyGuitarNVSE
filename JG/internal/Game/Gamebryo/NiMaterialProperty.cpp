#include "NiMaterialProperty.hpp"

const NiColor& NiMaterialProperty::GetSpecularColor() const {
	return m_kSpec;
}

void NiMaterialProperty::SetSpecularColor(const NiColor& arColor) {
	m_kSpec = arColor;
	SetChanged();
}

const NiColor& NiMaterialProperty::GetEmittanceColor() const {
	return m_kEmit;
}

// GAME - 0x4BC450
void NiMaterialProperty::SetEmittanceColor(const NiColor& arColor) {
	m_kEmit = arColor;
	SetChanged();
}

void NiMaterialProperty::SetExternalEmittanceSource(const NiColor* apColor) {
	pExternalEmittance = apColor;
}

float NiMaterialProperty::GetShineness() const {
	return m_fShine;
}

// GAME - 0x654700
void NiMaterialProperty::SetShineness(float afShine) {
	m_fShine = afShine;
	SetChanged();
}

float NiMaterialProperty::GetAlpha() const {
	return m_fAlpha;
}

// GAME - 0x68C9F0
void NiMaterialProperty::SetAlpha(float afAlpha) {
	m_fAlpha = afAlpha;
	SetChanged();
}

float NiMaterialProperty::GetEmittanceMult() const {
	return m_fEmitMult;
}

void NiMaterialProperty::SetEmittanceMult(float afEmitMult) {
	m_fEmitMult = afEmitMult;
	SetChanged();
}

const NiColor& NiMaterialProperty::GetEmittance() const {
    if (pExternalEmittance)
        return *pExternalEmittance;
    return m_kEmit;
}

// GAME - 0x4BC480
void NiMaterialProperty::SetChanged(bool abChanged) {
	++m_uiRevID;
}