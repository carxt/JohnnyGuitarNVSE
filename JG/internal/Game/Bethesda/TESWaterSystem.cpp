#include "TESWaterSystem.hpp"

#ifdef GAME
// GAME - 0x4E59F0
PlaceableWaterGroup* TESWaterSystem::FindWaterGroup(TESObjectREFR* apWaterRef, TESObjectREFR* apLookupRef, float afHeight) const {
    return ThisCall<PlaceableWaterGroup*>(0x4E59F0, this, apWaterRef, apLookupRef, afHeight);
}
#endif