#include "BGSCameraPath.hpp"

// GAME - 0x500940
const TESCondition* BGSCameraPath::GetConditions() const {
    return &kConditions;
}

// GAME - 0x500940
TESCondition* BGSCameraPath::GetConditions() {
    return &kConditions;
}

// GAME - 0x891170
const BSSimpleList<BGSCameraShot*>* BGSCameraPath::GetShotList() const {
    return &kShots;
}

// GAME - 0x891170
BSSimpleList<BGSCameraShot*>* BGSCameraPath::GetShotList() {
    return &kShots;
}

// GAME - 0x58B4D0
bool BGSCameraPath::GetZoomDisable() const {
    return kData.ucFlags.bZoomDisable;
}

void BGSCameraPath::SetZoomDisable() {
    kData.ucFlags.bZoomDisable = true;
    kData.ucFlags.bZoomShotList = false;
}

// GAME - 0x58B4F0
bool BGSCameraPath::GetZoomShotList() const {
    return kData.ucFlags.bZoomShotList;
}

void BGSCameraPath::SetZoomShotList() {
    kData.ucFlags.bZoomDisable = false;
    kData.ucFlags.bZoomShotList = true;
}

// GAME - 0x58B4A0
bool BGSCameraPath::GetZoomDefault() const {
#ifdef GAME
    return ThisCall<bool>(0x58B4A0, this);
#else
    return kData.ucFlags.IsClear(CameraPathFlags::ZOOM_DISABLE | CameraPathFlags::ZOOM_SHOT_LIST);
#endif
}

void BGSCameraPath::SetZoomDefault() {
    kData.ucFlags.Clear(CameraPathFlags::ZOOM_DISABLE | CameraPathFlags::ZOOM_SHOT_LIST);
}

// GAME - 0x58B470
bool BGSCameraPath::GetAllowNoShots() const {
    return kData.ucFlags.bAllowNoShots;
}

void BGSCameraPath::SetAllowNoShots(bool abVal) {
    kData.ucFlags.bAllowNoShots = abVal;
}

NiFormArray* BGSCameraPath::GetChildArray() const {
    return pChildPaths;
}

// GAME - 0x58B600
uint32_t BGSCameraPath::GetChildCount() const {
#ifdef GAME
    return ThisCall<uint32_t>(0x58B600, this);
#else
    return pChildPaths ? pChildPaths->GetSize() : 0;
#endif
}

// GAME - 0x58B630
// GECK - 0x5A5700
BGSCameraPath* BGSCameraPath::GetChildByIndex(uint32_t auiIndex) const {
#ifdef GAME
    return ThisCall<BGSCameraPath*>(0x58B630, this, auiIndex);
#else
    return ThisCall<BGSCameraPath*>(0x5A5700, this, auiIndex);
#endif
}

// GAME - 0x58B680
// GECK - 0x5A5730
uint32_t BGSCameraPath::GetIndexForChild(BGSCameraPath* apChild) const {
#ifdef GAME
    return ThisCall<uint32_t>(0x58B680, this, apChild);
#else
    return ThisCall<uint32_t>(0x5A5730, this, apChild);
#endif
}

// GAME - 0x58B730
void BGSCameraPath::RemoveChild(BGSCameraPath* apPath) {
#ifdef GAME
    ThisCall(0x58B730, this, apPath);
#else
    if (apPath && pChildPaths)
        RemoveChildAtIndex(GetIndexForChild(apPath));
#endif
}

// GAME - 0x58B6C0
// GECK - 0x5A6450
void BGSCameraPath::RemoveChildAtIndex(uint32_t auiIndex) {
#ifdef GAME
    ThisCall(0x58B6C0, this, auiIndex);
#else
    ThisCall(0x5A6450, this, auiIndex);
#endif
}

// GAME - 0x671D10
BGSCameraPath* BGSCameraPath::GetParentPath() const {
    return pParentPath;
}

// GAME - 0x5F36F0
BGSCameraPath* BGSCameraPath::GetPrevPath() const {
    return pPrevPath;
}

#ifdef GAME
// GAME - 0x58B510
BGSCameraPath* BGSCameraPath::GetCameraPathToPlay(TESObjectREFR* apActionRef, TESObjectREFR* apTargetRef) const {
    return ThisCall<BGSCameraPath*>(0x58B510, this, apActionRef, apTargetRef);
}
#endif