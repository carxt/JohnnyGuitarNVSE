#include "BGSQuestObjective.hpp"

// GAME - 0x82751830
bool BGSQuestObjective::GetCompleted() const {
    return eState > State::DISPLAYED;
}

// GAME - 0x5A5E70
bool BGSQuestObjective::GetDisplayed() const {
    return eState & State::DISPLAYED;
}

// GAME - 0x726070
uint32_t BGSQuestObjective::GetIndex() const {
    return uiIndex;
}

// GAME - 0x5EC330
const char* BGSQuestObjective::GetDisplayText() const {
    return ThisCall<const char*>(0x5EC330, this);
}

// GAME - 0x5EC440
void BGSQuestObjective::SetDisplayText(const char* apText) {
    ThisCall(0x5EC330, this, apText);
}

// GAME - 0x5EC310
uint32_t BGSQuestObjective::GetDisplayTextLength() const {
    return ThisCall<uint32_t>(0x5EC310, this);
}

// GAME - 0x44EDB0
TESQuest* BGSQuestObjective::GetOwner() const {
    return pOwnerQuest;
}

// GAME - 0x437730
void BGSQuestObjective::SetOwner(TESQuest* apOwner) {
    pOwnerQuest = apOwner;
}

// GAME - 0x7D6BB0
const BSSimpleList<TESQuestTarget*>* BGSQuestObjective::GetTargetList() const {
    return &kTargets;
}

// GAME - 0x7D6BB0
BSSimpleList<TESQuestTarget*>* BGSQuestObjective::GetTargetList() {
    return &kTargets;
}

// GAME - 0x7AF430
BGSQuestObjective::State BGSQuestObjective::GetState() const {
    return eState;
}

// GAME - 0x5EC5D0
void BGSQuestObjective::SetState(State aeState) {
    ThisCall(0x5EC5D0, this, aeState);
}

// GAME - 0x50F9C0
void BGSQuestObjective::SetStateSimple(State aeState) {
    eState = aeState;
}

// GAME - 0x7737A0
bool BGSQuestObjective::CheckState(State aeState) const {
    return eState & aeState;
}

// GAME - 0x5EC500
void BGSQuestObjective::UpdateCurrentTargetList(BSSimpleList<TESQuestTarget*>* apListToFill) {
    ThisCall(0x5EC500, this, apListToFill);
}
