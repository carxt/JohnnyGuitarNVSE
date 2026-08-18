#pragma once
#include "GameObjects.h"

#include "Bethesda/ValueModifierEffect.hpp"

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