#pragma once

#include "Gamebryo/NiTPointerList.hpp"
#include "Gamebryo/NiSmartPointer.hpp"

class NiDX9Renderer;
class NiTexture;
class NiDepthStencilBuffer;
class NiObject;
class NiCamera;
class BSRenderedTexture;
class NiRenderedTexture;

class BSTextureManager {
public:
		enum eTextureType {
		BSTM_RT_CUSTOM								= -1,

		BSTM_RT_HDR_FIRST							= 0,
		BSTM_RT_HDR_DOWNSAMPLE						= 0,
		BSTM_RT_HDR_DOWNSAMPLE_ANISOINTERMEDIATE	= 1,
		BSTM_RT_HDR_BLURSWAP						= 2,
		BSTM_RT_HDR_LAST							= 2,

		BSTM_RT_IMAGESPACE_FIRST					= 3,
		BSTM_RT_IMAGESPACE_SWAP						= 3,
		BSTM_RT_IMAGESPACE_LAST						= 3,

		BSTM_RT_MAIN_FIRST							= 4,
		BSTM_RT_MAIN_IMAGESPACE						= 4,
		BSTM_RT_MAIN_FIRSTPERSON					= 5,
		BSTM_RT_MAIN_MENUBG							= 6,
		BSTM_RT_MAIN_LAST							= 6,

		BSTM_RT_TESWATER_FIRST						= 7,
		BSTM_RT_TESWATER_FFT						= 7,
		BSTM_RT_TESWATER_GREY						= 8,
		BSTM_RT_TESWATER_REFLECTION					= 9,
		BSTM_RT_TESWATER_LOD_REFLECTION				= 0xA,
		BSTM_RT_TESWATER_REFRACTION					= 0xB,
		BSTM_RT_TESWATER_RAIN						= 0xC,
		BSTM_RT_TESWATER_SCRAMBLEMAP				= 0xD,
		BSTM_RT_TESWATER_IFFT_BUTTERFLYMAP			= 0xE,
		BSTM_RT_TESWATER_HIGH_W						= 0xF,
		BSTM_RT_TESWATER_HIGH_AMPLITUDE				= 0x10,
		BSTM_RT_TESWATER_DEPTH						= 0x11,
		BSTM_RT_TESWATER_NOISE_HEIGHTMAP			= 0x12,
		BSTM_RT_TESWATER_NOISE_NORMALMAP			= 0x13,
		BSTM_RT_TESWATER_DISPLACEMENT				= 0x14,
		BSTM_RT_TESWATER_DEBUG_DISPLAY				= 0x15,
		BSTM_RT_TESWATER_BLUR						= 0x16,
		BSTM_RT_TESWATER_LAST						= 0x16,

		BSTM_RT_TREES_FIRST							= 0x17,
		BSTM_RT_TREES_CANOPYSHADOWMASK				= 0x17,
		BSTM_RT_TREES_LAST							= 0x17,

		BSTM_RT_BLUR_FIRST							= 0x18,
		BSTM_RT_BLURFULL_BUFFER						= 0x18,
		BSTM_RT_BLURFULL_SWAP						= 0x19,
		BSTM_RT_BLUR_LAST							= 0x19,

		BSTM_RT_BLUR20_FIRST						= 0x1A,
		BSTM_RT_BLUR20_BUFFER						= 0x1A,
		BSTM_RT_BLUR20_LAST							= 0x1A,

		BSTM_RT_GETHIT_FIRST						= 0x1B,
		BSTM_RT_GETHIT_BUFFER						= 0x1B,
		BSTM_RT_GETHIT_LAST							= 0x1B,

		BSTM_RT_LOCALMAP_FIRST						= 0x1C,
		BSTM_RT_LOCALMAP_FINAL						= 0x1C,
		BSTM_RT_LOCALMAP_COLOR						= 0x1D,
		BSTM_RT_LOCALMAP_NORMALS					= 0x1E,
		BSTM_RT_LOCALMAP_LAST						= 0x1E,

		BSTM_RT_REFRACTION_FIRST					= 0x1F,
		BSTM_RT_REFRACTION_NORMALS					= 0x1F,
		BSTM_RT_REFRACTION_LAST						= 0x1F,

		BSTM_RT_VFOG_FIRST							= 0x20,
		BSTM_RT_VFOG								= 0x20,
		BSTM_RT_SCENE_DEPTH_BUFFER					= 0x21,
		BSTM_RT_VFOG_SWAP							= 0x22,
		BSTM_RT_VFOG_LAST							= 0x22,

		BSTM_RT_VELOCITY_FIRST						= 0x23,
		BSTM_RT_VELOCITY							= 0x23,
		BSTM_RT_VELOCITY_SWAP						= 0x24,
		BSTM_RT_VELOCITY_LAST						= 0x24,

