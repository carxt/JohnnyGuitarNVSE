#pragma once

#include "Actor.hpp"

class TESCreature;

class Creature : public Actor {
public:
	Creature();
	~Creature();

	bool		bHasRagdoll;
	float		fArmorRating;
	float		fArmorThreshold;

	TESFORM_TYPE(Creature);

	TESCreature* GetActorBase() const;
};

ASSERT_SIZE(Creature, 0x1C0);
