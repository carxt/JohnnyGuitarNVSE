#pragma once

#include "Gamebryo/NiShadeProperty.hpp"
#include "Gamebryo/NiTObjectArray.hpp"

class BSShaderAccumulator;
class Lighting30ShaderProperty;
class ShadowSceneLight;
class BGSTextureUseMap;
class NiAVObject;
class NiTexture;

NiSmartPointer(BSShaderProperty);

class BSShaderProperty : public NiShadeProperty {
public:
	BSShaderProperty();
	virtual ~BSShaderProperty();

	struct _TextureType {
		enum TextureType {
			DIFFUSE		= 0,
			NORMAL		= 1,
			GLOW		= 2,
			HEIGHT		= 3,
			ENV			= 4,
			ENV_MASK	= 5,
			COUNT,
		};
	};
	using TextureType = _TextureType::TextureType;

	class RenderPass {
	public:
		template<typename ...Args>
		RenderPass(NiGeometry* apGeometry, uint16_t ausPassEnum, bool abFirst = true, uint8_t aucNumLights = 0, Args ...args) noexcept;
		~RenderPass();
		
		struct _AccumHint {
			enum Hint {
				NORMAL					= 0,
				SORT					= 1,
				IMMEDIATE				= 2,
				NO_DEPTH				= 3,
				DECAL					= 4,
				DYNAMIC_DECAL			= 5,
				REFRACT					= 6,
				FIRST_PERSON_NO_REFRACT = 7,
				VOLUMETRIC_FOG			= 8,
				MORPH					= 9,
				LOD						= 10,
				LOD_TREE				= 11,
				LOD_BILLBOARD			= 12,
				VELOCITY				= 13,
				FADING					= 14,
			};
		};
		using AccumHint = _AccumHint::Hint;

		NiGeometry*			pGeometry;
		uint16_t			usPassEnum;
		uint8_t				eAccumulationHint;
		bool				bFirstPass;
		bool				bLastPass;
		uint8_t				ucNumLights;
		uint8_t				ucMaxNumLights;
		uint8_t				ucExtraParam;
		ShadowSceneLight**	ppSceneLights;

		template<typename ...Args>
		void SetLights(uint8_t aucNumLights, Args ...args);

		NiGeometry* GetGeometry() const;

		uint16_t GetPassType() const { return usPassEnum; }

		bool Between(uint32_t auiStart, uint32_t auiEnd) const;
		bool IsPass(uint32_t auiPassEnum) const;

		void FreeLightArray();
		void AllocateLightArray(uint8_t aucNumLights);
	};

	class RenderPassArray {
	public:
		RenderPassArray(uint32_t auiSize);
		~RenderPassArray();

		NiTObjectArray<RenderPass*> kPasses;
		uint32_t					uiPassCount;

		void AddPass(NiGeometry* apGeometry, uint32_t auiPassEnum, bool abFirst,
			uint8_t aucNumLights = 0, ShadowSceneLight* apSceneLight = nullptr, ShadowSceneLight* apSceneLight1 = nullptr, ShadowSceneLight* apSceneLight2 = nullptr, RenderPass* apRenderPass = nullptr);

		void Clear();

		bool IsEmpty() const { return uiPassCount == 0; }
		RenderPass* GetLastPass() const { return GetAt(uiPassCount - 1); }
		RenderPass* GetAt(uint32_t auiIndex) const { return kPasses.GetAt(auiIndex); }
	};

	virtual void						CopyTo(BSShaderProperty* apTarget);
	virtual void						CopyToMembers(BSShaderProperty* apTarget);
	virtual void						SetupGeometry(NiGeometry* apGeometry);
	virtual RenderPassArray*			GetRenderPasses(NiGeometry* apGeometry, uint32_t auiEnabledPasses, uint16_t& arPassCount, const uint32_t aeRenderMode, BSShaderAccumulator* apAccumulator, bool abUpdateList);
	virtual uint16_t					GetNumberofPasses(NiGeometry* apGeometry);
	virtual RenderPassArray*			GetSIBlockRenderPasses() const;
	virtual RenderPass*					GetRenderDepthPass(NiGeometry* apGeometry);
	virtual BSShaderProperty*			ClarifyShader(NiGeometry* apGeometry, bool abForceShader = false, bool abAllow30Shaders = true);
	virtual NiTexture*					GetBaseTexture() const;
	virtual RenderPassArray*			GetWaterFogPassList(NiGeometry* apGeometry);
	virtual void						GetTextureUse(void(__cdecl* apCallback)(NiTexture*, uint32_t, void*), void* apParam) const;
	virtual void						PrecacheTextures() const;

