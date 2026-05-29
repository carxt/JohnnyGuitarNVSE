#pragma once

#include "EffectItem.hpp"
#include "BSSimpleList.hpp"
#include "ActorValue.hpp"

class Actor;

class EffectItemList : public BSSimpleList<EffectItem*> {
public:
	EffectItemList();
	~EffectItemList();

	virtual bool		IsMedicine() const;
	virtual bool		IsFood() const;
	virtual float		GetCost(Actor* apActor) const;
	virtual uint32_t	GetMaxEffectCount() const;
	virtual uint32_t	GetLevel() const;

	uint32_t uiHostileCount;

	bool CanBePoison() const;

	float GetTotalEffect(uint32_t aeType, MagicSystem::Range aeRange, ActorValue::Index auiActorValue) const;

	void GetEffectsString(char* apBuffer, uint32_t auiBufferSize) const;
};

ASSERT_SIZE(EffectItemList, 0x10);