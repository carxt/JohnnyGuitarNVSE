#pragma once

#include "BSShaderProperty.hpp"
#include "BSRenderedTexture.hpp"
#include "Gamebryo/NiPoint4.hpp"
#include "Gamebryo/NiColorA.hpp"
#include "Gamebryo/NiTPointerList.hpp"

class NiLight;

class WaterShaderProperty : public BSShaderProperty {
public:
	WaterShaderProperty();
	~WaterShaderProperty();

	struct VarAmounts {
		float fSunSpecularPower;
		float fWaterReflectivityAmt;
		float fWaterOpacity;
		float fWaterDistortionAmt;
	};

	bool							bDisplacement;
	bool							bLOD;
	bool							bFullReflections;
	bool							bDepth;
	int32_t							iTexOffsetX;
	int32_t							iTexOffsetY;
	float							fBlendRadius;
	float							fBlendNormalsAmount;
	float							fFogFar;
	float							fFogRange;
	bool							bIsMoving;
	bool							bInWater;
	bool							bIsUnderwater;
	bool							bUpdateConstants;
	bool							bReflections;
	bool							bRefractions;
	bool							bObjectTexCoords;
	bool							bSpecularLighting;
	DWORD							uiStencilMask;
	NiColorA						kShallowColor;
	NiColorA						kDeepColor;
	NiColorA						kReflectionColor;
	VarAmounts						kVarAmounts;
	NiPoint4						kBlendRadius;
	NiPoint4						kDepthFalloff;
	NiPoint4						kDepthOffset;
	NiPoint4						kFresnelRI;
	NiColorA						kTile;
	float							fFresnelAmount;
	float							fNoiseScale;
	float							fFogAmount;
	float							fUVScale;
	NiTPointerList<NiLight*>		kLights;
	NiPointer<NiTexture>			spNoiseHeightMap;
	NiPointer<BSRenderedTexture>	spNoiseNormalMap;
	NiPointer<BSRenderedTexture>	spReflectionMap;
	NiPointer<BSRenderedTexture>	spRefractionMap;
	NiPointer<BSRenderedTexture>	spDepthMap;
	NiPointer<NiTexture>			spDisplacementNormalMap;
	RenderPass*						pWaterPass;

	CREATE_OBJECT(WaterShaderProperty, 0xB6AE60);
	NIRTTI_ADDRESS(0x11FA018);
};
ASSERT_SIZE(WaterShaderProperty, 0x150);