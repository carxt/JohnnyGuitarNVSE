#include "TESObjectBOOK.hpp"

// GAME - 0x409700
bool TESObjectBOOK::GetScroll() const {
    return kData.ucFlags.bScroll;
}

void TESObjectBOOK::SetScroll(bool abVal) {
    kData.ucFlags.bScroll = abVal;
}

// GAME - 0x73B460
bool TESObjectBOOK::GetCantTake() const {
    return kData.ucFlags.bCantTake;
}

void TESObjectBOOK::SetCantTake(bool abVal) {
    kData.ucFlags.bCantTake = abVal;
}

// GAME - 0x514FD0
// GECK - 0x5F7190
ActorValue::Index TESObjectBOOK::GetTeaches() const {
#ifdef GAME
    return ThisCall<ActorValue::Index>(0x514FD0, this);
#else
    return ThisCall<ActorValue::Index>(0x5F7190, this);
#endif
}

// GECK - 0x5F7300 - Inlined
void TESObjectBOOK::SetTeaches(ActorValue::Index aeIndex) {
    if (aeIndex == ActorValue::Index::NONE)
        kData.eTeaches = -1;
    else
        kData.eTeaches = ActorValue::ToArrayIndex(ActorValue::Section::SKILL, aeIndex);
}

// GAME - 0x73B430
const char* TESObjectBOOK::GetText() const {
#ifdef GAME
    return ThisCall<const char*>(0x73B430, this);
#else
    return GetDescription(nullptr, 'CSED');
#endif
}

#ifdef GAME
// GAME - 0x515040
bool TESObjectBOOK::Read(TESObjectREFR* apReader) {
    return ThisCall<bool>(0x515040, this, apReader);
}
#endif