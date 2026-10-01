#include "TESLandTexture.hpp"

// GAME - 0x9611E0
BGSTextureSet* TESLandTexture::GetTextureSet() const {
	return pTextureSet;
}

// GAME - 0x984F60
void TESLandTexture::SetTextureSet(BGSTextureSet* apTextureSet) {
	pTextureSet = apTextureSet;
}

// GAME - 0x541570
HK_MATERIAL_TYPE TESLandTexture::GetHavokMaterialType() const {
#ifdef GAME
    return ThisCall<HK_MATERIAL_TYPE>(0x541570, this);
#else
    return static_cast<HK_MATERIAL_TYPE>(kHavokData.eMaterialType);
#endif
}

void TESLandTexture::SetHavokMaterialType(HK_MATERIAL_TYPE aeType) {
	kHavokData.eMaterialType = aeType;
}

float TESLandTexture::GetHavokFrictionValue() const {
	float fFriction = kHavokData.ucFriction / 100.f;
	if (fFriction > 1.f)
		fFriction = 1.f;

	return fFriction;
}

void TESLandTexture::SetHavokFrictionValue(float afFriction) {
	if (afFriction > 1.f)
		afFriction = 1.f;

	if (afFriction < 0.f)
		afFriction = 0.f;

	kHavokData.ucFriction = afFriction * 100.f;
}

float TESLandTexture::GetHavokRestitutionValue() const {
	float fRestitution = kHavokData.ucRestitution / 100.f;
	if (fRestitution > 1.99f)
		fRestitution = 1.99f;

	return fRestitution;
}

void TESLandTexture::SetHavokRestitutionValue(float afRestitution) {
	if (afRestitution > 1.99f)
		afRestitution = 1.99f;

	if (afRestitution < 0.f)
		afRestitution = 0.f;

	kHavokData.ucRestitution = afRestitution * 100.f;
}

// GAME - 0x541590
uint8_t TESLandTexture::GetSpecularExponent() const {
	return ucSpecularExponent;
}

void TESLandTexture::SetSpecularExponent(uint8_t aucVal) {
	ucSpecularExponent = aucVal;
}

// GAME - 0x891170
const BSSimpleList<TESGrass*>* TESLandTexture::GetGrassList() const {
	return &kGrass;
}

// GAME - 0x891170
BSSimpleList<TESGrass*>* TESLandTexture::GetGrassList() {
	return &kGrass;
}

void TESLandTexture::AddGrass(TESGrass* apGrass) {
	if (apGrass && !kGrass.IsInList(apGrass))
		kGrass.AddHead(apGrass);
}

void TESLandTexture::RemoveGrass(TESGrass* apGrass) {
	if (apGrass)
		kGrass.Remove(apGrass);
}
