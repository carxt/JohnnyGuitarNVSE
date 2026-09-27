#pragma once

#include "TESForm.hpp"
#include "Gamebryo/NiFloatInterpolator.hpp"
#include "Gamebryo/NiColorInterpolator.hpp"
#include "Gamebryo/NiLinFloatKey.hpp"
#include "Gamebryo/NiLinColorKey.hpp"
#include "Gamebryo/NiPoint2.hpp"

class TESSound;
class NiAVObject;

class TESImageSpaceModifier : public TESFormBase {
public:
	TESImageSpaceModifier();
	~TESImageSpaceModifier();

	struct _Param {
		enum Param {
			HDR_EYE_ADAPT_SPEED = 0,
			HDR_BLUR_RADIUS,
			HDR_SKIN_DIMMER,
			HDR_EMISSIVE_MULT,
			HDR_TARGET_LUM,
			HDR_UPPER_LUM_CLAMP,
			HDR_BRIGHT_SCALE,
			HDR_BRIGHT_CLAMP,
			HDR_LUM_RAMP_NO_TEX,
			HDR_LUM_RAMP_MIN,
			HDR_LUM_RAMP_MAX,
			HDR_SUNLIGHT_DIMMER,
			HDR_GRASS_DIMMER,
			HDR_TREE_DIMMER,

			BLOOM_BLUR_RADIUS,
			BLOOM_ALPHA_MULT_INTERIOR,
			BLOOM_ALPHA_MULT_EXTERIOR,

			CINEMATIC_SATURATION,
			CINEMATIC_CONTRAST_AVG_LUM,
			CINEMATIC_CONTRAST,
			CINEMATIC_BRIGHTNESS,

			COUNT
		};
	};
	using Param = _Param::Param;

	struct _Operation {
		enum Op {
			MULT	= 0,
			ADD		= 1,
			COUNT
		};
	};
	using Operation = _Operation::Op;

	struct ImageSpaceModifierData {
		bool		bAnimatable;
		float		fDuration;
		uint32_t	uiKeySizes[Param::COUNT][Operation::COUNT];
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
		uint8_t		ucDepthOfFieldMode;
		uint32_t	uiRadialBlurRampDownKeySize;
		uint32_t	uiRadialBlurDownStartKeySize;
		uint32_t	uiFadeColorKeySize;
		uint32_t	uiMotionBlurStrengthKeySize;
	};

	TESSound*					pOutroSound;
	TESSound*					pIntroSound;
	ImageSpaceModifierData		kData;

	union {
		struct {
			NiFloatInterpolator	kHDREyeAdaptSpeedInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRBlurRadiusInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRSkinDimmerInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDREmissiveMultInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRTargetLumInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRUpperLumClampInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRBrightScaleInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRBrightClampInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRLumRampNoTexInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRLumRampMinInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRLumRampMaxInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRSunlightInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRGrassDimmerInterpolator[Operation::COUNT];
			NiFloatInterpolator	kHDRTreeDimmerInterpolator[Operation::COUNT];
			NiFloatInterpolator	kBloomBlurRadiusInterpolator[Operation::COUNT];
			NiFloatInterpolator	kBloomAlphaMultInteriorInterpolator[Operation::COUNT];
			NiFloatInterpolator	kBloomAlphaMultExteriorInterpolator[Operation::COUNT];
			NiFloatInterpolator	kCinematicSaturationInterpolator[Operation::COUNT];
			NiFloatInterpolator	kCinematicContrastAvgLumInterpolator[Operation::COUNT];
			NiFloatInterpolator	kCinematicContrastInterpolator[Operation::COUNT];
			NiFloatInterpolator	kCinematicBrightnessInterpolator[Operation::COUNT];
		};

		NiFloatInterpolator		kInterpolators[Param::COUNT][Operation::COUNT];
	};

	NiFloatInterpolator			kBlurInterpolator;
	NiFloatInterpolator			kDoubleInterpolator;
	NiColorInterpolator			kTintColorInterpolator;
	NiColorInterpolator			kFadeColorInterpolator;

