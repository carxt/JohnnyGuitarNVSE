#include "TESForm.hpp"

#ifdef GAME
static FORM_ENUM_STRING* const pFormEnumStrings = reinterpret_cast<FORM_ENUM_STRING*>(0x1187000);
#else
static FORM_ENUM_STRING* const pFormEnumStrings = reinterpret_cast<FORM_ENUM_STRING*>(0xE94400);
#endif

// GAME - 0x84E3A0
uint32_t TESForm::GetFormID() const{
	return uiFormID;
}

// GAME - 0x401170
FORM_TYPE TESForm::GetFormType() const {
	return static_cast<FORM_TYPE>(eFormType);
}

uint8_t TESForm::GetCompileIndex() const {
	return uiFormID.GetIndex();
}

#ifndef GAME
// GECK - 0x4FB450
bool TESForm::SetFormEditorID(const char* apID) {
	return ThisCall<bool>(0x4FB450, apID);
}
#endif

// GAME - 0x4B1B60
// GECK - 0x523860
const char* TESForm::GetFormTypeName(uint32_t auiFormType) {
#ifdef GAME
	return CdeclCall<const char*>(0x4B1B60, auiFormType);
#else
	return CdeclCall<const char*>(0x523860, auiFormType);
#endif
}

const char* TESForm::GetFormTypeName() const {
	return GetFormTypeName(GetFormType());
}

const char* TESForm::GetFormTypeString(uint32_t auiFormType) {
	return pFormEnumStrings[auiFormType].pFormString;
}

const char* TESForm::GetFormTypeString() const {
	return GetFormTypeString(GetFormType());
}

// GAME - 0x460250
bool TESForm::GetMaster() const {
	return uiFormFlags.IsSet(FormFlags::MASTER);
}

// GAME - 0x4844F0
void TESForm::SetMaster(bool abVal) {
	uiFormFlags.Set(FormFlags::MASTER, abVal);
}

// GAME - 0x460340
bool TESForm::GetAltered() const {
	return uiFormFlags.IsSet(FormFlags::ALTERED);
}

// GAME - 0x4013E0
bool TESForm::GetInitialized() const {
	return uiFormFlags.IsSet(FormFlags::INITIALIZED);
}

// GAME - 0x484AB0
void TESForm::SetInitialized(bool abVal) {
	uiFormFlags.Set(FormFlags::INITIALIZED, abVal);
}

// GAME - 0x50D4A0
bool TESForm::GetNoCollision() const {
	return uiFormFlags.IsSet(FormFlags::NO_COLLISION);
}

// GAME - 0x693EF0
void TESForm::SetNoCollision(bool abVal) {
	uiFormFlags.Set(FormFlags::NO_COLLISION, abVal);
}

// GAME - 0x440D80
bool TESForm::GetDeleted() const {
	return uiFormFlags.IsSet(FormFlags::DELETED);
}

// GAME - 0x549580
bool TESForm::GetTreeLOD() const {
	assert(GetFormType() == FORM_TYPE::TESObjectTREE);
	return uiFormFlags.IsSet(FormFlags::TREE_LOD);
}

void TESForm::SetTreeLOD(bool abVal) {
	assert(GetFormType() == FORM_TYPE::TESObjectTREE);
	uiFormFlags.Set(FormFlags::TREE_LOD, abVal);
}

// GAME - 0x549580
bool TESForm::GetInPlaceableWater() const {
	assert(GetFormType() != FORM_TYPE::TESObjectDOOR);
	return uiFormFlags.IsSet(FormFlags::IN_PLACEABLE_WATER);
}

// GAME - 0x484A10
void TESForm::SetInPlaceableWater(bool abVal) {
	assert(GetFormType() != FORM_TYPE::TESObjectDOOR);
	uiFormFlags.Set(FormFlags::IN_PLACEABLE_WATER, abVal);
	AddChange(0x1);
}

// GAME - 0x549580
bool TESForm::GetBorderRegion() const {
	assert(GetFormType() == FORM_TYPE::TESRegion);
	return uiFormFlags.IsSet(FormFlags::BORDER_REGION);
}

void TESForm::SetBorderRegion(bool abVal) {
	assert(GetFormType() == FORM_TYPE::TESRegion);
	uiFormFlags.Set(FormFlags::BORDER_REGION, abVal);
}

// GAME - 0x448A20
bool TESForm::GetFireOff() const {
	return uiFormFlags.IsSet(FormFlags::FIRE_OFF);
}

// GAME - 0x484A70
void TESForm::SetFireOff(bool abVal) {
	uiFormFlags.Set(FormFlags::FIRE_OFF, abVal);
}

