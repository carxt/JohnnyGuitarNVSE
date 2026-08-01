#include "BGSBodyPart.hpp"

// GAME - 0x7FA950
const char* BGSBodyPart::GetNodeName() const {
    return strNodeName.GetString();
}

void BGSBodyPart::SetNodeName(const char* apName) {
    strNodeName.Set(apName);
}

// GAME - 0x43B230
const char* BGSBodyPart::GetTargetName() const {
    return strTargetName.GetString();
}

void BGSBodyPart::SetTargetName(const char* apName) {
    strTargetName.Set(apName);
}

// GAME - 0x63D040
const char* BGSBodyPart::GetIKStartNodeName() const {
    return strIKStartNodeName.GetString();
}

void BGSBodyPart::SetIKStartNodeName(const char* apName) {
    strIKStartNodeName.Set(apName);
}

// GAME - 0x6838B0
const char* BGSBodyPart::GetPartName() const {
    return strPartName.GetString();
}

void BGSBodyPart::SetPartName(const char* apName) {
    strPartName.Set(apName);
}

// GAME - 0x8B6200
const char* BGSBodyPart::GetGoreObjectName() const {
    return strGoreObjectName.GetString();
}

void BGSBodyPart::SetGoreObjectName(const char* apName) {
    strGoreObjectName.Set(apName);
}

const char* BGSBodyPart::GetPoseMatchingModel() const {
    return kPoseMatchingModel.GetModel();
}

void BGSBodyPart::SetPoseMatchingModel(const char* apPath) {
    kPoseMatchingModel.SetModel(apPath);
}

// GAME - 0x8B5190
bool BGSBodyPart::IsSeverablePart() const {
    return kData.ucFlags.bSeverable;
}

// GAME - 0x5E5380
bool BGSBodyPart::HasIKData() const {
    return kData.ucFlags.bHasIK;
}

// GAME - 0x87E920
bool BGSBodyPart::IsIKBiped() const {
    return kData.ucFlags.bIKBipded;
}

// GAME - 0x8B4360
bool BGSBodyPart::IsExplodablePart() const {
    return kData.ucFlags.bExplodable;
}

// GAME - 0x87E940
bool BGSBodyPart::DoesHeadtracking() const {
    return kData.ucFlags.bHeadTracking;
}

// GAME - 0x8B4CD0
bool BGSBodyPart::IsExplodeChanceAbsolute() const {
    return kData.ucFlags.bExplodeChanceAbsolute;
}

// GAME - 0x5E5300
BODY_PART_TYPE BGSBodyPart::GetPartType() const {
    return static_cast<BODY_PART_TYPE>(kData.ucType);
}

// GAME - 0x5E5190
int8_t BGSBodyPart::GetActorValue() const {
    return kData.cActorValue;
}

// GAME - 0x5E4970
void BGSBodyPart::ShowLimb(LIMB_TYPE aeLimb, NiAVObject* apObject) {
    ThisCall(0x5E4970, this, aeLimb, apObject);
}

// GAME - 0x5E4890
void BGSBodyPart::UnhideLimb(LIMB_TYPE aeLimb, NiAVObject* apObject) {
    ThisCall(0x5E4890, this, aeLimb, apObject);
}
