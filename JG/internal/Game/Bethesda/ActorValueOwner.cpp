#include "ActorValueOwner.hpp"

// GAME - 0x66ED60
// GECK - 0x4914B0
bool ActorValueOwner::GetDerivedActorValue(ActorValueOwner* apOwner, ActorValue::Index aeIndex, float& arValue) {
#ifdef GAME
	return CdeclCall<bool>(0x66ED60, apOwner, aeIndex, &arValue);
#else
	return CdeclCall<bool>(0x4914B0, apOwner, aeIndex, &arValue);
#endif
}

// GAME - 0x66EF20
// GECK - 0x491D80
int32_t ActorValueOwner::GetClampedActorValueI(ActorValue::Index aeIndex) {
#ifdef GAME
	return ThisCall<int32_t>(0x66EF20, this, aeIndex);
#else
	return ThisCall<int32_t>(0x491D80, this, aeIndex);
#endif
}

// GAME - 0x66EF50
// GECK - 0x491920
float ActorValueOwner::GetClampedActorValueF(ActorValue::Index aeIndex) {
#ifdef GAME
	return ThisCall<float>(0x66EF50, this, aeIndex);
#else
	return ThisCall<float>(0x491920, this, aeIndex);
#endif
}
