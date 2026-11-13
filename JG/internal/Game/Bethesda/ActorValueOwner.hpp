#pragma once

#include "ActorValue.hpp"

class TESForm;

class ActorValueOwner {
public:
	virtual int32_t		GetBaseActorValueI(ActorValue::Index aeIndex);
	virtual float		GetBaseActorValueF(ActorValue::Index aeIndex);
	virtual int32_t		GetActorValueI(ActorValue::Index aeIndex);
	virtual float		GetActorValueF(ActorValue::Index aeIndex);
	virtual float		GetTemporaryModifier(ActorValue::Index aeIndex);
	virtual float		GetDamageModifier(ActorValue::Index aeIndex);
	virtual float		GetPermanentModifier(ActorValue::Index aeIndex);
	virtual int32_t		GetPermanentActorValueI(ActorValue::Index aeIndex);
	virtual float		GetPermanentActorValueF(ActorValue::Index aeIndex);
	virtual TESForm*	GetAsForm() const;
	virtual uint16_t	GetActorLevel() const;

	static bool GetDerivedActorValue(ActorValueOwner* apOwner, ActorValue::Index aeIndex, float& arValue);

	int32_t GetClampedActorValueI(ActorValue::Index aeIndex);
	float GetClampedActorValueF(ActorValue::Index aeIndex);
};

ASSERT_SIZE(ActorValueOwner, 0x4);