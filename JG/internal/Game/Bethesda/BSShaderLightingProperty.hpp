#pragma once

#include "BSShaderProperty.hpp"
#include "Gamebryo/NiTPointerList.hpp"
#include "Gamebryo/NiPoint4.hpp"
#include "Gamebryo/NiColorA.hpp"

NiSmartPointer(BSShaderLightingProperty);

class BSShaderLightingProperty : public BSShaderProperty {
public:
	BSShaderLightingProperty();
	virtual ~BSShaderLightingProperty();

	virtual void CopyTo(BSShaderLightingProperty* apShaderProp);
	virtual void CopyToMembers(BSShaderLightingProperty* apShaderProp);

	NiTPointerList<ShadowSceneLight*>	kLightList;
	float								fForcedDarkness;
	uint32_t							uiReferenceID;
	bool								bLightListChanged;
	NiTListIterator						kLightIterator;

	CREATE_OBJECT(BSShaderLightingProperty, 0xB71920);
	NIRTTI_ADDRESS(0x11FA560);

#ifdef GAME
	static constexpr AddressPtr<ShadowSceneLight, 0x11FA310>	kEmptyLight;
	static constexpr AddressPtr<NiPoint4, 0x11FA0C0, 37>		kShaderLightConstants;
	static constexpr AddressPtr<NiPoint4, 0x11FA090>			kHairTint;
	static constexpr AddressPtr<NiPoint4, 0x11FA0B0>			kLODLandParams;
#else
	static constexpr AddressPtr<ShadowSceneLight, 0xF24730>		kEmptyLight;
	static constexpr AddressPtr<NiPoint4, 0xF244E0, 37>			kShaderLightConstants;
	static constexpr AddressPtr<NiPoint4, 0xF244B0>				HairTint;
	static constexpr AddressPtr<NiPoint4, 0xF244D0>				kLODLandParams;
#endif

	uint32_t			GetNumberOfActiveLights() const;
	uint32_t			GetNumberOfActiveNonShadowLights() const;

	ShadowSceneLight*	GetNextLight(NiTListIterator& arIter) const;

	ShadowSceneLight*	GetFirstActiveLight(NiTListIterator& arIter) const;
	ShadowSceneLight*	GetNextActiveLight(NiTListIterator& arIter) const;

	ShadowSceneLight*	GetFirstActiveNonShadowLight(NiTListIterator& arIter) const;
	ShadowSceneLight*	GetNextActiveNonShadowLight(NiTListIterator& arIter) const;

	struct ShaderConstants {
		enum Index {
			AMBIENT					= 0,
			LIGHT_COLOR				= 1,
			LIGHT_POSITION			= 11,
			LIGHT_POSITION_START	= 11,
			LIGHT_POSITION_END		= 19,
			LIGHT_DIRECTION			= 19,
			LIGHT_RADIUS			= 19,
			EMITTANCE_COLOR			= 27,
			FOG_PARAM				= 28,
			FOG_COLOR				= 29,
			EYE_POSITION			= 30,
			EYE_DIRECTION			= 31,
			EYE_RIGHT				= 32,
			TOGGLES					= 33,
			HIGH_DETAIL_RANGE		= 34,
			STBB_COLOR_CONSTANTS	= 35,
			LOD_TEX_PARAMS			= 36,
			COUNT					= 37
		};

		union Toggles {
			struct {
				float bUseVertexColors;
				float fNormalStrength;
				float fEnvMapScale;
				float fHasMask;
			};

			struct {
				float bUseVertexColors;
				float bUseFog;
				float fSpecularity;
				float fAlphaTestRef;
			};
		};

		struct FogParams {
			float fDistFar;
			float fDistNear;
			float fPower;
			float fUnknown;
		};

		struct LODTexParams {
			float fTerrainTexOffsetX;
			float fTerrainTexOffsetY;
			float fTerrainTexFade;
			float fTerrainDetailTexScale;
		};

		NiColorA		kAmbientColor;
		NiColorA		kLightColors[10];
		NiPoint4		kLightPositions[8];
		union {
			NiPoint4	kLightDirection;
			NiPoint4	kLightRadius[8];
		};
		NiColorA		kEmittanceColor;
		FogParams		kFogParams;
		NiColorA		kFogColor;
		NiPoint4		kEyePosition;
		NiPoint4		kEyeDirection;
		NiPoint4		kEyeRight;
		Toggles			kToggles;
		NiPoint4		kHighDetailRange;
		NiPoint4		kSTBBColorConstants;
		LODTexParams	kLODTexParams;
	};

	static void				SetShaderConstant(uint32_t auiIndex, NiPoint4 akValue);
	static ShaderConstants&	GetShaderConstants();
};

ASSERT_SIZE(BSShaderLightingProperty, 0x7C);