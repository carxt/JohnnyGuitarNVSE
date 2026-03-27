#include "ActorValueOwner.hpp"

#ifdef GAME
// GAME - 0x66ED60
// GECK - N/A
bool ActorValueOwner::GetDerivedActorValue(ActorValueOwner* apOwner, ActorValue::Index aeIndex, float& arVal) {
	return CdeclCall<bool>(0x66ED60, apOwner, aeIndex, &arVal);
}

// GAME - 0x66EF20
int32_t ActorValueOwner::GetClampedActorValueI(ActorValue::Index aeIndex) {
	return ThisCall<int32_t>(0x66EF20, this, aeIndex);
}

// GAME - 0x66EF50
float ActorValueOwner::GetClampedActorValueF(ActorValue::Index aeIndex) {
	return ThisCall<float>(0x66EF50, this, aeIndex);
}
#endif
