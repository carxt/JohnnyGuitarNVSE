#pragma once

#include "BSSimpleList.hpp"
#include "BSEnums.hpp"

class TESSound;

struct CREATURE_SOUND {
	TESSound*	pSound;
	uint8_t		ucChance;
};

class CreatureSounds {
public:
	BSSimpleList<CREATURE_SOUND*>* pSoundLists[CREATURE_SOUND_TYPE::COUNT];

	void AddCreatureSound(CREATURE_SOUND* apSound, CREATURE_SOUND_TYPE aeType);
};