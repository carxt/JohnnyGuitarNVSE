#pragma once

#include "TESForm.hpp"
#include "TESModel.hpp"
#include "DecalData.hpp"

class BGSTextureSet;
class TESSound;

class BGSImpactData : public TESForm, public TESModel {
public:
	BGSImpactData();
	~BGSImpactData();

	enum Orientation {
		ORIENT_SURFACE_NORMAL	= 0,
		ORIENT_PROJ_VECTOR		= 1,
		ORIENT_PROJ_REFLECT		= 2,
		ORIENT_COUNT			= 3
	};

	struct ALIGN1 _ImpactDataFlags {
		enum Flags : uint8_t {
			USE_TEXTURESET_DECAL_DATA = 1u << 0,
		};

		bool bUseTextureSetDecalData : 1;
	};
	using ImpactDataFlags = _ImpactDataFlags::Flags;

	struct Data {
		float						fEffectDuration;
		Orientation					eOrient;
		float						fAngleThreshold;
		float						fPlacementRadius;
		uint32_t					eSoundLevel;
		Bitfield<_ImpactDataFlags>	ucFlags;
	};

	Data			kData;
	BGSTextureSet*	pTextureSet;
	TESSound*		pSound1;
	TESSound*		pSound2;
	DecalData		kDecalData;

	TESFORM_TYPE(BGSImpactData);
};

ASSERT_SIZE(BGSImpactData, 0x78);