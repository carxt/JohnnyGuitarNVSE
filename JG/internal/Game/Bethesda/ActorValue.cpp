#include "ActorValue.hpp"
#include "ActorValueInfo.hpp"

ActorValue* ActorValue::GetSingleton() {
#ifdef GAME
    return reinterpret_cast<ActorValue*>(0x11D61C8);
#else
    return reinterpret_cast<ActorValue*>(0xED20A8);
#endif
}

// GAME - 0x47F060
bool ActorValue::IsSkill(Index aeIndex) {
    return CdeclCall<bool>(0x47F060, aeIndex);
}

// GAME - 0x406D70
bool ActorValue::GetFlag(Index aeIndex, uint32_t auiFlag) {
    return CdeclCall<bool>(0x406D70, aeIndex, auiFlag);
}

// GAME - 0x66EC80
uint8_t ActorValue::ToArrayIndex(Section aeSection, Index aeIndex) {
	return CdeclCall<uint8_t>(0x66EC80, aeSection, aeIndex);
}

// GAME - 0x66EC10
ActorValue::Index ActorValue::ToActorValue(Section aeSection, uint8_t aeIndex) {
	return CdeclCall<Index>(0x66EC10, aeSection, aeIndex);
}

const char* ActorValue::GetActorValueName(ActorValue::Index aeIndex) {
    if (aeIndex >= Index::AGGRESSION && aeIndex < Index::COUNT)
        return GetSingleton()->pInfos[aeIndex]->pInfoName;
    return "Invalid";
}

// GAME - 0x66EE50
void ActorValue::CheckCallModifiedCallback(ActorValueOwner* apActor, Index aeIndex, float afOldVal, float afNewVal, ActorValueOwner* apActorSource) {
    CdeclCall(0x66EE50, apActor, aeIndex, afOldVal, afNewVal, apActorSource);
}
