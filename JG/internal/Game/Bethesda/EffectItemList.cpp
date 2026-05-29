#include "EffectItemList.hpp"

// GAME - 0x405DA0
bool EffectItemList::CanBePoison() const {
	return ThisCall<bool>(0x405DA0, this);
}

// GAME - 0x405C00
float EffectItemList::GetTotalEffect(uint32_t aeType, MagicSystem::Range aeRange, ActorValue::Index auiActorValue) const {
	return ThisCall<float>(0x405C00, this, aeType, aeRange, auiActorValue);
}

// GAME - 0x406620
void EffectItemList::GetEffectsString(char* apBuffer, uint32_t auiBufferSize) const {
	ThisCall(0x406620, this, apBuffer, auiBufferSize);
}
