#pragma once

#include "BSRenderedTexture.hpp"
#include "Gamebryo/NiColor.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "Gamebryo/NiPoint4.hpp"
#include "Gamebryo/NiTexture.hpp"
#include "TESAttackDamageForm.hpp"
#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESTexture.hpp"

class TESSound;
class SpellItem;
class BGSPlaceableWater;

struct WaterShaderData {
	float		fWindVelocity;
	float		fWindDirection;
	float		fWaveAmplitude;
	float		fWaveFrequency;
	float		fSunPower;
	float		fReflectionAmount;
	float		fFresnelAmount;
	float		fWaveSpeed;
	float		fFogDistNear;
	float		fFogDistFar;
	uint32_t	uiShallowColor;
	uint32_t	uiDeepColor;
	uint32_t	uiReflectionColor;
	uint8_t		ucBlend;
	float		fRainForce;
	float		fRainVelocity;
	float		fRainFalloff;
	float		fRainDampener;
	float		fDisplacementStartingSize;
	float		fDisplacementForce;
	float		fDisplacementVelocity;
	float		fDisplacementFalloff;
	float		fDisplacementDampener;
	float		fRainStartingSize;
	float		fNoiseScale;
	float		fWindDirections[3];
	float		fWindSpeeds[3];
	float		fDepthFalloffStart;
	float		fDepthFalloffEnd;
	float		fFogScale;
	float		fNoiseUVScale;
	float		fUnderwaterFogScale;
	float		fUnderwaterFogNear;
	float		fUnderwaterFogFar;
	float		fDistortionAmount;
	float		fShininess;
	float		fHDRMult;
	float		fLightRadius;
	float		fLightBrightness;
	float		fUVScales[3];
	float		fAmplitudeScales[3];
};

ASSERT_SIZE(WaterShaderData, 0xC4);

class TESWaterForm : public TESForm, public TESFullName, public TESAttackDamageForm {
public:
	TESWaterForm();
	~TESWaterForm();

	struct ALIGN1 _WaterFlags {
		enum Flags : uint8_t {
			CAUSES_DAMAGE	= 1u << 0,
			REFLECTIVE		= 1u << 1,
		};

		bool bCausesDamage	: 1;
		bool bReflective	: 1;
	};
	using WaterFlags = _WaterFlags::Flags;

	bool					bNeedUpdate;
	BSRenderedTexturePtr	spNoiseNormalMap;
	NiPoint4				kTexScrolls[3];
	TESTexture				kNoiseTexture;
	uint8_t					ucAlpha;
	Bitfield<_WaterFlags>	ucFlags;
	BSString				strMaterialID;
	TESSound*				pWaterSound;
	TESWaterForm*			pRemappedWaterForm;
	WaterShaderData			kShaderData;
	TESWaterForm*			pWaterWeatherControl[3];
	int32_t					iCurrentTextureSelect01;
	int32_t					iCurrentTextureSelect02;
	uint32_t				uiFrequencyX;
	uint32_t				uiFrequencyY;
	int32_t					iOctaves;
	float					fAmplitude;
	float					fLacunarity;
	float					fBias;
	float					fGain;
	SpellItem*				pConsumeSpell;
	NiTexturePtr			spNoiseTexture;
	BGSPlaceableWater*		pPlaceableAutoWater;
	BGSPlaceableWater*		pPlaceableLODWater;
	uint32_t				uiRadiationDamage;
	uint32_t				uiHealthDamage;
	bool					bResetNoiseTextures;

	TESFORM_TYPE(TESWaterForm);

	const char* GetNoiseTextureName() const;
	void SetNoiseTextureName(const char* apTexture);
	uint32_t GetNoiseTextureNameLength() const;

	void GetNoiseTexture(NiTexturePtr& arTexture);
	void SetNoiseTexture(NiTexture* apTexture);

	TESSound* GetWaterSound() const;
	void SetWaterSound(TESSound* apSound);

	SpellItem* GetSpellItem() const;
	void GetSpellItem(SpellItem* apSpell);

	const char* GetMaterialName() const;
	void SetMaterialName(const char* apMaterial);

	[[nodiscard]] BGSPlaceableWater* GetPlaceableAutoWater();
	[[nodiscard]] BGSPlaceableWater* GetPlaceableLODWater();
};

ASSERT_SIZE(TESWaterForm, 0x194);