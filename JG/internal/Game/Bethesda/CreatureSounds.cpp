#include "CreatureSounds.hpp"

// GAME - 0x5F0900
// GECK - 0x55D1D0
void CreatureSounds::AddCreatureSound(CreatureSound* apSound, CREATURE_SOUND_TYPE aeType) {
#ifdef GAME
	ThisCall(0x5F0900, this, apSound, aeType);
#else
	ThisCall(0x55D1D0, this, apSound, aeType);
#endif
}
