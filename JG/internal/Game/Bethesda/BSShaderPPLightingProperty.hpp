#pragma once

#include "BSShaderLightingProperty.hpp"
#include "BSShaderTextureSet.hpp"
#include "Gamebryo/NiColorA.hpp"
#include "Gamebryo/NiPoint4.hpp"
#include "Gamebryo/NiTexturingProperty.hpp"

#include <d3d9types.h>

class NiAVObject;
class NiSourceTexture;
class BSShaderAccumulator;
class NiAdditionalGeometryData;

NiSmartPointer(BSShaderPPLightingProperty);

class BSShaderPPLightingProperty : public BSShaderLightingProperty {
public:
	BSShaderPPLightingProperty();
	virtual ~BSShaderPPLightingProperty();

	virtual void							CopyTo(BSShaderPPLightingProperty* apTarget);
	virtual void							CopyToMembers(BSShaderPPLightingProperty* apTarget);
	virtual NiAdditionalGeometryData*		CreateRendererSpecificProperty(NiGeometry* apGeometry);
	virtual D3DTEXTUREADDRESS				GetClampD3D() const;
	virtual void							SetClampD3D(D3DTEXTUREADDRESS aeClampMode);
	virtual NiTexturingProperty::ClampMode	GetClampNI() const;
	virtual void							SetClampNI(NiTexturingProperty::ClampMode aeClampMode);
	virtual uint16_t						GetTextureCount() const;
	virtual uint16_t						GetLandscapeTextureCount() const;
	virtual void							SetTexture(TextureType aeTextureSlot, uint32_t auiTextureNumber, NiTexture* apTexture);
	virtual NiTexture*						GetTexture(TextureType aeTextureSlot, uint32_t auiTextureNumber);
	virtual void							SetTextures(BSTextureSet* apTextureSet);
	virtual void							SetDiffuseTexture(uint32_t auiTextureNumber, NiTexture* apTexture);
	virtual void							SetNormalTexture(uint32_t auiTextureNumber, NiTexture* apTexture);
	virtual void							SetGlowTexture(uint32_t auiTextureNumber, NiTexture* apTexture);
	virtual void							SetFlagsFromTextures();
	virtual float							GetSpecularLODFade();
	virtual float							GetEnvMapLODFade();
	virtual void							GetRenderPasses_1x(NiGeometry* apGeometry, uint32_t aeEnabledPasses, uint16_t* apusPassCount, uint32_t aeRenderMode, BSShaderAccumulator* apShaderAccum, bool abAddPass);
	virtual void							GetRenderPasses_2x(NiGeometry* apGeometry, uint32_t aeEnabledPasses, uint16_t* apusPassCount, uint32_t aeRenderMode, BSShaderAccumulator* apShaderAccum, bool abAddPass);

	NiSmartPointer(TextureEffectData);

	class TextureEffectData : public NiRefObject {
	public:
		TextureEffectData();
		~TextureEffectData();

		NiPointer<NiTexture>	spTexture;
		NiColorA				kCurrentFillColor;
		NiColorA				kCurrentRimColor;
		NiColorA				kFillColor;
		NiColorA				kRimColor;
		float					fTextureUOffset;
		float					fTextureVOffset;
		float					fEdgeExponent;
		float					fBoundDiameter;
		D3DBLEND				eSrcBlendMode;
		D3DBLEND				eDestBlendMode;
		D3DBLENDOP				eBlendOperation;
		D3DCMPFUNC				eZTestFunction;
		NiPointer<NiTexture>	spBlockOutTexture;
		uint32_t				uiAlphaTest;
	};

	NiSmartPointer(TangentSpaceData);

	class TangentSpaceData : public NiRefObject {
	public:
		bool		bOwnsMemory;
		NiPoint3*	pTangentExtraData;
		NiPoint3*	pBinormalExtraData;
	};

	float									fWaterDepthCameraOffset;
	float									fGeomorphParam;
	NiColorA								kHairTint;
	NiPoint4								kLandBlendParams;
	BSShaderTextureSetPtr					spTextureSet;
	uint16_t								usTextureCount;
	NiPointer<NiTexture>*					ppTextures[BSShaderProperty::TextureType::COUNT];
	uint8_t*								pSpecularExponents;
	uint16_t								usLandscapeTextures;
	bool*									pGlossMapStates;
	TangentSpaceDataPtr						spTangentSpaceData;
	float*									pTextureSplatVertexData;
	NiTexturingProperty::ClampMode			eTextureClampMode;
	TextureEffectDataPtr					spTexEffectData;
	float									fRefractionPower;
	int32_t									iRefractionFirePeriod;
	float									fParallaxOccMaxPasses;
	float									fParallaxOccScale;
	float									fTerrainTexOffsetX;
	float									fTerrainTexOffsetY;
	float									fTerrainTexFade;
	float									fTerrainDetailTexScale;
	RenderPass*								pRenderDepthPass;

	CREATE_OBJECT(BSShaderPPLightingProperty, 0xB68D50);
	NIRTTI_ADDRESS(0x11FA010);

	NiTexture* GetDiffuseTexture(uint32_t auID = 0) const	{ return ppTextures[TextureType::DIFFUSE][auID]; };
	NiTexture* GetNormalTexture(uint32_t auID = 0) const	{ return ppTextures[TextureType::NORMAL][auID]; };
	NiTexture* GetGlowTexture(uint32_t auID = 0) const		{ return ppTextures[TextureType::GLOW][auID]; };
	NiTexture* GetParallax(uint32_t auID = 0) const			{ return ppTextures[TextureType::HEIGHT][auID]; };
	NiTexture* GetCubeMap(uint32_t auID = 0) const			{ return ppTextures[TextureType::ENV][auID]; };
	NiTexture* GetEnvMask(uint32_t auID = 0) const			{ return ppTextures[TextureType::ENV_MASK][auID]; };
};

ASSERT_SIZE(BSShaderPPLightingProperty, 0x104);
ASSERT_SIZE(BSShaderPPLightingProperty::TangentSpaceData, 0x14)
ASSERT_SIZE(BSShaderPPLightingProperty::TextureEffectData, 0x74)