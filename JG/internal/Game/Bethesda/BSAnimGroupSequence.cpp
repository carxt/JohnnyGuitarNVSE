#include "BSAnimGroupSequence.hpp"

// GAME - 0x48F7F0
TESAnimGroup* BSAnimGroupSequence::GetAnimGroup() const {
    return spAnimGroup;
}

// GAME - 0xA343C0
// GECK - 0x7DBFD0
void BSAnimGroupSequence::CopyMembers(BSAnimGroupSequence* apOther, NiCloningProcess* apCloning) {
#ifdef GAME
	ThisCall(0xA343C0, this, apOther, apCloning);
#else
	ThisCall(0x7DBFD0, this, apOther, apCloning);
#endif
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
