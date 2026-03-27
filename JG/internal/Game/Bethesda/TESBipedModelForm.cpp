#include "TESBipedModelForm.hpp"

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

bool TESBipedModelForm::GetIsAddonModel() const {
	return kData.ucFlags.bAddonModel;
}

// GAME - 0x480D50
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
bool TESBipedModelForm::FillsBipedSlot(BIPED_OBJECT aeSlot, bool abHair, BGSBipedModelList* apModelList) const {
	return ThisCall<bool>(0x480AF0, this, aeSlot, abHair, apModelList);
}

void TESBipedModelForm::SetFillsBipedSlot(BIPED_OBJECT aeSlot, bool abVal) {
	kData.uiObjectSlots.SetBit(aeSlot, abVal);
}

// GAME - 0x480CE0
const char* TESBipedModelForm::GetBipedConstraint() const {
	return kConstraintTemplate.GetModel();
}

// GAME - 0x4811E0
const char* TESBipedModelForm::GetBipedModel(SEX aeSex) const {
	return ThisCall<const char*>(0x4811E0, this, aeSex);
}

// GAME - 0x481150
TESModelTextureSwap* TESBipedModelForm::GetBipedTESModel(SEX aeSex) const {
	return ThisCall<TESModelTextureSwap*>(0x481150, this, aeSex);
}

// GAME - 0x481090
TESModelTextureSwap* TESBipedModelForm::GetBipedTESModel(TESForm* apForm, TESObjectREFR* apRef) {
	return CdeclCall<TESModelTextureSwap*>(0x481090, apForm, apRef);
}

// GAME - 0x481190
const char* TESBipedModelForm::GetWorldModel(SEX aeSex) const {
	return ThisCall<const char*>(0x481190, this, aeSex);
}

// GAME - 0x480E60
const char* TESBipedModelForm::GetWorldModel(TESForm* apForm, TESObjectREFR* apRef) {
	return CdeclCall<const char*>(0x480E60, apForm, apRef);
}

// GAME - 0x481110
TESModelTextureSwap* TESBipedModelForm::GetWorldTESModel(SEX aeSex) const {
	return ThisCall<TESModelTextureSwap*>(0x481110, this, aeSex);
}

// GAME - 0x481010
TESModelTextureSwap* TESBipedModelForm::GetWorldTESModel(TESForm* apForm, TESObjectREFR* apRef) {
	return CdeclCall<TESModelTextureSwap*>(0x481010, apForm, apRef);
}

// GAME - 0x481230
const char* TESBipedModelForm::GetIcon(SEX aeSex) const {
	return ThisCall<const char*>(0x481230, this, aeSex);
}

// GAME - 0x480EF0
const char* TESBipedModelForm::GetIcon(TESForm* apForm, TESObjectREFR* apRef) {
	return CdeclCall<const char*>(0x480EF0, apForm, apRef);
}

// GAME - 0x481280
const char* TESBipedModelForm::GetMessageIcon(SEX aeSex) const {
	return ThisCall<const char*>(0x481280, this, aeSex);
}

// GAME - 0x480F80
const char* TESBipedModelForm::GetMessageIcon(TESForm* apForm, TESObjectREFR* apRef) {
	return CdeclCall<const char*>(0x480F80, apForm, apRef);
}

// GAME - 0x480DB0
TESBipedModelForm* TESBipedModelForm::GetFormAsBipedModel(TESForm* apForm) {
	return CdeclCall<TESBipedModelForm*>(0x480DB0, apForm);
}
