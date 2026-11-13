#pragma once

#include "ActiveEffect.hpp"
#include "ActorValue.hpp"

class TESObjectREFR;

class ValueModifierEffect : public ActiveEffect {
public:
	ValueModifierEffect();
	~ValueModifierEffect();

	virtual void				SetActorValue(ActorValue::Index aeIndex);
	virtual ActorValue::Index	GetActorValue() const;
	virtual void				ModifyActorValue(Actor* apActor, float afValue, ActorValue::Index aeIndex);

	ActorValue::Index eActorValue;
};

ASSERT_SIZE(ValueModifierEffect, 0x4C);