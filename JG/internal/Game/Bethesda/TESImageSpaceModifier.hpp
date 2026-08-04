#pragma once

#include "TESForm.hpp"
#include "Gamebryo/NiFloatInterpolator.hpp"
#include "Gamebryo/NiColorInterpolator.hpp"
#include "Gamebryo/NiPoint2.hpp"

class TESSound;

class TESImageSpaceModifier : public TESForm {
public:
	TESImageSpaceModifier();
	~TESImageSpaceModifier();

	enum {
		EYE_ADAPT_SPEED = 0,
		BLUR_RADIUS,
		EMISSIVE_MULT,
		TARGET_LUM,
		UPPER_LUM_CLAMP,
		BRIGHT_SCALE,
		BRIGHT_CLAMP,
		LUM_RAMP_NO_TEX,
		LUM_RAMP_MIN,
		LUM_RAMP_MAX,
		SUNLIGHT,
		GRASS_DIMMER,
		TREE_DIMMER,
		SKIN_DIMMER,
		BLOOM_BLUR_RADIUS,
		BLOOM_ALPHA_MULT_INTERIOR,
		BLOOM_ALPHA_MULT_EXTERIOR,
		BRIGHTNESS,
		SATURATION,
		CONTRAST,
		CONTRAST_AVG_LUM,
	};

	enum ColorKeys {
		TINT		= 0,
		FADE		= 1,
	};

	struct NiFloatKeyPair {
		NiFloatKey kKeys[2];
	};

	struct NiColorKeyPair {
		NiColorKey kKey[2];
	};

	struct ImageSpaceModifierData {
		bool		bAnimatable;
		float		fDuration;
		uint32_t	uiKeySizes[21][2];
		uint32_t	uiTintColorKeySize;
		uint32_t	uiBlurKeySize;
		uint32_t	uiDoubleKeySize;
		uint32_t	uiRadialBlurStrengthKeySize;
		uint32_t	uiRadialBlurRampUpKeySize;
		uint32_t	uiRadialBlurStartKeySize;
		bool		bUseTargetForRadialBlur;
		NiPoint2	kRadialBlurCenter;
		uint32_t	uiDepthOfFieldStrengthKeySize;
		uint32_t	uiDepthOfFieldDistanceKeySize;
		uint32_t	uiDepthOfFieldRangeKeySize;
		bool		bUseTargetForDepthOfField;
		char		ucDepthOfFieldMode;
		uint32_t	uiRadialBlurRampDownKeySize;
		uint32_t	uiRadialBlurDownStartKeySize;
		uint32_t	uiFadeColorKeySize;
		uint32_t	uiMotionBlurStrengthKeySize;
	};


	TESSound*				pOutroSound;
	TESSound*				pIntroSound;
	ImageSpaceModifierData	kData;

	union {
		struct {
			NiFloatInterpolator		kEyeAdaptSpeedInterpolator[2];
			NiFloatInterpolator		kBlurRadiusInterpolator[2];
			NiFloatInterpolator		kEmissiveMultInterpolator[2];
			NiFloatInterpolator		kTargetLumInterpolator[2];
			NiFloatInterpolator		kUpperLumClampInterpolator[2];
			NiFloatInterpolator		kBrightScaleInterpolator[2];
			NiFloatInterpolator		kBrightClampInterpolator[2];
			NiFloatInterpolator		kLumRampNoTexInterpolator[2];
			NiFloatInterpolator		kLumRampMinInterpolator[2];
			NiFloatInterpolator		kLumRampMaxInterpolator[2];
			NiFloatInterpolator		kSunlightInterpolator[2];
			NiFloatInterpolator		kGrassDimmerInterpolator[2];
			NiFloatInterpolator		kTreeDimmerInterpolator[2];
			NiFloatInterpolator		kSkinDimmerInterpolator[2];
			NiFloatInterpolator		kBloomBlurRadiusInterpolator[2];
			NiFloatInterpolator		kBloomAlphaMultInteriorInterpolator[2];
			NiFloatInterpolator		kBloomAlphaMultExteriorInterpolator[2];
			NiFloatInterpolator		kBrightnessInterpolator[2];
			NiFloatInterpolator		kSaturationInterpolator[2];
			NiFloatInterpolator		kContrastInterpolator[2];
			NiFloatInterpolator		kContrastAvgLumInterpolator[2];
		};