	struct ALIGN4 _ShaderFlags {
		struct _Bits {
			enum Bits {
				SPECULAR						= 0,
				SKINNED							= 1,
				LOW_DETAIL						= 2,
				VERTEX_ALPHA					= 3,
				MOTION_BLUR						= 4,
				SINGLE_PASS						= 5,
				FALLOFF							= 6,
				ENVIRONMENT_MAPPING				= 7,
				ALPHA_TEXTURE					= 8,
				ZPREPASS						= 9,
				FACEGEN							= 10,
				PARALLAX						= 11,
				MODEL_SPACE_NORMALS				= 12,
				NON_PROJECTIVE_SHADOWS			= 13,
				LANDSCAPE						= 14,
				REFRACTION						= 15,
				REFRACTION_FIRE					= 16,
				EYE_ENVIRONMENT_MAPPING			= 17,
				HAIR							= 18,
				DYNAMIC_ALPHA					= 19,
				LOCAL_MAP_HIDE_SECRET			= 20,
				WINDOW_ENVIRONMENT_MAPPING		= 21,
				TREE_BILLBOARD					= 22,
				SHADOW_FRUSTUM					= 23,
				MULTIPLE_TEXTURES				= 24,
				REMAPPABLE_TEXTURES				= 25,
				DECAL							= 26,
				DYNAMIC_DECAL					= 27,
				PARALLAX_OCCLUSION				= 28,
				EXTERNAL_EMITTANCE				= 29,
				SHADOW_MAP						= 30,
				ZBUFFER_TEST					= 31,
				ZBUFFER_WRITE					= 32,
				LOD_LANDSCAPE					= 33,
				LOD_BUILDING					= 34,
				NO_FADE							= 35,
				REFRACTION_TINT					= 36,
				VERTEX_COLORS					= 37,
				FIRST_PERSON					= 38,
				
				// HairShaderProperty
				FIRST_LIGHT_IS_POINTLIGHT		= 39,
				SECOND_LIGHT					= 40,
				THIRD_LIGHT						= 41,
				
				// TallGrassShaderProperty
				VERTEX_LIGHTING					= 42,
				UNIFORM_SCALE					= 43,
				FIT_SLOPE						= 44,
				BILLBOARD						= 45,
				
				NO_LOD_LAND_BLEND				= 46,
				ENVMAP_LIGHT_FADE				= 47,
				WIREFRAME						= 48,
				VATS_SELECTION					= 49,
				SHOW_IN_LOCAL_MAP				= 50,
				PREMULT_ALPHA					= 51,
				SKIP_NORMAL_MAPS				= 52,
				ALPHA_DECAL						= 53,
				NO_TRANSPARENCY_MULTISAMPLING	= 54,
				STINGER_PROP					= 55,
				UNK3							= 56,
				UNK4							= 57,
				UNK5							= 58,
				UNK6							= 59,
				UNK7							= 60,
				UNK8							= 61,
				SOFT_DEPTH						= 62,
				REALTIME_CUBEMAP				= 63,
				MAX_FLAGS						= 64
			};
		};
		using Bits = _Bits::Bits;

