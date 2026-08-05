#include "BSAnimGroupSequence.hpp"

// GAME - 0x48F7F0
TESAnimGroup* BSAnimGroupSequence::GetAnimGroup() const {
    return spAnimGroup;
}

// GAME - 0x4EEC60
// GECK - 0x538F30
float BSAnimGroupSequence::GetScaledTime(float afTime) {
#ifdef GAME
	return ThisCall<float>(0x4EEC60, this, afTime);
#else
	return ThisCall<float>(0x538F30, this, afTime);
#endif
}

bool BSAnimGroupSequence::PlaySounds(NiControllerSequence* apSequence, TESObjectREFR* apRef) {
	return CdeclCall<bool>(0x4EEF00, apSequence, apRef);
}
