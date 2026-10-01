#pragma once

#include "BSSimpleList.hpp"

class Actor;
class TESBoundObject;
class TESObjectREFR;
class EffectItem;
class ActiveEffect;
class MagicCaster;
class MagicItem;

class MagicTarget {
public:
	MagicTarget();
	virtual bool							AddTarget(MagicCaster* apCaster, MagicItem* apItem, ActiveEffect* apEffect, bool);
	virtual TESObjectREFR*					GetTargetStatsObject() const;
	virtual BSSimpleList<ActiveEffect*>*	GetActiveEffectList() const;
	virtual bool							MagicTargetIsActor() const;
	virtual bool							IsInvulnerable() const;
	virtual void							EffectAdded(ActiveEffect* apEffect);
	virtual void							EffectRemoved(ActiveEffect* apEffect);
	virtual void							EffectAbsorbed(MagicCaster* apCaster, ActiveEffect* apEffect);
	virtual void							EffectReflected(MagicCaster* apCaster, ActiveEffect* apEffect);
	virtual float							CheckResistance(MagicCaster* apCaster, MagicItem* apItem, ActiveEffect* apEffect);
	virtual bool							CheckAbsorb(MagicCaster* apCaster, MagicItem* apItem, ActiveEffect* apEffect, bool);
	virtual bool							CheckReflect(MagicCaster* apCaster, MagicItem* apItem, ActiveEffect* apEffect);


	struct SpellDispelData {
		MagicItem*		pSpell;
		MagicCaster*	pCaster;
		ActiveEffect*	pActiveEffect;
	};

	bool							bShowTargetStats;
	bool							bUpdating;
	BSSimpleList<SpellDispelData*>	kPostUpdateDispelList;

	void Dispel(TESBoundObject* apEnchantmentSource, bool abNow);

	Actor* GetTargetAsActor() const;

	bool HasDamageHealthEffect() const;
};

ASSERT_SIZE(MagicTarget, 0x010);