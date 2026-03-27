#include "BGSPlaceableWater.hpp"

// GAME - 0x624700
BGSPlaceableWater::Data* BGSPlaceableWater::GetData() {
    return &kData;
}

// GAME - 0x589F50
void BGSPlaceableWater::SetWaterType(TESWaterForm* apWaterType) {
    kData.pWaterType = apWaterType;
}

// GAME - 0x452460
bool BGSPlaceableWater::GetFlag(uint32_t aeFlag) const {
	return kData.uiWaterFlags.Get(aeFlag);
}

// GAME - 0x4FC990
void BGSPlaceableWater::SetFlag(uint32_t aeFlag, bool abVal) {
	kData.uiWaterFlags.Set(aeFlag, abVal);
}

// GAME - 0x4E3C50
bool BGSPlaceableWater::GetReflectionEnabled() const {
	return kData.uiWaterFlags.bReflectionEnabled;
}

// GAME - 0x4FC360
void BGSPlaceableWater::SetReflectionEnabled(bool abVal) {
	kData.uiWaterFlags.bReflectionEnabled = abVal;
}

bool BGSPlaceableWater::GetReflectsActors() const {
	return kData.uiWaterFlags.bReflectsActors;
}

// GAME - 0x580540
void BGSPlaceableWater::SetReflectsActors(bool abVal) {
	kData.uiWaterFlags.bReflectsActors = abVal;
}

// GAME - 0x4EA8B0
bool BGSPlaceableWater::GetReflectsLand() const {
	return kData.uiWaterFlags.bReflectsLand;
}

// GAME - 0x4FC380
void BGSPlaceableWater::SetReflectsLand(bool abVal) {
	kData.uiWaterFlags.bReflectsLand = abVal;
}

// GAME - 0x4EA930
bool BGSPlaceableWater::GetReflectsSky() const {
	return kData.uiWaterFlags.bReflectsSky;
}

// GAME - 0x4FC3C0
void BGSPlaceableWater::SetReflectsSky(bool abVal) {
	kData.uiWaterFlags.bReflectsSky = abVal;
}

// GAME - 0x4EA8D0
bool BGSPlaceableWater::GetReflectsLODLand() const {
	return kData.uiWaterFlags.bReflectsLODLand;
}

// GAME - 0x4FC3A0
void BGSPlaceableWater::SetReflectsLODLand(bool abVal) {
	kData.uiWaterFlags.bReflectsLODLand = abVal;
}

// GAME - 0x4EA8F0
bool BGSPlaceableWater::GetReflectsLODBuildings() const {
	return kData.uiWaterFlags.bReflectsLODBuildings;
}

// GAME - 0x5802D0
void BGSPlaceableWater::SetReflectsLODBuildings(bool abVal) {
	kData.uiWaterFlags.bReflectsLODBuildings = abVal;
}

// GAME - 0x4EA910
bool BGSPlaceableWater::GetReflectsLODTrees() const {
	return kData.uiWaterFlags.bReflectsLODTrees;
}

// GAME - 0x5802F0
void BGSPlaceableWater::SetReflectsLODTrees(bool abVal) {
	kData.uiWaterFlags.bReflectsLODTrees = abVal;
}

bool BGSPlaceableWater::GetReflectsLOD() const {
	return GetFlag(WaterFlags::REFLECTS_LOD_LAND | WaterFlags::REFLECTS_LOD_TREES | WaterFlags::REFLECTS_LOD_BUILDINGS);
}

void BGSPlaceableWater::SetReflectrsLOD(bool abVal) {
	return SetFlag(WaterFlags::REFLECTS_LOD_LAND | WaterFlags::REFLECTS_LOD_TREES | WaterFlags::REFLECTS_LOD_BUILDINGS, abVal);
}

bool BGSPlaceableWater::GetReflectsNoReference() const {
	return kData.uiWaterFlags.bReflectsNoReference;
}

// GAME - 0x580560
void BGSPlaceableWater::SetReflectsNoReference(bool abVal) {
	kData.uiWaterFlags.bReflectsNoReference = abVal;
}

bool BGSPlaceableWater::GetReflectsDeadActors() const {
	return kData.uiWaterFlags.bReflectsDeadActors;
}

// GAME - 0x580580
void BGSPlaceableWater::SetReflectsDeadActors(bool abVal) {
	kData.uiWaterFlags.bReflectsDeadActors = abVal;
}

// GAME - 0x4E32C0
bool BGSPlaceableWater::GetLODWater() const {
	return kData.uiWaterFlags.bLODWater;
}

// GAME - 0x5805A0
void BGSPlaceableWater::SetLODWater(bool abVal) {
	kData.uiWaterFlags.bLODWater = abVal;
}

// GAME - 0x4E3280
bool BGSPlaceableWater::GetRefractionEnabled() const {
	return kData.uiWaterFlags.bRefractionEnabled;
}

// GAME - 0x4FC3E0
void BGSPlaceableWater::SetRefractionEnabled(bool abVal) {
	kData.uiWaterFlags.bRefractionEnabled = abVal;
}

// GAME - 0x4EC7E0
bool BGSPlaceableWater::GetRefractsActors() const {
	return kData.uiWaterFlags.bRefractsActors;
}

// GAME - 0x580310
void BGSPlaceableWater::SetRefractsActors(bool abVal) {
	kData.uiWaterFlags.bRefractsActors = abVal;
}

// GAME - 0x4E32A0
bool BGSPlaceableWater::GetRefractsLand() const {
	return kData.uiWaterFlags.bRefractsLand;
}

// GAME - 0x4FC400
void BGSPlaceableWater::SetRefractsLand(bool abVal) {
	kData.uiWaterFlags.bRefractsLand = abVal;
}

// GAME - 0x4E3300
bool BGSPlaceableWater::GetSilhouetteReflections() const {
	return kData.uiWaterFlags.bSilhouetteReflections;
}

void BGSPlaceableWater::SetSilhouetteReflections(bool abVal) {
	kData.uiWaterFlags.bSilhouetteReflections = abVal;
}

// GAME - 0x4E32E0
bool BGSPlaceableWater::GetDepthEnabled() const {
	return kData.uiWaterFlags.bEnableDepth;
}

// GAME - 0x4FC490
void BGSPlaceableWater::SetDepthEnabled(bool abVal) {
	kData.uiWaterFlags.bEnableDepth = abVal;
}

// GAME - 0x4E3CA0
bool BGSPlaceableWater::GetObjectTexCoordsEnabled() const {
	return kData.uiWaterFlags.bEnableObjectTexCoord;
}

// GAME - 0x4FC470
void BGSPlaceableWater::SetObjectTexCoordsEnabled(bool abVal) {
	kData.uiWaterFlags.bEnableObjectTexCoord = abVal;
}

// GAME - 0x452440
bool BGSPlaceableWater::GetAutomaticWater() const {
	return kData.uiWaterFlags.bAutoWater;
}

// GAME - 0x4FC450
void BGSPlaceableWater::SetAutomaticWater(bool abVal) {
	kData.uiWaterFlags.bAutoWater = abVal;
}

// GAME - 0x4E3C70
bool BGSPlaceableWater::GetUnderwaterFog() const {
	return kData.uiWaterFlags.bNoUnderwaterFog == false;
}

// GAME - 0x4FC420
void BGSPlaceableWater::SetUnderwaterFog(bool abVal) {
	kData.uiWaterFlags.bNoUnderwaterFog = !abVal;
}