// GAME - 0x440DA0
bool TESForm::GetDisabled() const {
	assert(IsReference());
	return uiFormFlags.IsSet(FormFlags::DISABLED);
}

// GAME - 0x484AF0
void TESForm::SetDisabled(bool abVal) {
	assert(IsReference());
	uiFormFlags.Set(FormFlags::DISABLED, abVal);
	AddChange(0x1);
}

// GAME - 0x508D70
bool TESForm::GetEmpty() const {
	assert(GetFormType() == FORM_TYPE::TESFlora);
	return uiFormFlags.IsSet(FormFlags::EMPTY);
}

// GAME - 0x484580
// GECK - N/A
void TESForm::SetEmpty(bool abVal) {
#ifdef GAME
	assert(GetFormType() == FORM_TYPE::TESFlora);
	if (abVal) {
		AddChange(0x200000);
		uiFormFlags.Set(FormFlags::EMPTY);
	}
	else {
		RemoveChange(0x200000);
		uiFormFlags.Clear(FormFlags::EMPTY);
	}
#endif
}

// GAME - 0x508D70
bool TESForm::GetResetDestruct() const {
	return uiFormFlags.IsSet(FormFlags::RESET_DESTRUCT);
}

// GAME - 0x484610
void TESForm::SetResetDestruct(bool abVal) {
	uiFormFlags.Set(FormFlags::RESET_DESTRUCT, abVal);
}

// GAME - 0x508D70
bool TESForm::GetHasResults() const {
	assert(GetFormType() == FORM_TYPE::TESTopicInfo || GetFormType() == FORM_TYPE::TESTopic);
	return uiFormFlags.IsSet(FormFlags::HAS_RESULTS);
}

void TESForm::SetHasResults(bool abVal) {
	assert(GetFormType() == FORM_TYPE::TESTopicInfo || GetFormType() == FORM_TYPE::TESTopic);
	uiFormFlags.Set(FormFlags::HAS_RESULTS, abVal);
}

// GAME - 0x4077C0
bool TESForm::GetTemporary() const {
	return uiFormFlags.IsSet(FormFlags::TEMPORARY);
}

// GAME - 0x484490
// GECK - 0x4FBA50
void TESForm::SetTemporary() {
#ifdef GAME
	ThisCall(0x484490, this);
#else
	ThisCall(0x4FBA50, this);
#endif
}

// GAME - 0x564E40
bool TESForm::GetMustBeVisibleDistant() const {
	assert(!IsReference());
	return uiFormFlags.IsSet(FormFlags::VISIBLE_DISTANT);
}

void TESForm::SetMustBeVisibleDistant(bool abVal) {
	assert(!IsReference());
	uiFormFlags.Set(FormFlags::VISIBLE_DISTANT, abVal);
}

// GAME - 0x576D30
bool TESForm::IsStillLoading() const {
	return uiFormFlags.IsSet(FormFlags::STILL_LOADING);
}

// GAME - 0x46A010
void TESForm::SetStillLoading(bool abVal) {
	uiFormFlags.Set(FormFlags::STILL_LOADING, abVal);
}

bool TESForm::GetBeingDropped() const {
	assert(IsReference());
	return uiFormFlags.IsSet(FormFlags::BEING_DROPPED);
}

// GAME - 0x954910
void TESForm::SetBeingDropped(bool abVal) {
	assert(IsReference());
	uiFormFlags.Set(FormFlags::BEING_DROPPED, abVal);
}

// GAME - 0x477BA0
bool TESForm::GetDestroyed() const {
	assert(IsReference());	
	return uiFormFlags.IsSet(FormFlags::DESTROYED);
}

// GAME - 0x484650
void TESForm::SetDestroyed(bool abVal) {
	assert(IsReference());
	uiFormFlags.Set(FormFlags::DESTROYED, abVal);
	AddChange(0x1);
}

// GAME - 0x452370
bool TESForm::GetDestructible() const {
	assert(IsReference());
	return uiFormFlags.IsSet(FormFlags::DESTRUCTIBLE);
}

// GAME - 0x4846A0
void TESForm::SetDestructible(bool abVal) {
	assert(IsReference());
	uiFormFlags.Set(FormFlags::DESTRUCTIBLE, abVal);
}

// GAME - 0x401210
bool TESForm::GetNoAIAcquire() const {
	assert(IsReference());
	return uiFormFlags.IsSet(FormFlags::NO_AI_ACQUIRE);
}

void TESForm::SetNoAIAcquire(bool abVal) {
	assert(IsReference());
	uiFormFlags.Set(FormFlags::NO_AI_ACQUIRE, abVal);
}