	union {
		struct {
			NiFloatInterpolator	kRadialBlurStrengthInterpolator;
			NiFloatInterpolator	kRadialBlurRampUpInterpolator;
			NiFloatInterpolator	kRadialBlurStartInterpolator;
			NiFloatInterpolator	kRadialBlurRampDownInterpolator;
			NiFloatInterpolator	kRadialBlurDownStartInterpolator;
		};

		NiFloatInterpolator		kRadialBlurInterpolators[5];
	};

	union {
		struct {
			NiFloatInterpolator	kDepthOfFieldStrengthInterpolator;
			NiFloatInterpolator	kDepthOfFieldDistanceInterpolator;
			NiFloatInterpolator	kDepthOfFieldRangeInterpolator;
		};

		NiFloatInterpolator		kDepthOfFieldInterpolators[3];
	};

	NiFloatInterpolator			kMotionBlurStrengthInterpolator;

	union {
		struct {
			NiLinFloatKey*		pHDREyeAdaptSpeedKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRBlurRadiusKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRSkinDimmerKeys[Operation::COUNT];
			NiLinFloatKey*		pHDREmissiveMultKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRTargetLumKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRUpperLumClampKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRBrightScaleKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRBrightClampKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRLumRampNoTexKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRLumRampMinKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRLumRampMaxKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRSunlightKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRGrassDimmerKeys[Operation::COUNT];
			NiLinFloatKey*		pHDRTreeDimmerKeys[Operation::COUNT];
			NiLinFloatKey*		pBloomBlurRadiusKeys[Operation::COUNT];
			NiLinFloatKey*		pBloomAlphaMultInteriorKeys[Operation::COUNT];
			NiLinFloatKey*		pBloomAlphaMultExteriorKeys[Operation::COUNT];
			NiLinFloatKey*		pCinematicSaturationKeys[Operation::COUNT];
			NiLinFloatKey*		pCinematicContrastAvgLumKeys[Operation::COUNT];
			NiLinFloatKey*		pCinematicContrastKeys[Operation::COUNT];
			NiLinFloatKey*		pCinematicBrightnessKeys[Operation::COUNT];
		};

		NiLinFloatKey*			pFloatKeys[Param::COUNT][Operation::COUNT];
	};

	NiLinFloatKey*				pBlurKey;
	NiLinFloatKey*				pDoubleVisionKey;

	union {
		struct {
			NiLinColorKey*		pTintColorKey;
			NiLinColorKey*		pFadeColorKey;
		};

		NiLinColorKey*			pColorKeys[Operation::COUNT];
	};

	union {
		struct {
			NiLinFloatKey*		pRadialBlurStrengthKey;
			NiLinFloatKey*		pRadialBlurRampUpKey;
			NiLinFloatKey*		pRadialBlurStartKey;
			NiLinFloatKey*		pRadialBlurRampDownKey;
			NiLinFloatKey*		pRadialBlurDownKey;
		};

		NiLinFloatKey*			pRadialBlurKeys[5];
	};

	union {
		struct {
			NiLinFloatKey*		pDepthOfFieldStrengthKey;
			NiLinFloatKey*		pDepthOfFieldDistanceKey;
			NiLinFloatKey*		pDepthOfFieldRangeKey;
		};

		NiLinFloatKey*			pDepthOfFieldKeys[3];
	};

	NiLinFloatKey*				pMotionBlurStrengthKey;
#ifdef EDITOR
	float						fUnk744;
	float						fUnk748;
#endif

	TESFORM_TYPE(TESImageSpaceModifier);

	TESSound* GetIntroSound() const;
	void SetIntroSound(TESSound* apSound);

	TESSound* GetOutroSound() const;
	void SetOutroSound(TESSound* apSound);

	bool GetAnimatable() const;
	void SetAnimatable(bool abVal);

#ifdef GAME
	static TESImageSpaceModifier* GetConcussion();
	static TESImageSpaceModifier* GetExplosionInFace();
	static TESImageSpaceModifier* GetGetHit();
#endif
};

#ifdef GAME
ASSERT_SIZE(TESImageSpaceModifier, 0x730);
#else
ASSERT_SIZE(TESImageSpaceModifier, 0x74C);
#endif