		struct _Flags {
			enum Flags1 : uint32_t {
				SPECULAR						= 1u << Bits::SPECULAR,
				SKINNED							= 1u << Bits::SKINNED,
				LOW_DETAIL						= 1u << Bits::LOW_DETAIL,
				VERTEX_ALPHA					= 1u << Bits::VERTEX_ALPHA,
				MOTION_BLUR						= 1u << Bits::MOTION_BLUR,
				SINGLE_PASS						= 1u << Bits::SINGLE_PASS,
				FALLOFF							= 1u << Bits::FALLOFF,
				ENVIRONMENT_MAPPING				= 1u << Bits::ENVIRONMENT_MAPPING,
				ALPHA_TEXTURE					= 1u << Bits::ALPHA_TEXTURE,
				ZPREPASS						= 1u << Bits::ZPREPASS,
				FACEGEN							= 1u << Bits::FACEGEN,
				PARALLAX						= 1u << Bits::PARALLAX,
				MODEL_SPACE_NORMALS				= 1u << Bits::MODEL_SPACE_NORMALS,
				NON_PROJECTIVE_SHADOWS			= 1u << Bits::NON_PROJECTIVE_SHADOWS,
				LANDSCAPE						= 1u << Bits::LANDSCAPE,
				REFRACTION						= 1u << Bits::REFRACTION,
				REFRACTION_FIRE					= 1u << Bits::REFRACTION_FIRE,
				EYE_ENVIRONMENT_MAPPING			= 1u << Bits::EYE_ENVIRONMENT_MAPPING,
				HAIR							= 1u << Bits::HAIR,
				DYNAMIC_ALPHA					= 1u << Bits::DYNAMIC_ALPHA,
				LOCAL_MAP_HIDE_SECRET			= 1u << Bits::LOCAL_MAP_HIDE_SECRET,
				WINDOW_ENVIRONMENT_MAPPING		= 1u << Bits::WINDOW_ENVIRONMENT_MAPPING,
				TREE_BILLBOARD					= 1u << Bits::TREE_BILLBOARD,
				SHADOW_FRUSTUM					= 1u << Bits::SHADOW_FRUSTUM,
				MULTIPLE_TEXTURES				= 1u << Bits::MULTIPLE_TEXTURES,
				REMAPPABLE_TEXTURES				= 1u << Bits::REMAPPABLE_TEXTURES,
				DECAL							= 1u << Bits::DECAL,
				DYNAMIC_DECAL					= 1u << Bits::DYNAMIC_DECAL,
				PARALLAX_OCCLUSION				= 1u << Bits::PARALLAX_OCCLUSION,
				EXTERNAL_EMITTANCE				= 1u << Bits::EXTERNAL_EMITTANCE,
				SHADOW_MAP						= 1u << Bits::SHADOW_MAP,
				ZBUFFER_TEST					= 1u << Bits::ZBUFFER_TEST,
			};
			
