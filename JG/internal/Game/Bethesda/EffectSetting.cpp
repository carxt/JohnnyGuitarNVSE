#include "EffectSetting.hpp"

// GAME - 0x58CBA0
bool EffectSetting::GetFlag(uint32_t auiFlag) const {
    return kData.uiFlags.Get(auiFlag);
}

// GAME - 0x407E00
void EffectSetting::SetFlag(uint32_t auiFlag, bool abVal) {
	kData.uiFlags.Set(auiFlag, abVal);
}

// GAME - 0x6286D0
Bitfield<EffectSetting::_EffectFlags> EffectSetting::GetFlags() const {
    return kData.uiFlags;
}

// GAME - 0x5A8060
void EffectSetting::SetFlags(uint32_t auiFlags) {
    kData.uiFlags = auiFlags;
}

// GAME - 0x810FD0
EffectArchetypes::Type EffectSetting::GetEffectArchetype() const {
    return kData.eArchetype;
}

// GAME - 0x4078A0
void EffectSetting::SetEffectArchetype(EffectArchetypes::Type aeType) {
	kData.eArchetype = aeType;
}

// GAME - 0x586150
ActorValue::Index EffectSetting::GetAssociatedActorValue() const {
    return kData.eAssociatedActorValue;
}

// GAME - 0x810570
void EffectSetting::SetAssociatedActorValue(ActorValue::Index aeActorValue) {
	kData.eAssociatedActorValue = aeActorValue;
}

// GAME - 0x4046B0
BSString EffectSetting::GetEffectName() const {
    return ThisCall<BSString>(0x4046B0, this);
}
