#include "NiDynamicEffect.hpp"

bool NiDynamicEffect::IsOn() const {
	return m_bOn;
}

NiDynamicEffect::EffectType NiDynamicEffect::GetEffectType() const {
	return static_cast<EffectType>(m_ucEffectType);
}

bool NiDynamicEffect::IsLight() const {
	return m_ucEffectType < EffectType::TEXTURE_EFFECT;
}

bool NiDynamicEffect::IsAmbientLight() const { 
	return m_ucEffectType == EffectType::LIGHT_AMBIENT;
}

bool NiDynamicEffect::IsPointLight() const { 
	return m_ucEffectType == EffectType::LIGHT_POINT;
}

bool NiDynamicEffect::IsDirectionalLight() const {
	return m_ucEffectType == EffectType::LIGHT_DIR;
}

bool NiDynamicEffect::IsSpotLight() const {
	return m_ucEffectType == EffectType::LIGHT_SPOT;
}

bool NiDynamicEffect::IsTextureEffect() const {
	return m_ucEffectType == EffectType::TEXTURE_EFFECT;
}

// GAME - 0x4BC2C0
void NiDynamicEffect::IncRevisionID() {
	++m_uiRevID;
}
