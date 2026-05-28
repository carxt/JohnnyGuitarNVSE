#include "TESAmmo.hpp"

// GAME - 0x4C94D0
bool TESAmmo::GetIsPlayable() const {
	return kData.uiFlags.bNonPlayable == false;
}

// GAME - 0x8D80E0
BGSProjectile* TESAmmo::GetProjectile() const {
	return kNVData.pProjectile;
}

// GAME - 0x525BE0
uint8_t TESAmmo::GetNumProjectiles() const {
	return kNVData.ucProjectilePerAmmo;
}

// GAME - 0x97AE90
TESForm* TESAmmo::GetAmmoConsumedForm() const {
	return kNVData.pAmmoConsumedObject;
}

// GAME - 0x6D6D90
float TESAmmo::GetAmmoConsumedPercent() const {
	return kNVData.fAmmoConsumedPercent;
}

// GAME - 0x923000
const BSSimpleList<TESAmmoEffect*>* TESAmmo::GetAmmoEffectList() const {
	return &kAmmoEffects;
}

// GAME - 0x923000
BSSimpleList<TESAmmoEffect*>* TESAmmo::GetAmmoEffectList() {
	return &kAmmoEffects;
}

// GAME - 0x663B40
const char* TESAmmo::GetShortName() const {
	return strShortName.GetString();
}

// GAME - 0x772820
const char* TESAmmo::GetAbbreviation() const {
	return strAbbreviation.GetString();
}

// GAME - 0x503A70
void TESAmmo::GetEffectNames(char* apBuffer, uint32_t auiBufferSize) const {
	ThisCall(0x503A70, this, apBuffer, auiBufferSize);
}
