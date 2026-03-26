#include "TESAmmoEffect.hpp"

// GAME - 0x45CD60
AMMO_OPERATION_TYPE TESAmmoEffect::GetOperation() const {
    return static_cast<AMMO_OPERATION_TYPE>(kData.eOperation);
}

void TESAmmoEffect::SetOperation(AMMO_OPERATION_TYPE aeOperation) {
	kData.eOperation = aeOperation;
}

// GAME - 0x59BB30
AMMO_EFFECT_TYPE TESAmmoEffect::GetEffectType() const {
	return static_cast<AMMO_EFFECT_TYPE>(kData.eType);
}

void TESAmmoEffect::SetEffectType(AMMO_EFFECT_TYPE aeType) {
	kData.eType = aeType;
}

// GAME - 0x759450
float TESAmmoEffect::GetEffectValue() const {
	return kData.fValue;
}

void TESAmmoEffect::SetEffectValue(float afValue) {
	kData.fValue = afValue;
}
