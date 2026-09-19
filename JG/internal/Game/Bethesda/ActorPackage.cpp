#include "ActorPackage.hpp"

// GAME - 0x8C6080
void ActorPackage::InitFromPackage(TESPackage* apPackage, TESObjectREFR* apTarget) {
    ThisCall(0x8C6080, this, apPackage, apTarget);
}

// GAME - 0x559450
TESPackage* ActorPackage::GetTESPackage() const {
    return pPackage;
}

// GAME - 0x726070
ActorPackageData* ActorPackage::GetInstanceData() const {
    return pData;
}

// GAME - 0x6ECD40
void ActorPackage::SetInstanceData(ActorPackageData* apData) {
    pData = apData;
}

// GAME - 0x44DDC0
TESObjectREFR* ActorPackage::GetTarget() const {
    return pTarget;
}

// GAME - 0x403550
void ActorPackage::SetTarget(TESObjectREFR* apTarget) {
    pTarget = apTarget;
}

// GAME - 0x84E3A0
int32_t ActorPackage::GetCurrentProcedureIndex() const {
    return iCurrentProcedureIndex;
}

// GAME - 0x41FD00
void ActorPackage::SetCurrentProcedureIndex(int32_t aiIndex) {
    iCurrentProcedureIndex = aiIndex;
}

// GAME - 0x621B00
float ActorPackage::GetPackageStartTime() const {
    return fPackageStartTime;
}
