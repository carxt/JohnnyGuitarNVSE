#include "TESRace.hpp"
#ifdef EDITOR
#include "TESDataHandler.hpp"
#endif

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
#ifdef GAME
	ThisCall(0x613850, this);
#else
	GetHairList()->RemoveAll();
#endif
}

// GAME - 0x6137B0
// GECK - 0x584DB0
TESHair* TESRace::GetRaceHair(FormID auiFormID) const {
#ifdef GAME
	return ThisCall<TESHair*>(0x6137B0, this, auiFormID);
#else
	return ThisCall<TESHair*>(0x584DB0, this, auiFormID);
#endif
}

// GAME - 0x613810
// GECK - 0x585CA0
void TESRace::AddHair(TESHair* apHair) {
#ifdef GAME
	ThisCall(0x613810, this, apHair);
#else
	ThisCall(0x585CA0, this, apHair);
#endif
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
// GECK - 0x5840E0
float TESRace::GetClampFaceGeoValue() const {
#ifdef GAME
	return ThisCall<float>(0x613120, this);
#else
	return ThisCall<float>(0x5840E0, this);
#endif
}

void TESRace::SetClampFaceGeoValue(float afVal) {
	fClampFaceGeoValues[0] = afVal;
}

// GAME - 0x613160
// GECK - 0x584110
float TESRace::GetClampFaceGeoValue2() const {
#ifdef GAME
	return ThisCall<float>(0x613160, this);
#else
	return ThisCall<float>(0x584110, this);
#endif
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
#ifdef GAME
	ThisCall(0x613950, this);
#else
	GetEyeColorList()->RemoveAll();
#endif
}

// GAME - 0x6138B0
// GECK - 0x584DE0
TESEyes* TESRace::GetRaceEyeColor(FormID auiFormID) const {
#ifdef GAME
	return ThisCall<TESEyes*>(0x6138B0, this, auiFormID);
#else
	return ThisCall<TESEyes*>(0x584DE0, this, auiFormID);
#endif
}

// GAME - 0x613910
void TESRace::AddEyeColor(TESEyes* apEyes) {
#ifdef GAME
	ThisCall(0x613910, this, apEyes);
#else
	ThisCall(0x585CF0, this, apEyes);
#endif
}

// GAME - 0x613970
// GECK - 0x5844C0
const TESModel* TESRace::GetHeadPartModel(SEX aeSex, HeadPart aePart) const {
#ifdef GAME
	return ThisCall<TESModel*>(0x613970, this, aeSex, aePart);
#else
	return ThisCall<TESModel*>(0x5844C0, this, aeSex, aePart);
#endif
}

// GAME - 0x6139B0
void TESRace::SetHeadPartModel(SEX aeSex, HeadPart aePart, const char* apPath) {
#ifdef GAME
	ThisCall(0x6139B0, this, aeSex, aePart, apPath);
#else
	if (aeSex < SEX::COUNT && aePart < HeadPart::COUNT)
		kHeadModels[aeSex][aePart].SetModel(apPath);
#endif
}

// GAME - 0x613B20
// GECK - 0x584520
const TESTexture* TESRace::GetHeadPartTexture(SEX aeSex, HeadPart aePart) const {
#ifdef GAME
	return ThisCall<TESTexture*>(0x613B20, this, aeSex, aePart);
#else
	return ThisCall<TESTexture*>(0x584520, this, aeSex, aePart);
#endif
}

// GAME - 0x613B60
void TESRace::SetHeadPartTexture(SEX aeSex, HeadPart aePart, const char* apPath) {
#ifdef GAME
	ThisCall(0x613B60, this, aeSex, apPath);
#else
	if (aeSex < SEX::COUNT && aePart < HeadPart::COUNT)
		kHeadTextures[aeSex][aePart].SetTextureName(apPath);
#endif
}

// GAME - 0x613BB0
const TESTexture* TESRace::GetBodyPartTexture(SEX aeSex, BodyPart aePart) const {
#ifdef GAME
	return ThisCall<TESTexture*>(0x613BB0, this, aeSex, aePart);
#else
	if (aeSex < SEX::COUNT && aePart < BodyPart::COUNT)
		return &kBodyPartsTextures[aeSex][aePart];
	return nullptr;
#endif
}

// GAME - 0x613C00
void TESRace::SetBodyPartTexture(SEX aeSex, BodyPart aePart, const char* apPath) {
#ifdef GAME
	ThisCall(0x613C00, this, aeSex, aePart, apPath);
#else
	if (aeSex < SEX::COUNT && aePart < BodyPart::COUNT)
		kBodyPartsTextures[aeSex][aePart].SetTextureName(apPath);
#endif
}

// GAME - 0x613A20
// GECK - 0x5844F0
const TESModel* TESRace::GetBodyPartModel(SEX aeSex, BodyPart aePart) const {
#ifdef GAME
	return ThisCall<TESModel*>(0x613A20, this, aeSex, aePart);
#else
	return ThisCall<TESModel*>(0x5844F0, this, aeSex, aePart);
#endif
}

// GAME - 0x613A60
void TESRace::SetBodyPartModel(SEX aeSex, BodyPart aePart, const char* apPath) {
#ifdef GAME
	ThisCall(0x613A60, this, aeSex, aePart, apPath);
#else
	if (aeSex < SEX::COUNT && aePart < BodyPart::COUNT)
		kBodyModels[aeSex][aePart].SetModel(apPath);
#endif
}

// GAME - 0x6131A0
const BGSTextureModel* TESRace::GetBodyTextureModel(SEX aeSex) const {
#ifdef GAME
	return ThisCall<BGSTextureModel*>(0x6131A0, this, aeSex);
#else
	return &kBodyTexture[aeSex];
#endif
}

// GAME - 0x613AD0
void TESRace::SetBodyTextureModel(SEX aeSex, const char* apPath) {
#ifdef GAME
	ThisCall(0x613AD0, this, aeSex, apPath);
#else
	if (aeSex < SEX::COUNT)
		kBodyTexture[aeSex].SetModel(apPath);
#endif
}

// GAME - 0x5D9FB0
// GECK - 0x56F2A0
const FaceGenCoords* TESRace::GetMeanFaceCoord(SEX aeSex) const {
#ifdef GAME
	return ThisCall<FaceGenCoords*>(0x5D9FB0, this, aeSex);
#else
	return ThisCall<FaceGenCoords*>(0x56F2A0, this, aeSex);
#endif
}

// GAME - 0x5D9FB0
// GECK - 0x56F2A0
FaceGenCoords* TESRace::GetMeanFaceCoord(SEX aeSex) {
#ifdef GAME
	return ThisCall<FaceGenCoords*>(0x5D9FB0, this, aeSex);
#else
	return ThisCall<FaceGenCoords*>(0x56F2A0, this, aeSex);
#endif
}

// GAME - 0x604780
BGSVoiceType* TESRace::GetDefaultVoiceType(SEX aeSex) const {
	return pDefaultVoiceType[aeSex];
}

// GAME - 0x610C70
void TESRace::SetDefaultVoiceType(SEX aeSex, BGSVoiceType* apVoice) {
#ifdef GAME
	ThisCall(0x610C70, this, aeSex, apVoice);
#else
	if (apVoice) {
		pDefaultVoiceType[aeSex] = apVoice;
	}
	else {
		if (aeSex == SEX::MALE)
			pDefaultVoiceType[SEX::MALE] = const_cast<BGSVoiceType*>(pMaleVoice.Get());
			
		if (aeSex == SEX::FEMALE)
			pDefaultVoiceType[SEX::FEMALE] = const_cast<BGSVoiceType*>(pFemaleVoice.Get());
	}
#endif
}

// GAME - 0x5DA7F0
TESRace* TESRace::GetOlderRace() const {
	return pOldRace;
}

// GAME - 0x5DA7D0
TESRace* TESRace::GetYoungerRace() const {
	return pYoungRace;
}
