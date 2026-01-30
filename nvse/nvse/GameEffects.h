#pragma once
#include "GameObjects.h"
// 48
class ActiveEffect {
public:
	ActiveEffect();
	virtual ~ActiveEffect();

	virtual ActiveEffect* Clone(void);
	virtual void			Unk_02(uint32_t arg);
	virtual void			Unk_03(uint32_t arg);
	virtual void			SaveGame(uint32_t arg);
	virtual void			LoadGame(uint32_t arg);
	virtual void			Unk_06(uint32_t arg);
	virtual void			Unk_07(uint32_t arg);
	virtual void			Unk_08(uint32_t arg);
	virtual bool			UnregisterCaster(MagicCaster* _caster);	// returns 1 and clears caster if it matches the parameter, else returns 0
	virtual bool			Unk_0A(void);
	virtual void			CopyTo(ActiveEffect* _target);
	virtual bool			Unk_0C(uint32_t arg);
	virtual bool			Unk_0D(uint32_t arg);
	virtual void			Unk_0E(uint32_t arg);		// update/add effect?
	virtual void			Terminate(void);	// update/add effect?
	virtual void			Unk_10(uint32_t arg);
	virtual void			Unk_11(uint32_t arg);
	virtual void			Unk_12(uint32_t arg);
	virtual void			Unk_13(uint32_t arg);
	virtual void			Unk_14(void);
	virtual void			Unk_15(void);
	virtual void			Unk_16(void);

	float			timeElapsed;		// 04
	MagicItem*		magicItem;			// 08
	EffectItem*		effectItem;		// 0C
	bool			bActive;			// 10
	bool			bApplied;		// 11 set to 1 when effect is to be removed
	bool			byte12;			// 12
	bool			bTerminated;				// 13
	uint32_t			unk14;				// 14
	uint32_t			unk18;				// 18
	float			magnitude;			// 1C - adjusted based on target?
	float			duration;			// 20 - adjusted based on target?
	MagicTarget*	target;			// 24
	MagicCaster*	caster;			// 28
	uint32_t			spellType;			// 2C e.g. SpellItem::kType_Ability
	uint32_t			unk30;				// 30
	uint32_t			unk34;				// 34
	uint32_t			unk38;				// 38
	TESForm* enchantObject;		// 3C enchanted obj responsible for effect
	TESForm* data;				// 40 - in ScriptEffect this is a Script *
	uint32_t			unk44;				// 44

	__forceinline void Remove(bool immediate) {
		ThisCall(0x804210, this, immediate);
	}
};

// 4C
class ValueModifierEffect : public ActiveEffect {
public:
	ValueModifierEffect();
	~ValueModifierEffect();

	virtual void	Unk_17(void);
	virtual void	Unk_18(void);
	virtual void	Unk_19(void);

	uint32_t		actorVal;
};

// 50
class ScriptEffect : public ActiveEffect {
public:
	ScriptEffect();
	~ScriptEffect();

	uint32_t		unk48[2];	// 48
};

// 48
class DispelEffect : public ActiveEffect {
public:
	DispelEffect();
	~DispelEffect();

	virtual void	Unk_17(void);
};

// 50
class CureEffect : public ActiveEffect {
public:
	CureEffect();
	~CureEffect();

	virtual void	Unk_17(void);

	uint32_t		unk48[2];	// 48
};

// 5C
class AbsorbEffect : public ValueModifierEffect {
public:
	AbsorbEffect();
	~AbsorbEffect();

	virtual void	Unk_1A(void);

	uint32_t		unk4C[4];	// 4C
};

// 50
class ShieldEffect : public ValueModifierEffect {
public:
	ShieldEffect();
	~ShieldEffect();

	virtual void	Unk_1A(void);

	uint32_t		unk4C;	// 4C
};

// 4C
class CalmEffect : public ValueModifierEffect {
public:
	CalmEffect();
	~CalmEffect();

	virtual void	Unk_1A(void);
};

// 4C
class DemoralizeEffect : public ActiveEffect {
public:
	DemoralizeEffect();
	~DemoralizeEffect();

	virtual void	Unk_17(void);

	uint32_t		unk48;	// 48
};

// 50
class FrenzyEffect : public ValueModifierEffect {
public:
	FrenzyEffect();
	~FrenzyEffect();

	virtual void	Unk_1A(void);

	uint32_t		unk4C;	// 4C
};

// 48
class CommandEffect : public ActiveEffect {
public:
	CommandEffect();
	~CommandEffect();

	virtual void	Unk_17(void);
};

// 48
class CommandCreatureEffect : public CommandEffect {
public:
	CommandCreatureEffect();
	~CommandCreatureEffect();
};

// 48
class CommandHumanoidEffect : public CommandEffect {
public:
	CommandHumanoidEffect();
	~CommandHumanoidEffect();
};

// 4C
class InvisibilityEffect : public ValueModifierEffect {
public:
	InvisibilityEffect();
	~InvisibilityEffect();

	virtual void	Unk_1A(void);
};

// 4C
class ChameleonEffect : public ValueModifierEffect {
public:
	ChameleonEffect();
	~ChameleonEffect();

	virtual void	Unk_1A(void);
};

// 4C
class LightEffect : public ActiveEffect {
public:
	LightEffect();
	~LightEffect();

	uint32_t		unk48;	// 48
};

// 4C
class DarknessEffect : public ValueModifierEffect {
public:
	DarknessEffect();
	~DarknessEffect();

	virtual void	Unk_1A(void);
};

// 4C
class NightEyeEffect : public ValueModifierEffect {
public:
	NightEyeEffect();
	~NightEyeEffect();

