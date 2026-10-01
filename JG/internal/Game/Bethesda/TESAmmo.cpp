#include "TESAmmo.hpp"

float TESAmmo::GetSpeed() const {
	return kData.fSpeed;
}

void TESAmmo::SetSpeed(float afSpeed) {
	kData.fSpeed = afSpeed;
}

// GAME - 0x4C94D0
bool TESAmmo::GetIsPlayable() const {
	return !kData.uiFlags.bNonPlayable;
}

void TESAmmo::SetIsPlayable(bool abVal) {
	kData.uiFlags.bNonPlayable = !abVal;
}

// GAME - 0x525BE0
uint8_t TESAmmo::GetNumProjectiles() const {
	return kNVData.ucProjectilePerAmmo;
}

void TESAmmo::SetNumProjectiles(uint8_t aucCount) {
	kNVData.ucProjectilePerAmmo = aucCount;
}

// GAME - 0x8D80E0
BGSProjectile* TESAmmo::GetProjectile() const {
	return kNVData.pProjectile;
}

// GAME - 0x502C90
void TESAmmo::SetProjectile(BGSProjectile* apProjectile) {
	kNVData.pProjectile = apProjectile;
}

// GAME - 0x48EE50
float TESAmmo::GetWeight() const {
	return kNVData.fWeight;
}

void TESAmmo::SetWeight(float afWeight) {
	kNVData.fWeight = afWeight;
}

// GAME - 0x97AE90
TESForm* TESAmmo::GetAmmoConsumedForm() const {
	return kNVData.pAmmoConsumedObject;
}

// GAME - 0x502CB0
void TESAmmo::SetAmmoConsumedForm(TESForm* apForm) {
	kNVData.pAmmoConsumedObject = apForm;
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

void TESAmmo::SetShortName(const char* apText) {
	strShortName.Set(apText);
}

// GAME - 0x772820
const char* TESAmmo::GetAbbreviation() const {
	return strAbbreviation.GetString();
}

void TESAmmo::SetAbbreviation(const char* apText) {
	strAbbreviation.Set(apText);
}

#ifdef GAME
// GAME - 0x503A70
void TESAmmo::GetEffectNames(char* apBuffer, uint32_t auiBufferSize) const {
	ThisCall(0x503A70, this, apBuffer, auiBufferSize);
}
#endif
