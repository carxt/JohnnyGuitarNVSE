#include "TESQuestTarget.hpp"

// GAME - 0x610190
bool TESQuestTarget::GetIgnoreLocks() const {
    return ucFlags.bIgnoreLocks;
}

void TESQuestTarget::SetIgnoreLocks(bool abVal) {
    ucFlags.bIgnoreLocks = abVal;
}

// GAME - 0x717E50
const TESCondition* TESQuestTarget::GetConditions() const {
    return &kConditions;
}

// GAME - 0x717E50
TESCondition* TESQuestTarget::GetConditions() {
    return &kConditions;
}

// GAME - 0x6101B0
TESObjectREFR* TESQuestTarget::GetReference(bool abAllowPickUpActor) const {
    return ThisCall<TESObjectREFR*>(0x6101B0, this, abAllowPickUpActor);
}

// GAME - 0x5CBB70
TESObjectREFR* TESQuestTarget::GetTrackingRef() const {
    return ThisCall<TESObjectREFR*>(0x5CBB70, this);
}

// GAME - 0x460140
const TeleportPath* TESQuestTarget::GetTargetPath() const {
    return &kTeleportPath;
}

// GAME - 0x460140
TeleportPath* TESQuestTarget::GetTargetPath() {
    return &kTeleportPath;
}
