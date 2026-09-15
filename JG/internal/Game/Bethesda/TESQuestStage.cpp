#include "TESQuestStage.hpp"

#ifdef EDITOR
TESQuest* TESQuestStage::GetOwnerQuest() const {
    return pOwner;
}
#endif

// GAME - 0x9373F0
uint8_t TESQuestStage::GetIndex() const {
    return kData.ucIndex;
}

// GAME - 0x5DC960
bool TESQuestStage::GetDone() const {
    return kData.bIsDone;
}

// GAME - 0x67FDB0
void TESQuestStage::SetDone(bool abVal) {
    kData.bIsDone = abVal;
}

#ifdef GAME
// GAME - 0x60F4A0
void TESQuestStage::SetDone(TESQuest* apQuest, bool abAllItems) {
    ThisCall(0x60F4A0, this, apQuest, abAllItems);
}
#endif

// GAME - 0x717E50
const BSSimpleList<TESQuestStageItem*>* TESQuestStage::GetStageItemList() const {
    return &kStageItems;
}

// GAME - 0x717E50
BSSimpleList<TESQuestStageItem*>* TESQuestStage::GetStageItemList() {
    return &kStageItems;
}

#ifdef GAME
// GAME - 0x60F2C0
TESQuestStageItem* TESQuestStage::GetStageItem(uint8_t aucIndex) const {
    return ThisCall<TESQuestStageItem*>(0x60F2C0, this, aucIndex);
}
#endif