#include "TESBipedModelForm.hpp"
#ifndef GAME
#include <GameRTTI.h>
#include "TESObjectREFR.hpp"
#include "TESActorBase.hpp"
#endif

// GAME - 0x480D30
bool TESBipedModelForm::GetHasBackpack() const {
	return kData.ucFlags.bHasBackpack;
}

void TESBipedModelForm::SetHasBackpack(bool abVal) {
	kData.ucFlags.bHasBackpack = abVal;
}

// GAME - 0x514450
bool TESBipedModelForm::GetIsMediumArmor() const {
	return kData.ucFlags.bMediumArmor;
}

void TESBipedModelForm::SetIsMediumArmor(bool abVal) {
	kData.ucFlags.bMediumArmor = abVal;
}

// GECK - 0x4F2440
bool TESBipedModelForm::GetIsAddonModel() const {
	return kData.ucFlags.bAddonModel;
}

// GAME - 0x480D50
// GECK - 0x4F2450
void TESBipedModelForm::SetIsAddonModel(bool abVal) {
	kData.ucFlags.bAddonModel = abVal;
}

// GAME - 0x480D10
bool TESBipedModelForm::GetIsPowerArmor() const {
	return kData.ucFlags.bPowerArmor;
}

void TESBipedModelForm::SetIsPowerArmor(bool abVal) {
	kData.ucFlags.bPowerArmor = abVal;
}

// GAME - 0x480D90
// GECK - 0x4F2470
bool TESBipedModelForm::GetPlayable() const {
	return kData.ucFlags.bNonPlayable == false;
}

void TESBipedModelForm::SetPlayable(bool abVal) {
	kData.ucFlags.bNonPlayable = !abVal;
}

// GAME - 0x4C0BD0
bool TESBipedModelForm::GetIsHeavyArmor() const {
	return kData.ucFlags.bHeavyArmor;
}

void TESBipedModelForm::SetIsHeavyArmor(bool abVal) {
	kData.ucFlags.bHeavyArmor = abVal;
}

// GAME - 0x480AF0
// GECK - 0x4F29A0
bool TESBipedModelForm::FillsBipedSlot(BIPED_OBJECT aeSlot, bool abHair, BGSBipedModelList* apModelList) const {
#ifdef GAME
	return ThisCall<bool>(0x480AF0, this, aeSlot, abHair, apModelList);
#else
	return ThisCall<bool>(0x4F29A0, this, aeSlot, abHair, apModelList);
#endif
}

void TESBipedModelForm::SetFillsBipedSlot(BIPED_OBJECT aeSlot, bool abVal) {
	kData.uiObjectSlots.SetBit(aeSlot, abVal);
}

// GAME - 0x480AD0
// GECK - 0x4F23D0
bool TESBipedModelForm::FillsMatchingBipedSlots(const TESBipedModelForm* apOther) const {
	return apOther->kData.uiObjectSlots.IsSet(kData.uiObjectSlots);
}

// GAME - 0x480CE0
const char* TESBipedModelForm::GetBipedConstraint() const {
	return kConstraintTemplate.GetModel();
}

// GAME - 0x4811E0
const char* TESBipedModelForm::GetBipedModel(SEX aeSex) const {
#ifdef GAME
	return ThisCall<const char*>(0x4811E0, this, aeSex);
#else
	if (!kBipedModels[aeSex].GetModelLength() && aeSex == SEX::FEMALE)
		aeSex = SEX::MALE;

	return kBipedModels[aeSex].GetModel();
#endif
}

void TESBipedModelForm::SetBipedModel(SEX aeSex, const char* apPath) {
	kBipedModels[aeSex].SetModel(apPath);
}

// GAME - 0x481150
// GECK - 0x4F2BA0
TESModelTextureSwap* TESBipedModelForm::GetBipedTESModel(SEX aeSex) const {
#ifdef GAME
	return ThisCall<TESModelTextureSwap*>(0x481150, this, aeSex);
#else
	return ThisCall<TESModelTextureSwap*>(0x4F2BA0, this, aeSex);
#endif
}

// GAME - 0x481090
// GECK - 0x4F3510
TESModelTextureSwap* TESBipedModelForm::GetBipedTESModel(const TESForm* apForm, const TESObjectREFR* apRef) {
#ifdef GAME
	return CdeclCall<TESModelTextureSwap*>(0x481090, apForm, apRef);
#else
	return CdeclCall<TESModelTextureSwap*>(0x4F3510, apForm, apRef);
#endif
}

