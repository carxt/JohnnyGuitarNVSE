#include "GameProcess.h"

bool LowProcess::FindSpecialIdletoPlay(Actor* apActor, TESBoundObject* apObject, TESObjectREFR* apRef) {
	return ThisCall<bool>(0x8FF0B0, this, apActor, apObject, apRef);
}
