#include "TESRace.hpp"

// GAME - 0x6130C0
const TESRace::SkillBonus* TESRace::GetSkillBonus(uint32_t auiIndex) const {
	return &kData.kSkillBonus[auiIndex];
}

// GAME - 0x6130C0
TESRace::SkillBonus* TESRace::GetSkillBonus(uint32_t auiIndex) {
	return &kData.kSkillBonus[auiIndex];
}

// GAME - 0x604210
float TESRace::GetHeight(SEX aeSex) const {
	ASSUME_ASSERT(aeSex > SEX::NONE);
	if (aeSex < SEX::COUNT)
		return kData.fHeight[aeSex];
	return 0.0f;
}

void TESRace::SetHeight(SEX aeSex, float afVal) {
	ASSUME_ASSERT(aeSex > SEX::NONE);
	if (aeSex < SEX::COUNT)
		kData.fHeight[aeSex] = afVal;
}

// GAME - 0x6042D0
float TESRace::GetWeight(SEX aeSex) const {
	ASSUME_ASSERT(aeSex > SEX::NONE);
	if (aeSex < SEX::COUNT)
		return kData.fWeight[aeSex];
	return 0.0f;
}

void TESRace::SetWeight(SEX aeSex, float afVal) {
	ASSUME_ASSERT(aeSex > SEX::NONE);
	if (aeSex < SEX::COUNT)
		kData.fWeight[aeSex] = afVal;
}

// GAME - 0x59F610
bool TESRace::GetPlayable() const {
	return kData.uiFlags.bPlayable;
}

void TESRace::SetPlayable(bool abVal) {
	kData.uiFlags.bPlayable = abVal;
}

// GAME - 0x8D41F0
bool TESRace::GetChildRace() const {
	return kData.uiFlags.bChild;
}

void TESRace::SetChildRace(bool abVal) {
	kData.uiFlags.bChild = abVal;
}

// GAME - 0x4FADC0
const TESAttributes* TESRace::GetMaleAttributes() const {
	return &kAttributes[SEX::MALE];
}

// GAME - 0x4FADC0
TESAttributes* TESRace::GetMaleAttributes() {
	return &kAttributes[SEX::MALE];
}

// GAME - 0x6130E0
const TESAttributes* TESRace::GetFemaleAttributes() const {
	return &kAttributes[SEX::FEMALE];
}

// GAME - 0x6130E0
TESAttributes* TESRace::GetFemaleAttributes() {
	return &kAttributes[SEX::FEMALE];
}

// GAME - 0x45BB80
const BSSimpleList<TESHair*>* TESRace::GetHairList() const {
	return &kHairList;
}

// GAME - 0x45BB80
BSSimpleList<TESHair*>* TESRace::GetHairList() {
	return &kHairList;
}

// GAME - 0x613850
void TESRace::ClearHairList() {
	ThisCall(0x613850, this);
}

// GAME - 0x6137B0
TESHair* TESRace::GetRaceHair(uint32_t auiFormID) const {
	return ThisCall<TESHair*>(0x6137B0, this, auiFormID);
}

// GAME - 0x613810
void TESRace::AddHair(TESHair* apHair) {
	ThisCall(0x613810, this, apHair);
}

// GAME - 0x613870
TESHair* TESRace::GetDefaultHair(SEX aeSex) const {
	return pDefaultHair[aeSex];
}

// GAME - 0x613890
void TESRace::SetDefaultHair(SEX aeSex, TESHair* apHair) {
	pDefaultHair[aeSex] = apHair;
}

// GAME - 0x613100
uint8_t TESRace::GetDefaultHairColor(SEX aeSex) const {
	return ucDefaultHairColor[aeSex];
}

// GAME - 0x611E30
void TESRace::SetDefaultHairColor(SEX aeSex, uint8_t aucColor) {
	ucDefaultHairColor[aeSex] = aucColor;
}

// GAME - 0x613120
float TESRace::GetClampFaceGeoValue() const {
	return ThisCall<float>(0x613120, this);
}

void TESRace::SetClampFaceGeoValue(float afVal) {
	fClampFaceGeoValues[0] = afVal;
}