	virtual void	Unk_1A(void);
};

// 48
class LockEffect : public ActiveEffect {
public:
	LockEffect();
	~LockEffect();

	virtual void	Unk_17(void);
};

// 48
class OpenEffect : public ActiveEffect {
public:
	OpenEffect();
	~OpenEffect();

	virtual void	Unk_17(void);
};

// 4C
class AssociatedItemEffect : public ActiveEffect {
public:
	AssociatedItemEffect();
	~AssociatedItemEffect();

	virtual void	Unk_17(void);

	TESObject* item;	// 48 - creature, armor, weapon
};

// AC
class BoundItemEffect : public AssociatedItemEffect {
public:
	BoundItemEffect();
	~BoundItemEffect();

	uint32_t		unk48[24];	// 4C
};

// 74
class SummonCreatureEffect : public AssociatedItemEffect {
public:
	SummonCreatureEffect();
	~SummonCreatureEffect();

	uint32_t		unk48[10];	// 4C
};

// 4C
class DetectLifeEffect : public ValueModifierEffect {
public:
	DetectLifeEffect();
	~DetectLifeEffect();

	virtual void	Unk_1A(void);
};

// 60
class TelekinesisEffect : public ValueModifierEffect {
public:
	TelekinesisEffect();
	~TelekinesisEffect();

	virtual void	Unk_1A(void);

	uint32_t		unk4C[5];	// 4C
};

// 4C
class DisintegrateArmorEffect : public ActiveEffect {
public:
	DisintegrateArmorEffect();
	~DisintegrateArmorEffect();

	uint32_t		unk48;	// 48
};

// 48
class DisintegrateWeaponEffect : public ActiveEffect {
public:
	DisintegrateWeaponEffect();
	~DisintegrateWeaponEffect();
};

// 4C
class ParalysisEffect : public ValueModifierEffect {
public:
	ParalysisEffect();
	~ParalysisEffect();

	virtual void	Unk_1A(void);
};

// 70
class ReanimateEffect : public ActiveEffect {
public:
	ReanimateEffect();
	~ReanimateEffect();

	uint32_t		unk48[10];	// 48
};

// 4C
class TurnUndeadEffect : public ActiveEffect {
public:
	TurnUndeadEffect();
	~TurnUndeadEffect();

	virtual void	Unk_17(void);

	uint32_t		unk48;	// 48
};

// 50
class SunDamageEffect : public ActiveEffect {
public:
	SunDamageEffect();
	~SunDamageEffect();

	virtual void	Unk_17(void);

	uint32_t		unk48[2];	// 48
};

// 48
class VampirismEffect : public ActiveEffect {
public:
	VampirismEffect();
	~VampirismEffect();

	virtual void	Unk_17(void);
};

// 4C
class ConcussionEffect : public ActiveEffect {
public:
	ConcussionEffect();
	~ConcussionEffect();

	float	unk48;		//  48
};

// 50
class ValueAndConditionsEffect : public ValueModifierEffect {
public:
	ValueAndConditionsEffect();
	~ValueAndConditionsEffect();

	virtual void	Unk_1A(void);

	uint32_t		unk4C;	// 4C
};

// 50
class LimbConditionEffect : public ValueModifierEffect {
public:
	LimbConditionEffect();
	~LimbConditionEffect();

	virtual void	Unk_1A(void);

	uint32_t		unk4C;	// 4C
};

// 18
class BSTempEffect : public NiObject {
public:
	BSTempEffect();
	~BSTempEffect();

	virtual void	Unk_23(void);
	virtual void	Unk_24(void);
	virtual void	Unk_25(void);
	virtual void	Unk_26(void);
	virtual void	Unk_27(void);
	virtual void	Unk_28(void);
	virtual void	Unk_29(void);
	virtual void	Unk_2A(void);
	virtual void	Unk_2B(void);
	virtual void	Unk_2C(void);
	virtual void	Unk_2D(void);
	virtual void	Unk_2E(void);
	virtual void	Unk_2F(void);
	virtual void	Unk_30(void);

	float			duration;	// 08
	TESObjectCELL* cell;		// 0C
	float			age;		// 10
	bool			initialized;// 14
	uint8_t			pad15[3];	// 15
};

// 28
class MagicHitEffect : public BSTempEffect {
public:
	MagicHitEffect();
	~MagicHitEffect();

	virtual void	Unk_31(void);
	virtual void	Unk_32(void);
	virtual void	Unk_33(void);
	virtual void	Unk_34(void);
	virtual void	Unk_35(void);
	virtual void	Unk_36(void);
	virtual void	Unk_37(void);
	virtual void	Unk_38(void);

	ActiveEffect* activeEffect;	// 18
	TESObjectREFR* target;		// 1C
	float			timeElapsed;			// 20
	uint8_t			flags;			// 24	1 - Stop
	uint8_t			pad25[3];		// 25
};

// 6C
class MagicShaderHitEffect : public MagicHitEffect {
public:
	MagicShaderHitEffect();
	~MagicShaderHitEffect();

	uint32_t									unk28[2];		// 28
	TESEffectShader* effectShader;	// 30
	float									timeElapsed;	// 34
	BSSimpleArray<ParticleShaderProperty>	shaderProps;	// 38
	NiNode* shaderNode;	// 48
	uint32_t									unk4C;			// 4C
	BSSimpleArray<NiAVObject>				objects;		// 50	Seen BSFadeNode
	float									flt60;			// 60
	float									flt64;			// 64
	NiProperty* prop68;		// 68	Seen 0x10AE0C8
};
static_assert(sizeof(MagicShaderHitEffect) == 0x6C);