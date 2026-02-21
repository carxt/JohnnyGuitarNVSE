#pragma once

#include "INISettingCollection.hpp"

class RendererSettingCollection : public INISettingCollection {
public:
	struct BlurShader {
		static constexpr AddressPtr<Setting, 0x11C76C0> bDoHighDynamicRange;
		static constexpr AddressPtr<Setting, 0x11C7768> bUseBlurShader;
	};

	struct Decals {
		static constexpr AddressPtr<Setting, 0x11C57FC> uMaxDecals;
	};
	
	struct Display {
		static constexpr AddressPtr<Setting, 0x11C74D4> bDrawShadows;
		static constexpr AddressPtr<Setting, 0x11C771C> bEnableEyefinity;
		static constexpr AddressPtr<Setting, 0x11C77B4> bFullScreen;
		static constexpr AddressPtr<Setting, 0x11C7790> bTransparencyMultisampling;
		static constexpr AddressPtr<Setting, 0x11C72CC> fDecalLOD1;
		static constexpr AddressPtr<Setting, 0x11C7428> fDecalLOD2;
		static constexpr AddressPtr<Setting, 0x11C7740> fLightLODStartFade;
		static constexpr AddressPtr<Setting, 0x11C7568> fShadowLODStartFade;
		static constexpr AddressPtr<Setting, 0x11C7598> fSpecularLODStartFade;
		static constexpr AddressPtr<Setting, 0x11C72E4> iActorShadowCountExt;
		static constexpr AddressPtr<Setting, 0x11C72D8> iActorShadowCountInt;
		static constexpr AddressPtr<Setting, 0x11C738C> iAdapter;
		static constexpr AddressPtr<Setting, 0x11F94EC> iMaxAnisotropy;
		static constexpr AddressPtr<Setting, 0x11C5890> iMaxDecalsPerFrame;
		static constexpr AddressPtr<Setting, 0x11C5858> iMaxSkinDecalsPerFrame;
		static constexpr AddressPtr<Setting, 0x11C73F4> iMultiSample;
		static constexpr AddressPtr<Setting, 0x11C76CC> iShadowFilter;
		static constexpr AddressPtr<Setting, 0x11C7520> iShadowMapResolution;
		static constexpr AddressPtr<Setting, 0x11C752C> iShadowMode;
		static constexpr AddressPtr<Setting, 0x11C718C> iSizeH;
		static constexpr AddressPtr<Setting, 0x11C73DC> iSizeW;
		static constexpr AddressPtr<Setting, 0x11C7254> iTexMipMapMinimum;
		static constexpr AddressPtr<Setting, 0x11C779C> iTexMipMapSkip;
		static constexpr AddressPtr<Setting, 0x11C7284> iWaterMultiSamples;
		static constexpr AddressPtr<Setting, 0x11C72C0> sD3DDevice;
	};

	struct Grass {
		static constexpr AddressPtr<Setting, 0x11C7308> b30GrassVS;
		static constexpr AddressPtr<Setting, 0x11CA450> fGrassStartFadeDistance;
	};

	struct Imagespace {
		static constexpr AddressPtr<Setting, 0x12023D0> bDoDepthOfField;
		static constexpr AddressPtr<Setting, 0x11F9694> iRadialBlurLevel;
	};

	struct LOD {
		static constexpr AddressPtr<Setting, 0x11C3EC0> fLODFadeOutMultActors;
		static constexpr AddressPtr<Setting, 0x11C3D0C> fLODFadeOutMultItems;
		static constexpr AddressPtr<Setting, 0x11C3D78> fLODFadeOutMultObjects;
	};

	struct TerrainManager {
		static constexpr AddressPtr<Setting, 0x11D877C> fBlockLoadDistance;
		static constexpr AddressPtr<Setting, 0x11D8724> fBlockLoadDistanceLow;
		static constexpr AddressPtr<Setting, 0x11D86E0> fSplitDistanceMult;
		static constexpr AddressPtr<Setting, 0x11D8788> fTreeLoadDistance;
	};

	struct Water {
		static constexpr AddressPtr<Setting, 0x11C7A90> bAutoWaterSilhouetteReflections;
		static constexpr AddressPtr<Setting, 0x11C7C00> bForceHighDetailReflections;
		static constexpr AddressPtr<Setting, 0x11C7BBC> bUseWaterDepth;
		static constexpr AddressPtr<Setting, 0x11C7AC4> bUseWaterDisplacements;
		static constexpr AddressPtr<Setting, 0x11C7C48> bUseWaterReflectionBlur;
		static constexpr AddressPtr<Setting, 0x11C7B6C> bUseWaterReflections;
		static constexpr AddressPtr<Setting, 0x11C7C60> bUseWaterRefractions;
		static constexpr AddressPtr<Setting, 0x11C7C1C> iWaterBlurAmount;
		static constexpr AddressPtr<Setting, 0x11C7680> iWaterReflectHeight;
		static constexpr AddressPtr<Setting, 0x11C7784> iWaterReflectWidth;
	};
};