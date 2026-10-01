#include "TESRegionData.hpp"

// GAME - 0x4F1540
bool TESRegionData::GetOverride() const {
    return bOverride;
}

// GAME - 0x4F15A0
void TESRegionData::SetOverride(bool abOverride) {
    bOverride = abOverride;
}

// GAME - 0x4F6DE0
bool TESRegionData::GetIgnore() const {
    return bIgnore;
}

// GAME - 0x5BB4D0
uint8_t TESRegionData::GetPriority() const {
    return ucPriority;
}

// GAME - 0x4F15C0
bool TESRegionData::SetPriority(uint8_t aucPriority) {
#ifdef GAME
    return ThisCall<bool>(0x4F15C0, this, aucPriority);
#else
    if (aucPriority > 100)
        return false;

    ucPriority = aucPriority;
    return true;
#endif
}