// GAME - 0x481190
// GECK - 0x4F2BF0
const char* TESBipedModelForm::GetWorldModel(SEX aeSex) const {
#ifdef GAME
	return ThisCall<const char*>(0x481190, this, aeSex);
#else
	return ThisCall<const char*>(0x4F2BF0, this, aeSex);
#endif
}

// GAME - 0x480E60
// GECK - 0x4F33F0
const char* TESBipedModelForm::GetWorldModel(const TESForm* apForm, const TESObjectREFR* apRef) {
#ifdef GAME
	return CdeclCall<const char*>(0x480E60, apForm, apRef);
#else
	return CdeclCall<const char*>(0x4F33F0, apForm, apRef);
#endif
}

void TESBipedModelForm::SetWorldModel(SEX aeSex, const char* apPath) {
	kWorldModels[aeSex].SetModel(apPath);
}

// GAME - 0x481110
// GECK - 0x4F2B50
TESModelTextureSwap* TESBipedModelForm::GetWorldTESModel(SEX aeSex) const {
#ifdef GAME
	return ThisCall<TESModelTextureSwap*>(0x481110, this, aeSex);
#else
	return ThisCall<TESModelTextureSwap*>(0x4F2B50, this, aeSex);
#endif
}

// GAME - 0x481010
// GECK - 0x4F34B0
TESModelTextureSwap* TESBipedModelForm::GetWorldTESModel(const TESForm* apForm, const TESObjectREFR* apRef) {
#ifdef GAME
	return CdeclCall<TESModelTextureSwap*>(0x481010, apForm, apRef);
#else
	return CdeclCall<TESModelTextureSwap*>(0x4F34B0, apForm, apRef);
#endif
}

// GAME - 0x481230
// GECK - 0x4F2C50
const char* TESBipedModelForm::GetIcon(SEX aeSex) const {
#ifdef GAME
	return ThisCall<const char*>(0x481230, this, aeSex);
#else
	return ThisCall<const char*>(0x4F2C50, this, aeSex);
#endif
}

// GAME - 0x480EF0
// GECK - 0x4F3450
const char* TESBipedModelForm::GetIcon(const TESForm* apForm, const TESObjectREFR* apRef) {
#ifdef GAME
	return CdeclCall<const char*>(0x480EF0, apForm, apRef);
#else
	return CdeclCall<const char*>(0x4F3450, apForm, apRef);
#endif
}

void TESBipedModelForm::SetIcon(SEX aeSex, const char* apPath) {
	kIcons[aeSex].SetTextureName(apPath);
}

// GAME - 0x481280
const char* TESBipedModelForm::GetMessageIcon(SEX aeSex) const {
#ifdef GAME
	return ThisCall<const char*>(0x481280, this, aeSex);
#else
	if (!kMessageIcons[aeSex].GetMessageIconTextureNameLength() && aeSex == SEX::FEMALE)
		aeSex = SEX::MALE;

	return kMessageIcons[aeSex].GetMessageIconTextureName();
#endif
}

// GAME - 0x480F80
const char* TESBipedModelForm::GetMessageIcon(const TESForm* apForm, const TESObjectREFR* apRef) {
#ifdef GAME
	return CdeclCall<const char*>(0x480F80, apForm, apRef);
#else
	TESBipedModelForm* pBiped = DYNAMIC_CAST(apForm, TESForm, TESBipedModelForm);
	if (!pBiped)
		return nullptr;

	if (!apRef)
		return pBiped->kMessageIcons[SEX::MALE].GetMessageIconTextureName();

	TESForm* pOwner = apRef->GetOwner();
	SEX eSex = SEX::MALE;
	if (pOwner  && pOwner->GetFormType() == FORM_TYPE::TESNPC)
		eSex = static_cast<TESActorBase*>(pOwner)->GetSex();

	return pBiped->GetMessageIcon(eSex);
#endif
}

void TESBipedModelForm::SetMessageIcon(SEX aeSex, const char* apPath) {
	kMessageIcons[aeSex].SetMessageIconTextureName(apPath);
}

// GAME - 0x480DB0
// GECK - 0x4F2480
TESBipedModelForm* TESBipedModelForm::GetFormAsBipedModel(const TESForm* apForm) {
#ifdef GAME
	return CdeclCall<TESBipedModelForm*>(0x480DB0, apForm);
#else
	return CdeclCall<TESBipedModelForm*>(0x4F2480, apForm);
#endif
}
