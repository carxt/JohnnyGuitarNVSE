#include "TESCreature.hpp"

// GAME - 0x5F9100
TESCreature* TESCreature::GetSoundCreature() const {
	return ThisCall<TESCreature*>(0x5F9100, this);
}

// GAME - 0x5F9140
void TESCreature::SetSoundCreature(TESCreature* apCreature) {
	ThisCall(0x5F9140, this, apCreature);
}

// GAME - 0x5F91D0
CreatureSounds* TESCreature::GetCreatureSounds() const {
	return ThisCall<CreatureSounds*>(0x5F91D0, this);
}

// GAME - 0x59F3A0
int8_t TESCreature::GetCreatureType() const {
	return kData.eType;
}

// GAME - 0x5FBF20
bool TESCreature::IsHumanoidCreature() const {
	return ThisCall<bool>(0x5FBF20, this);
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

// GAME - 0x5FBEB0
int32_t TESCreature::GetSoundLevelValue() const {
	return ThisCall<int32_t>(0x5FBEB0, this);
}

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
	return ThisCall<bool>(0x5FA120, this, apForm);
}

// GAME - 0x5F9E00
bool TESCreature::InitDefaultWorn(Actor* apActor, bool abAwake, bool abWeapon, bool abAllowChanges) {
	return ThisCall<bool>(0x5F9E00, this, apActor, abAwake, abWeapon, abAllowChanges);
}
