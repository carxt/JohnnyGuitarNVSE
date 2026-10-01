#pragma once

#include "Bethesda/ValueModifierEffect.hpp"
#include "Bethesda/MagicHitEffect.hpp"

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