#pragma once

#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "Gamebryo/NiPoint3.hpp"

class BGSDebris;

class TESEffectShader : public TESForm {
public:
	TESEffectShader();
	~TESEffectShader();

	struct ALIGN1 _EffectShaderFlags {
		enum Flags : uint8_t {
			DISABLE_TEXTURE_SHADER	= 1u << 0,
			// UNUSED				= 1u << 1,
			// UNUSED				= 1u << 2,
			DISABLE_PARTICLE_SHADER = 1u << 3,
			EDGE_COLOR_SUBTRACTIVE	= 1u << 4,
			SKIN_ONLY				= 1u << 5,
		};

		bool bDisableTextureShader	: 1;
		bool 						: 1;
		bool 						: 1;
		bool bDisableParticleShader : 1;
		bool bEdgeColorSubtractive	: 1;
		bool bSkinOnly				: 1;
	};
	using EffectShaderFlags = _EffectShaderFlags::Flags;

	struct Data {
		Bitfield<_EffectShaderFlags>	ucFlags;
		D3DBLEND						eTextureBlendModeSource;
		D3DBLENDOP						eTextureBlendOperation;
		D3DCMPFUNC						eTextureZTestFunction;
		uint32_t						uiFillColor;
		float							fFillAlphaFadeInTime;
		float							fFillAlphaFullTime;
		float							fFillAlphaFadeOutTime;
		float							fFillAlphaPersistentPercent;
		float							fFillAlphaPulseAmplitude;
		float							fFillAlphaPulseFrequency;
		float							fFillTextureUAnimSpeed;
		float							fFillTextureVAnimSpeed;
		float							fEdgeExponentValue;
		uint32_t						uiEdgeColor;
		float							fEdgeAlphaFadeInTime;
		float							fEdgeAlphaFullTime;
		float							fEdgeAlphaFadeOutTime;
		float							fEdgeAlphaPersistentPercent;
		float							fEdgeAlphaPulseAmplitude;
		float							fEdgeAlphaPulseFrequency;
		float							fFillAlphaFullPercent;
		float							fEdgeAlphaFullPercent;
		D3DBLEND						eTextureBlendModeDest;
		D3DBLEND						eParticleSourceBlendMode;
		D3DBLENDOP						eParticleBlendOp;
		D3DCMPFUNC						eParticleZTestFunc;
		D3DBLEND						eParticleDestBlendMode;
		float							fParticleFadeInTime;
		float							fParticleFullTime;
		float							fParticleFadeOutTime;
		float							fParticleFull;
		float							fParticlePersistent;
		float							fParticleLifetime;
		float							fParticleLifeVar;
		float							fParticleNormalSpeed;
		float							fParticleNormalAcc;
		NiPoint3						kParticleVelocity;
		NiPoint3						kParticleAcceleration;
		float							fParticleScale[2];
		float							fParticleScaleTime[2];
		uint32_t						uiParticleColor[3];
		float							fParticleColorAlpha[3];
		float							fParticleColorTime[3];
		float							fParticleNormalSpeedVar;
		float							fParticleRotate;
		float							fParticleRotateVar;
		float							fParticleRotateSpeed;
		float							fParticleRotateSpeedVar;
		BGSDebris*						pAddonModels;
		float							fAlphaTestStartTime;
		float							fAlphaTestEndTime;
		float							fAlphaTestStartValue;
		float							fAlphaTestEndValue;
		float							fAlphaEdgeWidth;
		uint32_t						uiAlphaEdgeColor;
		float							fExplosionWindSpeed;
		uint32_t						uiParticleTextureCountU;
		uint32_t						uiParticleTextureCountV;
		float							fAddonFadeInTime;
		float							fAddonFadeOutTime;
		float							fAddonScaleStart;
		float							fAddonScaleEnd;
		float							fAddonScaleInTime;
		float							fAddonScaleOutTime;
	};

	Data		kData;
	TESTexture	kFillTexture;
	TESTexture	kParticleTexture;
	TESTexture	kHolesTexture;

	TESFORM_TYPE(TESEffectShader);

	const Data* GetData() const;
	Data* GetData();

	BGSDebris* GetAddonModels() const;
	void SetAddonModels(BGSDebris* apModels);

	const TESTexture* GetFillTexture() const;
	TESTexture* GetFillTexture();
	void SetFillTexture(const char* apPath);

	const TESTexture* GetParticleTexture() const;
	TESTexture* GetParticleTexture();
	void SetParticleTexture(const char* apPath);

	const TESTexture* GetHolesTexture() const;
	TESTexture* GetHolesTexture();
	void SetHolesTexture(const char* apPath);
};

ASSERT_SIZE(TESEffectShader, 0x170);