			enum Flags2 : uint32_t {
				ZBUFFER_WRITE					= 1u << (Bits::ZBUFFER_WRITE - 32),
				LOD_LANDSCAPE					= 1u << (Bits::LOD_LANDSCAPE - 32),
				LOD_BUILDING					= 1u << (Bits::LOD_BUILDING - 32),
				NO_FADE							= 1u << (Bits::NO_FADE - 32),
				REFRACTION_TINT					= 1u << (Bits::REFRACTION_TINT - 32),
				VERTEX_COLORS					= 1u << (Bits::VERTEX_COLORS - 32),
				FIRST_PERSON					= 1u << (Bits::FIRST_PERSON - 32),
				FIRST_LIGHT_IS_POINTLIGHT		= 1u << (Bits::FIRST_LIGHT_IS_POINTLIGHT - 32),
				SECOND_LIGHT					= 1u << (Bits::SECOND_LIGHT - 32),
				THIRD_LIGHT						= 1u << (Bits::THIRD_LIGHT - 32),
				VERTEX_LIGHTING					= 1u << (Bits::VERTEX_LIGHTING - 32),
				UNIFORM_SCALE					= 1u << (Bits::UNIFORM_SCALE - 32),
				FIT_SLOPE						= 1u << (Bits::FIT_SLOPE - 32),
				BILLBOARD						= 1u << (Bits::BILLBOARD - 32),
				NO_LOD_LAND_BLEND				= 1u << (Bits::NO_LOD_LAND_BLEND - 32),
				ENVMAP_LIGHT_FADE				= 1u << (Bits::ENVMAP_LIGHT_FADE - 32),
				WIREFRAME						= 1u << (Bits::WIREFRAME - 32),
				VATS_SELECTION					= 1u << (Bits::VATS_SELECTION - 32),
				SHOW_IN_LOCAL_MAP				= 1u << (Bits::SHOW_IN_LOCAL_MAP - 32),
				PREMULT_ALPHA					= 1u << (Bits::PREMULT_ALPHA - 32),
				SKIP_NORMAL_MAPS				= 1u << (Bits::SKIP_NORMAL_MAPS - 32),
				ALPHA_DECAL						= 1u << (Bits::ALPHA_DECAL - 32),
				NO_TRANSPARENCY_MULTISAMPLING	= 1u << (Bits::NO_TRANSPARENCY_MULTISAMPLING - 32),
				STINGER_PROP					= 1u << (Bits::STINGER_PROP - 32),
				UNK3							= 1u << (Bits::UNK3 - 32),
				UNK4							= 1u << (Bits::UNK4 - 32),
				UNK5							= 1u << (Bits::UNK5 - 32),
				UNK6							= 1u << (Bits::UNK6 - 32),
				UNK7							= 1u << (Bits::UNK7 - 32),
				UNK8							= 1u << (Bits::UNK8 - 32),
				SOFT_DEPTH						= 1u << (Bits::SOFT_DEPTH - 32),
				REALTIME_CUBEMAP				= 1u << (Bits::REALTIME_CUBEMAP - 32),
			};
		};
		using Flags1 = _Flags::Flags1;
		using Flags2 = _Flags::Flags2;

		bool bSpecular						: 1;
		bool bSkinned						: 1;
		bool bLowDetail						: 1;
		bool bVertexAlpha					: 1;
		bool bMotionBlur					: 1;
		bool bSinglePass					: 1;
		bool bFalloff						: 1;
		bool bEnvironmentMapping			: 1;
		bool bAlphaTexture					: 1;
		bool bZPrepass						: 1;
		bool bFacegen						: 1;
		bool bParallax						: 1;
		bool bModelSpaceNormals				: 1;
		bool bNonProjectiveShadows			: 1;
		bool bLandscape						: 1;
		bool bRefraction					: 1;
		bool bFireRefraction				: 1;
		bool bEyeEnvironmentMapping			: 1;
		bool bHair							: 1;
		bool bDynamicAlpha					: 1;
		bool bLocalMapHideSecret			: 1;
		bool bWindowEnvironmentMapping		: 1;
		bool bTreeBillboard					: 1;
		bool bShadowFrustum					: 1;
		bool bMultipleTextures				: 1;
		bool bRemappableTextures			: 1;
		bool bDecal							: 1;
		bool bDynamicDecal					: 1;
		bool bParallaxOcclusion				: 1;
		bool bExternalEmittance				: 1;
		bool bShadowMap						: 1;
		bool bZBufferTest					: 1;
		bool bZBufferWrite					: 1;
		bool bLODLandscape					: 1;
		bool bLODBuilding					: 1;
		bool bNoFade						: 1;
		bool bRefractionTint				: 1;
		bool bVertexColors					: 1;
		bool b1stPerson						: 1;
		bool b1stLightIsPointlight			: 1;
		bool b2ndLight						: 1;
		bool b3rdLight						: 1;
		bool bVertexLighting				: 1;
		bool bUniformScale					: 1;
		bool bFitSlope						: 1;
		bool bBillboardEnvFade				: 1;
		bool bNoLODLandBlend				: 1;
		bool bEnvmapLightFade				: 1;
		bool bWireframe						: 1;
		bool bVatsSelection					: 1;
		bool bShowInLocalMap				: 1;
		bool bPremultAlpha					: 1;
		bool bSkipNormalMaps				: 1;
		bool bAlphaDecal					: 1;
		bool bNoTransparencyMultisampling	: 1;
		bool bStingerProp					: 1;
		bool bUnk3							: 1;
		bool bUnk4							: 1;
		bool bUnk5							: 1;
		bool bUnk6							: 1;
		bool bUnk7							: 1;
		bool bUnk8							: 1;
		bool bSoftDepth						: 1;
		bool bRealtimeCubemap				: 1;
	};
	using ShaderBits = _ShaderFlags::_Bits::Bits;
	using ShaderFlags1 = _ShaderFlags::_Flags::Flags1;
	using ShaderFlags2 = _ShaderFlags::_Flags::Flags2;