		BSTM_RT_DOF_FIRST							= 0x25,
		BSTM_RT_DOF_BLUR							= 0x25,
		BSTM_RT_DOF_BLUR_SWAP						= 0x26,
		BSTM_RT_DOF_MASK							= 0x27,
		BSTM_RT_DOF_LAST							= 0x27,

		BSTM_RT_DEPTH_RADIALBLUR_FIRST				= 0x28,
		BSTM_RT_DEPTH_RADIALBLUR_BLUR				= 0x28,
		BSTM_RT_DEPTH_RADIALBLUR_LAST				= 0x28,

		BSTM_RT_CUBEMAP_FIRST						= 0x29,
		BSTM_RT_CUBEMAP_CAMERA						= 0x29,
		BSTM_RT_CUBEMAP_LAST						= 0x29,

		BSTM_RT_SHADOWS_FIRST						= 0x2A,
		BSTM_RT_SHADOWS_SHADOWMAP					= 0x2A,
		BSTM_RT_SHADOWS_SHADOWMAPFRUSTUM			= 0x2B,
		BSTM_RT_SHADOWS_LAST						= 0x2B,

		BSTM_RT_ENVMAP_FIRST						= 0x2C,
		BSTM_RT_ENVMAP_WINDOWS						= 0x2C,
		BSTM_RT_ENVMAP_LAST							= 0x2C,

		BSTM_RT_INTERFACE_FIRST						= 0x2D,
		BSTM_RT_INTERFACE_RENDEREDMENU				= 0x2D,
		BSTM_RT_INTERFACE_RENDEREDMENU_SWAP			= 0x2E,
		BSTM_RT_INTERFACE_VATS						= 0x2F,
		BSTM_RT_INTERFACE_RACESEXMENU				= 0x30,
		BSTM_RT_INTERFACE_TEMP						= 0x31,
		BSTM_RT_INTERFACE_LAST						= 0x31,

		BSTM_RT_NOISE_FIRST							= 0x32,
		BSTM_RT_NOISE_BUFFER						= 0x32,
		BSTM_RT_NOISE_LAST							= 0x32,

		BSTM_RT_DECAL_FIRST							= 0x33,
		BSTM_RT_DECAL_OCCLUSION						= 0x33,
		BSTM_RT_DECAL_LAST							= 0x33,

		BSTM_RT_COUNT,
	};

	enum eRenderedTextureFlags {
		BSTM_CF_NONE					= 0,
		BSTM_CF_UNK_1					= 1u << 0,
		BSTM_CF_CLEAR					= 1u << 1,
		BSTM_CF_NO_DEPTH				= 1u << 2,
		BSTM_CF_NOT_RENDERABLE			= 1u << 3,
		BSTM_CF_CUBE_MAP				= 1u << 4,
		BSTM_CF_PRECREATE				= 1u << 5,
		BSTM_CF_MULTISAMPLE				= 1u << 6,
		BSTM_CF_NOT_DISCARDABLE_DEPTH	= 1u << 7,
		BSTM_CF_UNIQUE_DEPTH_BUFFER		= 1u << 8,
		BSTM_CF_DONT_FREE				= 1u << 9,
		BSTM_CF_UNK_400					= 1u << 10,
	};

	class RenderedTextureData {
	public:
		NiPointer<BSRenderedTexture>	spTexture;
		D3DFORMAT						eFormat;
		RenderedTextureData*			pNext;
		Bitfield32						uiFlags;
		bool							bUsedThisFrame;
		eTextureType					eType;
	};

	struct TextureLists {
		NiTPointerList<NiPointer<BSRenderedTexture>> kShadowMaps;
		NiTPointerList<NiPointer<BSRenderedTexture>> kWaterDepthMaps;
		NiTPointerList<NiPointer<BSRenderedTexture>> kWaterReflectionMaps;
		NiTPointerList<NiPointer<BSRenderedTexture>> kWaterBlurMaps;
		NiTPointerList<NiPointer<BSRenderedTexture>> kWaterNoiseMaps;
	};

	TextureLists							kUnusedShaderTextures;
	TextureLists							kUsedShaderTextures;
	NiTPointerList<RenderedTextureData*>	kUnusedTextures;
	NiTPointerList<RenderedTextureData*>	kUsedTextures;
	NiTPointerList<BSRenderedTexture*>		kUnusedShadowMaps;
	NiTPointerList<BSRenderedTexture*>		kUsedShadowMaps;
	NiPointer<NiDepthStencilBuffer>			spShadowDepthBuffer;
	NiPointer<NiObject>						spUnk0AC;

	BSRenderedTexture* BorrowRenderedTexture(NiDX9Renderer* apRenderer, eTextureType aeType, uint32_t auiFlags = 0, NiRenderedTexture* apAliasTex = nullptr, uint32_t auiAliasOffset = 0);
	void ReturnRenderedTexture(BSRenderedTexture* apRenderedTexture);
};