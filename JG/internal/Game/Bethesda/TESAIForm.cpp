#include "TESAIForm.hpp"

#ifdef EDITOR
static constexpr inline AddressPtr<float, 0xED54AC, 5> fConfidences;
#endif

// GAME - 0x4F1540
uint8_t TESAIForm::GetAggression() const {
	return kData.ucAgression;
}

// GAME - 0x47EE00
void TESAIForm::SetAggression(uint8_t aucVal, bool abAddChange) {
#ifdef GAME
	ThisCall(0x47EE00, this, aucVal, abAddChange);
#else
	kData.ucAgression = aucVal;
#endif
}

// GAME - 0x4F6DE0
uint8_t TESAIForm::GetConfidence() const {
	return kData.ucConfidence;
}

// GAME - 0x47EED0
void TESAIForm::SetConfidence(uint8_t aucVal, bool abAddChange) {
#ifdef GAME
	ThisCall(0x47EED0, this, aucVal, abAddChange);
#else
	kData.ucConfidence = aucVal;
#endif
}

float TESAIForm::GetConfidenceLevel() const {
	return GetConfidenceLevel(GetConfidence());
}

// GAME - 0x47EEB0
float TESAIForm::GetConfidenceLevel(uint8_t aucConfidence) {
#ifdef GAME
	return CdeclCall<float>(0x47EEB0, aucConfidence);
#else
	if (aucConfidence < 5)
		return fConfidences[aucConfidence];
	return 0.f;
#endif
}

// GAME - 0x5BB4D0
uint8_t TESAIForm::GetEnergy() const {
	return kData.ucEnergy;
}

// GAME - 0x47EF00
void TESAIForm::SetEnergy(uint8_t aucVal, bool abAddChange) {
#ifdef GAME
	ThisCall(0x47EF00, this, aucVal, abAddChange);
#else
	kData.ucEnergy = aucVal;
#endif
}

// GAME - 0x47EF30
uint8_t TESAIForm::GetResponsibility() const {
	return kData.ucResponsibility;
}

// GAME - 0x47EF50
void TESAIForm::SetResponsibility(uint8_t aucVal, bool abAddChange) {
#ifdef GAME
	ThisCall(0x47EF50, this, aucVal, abAddChange);
#else
	kData.ucResponsibility = aucVal;
#endif
}

// GAME - 0x62F2F0
uint8_t TESAIForm::GetMood() const {
	return kData.ucMood;
}

// GAME - 0x47EF80
void TESAIForm::SetMood(uint8_t aucVal, bool abAddChange) {
#ifdef GAME
	ThisCall(0x47EF80, this, aucVal, abAddChange);
#else
	if (aucVal < 8)
		kData.ucMood = aucVal;
#endif
}

// GAME - 0x84E3A0
uint32_t TESAIForm::GetServiceFlags() const {
	return kData.uiServiceFlags;
}

// GAME - 0x47EFE0
bool TESAIForm::GetOffersService(uint32_t auiServiceFlag) const {
#ifdef GAME
	return ThisCall<bool>(0x47EFE0, this, auiServiceFlag);
#else
	return kData.uiServiceFlags.Get(auiServiceFlag);
#endif
}

// GAME - 0x47EFB0
void TESAIForm::SetServiceFlags(uint32_t auiFlags, bool abAddChange) {
#ifdef GAME
	ThisCall(0x47EFB0, this, auiFlags, abAddChange);
#else
	kData.uiServiceFlags = auiFlags;
#endif
}

// GAME - 0x47F000
ActorValue::Index TESAIForm::GetTrainingSkill() const {
#ifdef GAME
	return ThisCall<ActorValue::Index>(0x47F000, this);
#else
	return ActorValue::ToActorValue(ActorValue::Section::SKILL, kData.ucTrainingSkill);
#endif
}

// GAME - 0x47F020
void TESAIForm::SetTrainingSkill(ActorValue::Index aeSkill) {
#ifdef GAME
	ThisCall(0x47F020, this, aeSkill);
#else
	if (ActorValue::IsSkill(aeSkill))
		kData.ucTrainingSkill = ActorValue::ToArrayIndex(ActorValue::Section::SKILL, aeSkill);
#endif
}

// GAME - 0x824060
uint8_t TESAIForm::GetTrainingSkillLevel() const {
	return kData.ucTrainingLevel;
}

// GAME - 0x47F090
void TESAIForm::SetTrainingSkillLevel(uint8_t aucLevel) {
#ifdef GAME
	ThisCall(0x47F090, this, aucLevel);
#else
	kData.ucTrainingLevel = aucLevel;
#endif
}

// GAME - 0x47EE30
uint8_t TESAIForm::GetAssistance() const {
	return kData.ucAssistance;
}

// GAME - 0x47EE50
void TESAIForm::SetAssistance(uint8_t aucVal) {
#ifdef GAME
	ThisCall(0x47EE50, this, aucVal);
#else
	kData.ucAssistance = aucVal;
#endif
}

// GAME - 0x705CF0
bool TESAIForm::GetHasAggroRadius() const {
	return kData.bAggroRadius;
}

// GAME - 0x47EE70
void TESAIForm::SetHasAggroRadius(bool abVal) {
#ifdef GAME
	ThisCall(0x47EE70, this, abVal);
#else
	kData.bAggroRadius = abVal;
#endif
}

// GAME - 0x825C00
uint32_t TESAIForm::GetAggroRadius() const {
	return kData.uiAggroRadius;
}

// GAME - 0x47EE90
void TESAIForm::SetAggroRadius(uint32_t auiRadius) {
#ifdef GAME
	ThisCall(0x47EE90, this, auiRadius);
#else
	kData.uiAggroRadius = auiRadius;
#endif
}

// GAME - 0x500940
const PackageList* TESAIForm::GetPackageList() const {
	return &kPackages;
}

// GAME - 0x500940
PackageList* TESAIForm::GetPackageList() {
	return &kPackages;
}

uint32_t TESAIForm::GetPackageCount() const {
	return kPackages.ItemsInList();
}

// GAME - 0x47F2D0
void TESAIForm::CopyAIPackageList(const TESAIForm* apSource) {
#ifdef GAME
	ThisCall(0x47F2D0, this, apSource);
#else
	GetPackageList()->Copy(apSource->GetPackageList());
#endif
}

#ifdef GAME
// GAME - 0x47F790
void TESAIForm::AddFormChange(uint32_t auiChangeFlags) {
	ThisCall(0x47F790, this, auiChangeFlags);
}

// GAME - 0x47F600
bool TESAIForm::SellBuysItem(const TESObject* apObject) const {
	return ThisCall<bool>(0x47F600, this, apObject);
}

// GAME - 0x47F520
TESPackage* TESAIForm::GetCurrentPackage(Actor* apActor) {
	return CdeclCall<TESPackage*>(0x47F520, apActor);
}

// GAME - 0x47F590
void TESAIForm::GetMissedPackages(Actor* apActor, BSSimpleList<TESPackage*>& arOut, float afStartDate, float afHour) {
	CdeclCall(0x47F590, apActor, &arOut, afStartDate, afHour);
}
#endif