	union {
		Bitfield32		ulFlags[2];
		_ShaderFlags	ullFlags;
	};
	float				fAlpha;
	float				fFadeAlpha;
	float				fEnvMapScale;
	float				fCameraDistance;
	int32_t				iLastRenderPassState;
	RenderPassArray*	pRenderPassArray;				// Mistakenly called pRenderPassList, Oblivion leftover
	RenderPassArray*	pDepthMapRenderPassArray;
	RenderPassArray*	pConstAlphaRenderPassArray;
	RenderPassArray*	pLocalMapRenderPassArray;
	RenderPassArray*	pSIBlockRenderPassArray;
	RenderPassArray*	pWaterFogRenderPassArray;
	RenderPassArray*	pSilhouettePassArray;
	int32_t				iShader;
	float				fDepthBias;

	CREATE_OBJECT(BSShaderProperty, 0xBA9250);
	NIRTTI_ADDRESS(0x1200464);

	int32_t GetShader() const;
	void SetShader(int32_t aiShader);

	bool GetFlag(ShaderBits aeBit) const;
	void SetFlag(ShaderBits aeBit, bool abEnable);
	static void SetFlagRecurse(NiAVObject* apObject, ShaderBits aeBit, bool abSet);

	void SetAlpha(float afAlpha);

	void ClearRenderPasses();

	void InvalidateState() {
		iLastRenderPassState = -1;
	}

