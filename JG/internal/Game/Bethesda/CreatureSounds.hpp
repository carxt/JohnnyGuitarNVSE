#pragma once

#include "BSSimpleList.hpp"
#include "BSEnums.hpp"
#ifdef EDITOR
#include "BSStringT.hpp"
#endif

class TESSound;
class TESForm;

struct CreatureSound {
	TESSound*	pSound;
	uint8_t		ucChance;
};

class CreatureSounds {
public:
#ifdef EDITOR
	virtual bool Unk00(TESForm*, void*);
	virtual void Unk01(TESForm*, void*, BSString&);
#endif

	BSSimpleList<CreatureSound*>* pSoundLists[CREATURE_SOUND_TYPE::COUNT];

	void AddCreatureSound(CreatureSound* apSound, CREATURE_SOUND_TYPE aeType);
};

#ifdef GAME
ASSERT_SIZE(CreatureSounds, 0x58);
#else
ASSERT_SIZE(CreatureSounds, 0x5C);
#endif