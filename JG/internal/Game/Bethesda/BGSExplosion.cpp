#include "BGSExplosion.hpp"

// GAME - 0x4FD380
TESForm* BGSExplosion::GetImpactPlacedObject() const {
	return kData.pImpactPlacedObject;
}

// GAME - 0x57BD60
void BGSExplosion::SetImpactPlacedObject(TESForm* apForm) {
	kData.pImpactPlacedObject = apForm;
}

// GAME - 0x9B0BD0
float BGSExplosion::GetForce() const {
	return kData.fForce;
}

// GAME - 0x6D3B00
void BGSExplosion::SetForce(float afForce) {
	kData.fForce = afForce;
}

// GAME - 0x6A78F0
float BGSExplosion::GetDamage() const {
	return kData.fDamage;
}

void BGSExplosion::SetDamage(float afDamage) {
	kData.fDamage = afDamage;
}

float BGSExplosion::GetRadius() const {
	return kData.fRadius;
}

// GAME - 0x477900
// GECK - 0x5D0480
float BGSExplosion::GetRadiusBSUnits() const {
#ifdef GAME
	return ThisCall<float>(0x477900, this);
#else
	return ThisCall<float>(0x5D0480, this);
#endif
}

void BGSExplosion::SetRadius(float afRadius) {
	kData.fRadius = afRadius;
}

// GAME - 0x4FB070
TESObjectLIGH* BGSExplosion::GetLight() const {
	return kData.pLight;
}

// GAME - 0x8AC890
void BGSExplosion::SetLight(TESObjectLIGH* apLight) {
	kData.pLight = apLight;
}

// GAME - 0x4FD3C0
TESSound* BGSExplosion::GetSound1() const {
	return kData.pSound1;
}

// GAME - 0x4FB090
void BGSExplosion::SetSound1(TESSound* apSound) {
	kData.pSound1 = apSound;
}

// GAME - 0x477950
bool BGSExplosion::GetFlag(uint32_t auiFlag) {
	return kData.uiFlags.Get(auiFlag);
}

void BGSExplosion::SetFlag(uint32_t auiFlag, bool abVal) {
	kData.uiFlags.Set(auiFlag, abVal);
}

float BGSExplosion::GetImageSpaceRadius() const {
	return kData.fImageSpaceRadius;
}

#ifdef GAME
// GAME - 0x9AC550
float BGSExplosion::GetImageSpaceRadiusBSUnits() const {
	return ThisCall<float>(0x9AC550, this);
}
#endif

void BGSExplosion::SetImageSpaceRadius(float afRadius) {
	kData.fImageSpaceRadius = afRadius;
}

// GAME - 0x516BF0
BGSImpactDataSet* BGSExplosion::GetImpactDataSet() const {
	return kData.pImpactDataSet;
}

// GAME - 0x4FB0B0
void BGSExplosion::SetImpactDataSet(BGSImpactDataSet* apImpactDataSet) {
	kData.pImpactDataSet = apImpactDataSet;
}

// GAME - 0x9185E0
TESSound* BGSExplosion::GetSound2() const {
	return kData.pSound2;
}

// GAME - 0x4FEBF0
void BGSExplosion::SetSound2(TESSound* apSound) {
	kData.pSound2 = apSound;
}

// GAME - 0x8D01E0
float BGSExplosion::GetRadiationRads() const {
	return kData.fRadiationRads;
}

void BGSExplosion::SetRadiationRads(float afRads) {
	kData.fRadiationRads = afRads;
}

// GAME - 0x4E3CC0
float BGSExplosion::GetRadiationDissipationTime() const {
	return kData.fRadiationDissipationTime;
}

void BGSExplosion::SetRadiationDissipationTime(float afTime) {
	kData.fRadiationDissipationTime = afTime;
}

float BGSExplosion::GetRadiationRadius() const {
	return kData.fRadiationRadius;
}

#ifdef GAME
// GAME - 0x9AD5A0
float BGSExplosion::GetRadiationRadiusBSUnits() const {
	return ThisCall<float>(0x9AD5A0, this);
}
#endif

void BGSExplosion::SetRadiationRadius(float afRadius) {
	kData.fRadiationRadius = afRadius;
}

SOUND_LEVEL BGSExplosion::GetSoundLevel() const {
	return kData.eSoundLevel;
}

void BGSExplosion::SetSoundLevel(SOUND_LEVEL aeLevel) {
	kData.eSoundLevel = aeLevel;
}

#ifdef GAME
int32_t BGSExplosion::GetSoundLevelValue() const {
	return ThisCall<int32_t>(0x4FB810, this);
}
#endif