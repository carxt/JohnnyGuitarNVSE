#pragma once

#include "MagicHitEffect.hpp"
#include "BSShaderPPLightingProperty.hpp"
#include "BSSimpleArray.hpp"

class TESBoundObject;
class TESEffectShader;

class MagicShaderHitEffect : public MagicHitEffect {
public:
	MagicShaderHitEffect();
	~MagicShaderHitEffect();

	bool														bWeaponEnchantment;
	TESBoundObject*												pBoundObject;
	TESEffectShader*											pEffectShader;
	float														fAlphaTimer;
	BSSimpleArray<NiPointer<BSShaderProperty>>					kShaderProperties;
	NiPointer<NiNode>											spParticleNode;
	bool														b3rdPerson;
	BSSimpleArray<NiPointer<NiAVObject>>						kAddonObjects;
	float														fAddonAlpha;
	float														fAddonScale;
	NiPointer<BSShaderPPLightingProperty::TextureEffectData>	spTexEffectData;

	NIRTTI_ADDRESS(0x11DC804);
};

ASSERT_SIZE(MagicShaderHitEffect, 0x6C);