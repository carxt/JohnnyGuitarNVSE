#pragma once

class TESForm;
class MagicItem;
class SpellItem;
class MagicTarget;
class MagicLight;
class ActiveEffect;
class EffectItem;
class TESBoundObject;
class TESObjectREFR;
class NiNode;

class MagicCaster {
public:
	MagicCaster();
	~MagicCaster();

	virtual void			CastAbility(SpellItem* apAbility, bool abLoadCast);
	virtual void			CastAddiction(SpellItem* apAddiction, bool abLoadCast);
	virtual void			CastRadiation(SpellItem* apRadiation, bool abLoadCast);
	virtual void			CastSpellImmediate(MagicItem* apMagicItem, bool, MagicTarget* apTarget, float afEffectivenessMult, bool abAdjustOnlyHostileEffectiveness);
	virtual void			TransferDisease(SpellItem* apDisease, MagicTarget* apTarget, bool a4);
	virtual void			CastWornEnchantment(MagicItem* apSpell, TESBoundObject* apSource, bool abLoadCast);
	virtual MagicTarget*	GetTouchTarget();
	virtual void			StartAim();
	virtual void			StartCast();
	virtual void			SpellCast(MagicItem* apSpell, bool);
	virtual bool			CheckCast(MagicItem* apSpell, float*, uint32_t* apReason, bool);
	virtual TESObjectREFR*	GetCasterStatsObject() const;
	virtual NiNode*			GetMagicNode() const;
	virtual MagicItem*		GetCurrentSpell() const;
	virtual bool			TargetSelf(ActiveEffect* apActiveEffect);
	virtual float			GetMagicEffectivenessModifier(bool, float);
	virtual void			SetCurrentSpell(MagicItem* apMagicItem);
	virtual MagicTarget*	GetDesiredTarget() const;
	virtual void			SetDesiredTarget(MagicTarget* apTarget);
	virtual ActiveEffect*	CreateActiveEffect(MagicItem* apMagicItem, EffectItem* apEffectItem, TESBoundObject* apObject);

	enum State {
		NO_SPELL			= 0,
		AIM					= 1,
		CAST				= 2,
		RELEASE				= 3,
		FIND_TARGETS		= 4,
		ERR_SPELL_DISABLED	= 5,
		ERR_ALREADY_CASTING = 6,
		ERR_CANNOT_CAST		= 7
	};

	MagicLight* pLight;
	State		eState;
};

ASSERT_SIZE(MagicCaster, 0x0C);