#pragma once

#include "Gamebryo/NiColor.hpp"
#include "Gamebryo/NiColorA.hpp"

class ImageSpaceParameterData {
public:
	struct HDRValues {
		union {
			struct {
				float fEyeAdaptSpeed;
				float fBlurRadius;
				float fBlurPasses;
				float fEmissiveMult;
				float fTargetLUM;
				float fUpperLUMClamp;
				float fBrightScale;
				float fBrightClamp;
				float fLUMRampNoTex;
				float fLUMRampMin;
				float fLUMRampMax;
				float fSunlightDimmer;
				float fGrassDimmer;
				float fTreeDimmer;
				float fSkinDimmer;
			};
			float fHDRValues[15];
		};
	};

	struct BloomValues {
		union {
			struct {
				float fBlurRadius;
				struct {
					float fInterior;
					float fExterior;
				} kAlphaMults;
			};
			float fBloomValues[3];
		};
	};

	struct GetHitValues {
		union {
			struct {
				float fBlurRadius;
				float fBlurDamping;
				float fDamping;
			};
			float fGetHitValues[3];
		};
	};

	struct NightEyeValues {
		union {
			struct {
				NiColor kColor;
				float	fBrightness;
			};
			float	fNightEyeValues[4];
		};
	};

	struct CinematicValues {
		union {
			struct {
				float	fSaturation;
				struct {
					float	fAvgLumValue;
					float	fValue;
				} kContrast;
				float	fBrightness;
				struct {
					NiColor kColor;
					float	fValue;
				} kTint;
				NiColorA kUnknown;
			};
			float	fCinematicValues[12];
		};
	};

	HDRValues		kHDR;
	BloomValues		kBloom;
	GetHitValues	kGetHit;
	NightEyeValues	kNightEye;
	CinematicValues	kCinematic;
	uint32_t		uiCinematicsEnabled;
};

ASSERT_SIZE(ImageSpaceParameterData, 0x98);