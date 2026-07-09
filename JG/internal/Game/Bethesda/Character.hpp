#pragma once

#include "Actor.hpp"
#include "BipedAnim.hpp"

class TESObjectARMO;
class TESNPC;

class Character : public Actor {
public:
	Character();
	~Character();

	virtual void		InitiateCannibal(Actor* apTarget);
	virtual void		InitiateDisMountHorsePackage();

	BipedAnim*	pBipedAnim;
	float		fArmorRating;
	float		fArmorThreshold;
	bool		bIsTrespassing;
	bool		bIsGuard;
	float		fEquippedWeight;

	TESFORM_TYPE(Character);

	TESNPC* GetActorBase() const;
};

ASSERT_SIZE(Character, 0x1C8);