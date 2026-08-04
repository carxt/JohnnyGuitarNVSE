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

float BGSExplosion::GetRadius() const {
	return kData.fRadius;
}

// GAME - 0x477900
float BGSExplosion::GetRadiusBSUnits() const {
	return ThisCall<float>(0x477900, this);
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

void BGSExplosion::SetFlag(uint32_t auiFlag, bool abVal) {
	kData.uiFlags.Set(auiFlag, abVal);
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