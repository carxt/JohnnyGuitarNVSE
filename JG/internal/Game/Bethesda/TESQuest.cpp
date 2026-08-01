#include "TESQuest.hpp"

// GAME - 0x5A8080
const TESQuest::Data& TESQuest::GetData() const {
	return kData;
}

// GAME - 0x5A8080
TESQuest::Data& TESQuest::GetData() {
	return kData;
}

// GAME - 0x5C3BD0
uint32_t TESQuest::GetPriority() const {
	return GetData().ucPriority;
}

// GAME - 0x792760
float TESQuest::GetScriptProcessingDelay() const {
	return kData.fQuestDelayTime;
}

// GAME - 0x444020
void TESQuest::SetScriptProcessingDelay(float afVal) {
	kData.fQuestDelayTime = afVal;
}

// GAME - 0x5D43C0
const BSSimpleList<TESQuestStage*>* TESQuest::GetStageList() const {
	return &kStages;
}

// GAME - 0x5D43C0
BSSimpleList<TESQuestStage*>* TESQuest::GetStageList() {
	return &kStages;
}

// GAME - 0x60DB40
TESQuestStage* TESQuest::GetStage(uint8_t aucIndex) const {
	return ThisCall<TESQuestStage*>(0x60DB40, this, aucIndex);
}

// GAME - 0x60D600
bool TESQuest::IsStageDone(uint8_t aucIndex) const {
	return ThisCall<bool>(0x60D600, this, aucIndex);
}

// GAME - 0x60F1A0
uint8_t TESQuest::GetStageIndexForStageItem(TESQuestStageItem* apItem) const {
	return ThisCall<uint8_t>(0x60F1A0, this, apItem);
}

// GAME - 0x5D43E0
const BSSimpleList<BGSQuestObjective*>* TESQuest::GetObjectiveList() const {
	return &kObjectives;
}

// GAME - 0x5D43E0
BSSimpleList<BGSQuestObjective*>* TESQuest::GetObjectiveList() {
	return &kObjectives;
}

// GAME - 0x60C8E0
BGSQuestObjective* TESQuest::GetObjective(uint32_t auiIndex) const {
	return ThisCall<BGSQuestObjective*>(0x60C8E0, this, auiIndex);
}

// GAME - 0x455620
bool TESQuest::GetEnabled() const {
	return GetData().ucFlags.bEnabled;
}

// GAME - 0x60C9C0
void TESQuest::SetEnabled(bool abVal) {
	ThisCall(0x60C9C0, this, abVal);
}

// GAME - 0x59E400
bool TESQuest::GetCompleted() const {
	return GetData().ucFlags.bCompleted;
}

// GAME - 0x60CA30
void TESQuest::SetCompleted(bool abVal) {
	ThisCall(0x60CA30, this, abVal);
}

// GAME - 0x61AF10
bool TESQuest::GetAllowRepeats() const {
	return GetData().ucFlags.bAllowRepeatedTopics;
}

void TESQuest::SetAllowRepeats(bool abVal) {
	GetData().ucFlags.bAllowRepeatedTopics = abVal;
}

// GAME - 0x60D5E0
bool TESQuest::GetAllowRepeatStages() const {
	return GetData().ucFlags.bAllowRepeatedStages;
}

void TESQuest::SetAllowRepeatStages(bool abVal) {
	GetData().ucFlags.bAllowRepeatedStages = abVal;
}

// GAME - 0x60D8D0
bool TESQuest::GetStartsEnabled() const {
	return GetData().ucFlags.bStartsEnabled;
}

// GAME - 0x60CD00
void TESQuest::SetStartsEnabled(bool abVal) {
	GetData().ucFlags.bStartsEnabled = abVal;
}

// GAME - 0x5EC6E0
bool TESQuest::GetDisplayedInHUD() const {
	return GetData().ucFlags.bDisplayedInHUD;
}

// GAME - 0x5EC700
void TESQuest::SetDisplayedInHUD(bool abVal) {
	GetData().ucFlags.bDisplayedInHUD = abVal;
}

// GAME - 0x77A590
bool TESQuest::GetFailed() const {
	return GetData().ucFlags.bFailed;
}

// GAME - 0x60CAF0
void TESQuest::SetFailed(bool abVal) {
	ThisCall(0x60CAF0, this, abVal);
}

// GAME - 0x5F5760
const TESCondition* TESQuest::GetConditions() const {
	return &kConditions;
}

// GAME - 0x5F5760
TESCondition* TESQuest::GetConditions() {
	return &kConditions;
}

// GAME - 0x59E300
ScriptLocals* TESQuest::GetScriptLocals() const {
	return pScriptLocals;
}

// GAME - 0x60D700
uint32_t TESQuest::GetCurrentStage() const {
	return ucCurrentStage;
}

// GAME - 0x60C950
void TESQuest::SetAllObjectivesComplete(bool abVal) {
	ThisCall(0x60C950, this, abVal);
}

// GAME - 0x60D720
void TESQuest::ResetQuest() {
	ThisCall(0x60D720, this);
}

// GAME - 0x60D4D0
void TESQuest::RunScript() {
	ThisCall(0x60D4D0, this);
}

// GAME - 0x60D8F0
void TESQuest::GetQuestLog(BSSimpleList<TESQuestStageItem*>* apListToFill, TESQuest* apQuest, bool abShowCompleted, bool abNewestFirst, bool abShowAll) {
	CdeclCall(0x60D8F0, apListToFill, apQuest, abShowCompleted, abNewestFirst, abShowAll);
}