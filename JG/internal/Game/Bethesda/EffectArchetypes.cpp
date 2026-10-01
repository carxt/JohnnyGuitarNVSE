#include "EffectArchetypes.hpp"

EffectArchetypes::ArchetypeDef* EffectArchetypes::GetArchetype(Type aeType) {
    return &(kArchetypes[aeType]);
}

// GAME - 0x403C80
bool EffectArchetypes::IsFlagSet(Type aeType, uint32_t auiFlag) {
    return GetArchetype(aeType)->uiFlags.Get(auiFlag);
}

// GAME - 0x408A60
const char* EffectArchetypes::GetArchetypeName(Type aeType) {
    return GetArchetype(aeType)->pName;
}
