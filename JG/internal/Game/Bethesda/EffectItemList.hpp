#pragma once

#include "ActorValue.hpp"
#include "BSSimpleList.hpp"
#include "EffectArchetypes.hpp"
#include "EffectItem.hpp"
#ifdef EDITOR
#include "EffectSetting.hpp"
#endif

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
#ifdef EDITOR
	EffectSetting kSetting;
#endif

	bool CanBePoison() const;

#ifdef GAME
	float GetEffectScore(EffectArchetypes::Type aeType, MagicSystem::Range aeRange, ActorValue::Index auiActorValue) const;

	void GetEffectsString(char* apBuffer, uint32_t auiBufferSize) const;
#endif
};

#ifdef GAME
ASSERT_SIZE(EffectItemList, 0x10);
#else
ASSERT_SIZE(EffectItemList, 0xF0);
#endif