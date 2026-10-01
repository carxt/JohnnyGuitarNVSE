#include "EffectItemList.hpp"

// GAME - 0x405DA0
// GECK - 0x66E2A0
bool EffectItemList::CanBePoison() const {
#ifdef GAME
	return ThisCall<bool>(0x405DA0, this);
#else
	return ThisCall<bool>(0x66E2A0, this);
#endif
}

#ifdef GAME
// GAME - 0x405C00
float EffectItemList::GetEffectScore(EffectArchetypes::Type aeType, MagicSystem::Range aeRange, ActorValue::Index auiActorValue) const {
	return ThisCall<float>(0x405C00, this, aeType, aeRange, auiActorValue);
}

// GAME - 0x406620
void EffectItemList::GetEffectsString(char* apBuffer, uint32_t auiBufferSize) const {
	ThisCall(0x406620, this, apBuffer, auiBufferSize);
}
#endif