		NiFloatInterpolator		kInterpolators[21][2];
	};

	NiFloatInterpolator		kBlurInterpolator;
	NiFloatInterpolator		kDoubleInterpolator;
	NiColorInterpolator		kTintColorInterpolator;
	NiColorInterpolator		kFadeColorInterpolator;

	union {
		struct {
			NiFloatInterpolator		kRadialBlurStrengthInterpolator;
			NiFloatInterpolator		kRadialBlurRampUpInterpolator;
			NiFloatInterpolator		kRadialBlurStartInterpolator;
			NiFloatInterpolator		kRadialBlurRampDownInterpolator;
			NiFloatInterpolator		kRadialBlurDownStartInterpolator;
		};

		NiFloatInterpolator		kRadialBlurInterpolators[5];
	};

	union {
		struct {
			NiFloatInterpolator		kDepthOfFieldStrengthInterpolator;
			NiFloatInterpolator		kDepthOfFieldDistanceInterpolator;
			NiFloatInterpolator		kDepthOfFieldRangeInterpolator;
		};

		NiFloatInterpolator		kDepthOfFieldInterpolators[3];
	};

	NiFloatInterpolator		kMotionBlurStrengthInterpolator;

	union {
		struct {
			NiFloatKeyPair* pEyeAdaptSpeedKeys[2];
			NiFloatKeyPair* pBlurRadiusKeys[2];
			NiFloatKeyPair* pEmissiveMultKeys[2];
			NiFloatKeyPair* pTargetLumKeys[2];
			NiFloatKeyPair* pUpperLumClampKeys[2];
			NiFloatKeyPair* pBrightScaleKeys[2];
			NiFloatKeyPair* pBrightClampKeys[2];
			NiFloatKeyPair* pLumRampNoTexKeys[2];
			NiFloatKeyPair* pLumRampMinKeys[2];
			NiFloatKeyPair* pLumRampMaxKeys[2];
			NiFloatKeyPair* pSunlightKeys[2];
			NiFloatKeyPair* pGrassDimmerKeys[2];
			NiFloatKeyPair* pTreeDimmerKeys[2];
			NiFloatKeyPair* pSkinDimmerKeys[2];
			NiFloatKeyPair* pBloomBlurRadiusKeys[2];
			NiFloatKeyPair* pBloomAlphaMultInteriorKeys[2];
			NiFloatKeyPair* pBloomAlphaMultExteriorKeys[2];
			NiFloatKeyPair* pBrightnessKeys[2];
			NiFloatKeyPair* pSaturationKeys[2];
			NiFloatKeyPair* pContrastKeys[2];
			NiFloatKeyPair* pContrastAvgLumKeys[2];
		};

		NiFloatKeyPair* pFloatKeys[21][2];
	};

	NiFloatKeyPair*			pBlurKeys;
	NiFloatKeyPair*			pDoubleVisionKeys;

	union {
		struct {
			NiColorKeyPair* pTintColorKeys;
			NiColorKeyPair* pFadeColorKeys;
		};

		NiColorKeyPair* pColorKeys[2];
	};


	union {
		struct {
			NiFloatKeyPair* pRadialBlurStrengthKeys;
			NiFloatKeyPair* pRadialBlurRampUpKeys;
			NiFloatKeyPair* pRadialBlurStartKeys;
			NiFloatKeyPair* pRadialBlurRampDownKeys;
			NiFloatKeyPair* pRadialBlurDownKeys;
		};

		NiFloatKeyPair* pRadialBlurKeys[5];
	};

	union {
		struct {
			NiFloatKeyPair* pDepthOfFieldStrengthKeys;
			NiFloatKeyPair* pDepthOfFieldDistanceKeys;
			NiFloatKeyPair* pDepthOfFieldRangeKeys;
		};

		NiFloatKeyPair* pDepthOfFieldKeys[3];
	};

	NiFloatKeyPair*			pMotionBlurStrengthKeys;

	TESFORM_TYPE(TESImageSpaceModifier);
};

ASSERT_SIZE(TESImageSpaceModifier, 0x730);