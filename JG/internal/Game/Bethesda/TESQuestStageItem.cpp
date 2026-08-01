#include "TESQuestStageItem.hpp"

// GAME - 0x60FD70
bool TESQuestStageItem::GetEndQuest() const {
    return kData.ucFlags.bEndQuest;
}

// GAME - 0x60FD90
bool TESQuestStageItem::GetFailQuest() const {
    return kData.ucFlags.bFailQuest;
}

// GAME - 0x717E50
const TESCondition* TESQuestStageItem::GetConditions() const {
    return &kConditions;
}

// GAME - 0x717E50
TESCondition* TESQuestStageItem::GetConditions() {
    return &kConditions;
}

// GAME - 0x48D150
const Script* TESQuestStageItem::GetResultScript() const {
    return &kScript;
}

// GAME - 0x48D150
Script* TESQuestStageItem::GetResultScript() {
    return &kScript;
}

// GAME - 0x5DC980
uint8_t TESQuestStageItem::GetIndex() const {
    return ucIndex;
}

// GAME - 0x60D4B0
void TESQuestStageItem::SetIndex(uint8_t aucIndex) {
    ucIndex = aucIndex;
}

bool TESQuestStageItem::GetHasLogEntry() const {
    return bHasLogEntry;
}

// GAME - 0x60D490
void TESQuestStageItem::SetHasLogEntry(bool abVal) {
    bHasLogEntry = abVal;
}

// GAME - 0x8D8520
Date* TESQuestStageItem::GetLogDate() const {
    return pLogDate;
}

// GAME - 0x407800
void TESQuestStageItem::SetLogDate(Date* apDate) {
    pLogDate = apDate;
}

// GAME - 0x5E3FA0
TESQuest* TESQuestStageItem::GetOwner() const {
    return pOwner;
}

// GAME - 0x4FD380
TESQuest* TESQuestStageItem::GetNextQuest() const {
    return pNextQuest;
}

// GAME - 0x57BD60
void TESQuestStageItem::SetNextQuest(TESQuest* apQuest) {
    pNextQuest = apQuest;
}

// GAME - 0x60FDB0
const char* TESQuestStageItem::GetLogEntry(TESForm* apOwner) {
    return ThisCall<const char*>(0x60FDB0, this, apOwner);
}
