#include "CreatureSounds.hpp"

// GAME - 0x5F0900
void CreatureSounds::AddCreatureSound(CREATURE_SOUND* apSound, CREATURE_SOUND_TYPE aeType) {
	ThisCall(0x5F0900, this, apSound, aeType);
}
