#pragma once

#include "BSSimpleList.hpp"
#include "TESIcon.hpp"
#include "TESFullName.hpp"
#include "TESModel.hpp"
#include "TESDescription.hpp"
#include "TESForm.hpp"
#include "MagicSystem.hpp"
#include "EffectArchetypes.hpp"
#include "ActorValue.hpp"

class TESObjectLIGH;
class TESEffectShader;
class TESSound;

class EffectSetting : public TESForm, public TESModel, public TESDescription, public TESFullName, public TESIcon {
public:
	EffectSetting();
	~EffectSetting();

	struct ALIGN4 _EffectFlags {
		enum Flags : uint32_t {
			HOSTILE						= 1u << 0,
			RECOVER						= 1u << 1,
			DETRIMENTAL					= 1u << 2,
			MAGNITUDE_PERCENT			= 1u << 3,
			RANGE_SELF					= 1u << 4,
			RANGE_TOUCH					= 1u << 5,
			RANGE_TARGET				= 1u << 6,
			NO_DURATION					= 1u << 7,
			NO_MAGNITUDE				= 1u << 8,
			NO_AREA						= 1u << 9,
			PERSIST						= 1u << 10,
			CREATE_SPELLMAKING			= 1u << 11,
			GORY_VISUALS				= 1u << 12,
			DISPLAY_EFFECT_NAME			= 1u << 13,
			LIGHT_NEGATE				= 1u << 14,
			NO_RECAST					= 1u << 15,
			USE_ASSOCIATED_WEAPON		= 1u << 16,
			USE_ASSOCIATED_ARMOR		= 1u << 17,
			USE_ASSOCIATED_CREATURE		= 1u << 18,
			USE_ASSOCIATED_SKILL		= 1u << 19,
			USE_ASSOCIATED_ATTRIBUTE	= 1u << 20,
			PLAYER_KNOWS				= 1u << 21,
			DISABLED					= 1u << 22,
			MARKER_EFFECT				= 1u << 23,
			PAINLESS					= 1u << 24,
			SPRAY_PROJECTILE			= 1u << 25,
			BOLT_PROJECTILE				= 1u << 26,
			NO_HIT_EFFECT				= 1u << 27,
			NO_DEATH_DISPEL				= 1u << 28,
			HAVOK_EXPLOSION				= 1u << 29,
			MAGNITUDE_LEVEL				= 1u << 30,
			MAGNITUDE_FEET				= 1u << 31,
		};

		bool bHostile					: 1;
		bool bRecover					: 1;
		bool bDetrimental				: 1;
		bool bMagnitudePercent			: 1;
		bool bRangeSelf					: 1;
		bool bRangeTouch				: 1;
		bool bRangeTarget				: 1;
		bool bNoDuration				: 1;
		bool bNoMagnitude				: 1;
		bool bNoArea					: 1;
		bool bPersist					: 1;
		bool bCreateSpellmaking			: 1;
		bool bGoryVisuals				: 1;
		bool bDisplayEffectName			: 1;
		bool bLightNegate				: 1;
		bool bNoRecast					: 1;
		bool bUseAssociatedWeapon		: 1;
		bool bUseAssociatedArmor		: 1;
		bool bUseAssociatedCreature		: 1;
		bool bUseAssociatedSkill		: 1;
		bool bUseAssociatedAttribute	: 1;
		bool bPlayerKnows				: 1;
		bool bDisabled					: 1;
		bool bMarkerEffect				: 1;
		bool bPainless					: 1;
		bool bSprayProjectile			: 1;
		bool bBoltProjectile			: 1;
		bool bNoHitEffect				: 1;
		bool bNoDeathDispel				: 1;
		bool bHavokExplosion			: 1;
		bool bMagnitudeLevel			: 1;
		bool bMagnitudefeet				: 1;
	};
	using EffectFlags = _EffectFlags::Flags;

	struct EffectSettingData {
		Bitfield<_EffectFlags>	uiFlags;
		float					fBaseCost;
		TESForm*				pAssociatedItem;
		ActorValue::Index		eAssociatedSkill;
		ActorValue::Index		eResistVariable;
		int16_t					sCounterEffectCount;
		TESObjectLIGH*			pLight;
		float					fProjectileSpeed;
		TESEffectShader*		pEffectShader;
		TESEffectShader*		pEnchantEffectShader;
		TESSound*				pEffectSound;
		TESSound*				pBoltSound;
		TESSound*				pHitSound;
		TESSound*				pAreaSound;
		float					fEnchantFactor;
		float					fBarterFactor;
		EffectArchetypes::Type	eArchetype;
		ActorValue::Index		eAssociatedActorValue;
	};

	bool(__cdecl*					pFilterValidationFunction)(EffectSetting*, void*);
	void*							pFilterValidationItem;
	EffectSettingData				kData;
	BSSimpleList<EffectSetting*>	kCounterEffects;
	int32_t							iEffectLoadedCount;
	int32_t							iAssociatedItemLoadedCount;

	TESFORM_TYPE(EffectSetting);

	bool GetFlag(uint32_t auiFlag) const;
	void SetFlag(uint32_t auiFlag, bool abVal);

	Bitfield<_EffectFlags> GetFlags() const;
	void SetFlags(uint32_t auiFlags);

	EffectArchetypes::Type GetEffectArchetype() const;
	void SetEffectArchetype(EffectArchetypes::Type aeType);

	ActorValue::Index GetAssociatedActorValue() const;
	void SetAssociatedActorValue(ActorValue::Index aeActorValue);

	BSString GetEffectName() const;
};

ASSERT_SIZE(EffectSetting, 0xB0);