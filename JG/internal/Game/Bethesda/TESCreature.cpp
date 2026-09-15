#include "TESCreature.hpp"
#ifdef EDITOR
#include <GameForms.h>
#endif

// GAME - 0x5F90C0
bool TESCreature::GetTiltFrontBack() const {
#ifdef GAME
	return ThisCall<bool>(0x5F90C0, this);
#else
	return GetCreatureFlags().bTiltFrontBack;
#endif
}

// GAME - 0x5F90E0
bool TESCreature::GetTiltLeftRight() const {
#ifdef GAME
	return ThisCall<bool>(0x5F90E0, this);
#else
	return GetCreatureFlags().bTiltLeftRight;
#endif
}

// GAME - 0x5F9100
TESCreature* TESCreature::GetSoundCreature() const {
#ifdef GAME
	return ThisCall<TESCreature*>(0x5F9100, this);
#else
	if (GetCharacterFlags().bUseTemplate)
		return nullptr;
	else
		return pSoundCreature;
#endif
}

// GAME - 0x5F9140
// GECK - 0x561AF0
void TESCreature::SetSoundCreature(TESCreature* apCreature) {
#ifdef GAME
	ThisCall(0x5F9140, this, apCreature);
#else
	ThisCall(0x561AF0, this, apCreature);
#endif
}

// GAME - 0x5F91D0
// GECK - 0x561B70
CreatureSounds* TESCreature::GetCreatureSounds() const {
#ifdef GAME
	return ThisCall<CreatureSounds*>(0x5F91D0, this);
#else
	return ThisCall<CreatureSounds*>(0x561B70, this);
#endif
}

// GAME - 0x59F3A0
int8_t TESCreature::GetCreatureType() const {
	return kData.eType;
}

// GAME - 0x5FBF20
bool TESCreature::IsHumanoidCreature() const {
#ifdef GAME
	return ThisCall<bool>(0x5FBF20, this);
#else
	const uint8_t ucType = GetCreatureType();
	return ucType == CREATURE_TYPE::ABOMINATION 
		|| ucType == CREATURE_TYPE::SUPER_MUTANT 
		|| ucType == CREATURE_TYPE::FERAL_GHOUL 
		|| ucType == CREATURE_TYPE::GIANT;
#endif
}

// GAME - 0x5F9AD0
uint8_t TESCreature::GetHandReach() const {
	return ucHandReach;
}

// GAME - 0x5F9AF0
void TESCreature::SetHandReach(uint8_t aucReach) {
	ucHandReach = aucReach;
}

// GAME - 0x821640
float TESCreature::GetTurnSpeed() const {
	return fTurningSpeed;
}

// GAME - 0x507780
void TESCreature::SetTurnSpeed(float afSpeed) {
	fTurningSpeed = afSpeed;
}

// GAME - 0x821660
float TESCreature::GetFootWeight() const {
	return fFootWeight;
}

// GAME - 0x5F9B10
void TESCreature::SetFootWeight(float afWeight) {
	fFootWeight = afWeight;
}

// GAME - 0x567470
float TESCreature::GetBaseScale() const {
	return fBaseScale;
}

// GAME - 0x803A90
void TESCreature::SetBaseScale(float afScale) {
	fBaseScale = afScale;
}

// GAME - 0x5F9B30
BGSImpactDataSet* TESCreature::GetImpactDataSet() const {
	return pImpactDataSet;
}

// GAME - 0x5F8BB0
void TESCreature::SetImpactDataSet(BGSImpactDataSet* apSet) {
	pImpactDataSet = apSet;
}

// GAME - 0x9C0070
SOUND_LEVEL TESCreature::GetSoundLevel() const {
	return eSoundLevel;
}

#ifdef GAME
// GAME - 0x5FBEB0
int32_t TESCreature::GetSoundLevelValue() const {
	return ThisCall<int32_t>(0x5FBEB0, this);
}
#endif

// GAME - 0x5F9B50
BGSListForm* TESCreature::GetWeaponList() const {
	return pWeapons;
}

// GAME - 0x5F8BD0
void TESCreature::SetWeaponList(BGSListForm* apList) {
	pWeapons = apList;
}

// GAME - 0x5FA120
bool TESCreature::CanWearItem(TESForm* apForm) const {
#ifdef GAME
	return ThisCall<bool>(0x5FA120, this, apForm);
#else
	const FORM_TYPE eFormType = apForm->GetFormType();
	if (eFormType == FORM_TYPE::TESObjectLIGH)
		return true;

	if (eFormType > FORM_TYPE::TESFurniture && eFormType <= FORM_TYPE::TESAmmo)
		return true;

	// Yes, the weapon handling is weird
	return eFormType == FORM_TYPE::TESObjectWEAP && static_cast<TESObjectWEAP*>(apForm)->IsEmbeddedWeapon();
#endif
}

// GAME - 0x5F9E00
// GECK - 0x564A90
bool TESCreature::InitDefaultWorn(Actor* apActor, bool abAwake, bool abWeapon, bool abAllowChanges) {
#ifdef GAME
	return ThisCall<bool>(0x5F9E00, this, apActor, abAwake, abWeapon, abAllowChanges);
#else
	return ThisCall<bool>(0x564A90, this, apActor, abAwake, abWeapon, abAllowChanges);
#endif
}
