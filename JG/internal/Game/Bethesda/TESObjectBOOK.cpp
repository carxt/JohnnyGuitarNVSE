#include "TESObjectBOOK.hpp"

// GAME - 0x514FD0
ActorValue::Index TESObjectBOOK::GetTeaches() const {
    if (kData.eTeaches == ActorValue::Index::NONE)
        return ActorValue::Index::NONE;
    else
        return ActorValue::ToActorValue(ActorValue::Section::SKILL, kData.eTeaches);
}

void TESObjectBOOK::SetTeaches(ActorValue::Index aeIndex) {
    if (aeIndex == ActorValue::Index::NONE)
        kData.eTeaches = -1;
    else
        kData.eTeaches = ActorValue::ToArrayIndex(ActorValue::Section::SKILL, aeIndex);
}