// GAME - 0x5760E0
bool TESForm::GetVATSTarget() const {
	assert(IsReference());
	return uiFormFlags.IsSet(FormFlags::VATS_TARGET_OVERRIDE);
}

// GAME - 0x4846E0
void TESForm::SetVATSTarget(bool abVal) {
	assert(IsReference());
	uiFormFlags.Set(FormFlags::VATS_TARGET_OVERRIDE, abVal);
	AddChange(0x1);
}

// GAME - 0x56C760
bool TESForm::GetDisableFade() const {
	assert(IsReference());
	return uiFormFlags.IsSet(FormFlags::DISABLE_FADE);
}

// GAME - 0x56C780
void TESForm::SetDisableFade(bool abVal) {
	assert(IsReference());
	uiFormFlags.Set(FormFlags::DISABLE_FADE, abVal);
}

// GAME - 0x548700
bool TESForm::GetReflectedByAutoWater() const {
	assert(IsReference());
	return uiFormFlags.IsSet(FormFlags::REFLECTED_BY_AUTO_WATER);
}

void TESForm::SetReflectedByAutoWater(bool abVal) {
	assert(IsReference());
	uiFormFlags.Set(FormFlags::REFLECTED_BY_AUTO_WATER, abVal);
}

// GAME - 0x885A30
bool TESForm::GetRefractedByAutoWater() const {
	assert(IsReference());
	return uiFormFlags.IsSet(FormFlags::REFRACTED_BY_AUTO_WATER);
}

void TESForm::SetRefractedByAutoWater(bool abVal) {
	assert(IsReference());
	uiFormFlags.Set(FormFlags::REFRACTED_BY_AUTO_WATER, abVal);
}

// GAME - 0x885A30
bool TESForm::GetChildCanUse() const {
	assert(GetFormType() == FORM_TYPE::TESObjectACTI || GetFormType() == FORM_TYPE::TESFurniture || GetFormType() == FORM_TYPE::BGSIdleMarker);
	return uiFormFlags.IsSet(FormFlags::CHILD_CAN_USE);
}

void TESForm::SetChildCanUse(bool abVal) {
	assert(GetFormType() == FORM_TYPE::TESObjectACTI || GetFormType() == FORM_TYPE::TESFurniture || GetFormType() == FORM_TYPE::BGSIdleMarker);
	uiFormFlags.Set(FormFlags::CHILD_CAN_USE, abVal);
}

void TESForm::SetContinuousBroadcast(bool abVal) {
	assert(GetFormType() == FORM_TYPE::BGSTalkingActivator);
	uiFormFlags.Set(FormFlags::CONTINUOUS_BROADCAST, abVal);
}

// GAME - 0x484E60
// GECK - 0x4F9960
TESFile* TESForm::GetFile(int32_t aiIndex) const {
#ifdef GAME
	return ThisCall<TESFile*>(0x484E60, this, aiIndex);
#else
	return ThisCall<TESFile*>(0x4F9960, this, aiIndex);
#endif
}

// GAME - 0x484EE0
// GECK - 0x4F9990
TESFile* TESForm::GetOwnerMaster() const {
#ifdef GAME
	return ThisCall<TESFile*>(0x484EE0, this);
#else
	return ThisCall<TESFile*>(0x4F9990, this);
#endif
}

// GAME - 0x485BC0
uint32_t TESForm::GetFormIDWithoutIndex() const {
	return uiFormID.GetID();
}

// GAME - 0x5504E0
uint32_t TESForm::GetFileCount() const {
	return kFiles.ItemsInList();
}

// GAME - 0x4839C0
// GECK - 0x4F9620
TESForm* TESForm::GetFormByNumericID(uint32_t auID) {
#ifdef GAME
	return CdeclCall<TESForm*>(0x4839C0, auID);
#else
	return CdeclCall<TESForm*>(0x4F9620, auID);
#endif
}

// GAME - 0x483A00
// GECK - 0x4F9650
TESForm* TESForm::GetFormByEditorID(const char* apEDID) {
#ifdef GAME
	return CdeclCall<TESForm*>(0x483A00, apEDID);
#else
	return CdeclCall<TESForm*>(0x4F9650, apEDID);
#endif
}

const FORM_ENUM_STRING* TESForm::GetFormEnumString(uint8_t aucFormID) {
	return &pFormEnumStrings[aucFormID];
}

// GAME - 0x486890
// GECK - 0x4F8E80
uint32_t TESForm::GetFormTypeFromFormString(uint32_t auiFormString) {
#ifdef GAME
	return CdeclCall<uint32_t>(0x486890, auiFormString);
#else
	return CdeclCall<uint32_t>(0x4F8E80, auiFormString);
#endif
}