	bool HasSpecular() const { return ullFlags.bSpecular; }
	bool IsSkinned() const { return ullFlags.bSkinned; }
	bool IsLowDetail() const { return ullFlags.bLowDetail; }
	bool HasVertexAlpha() const { return ullFlags.bVertexAlpha; }
	bool HasMotionBlur() const { return ullFlags.bMotionBlur; }
	bool IsSinglePass() const { return ullFlags.bSinglePass; }
	bool IsEmpty() const { return ullFlags.bFalloff; }
	bool HasEnvironmentMapping() const { return ullFlags.bEnvironmentMapping; }
	bool HasAlphaTexture() const { return ullFlags.bAlphaTexture; }
	bool IsZPrePass() const { return ullFlags.bZPrepass; }
	bool IsFaceGen() const { return ullFlags.bFacegen; }
	bool IsParallax() const { return ullFlags.bParallax; }
	bool HasModelSpaceNormals() const { return ullFlags.bModelSpaceNormals; }
	bool HasNonProjectiveShadows() const { return ullFlags.bNonProjectiveShadows; }
	bool IsLandscape() const { return ullFlags.bLandscape; }
	bool HasRefraction() const { return ullFlags.bRefraction; }
	bool HasFireRefraction() const { return ullFlags.bFireRefraction; }
	bool HasEyeEnvironmentMapping() const { return ullFlags.bEyeEnvironmentMapping; }
	bool IsHair() const { return ullFlags.bHair; }
	bool HasDynamicAlpha() const { return ullFlags.bDynamicAlpha; }
	bool IsLocalMapHideSecret() const { return ullFlags.bLocalMapHideSecret; }
	bool HasWindowEnvironmentMapping() const { return ullFlags.bWindowEnvironmentMapping; }
	bool IsTreeBillboard() const { return ullFlags.bTreeBillboard; }
	bool UsesShadowFrustum() const { return ullFlags.bShadowFrustum; }
	bool HasMultipleTextures() const { return ullFlags.bMultipleTextures; }
	bool HasRemappableTextures() const { return ullFlags.bRemappableTextures; }
	bool IsSinglePassDecal() const { return ullFlags.bDecal; }
	bool IsSinglePassDynamicDecal() const { return ullFlags.bDynamicDecal; }
	bool HasParallaxOcclusion() const { return ullFlags.bParallaxOcclusion; }
	bool HasExternalEmittance() const { return ullFlags.bExternalEmittance; }
	bool IsShadowMap() const { return ullFlags.bShadowMap; }
	bool HasZBufferTest() const { return ullFlags.bZBufferTest; }
	bool HasZBufferWrite() const { return ullFlags.bZBufferWrite; }
	bool IsLODLand() const { return ullFlags.bLODLandscape; }
	bool IsLODBuilding() const { return ullFlags.bLODBuilding; }
	bool HasNoFade() const { return ullFlags.bNoFade; }
	bool HasRefractionTint() const { return ullFlags.bRefractionTint; }
	bool HasVertexColors() const { return ullFlags.bVertexColors; }
	bool Is1stPerson() const { return ullFlags.b1stPerson; }
	bool Is1stLightPointlight() const { return ullFlags.b1stLightIsPointlight; }
	bool Is2ndLight() const { return ullFlags.b2ndLight; }
	bool Is3rdLight() const { return ullFlags.b3rdLight; }
	bool HasVertexLighting() const { return ullFlags.bVertexLighting; }
	bool HasUniformScale() const { return ullFlags.bUniformScale; }
	bool DoesFitSlopes() const { return ullFlags.bFitSlope; }
	bool HasBillboardAndEnvmapLightFade() const { return ullFlags.bBillboardEnvFade; }
	bool HasNoLODLandBlend() const { return ullFlags.bNoLODLandBlend; }
	bool HasEnvmapLightFade() const { return ullFlags.bEnvmapLightFade; }
	bool IsWireframe() const { return ullFlags.bWireframe; }
	bool IsVATSSelection() const { return ullFlags.bVatsSelection; }
	bool IsShownOnMap() const { return ullFlags.bShowInLocalMap; }
	bool HasPremultAlpha() const { return ullFlags.bPremultAlpha; }
	bool DoesSkipNormalMaps() const { return ullFlags.bSkipNormalMaps; }
	bool IsAlphaDecal() const { return ullFlags.bAlphaDecal; }
	bool HasNoTMSAA() const { return ullFlags.bNoTransparencyMultisampling; }
	bool IsStingerProperty() const { return ullFlags.bStingerProp; }
	bool HasRealtimeCubeMaps() const { return ullFlags.bRealtimeCubemap; }

	static constexpr AddressPtr<float, 0x11F9460> fEnvMapLOD2;
	static constexpr AddressPtr<float, 0x11F9468> fEyeEnvMapLOD2;
	static constexpr AddressPtr<float, 0x11F9458> fSpecularLODEndFade;
};

ASSERT_SIZE(BSShaderProperty, 0x60);
ASSERT_SIZE(BSShaderProperty::RenderPass, 0x10);
ASSERT_SIZE(BSShaderProperty::RenderPassArray, 0x14);

// GAME - 0xBA8EC0
// GECK - 0x908B90
template<typename ...Args>
inline BSShaderProperty::RenderPass::RenderPass(NiGeometry* apGeometry, uint16_t ausPassEnum, bool abFirst, uint8_t aucNumLights, Args ...args) noexcept {
#ifdef GAME
	CdeclCall(0xBA8EC0, this, apGeometry, ausPassEnum, abFirst, aucNumLights, std::forward<Args>(args)...);
#else
	CdeclCall(0x908B90, this, apGeometry, ausPassEnum, abFirst, aucNumLights, std::forward<Args>(args)...);
#endif
}

// GAME - 0xBA8C50
// GECK - 0x908950
template<typename ...Args>
inline void BSShaderProperty::RenderPass::SetLights(uint8_t aucNumLights, Args ...args) {
#ifdef GAME
	CdeclCall(0xBA8C50, this, aucNumLights, std::forward<Args>(args)...);
#else
	CdeclCall(0x908950, this, aucNumLights, std::forward<Args>(args)...);
#endif
}
