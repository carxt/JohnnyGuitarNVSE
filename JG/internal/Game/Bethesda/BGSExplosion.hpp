#pragma once

#include "BGSPreloadable.hpp"
#include "TESBoundObject.hpp"
#include "TESEnchantableForm.hpp"
#include "TESFullName.hpp"
#include "TESImageSpaceModifiableForm.hpp"
#include "TESModel.hpp"

class TESObjectLIGH;
class TESSound;
class BGSImpactDataSet;

class BGSExplosion : public TESBoundObject, public TESFullName, public TESModel, public TESEnchantableForm, public BGSPreloadable, public TESImageSpaceModifiableForm {
public:
	BGSExplosion();
	~BGSExplosion();

	struct ALIGN4 _ExplosionFlags {
		enum Flags : uint32_t {
			RADIUS_IN_BS_UNITS				= 1u << 0,
			USE_WORLD_ORIENTATION			= 1u << 1,
			KNOCKDOWN_ALWAYS				= 1u << 2,
			KNOCKDOWN_BY_FORMULA			= 1u << 3,
			IGNORE_LOS_CHECK				= 1u << 4,
			PUSH_SOURCE_REF_ONLY			= 1u << 5,
			IGNORE_IMAGESPACE_SWAP			= 1u << 6,
		};

		bool bRadiusInBSUnits			: 1;
		bool bUseWorldOrientation		: 1;
		bool bKnockdownAlways			: 1;
		bool bKnockdownByFormula		: 1;
		bool bIgnoreLOSCheck			: 1;
		bool bPushSourceRefOnly			: 1;
		bool bIgnoreImageSpaceSwap		: 1;
	};
	using ExplosionFlags = _ExplosionFlags::Flags;

	struct Data {
		TESForm*					pImpactPlacedObject;
		float						fForce;
		float						fDamage;
		float						fRadius;
		TESObjectLIGH*				pLight;
		TESSound*					pSound1;
		Bitfield<_ExplosionFlags>	uiFlags;
		float						fImageSpaceRadius;
		BGSImpactDataSet*			pImpactDataSet;
		TESSound*					pSound2;
		float						fRadiationRads;
		float						fRadiationDissipationTime;
		float						fRadiationRadius;
		SOUND_LEVEL					eSoundLevel;
	};

	Data kData;

	TESFORM_TYPE(BGSExplosion);

	TESForm* GetImpactPlacedObject() const;
	void SetImpactPlacedObject(TESForm* apForm);

	float GetForce() const;
	void SetForce(float afForce);

	float GetDamage() const;
	void SetDamage(float afDamage);

	float GetRadius() const;
	float GetRadiusBSUnits() const;
	void SetRadius(float afRadius);

	TESObjectLIGH* GetLight() const;
	void SetLight(TESObjectLIGH* apLight);

	TESSound* GetSound1() const;
	void SetSound1(TESSound* apSound);

	bool GetFlag(uint32_t auiFlag);
	void SetFlag(uint32_t auiFlag, bool abVal);

	float GetImageSpaceRadius() const;
#ifdef GAME
	float GetImageSpaceRadiusBSUnits() const;
#endif
	void SetImageSpaceRadius(float afRadius);

	BGSImpactDataSet* GetImpactDataSet() const;
	void SetImpactDataSet(BGSImpactDataSet* apImpactDataSet);

	TESSound* GetSound2() const;
	void SetSound2(TESSound* apSound);

	float GetRadiationRads() const;
	void SetRadiationRads(float afRads);

	float GetRadiationDissipationTime() const;
	void SetRadiationDissipationTime(float afTime);

	float GetRadiationRadius() const;
#ifdef GAME
	float GetRadiationRadiusBSUnits() const;
#endif
	void SetRadiationRadius(float afRadius);

	SOUND_LEVEL GetSoundLevel() const;
	void SetSoundLevel(SOUND_LEVEL aeLevel);
#ifdef GAME
	int32_t GetSoundLevelValue() const;
#endif
};

#ifdef GAME
ASSERT_SIZE(BGSExplosion, 0xA8);
#else
ASSERT_SIZE(BGSExplosion, 0xD8);
#endif