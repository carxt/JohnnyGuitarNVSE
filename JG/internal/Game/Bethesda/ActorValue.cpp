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
bool ActorValue::GetIsSkill(Index aeIndex) {
    return aeIndex >= Index::BARTER && aeIndex < Index::INVENTORY_WEIGHT;
}

// GAME - 0x406D70
bool ActorValue::GetFlag(Index aeIndex, uint32_t auiFlag) {
    return (GetSingleton()->pInfos[aeIndex]->uiAVFlags & auiFlag) != 0;
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