// GAME - 0x613160
float TESRace::GetClampFaceGeoValue2() const {
	return ThisCall<float>(0x613160, this);
}

void TESRace::SetClampFaceGeoValue2(float afVal) {
	fClampFaceGeoValues[1] = afVal;
}

// GAME - 0x503650
const BSSimpleList<TESEyes*>* TESRace::GetEyeColorList() const {
	return &kEyes;
}

// GAME - 0x503650
BSSimpleList<TESEyes*>* TESRace::GetEyeColorList() {
	return &kEyes;
}

// GAME - 0x613950
void TESRace::ClearEyeColorList() {
	ThisCall(0x613950, this);
}

// GAME - 0x6138B0
TESEyes* TESRace::GetRaceEyeColor(uint32_t auiFormID) const {
	return ThisCall<TESEyes*>(0x6138B0, this, auiFormID);
}

// GAME - 0x613910
void TESRace::AddEyeColor(TESEyes* apHair) {
	ThisCall(0x613910, this, apHair);
}

// GAME - 0x613970
TESModel* TESRace::GetHeadPartModel(SEX aeSex, HeadPart aePart) const {
	return ThisCall<TESModel*>(0x613970, this, aeSex, aePart);
}

// GAME - 0x6139B0
void TESRace::SetHeadPartModel(SEX aeSex, HeadPart aePart, const char* apPath) {
	ThisCall(0x6139B0, this, aeSex, aePart, apPath);
}

// GAME - 0x613B20
TESTexture* TESRace::GetHeadPartTexture(SEX aeSex, HeadPart aePart) const {
	return ThisCall<TESTexture*>(0x613B20, this, aeSex, aePart);
}

// GAME - 0x613B60
void TESRace::SetHeadPartTexture(SEX aeSex, HeadPart aePart, const char* apPath) {
	ThisCall(0x613B60, this, aeSex, apPath);
}

// GAME - 0x613BB0
TESTexture* TESRace::GetBodyPartTexture(SEX aeSex, BodyPart aePart) const {
	return ThisCall<TESTexture*>(0x613BB0, this, aeSex, aePart);
}

// GAME - 0x613C00
void TESRace::SetBodyPartTexture(SEX aeSex, BodyPart aePart, const char* apPath) {
	ThisCall(0x613C00, this, aeSex, aePart, apPath);
}

// GAME - 0x613A20
TESModel* TESRace::GetBodyPartModel(SEX aeSex, BodyPart aePart) const {
	return ThisCall<TESModel*>(0x613A20, this, aeSex, aePart);
}

// GAME - 0x613A60
void TESRace::GetBodyPartModel(SEX aeSex, BodyPart aePart, const char* apPath) {
	ThisCall(0x613A60, this, aeSex, aePart, apPath);
}

// GAME - 0x6131A0
BGSTextureModel* TESRace::GetBodyTextureModel(SEX aeSex) const {
	return ThisCall<BGSTextureModel*>(0x6131A0, this, aeSex);
}

// GAME - 0x613AD0
void TESRace::SetBodyTextureModel(SEX aeSex, const char* apPath) {
	ThisCall(0x613AD0, this, aeSex, apPath);
}

// GAME - 0x5D9FB0
const FaceGenCoords* TESRace::GetMeanFaceCoord(SEX aeSex) const {
	return ThisCall<FaceGenCoords*>(0x5D9FB0, this, aeSex);
}

// GAME - 0x5D9FB0
FaceGenCoords* TESRace::GetMeanFaceCoord(SEX aeSex) {
	return ThisCall<FaceGenCoords*>(0x5D9FB0, this, aeSex);
}

// GAME - 0x604780
BGSVoiceType* TESRace::GetDefaultVoiceType(SEX aeSex) const {
	return pDefaultVoiceType[aeSex];
}

// GAME - 0x610C70
void TESRace::SetDefaultVoiceType(SEX aeSex, BGSVoiceType* apVoice) {
	ThisCall(0x610C70, this, aeSex, apVoice);
}

// GAME - 0x5DA7F0
TESRace* TESRace::GetOlderRace() const {
	return pOldRace;
}

// GAME - 0x5DA7D0
TESRace* TESRace::GetYoungerRace() const {
	return pYoungRace;
}
