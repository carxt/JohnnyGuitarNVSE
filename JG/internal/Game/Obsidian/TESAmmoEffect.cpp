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

// GAME - 0x59A1E0
void TESAmmoEffect::BuildMenuString(char* apBuffer, uint32_t auiBufferSize) const {
	ThisCall(0x59A1E0, this, apBuffer, auiBufferSize);
}

// GAME - 0x59A030
float TESAmmoEffect::ApplyAmmoEffect(uint32_t aeType, BSSimpleList<TESAmmoEffect*>* apEffects, float afDamage) {
	return CdeclCall<float>(0x59A030, aeType, apEffects, afDamage);
}
