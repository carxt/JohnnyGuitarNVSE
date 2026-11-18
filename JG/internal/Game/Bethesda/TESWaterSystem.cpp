#include "TESWaterSystem.hpp"

#ifdef GAME
// GAME - 0x4E59F0
PlaceableWaterGroup* TESWaterSystem::FindWaterGroup(TESObjectREFR* apWaterRef, TESObjectREFR* apLookupRef, float afHeight) const {
    return ThisCall<PlaceableWaterGroup*>(0x4E59F0, this, apWaterRef, apLookupRef, afHeight);
}
#endif

// GAME - 0x4E46B0
// GECK - 0x536BD0
bool TESWaterSystem::AddPlaceableWater(TESObjectREFR* apWaterRef) {
#ifdef GAME
    return ThisCall<bool>(0x4E46B0, this, apWaterRef);
#else
    return ThisCall<bool>(0x536BD0, this, apWaterRef);
#endif
}

// GAME - 0x4E4730
// GECK - 0x536490
bool TESWaterSystem::AddPlaceableWater(TESObjectREFR* apWaterRef, const NiPoint3& arPos, const NiMatrix3& arRot) {
#ifdef GAME
    return ThisCall<bool>(0x4E4730, this, apWaterRef, &arPos, &arRot);
#else
    return ThisCall<bool>(0x536490, this, apWaterRef, &arPos, &arRot);
#endif
}

// GAME - 0x4E52F0
// GECK - 0x536C40
bool TESWaterSystem::RemovePlaceableWater(TESObjectREFR* apWaterRef) {
#ifdef GAME
    return ThisCall<bool>(0x4E52F0, this, apWaterRef);
#else
    return ThisCall<bool>(0x536C40, this, apWaterRef);
#endif
}

// GAME - 0x4E5370
// GECK - 0x536950
bool TESWaterSystem::RemovePlaceableWater(TESObjectREFR* apWaterRef, const NiPoint3& arPos, const NiMatrix3& arRot) {
#ifdef GAME
    return ThisCall<bool>(0x4E5370, this, apWaterRef, &arPos, &arRot);
#else
    return ThisCall<bool>(0x536950, this, apWaterRef, &arPos, &arRot);
#endif
}