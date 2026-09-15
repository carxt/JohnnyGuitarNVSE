#include "TESRegion.hpp"

// GAME - 0x9611E0
TESRegionDataList* TESRegion::GetRegionDataList() const {
    return pRegionDataList;
}

// GAME - 0x441110
BSSimpleList<TESRegionPointList*>* TESRegion::GetRegionPointLists() const {
    return pRegionPointLists;
}

// GAME - 0x7AF430
TESWorldSpace* TESRegion::GetWorldSpace() const {
    return pWorldSpace;
}

// GAME - 0x4F1260
// GECK - 0x539B40
void TESRegion::SetWorldSpace(TESWorldSpace* apWorldSpace) {
#ifdef GAME
    ThisCall(0x4F1260, this, apWorldSpace);
#else
    pWorldSpace = apWorldSpace;
#endif
}

// GAME - 0x59BB30
TESWeather* TESRegion::GetCurrentWeather() const {
    return pCurrentWeather;
}

// GAME - 0x7037C0
void TESRegion::SetCurrentWeather(TESWeather* apWeather) {
    pCurrentWeather = apWeather;
}

float TESRegion::GetLastWeatherUpdate() const {
    return fLastWeatherUpdate;
}

void TESRegion::SetLastWeatherUpdate(float afVal) {
    fLastWeatherUpdate = afVal;
}

// GAME - 0x4F1050
// GECK - 0x539B00
void TESRegion::UpdateWeather() {
#ifdef GAME
    ThisCall(0x4F1050, this);
#else
    ThisCall(0x539B00, this);
#endif
}
