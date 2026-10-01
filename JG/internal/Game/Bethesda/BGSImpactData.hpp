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

	struct _Orientation {
		enum Orientation {
			SURFACE_NORMAL	= 0,
			PROJ_VECTOR		= 1,
			PROJ_REFLECT	= 2,
			COUNT			= 3
		};
	};
	using Orientation = _Orientation::Orientation;

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
		SOUND_LEVEL					eSoundLevel;
		Bitfield<_ImpactDataFlags>	ucFlags;
	};

	Data			kData;
	BGSTextureSet*	pTextureSet;
	TESSound*		pSoundA;
	TESSound*		pSoundB;
	DecalData		kDecalData;

	TESFORM_TYPE(BGSImpactData);

	float GetEffectDuration() const;
	void SetEffectDuration(float afDuration);

	Orientation GetImpactOrientation() const;
	void SetImpactOrientation(Orientation aeOrientation);

	float GetDecalAngleThreshold() const;
	void SetDecalAngleThreshold(float afThreshold);

	float GetPlacementRadius() const;
	void SetPlacementRadius(float afRadius);

	SOUND_LEVEL GetSoundLevel() const;
	void SetSoundLevel(SOUND_LEVEL aeLevel);
#ifdef GAME
	int32_t GetSoundLevelValue() const;
#endif

	bool GetUseTextureSetDecalData() const;
	void SetUseTextureSetDecalData(bool abVal);

	BGSTextureSet* GetDecalTextureSet() const;
	void SetDecalTextureSet(BGSTextureSet* apTextureSet);

	TESSound* GetSoundA() const;
	void SetSoundA(TESSound* apSound);

	TESSound* GetSoundB() const;
	void SetSoundB(TESSound* apSound);

	float GetDecalMinWidth() const;

	float GetDecalMaxWidth() const;

	float GetDecalMinHeight() const;

	float GetDecalMaxHeight() const;

	float GetDecalDepth() const;

	float GetDecalShininess() const;

	float GetDecalParallaxScale() const;

	uint16_t GetDecalParallaxPasses() const;

	bool GetIsParallax() const;

	bool GetAlphaBlending() const;

	bool GetAlphaTesting() const;

	uint32_t GetDecalColor() const;
};

#ifdef GAME
ASSERT_SIZE(BGSImpactData, 0x78);
#else
ASSERT_SIZE(BGSImpactData, 0x98);
#endif