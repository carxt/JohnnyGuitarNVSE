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
#ifdef GAME
    return CdeclCall<bool>(0x47F060, aeIndex);
#else
    return aeIndex >= Index::BARTER && aeIndex < Index::INVENTORY_WEIGHT;
#endif
}

// GAME - 0x406D70
bool ActorValue::GetFlag(Index aeIndex, uint32_t auiFlag) {
#ifdef GAME
    return CdeclCall<bool>(0x406D70, aeIndex, auiFlag);
#else
    return GetSingleton()->pInfos[aeIndex]->uiAVFlags.Get(auiFlag);
#endif
}

// GAME - 0x66F190
// GECK - 0x491520
float ActorValue::ClampActorValue(Index aeIndex, float afValue) {
#ifdef GAME
    return CdeclCall<float>(0x66F190, aeIndex, afValue);
#else
    return CdeclCall<float>(0x491520, aeIndex, afValue);
#endif
}

// GAME - 0x66EC80
// GECK - 0x491400
uint8_t ActorValue::ToArrayIndex(Section aeSection, Index aeIndex) {
#ifdef GAME
	return CdeclCall<uint8_t>(0x66EC80, aeSection, aeIndex);
#else
	return CdeclCall<uint8_t>(0x491400, aeSection, aeIndex);
#endif
}

// GAME - 0x66EC10
// GECK - 0x4913A0
ActorValue::Index ActorValue::ToActorValue(Section aeSection, uint8_t aucIndex) {
#ifdef GAME
    return CdeclCall<Index>(0x66EC10, aeSection, aucIndex);
#else
	return CdeclCall<Index>(0x4913A0, aeSection, aucIndex);
#endif
}

// GAME - 0x66E920
// GECK - 0x4912C0
ActorValueInfo* ActorValue::GetActorValueInfo(Index aeIndex) {
#ifdef GAME
    return CdeclCall<ActorValueInfo*>(0x66E920, aeIndex);
#else
    return CdeclCall<ActorValueInfo*>(0x4912C0, aeIndex);
#endif
}

// GAME - 0x66E950
// GECK - 0x4918D0
const char* ActorValue::GetActorValueName(Index aeIndex) {
#ifdef GAME
    return CdeclCall<const char*>(0x66E950, aeIndex);
#else
    return CdeclCall<const char*>(0x4918D0, aeIndex);
#endif
}

// GAME - 0x66EAC0
// GECK - 0x4912E0
const char* ActorValue::GetActorValueScriptName(Index aeIndex) {
#ifdef GAME
    return CdeclCall<const char*>(0x66EAC0, aeIndex);
#else
    return CdeclCall<const char*>(0x4912E0, aeIndex);
#endif
}

#ifdef GAME
// GAME - 0x66EE50
void ActorValue::CheckCallModifiedCallback(ActorValueOwner* apActor, Index aeIndex, float afOldVal, float afNewVal, ActorValueOwner* apActorSource) {
    CdeclCall(0x66EE50, apActor, aeIndex, afOldVal, afNewVal, apActorSource);
}
#endif
