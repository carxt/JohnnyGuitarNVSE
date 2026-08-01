#include "TESIdleForm.hpp"

// GAME - 0x436AA0
TESCondition* TESIdleForm::GetConditions() {
	return &kConditions;
}

// GAME - 0x436AA0
const TESCondition* TESIdleForm::GetConditions() const {
	return &kConditions;
}

// GAME - 0x5FF160
ANIM_GROUP_SECTION TESIdleForm::GetIdleAnimGroupSection() const {
    return static_cast<ANIM_GROUP_SECTION>(kData.ucAnimFlags.ucGroup);
}

// GAME - 0x5FF190
void TESIdleForm::SetIdleAnimGroupSection(ANIM_GROUP_SECTION aeSection) {
	kData.ucAnimFlags.ucGroup = static_cast<uint8_t>(aeSection);
}

// GAME - 0x5FF200
bool TESIdleForm::GetLooseIdle() const {
	return kData.ucAnimFlags.bLooseIdle;
}

// GAME - 0x5FF220
void TESIdleForm::SetLooseIdle(bool abVal) {
	kData.ucAnimFlags.bLooseIdle = abVal;
}

// GAME - 0x5FF1D0
bool TESIdleForm::GetAllowNoFile() const {
	return kData.ucAnimFlags.bAllowNoFile;
}

void TESIdleForm::SetAllowNoFile(bool abVal) {
	kData.ucAnimFlags.bAllowNoFile = abVal;
}

// GAME - 0x5FF770
uint8_t TESIdleForm::GetLoops() const {
	return ThisCall<uint8_t>(0x5FF770, this);
}

// GAME - 0x4D8A00
uint16_t TESIdleForm::GetReplayDelay() const {
	return kData.usReplayDelay;
}

// GAME - 0x5FF260
bool TESIdleForm::GetNoAttacking() const {
	return kData.ucFlags.bNoAttacking;
}

void TESIdleForm::SetNoAttacking(bool abVal) {
	kData.ucFlags.bNoAttacking = abVal;
}

// GAME - 0x8D6F30
NiFormArray* TESIdleForm::GetChildArray() {
	return pChildren;
}

// GAME - 0x8D6F30
const NiFormArray* TESIdleForm::GetChildArray() const {
	return pChildren;
}

// GAME - 0x5FF4A0
uint32_t TESIdleForm::GetChildCount() const {
	return ThisCall<uint32_t>(0x5FF4A0, this);
}

// GAME - 0x5FF4D0
TESIdleForm* TESIdleForm::GetChildByIndex(uint32_t auiIndex) const {
	return ThisCall<TESIdleForm*>(0x5FF4D0, this, auiIndex);
}

// GAME - 0x5FF520
uint32_t TESIdleForm::GetIndexForChild(TESIdleForm* apChild) const {
	return ThisCall<uint32_t>(0x5FF520, this, apChild);
}

// GAME - 0x5FF5D0
void TESIdleForm::RemoveChild(TESIdleForm* apChild) {
	ThisCall(0x5FF5D0, this, apChild);
}

// GAME - 0x5FF560
void TESIdleForm::RemoveChildAtIndex(uint32_t auiIndex) {
	ThisCall(0x5FF560, this, auiIndex);
}

// GAME - 0x8041A0
TESIdleForm* TESIdleForm::GetParentIdle() const {
	return pParentIdle;
}

// GAME - 0x8D8040
void TESIdleForm::SetParentIdle(TESIdleForm* apIdle) {
	pParentIdle = apIdle;
}

// GAME - 0x6733E0
TESIdleForm* TESIdleForm::GetPrevIdle() const {
	return pPrevIdle;
}

// GAME - 0x673400
void TESIdleForm::SetPrevIdle(TESIdleForm* apIdle) {
	pPrevIdle = apIdle;
}

// GAME - 0x5FF2E0
TESIdleForm* TESIdleForm::GetIdleToPlay(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef, BSSimpleList<IdleReplayDelay*>* apReplayDelays) const {
	return ThisCall<TESIdleForm*>(0x5FF2E0, this, apActionRef, apTargetRef, apReplayDelays);
}

// GAME - 0x5FF430
bool TESIdleForm::CheckConditions(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef, bool abRecurseUp) const {
	return ThisCall<bool>(0x5FF430, this, apActionRef, apTargetRef, abRecurseUp);
}
