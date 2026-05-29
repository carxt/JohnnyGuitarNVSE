#pragma once

#include "BGSDestructibleObjectForm.hpp"
#include "BGSPreloadable.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "TESBoundObject.hpp"
#include "TESFullName.hpp"
#include "TESModel.hpp"

class TESObjectLIGH;
class TESSound;
class TESObjectWEAP;

class BGSProjectile : public TESBoundObject, public TESFullName, public TESModel, public BGSPreloadable, public BGSDestructibleObjectForm {
public:
	BGSProjectile();
	~BGSProjectile();

	struct ALIGN4 _ProjectileFlags {
		enum Flags : uint32_t {
			HITSCAN						= 1u << 0,
			HAS_EXPLOSION				= 1u << 1,
			HAS_EXPLOSION_ALT_TRIGGER	= 1u << 2,
			HAS_MUZZLE_FLASH			= 1u << 3,
			BOUNCE_ON_IMPACT			= 1u << 4,
			CAN_TURN_OFF				= 1u << 5,
			CAN_PICK_UP					= 1u << 6,
			SUPERSONIC					= 1u << 7,
			PINS_LIMBS					= 1u << 8,
			PASS_SMALL_TRANSPARENT		= 1u << 9,
			DETONATES					= 1u << 10,
			ROTATES						= 1u << 11,

			MOTION_MISSILE				= 1u << 16,
			MOTION_GRENADE				= 1u << 17,
			MOTION_BEAM					= 1u << 18,
			MOTION_FLAMETHROWER			= 1u << 19,
			MOTION_CONTINUOUS_BEAM		= 1u << 20,

			MOTION_TYPE_MASK			= 0x1F0000,
		};

		bool bHitScan						: 1;
		bool bHasExplosion					: 1;
		bool bHasExplosionAltTrigger		: 1;
		bool bHasMuzzleFlash				: 1;
		bool bBounceOnImpact				: 1;
		bool bCanTurnOff					: 1;
		bool bCanPickUp						: 1;
		bool bSupersonic					: 1;
		bool bPinsLimbs						: 1;
		bool bPassThroughSmallTransparent	: 1;
		bool bDetonates						: 1;
		bool bRotates						: 1;
		bool								: 4;
		bool bMotionMissile					: 1;
		bool bMotionGrenade					: 1;
		bool bMotionBeam					: 1;
		bool bMotionFlamethrower			: 1;
		bool bMotionContinuousBeam			: 1;
	};
	using ProjectileFlags = _ProjectileFlags::Flags;

	struct Data {
		Bitfield<_ProjectileFlags>	uiFlags;	
		float						fGravity;		
		float						fSpeed;			
		float						fRange;			
		TESObjectLIGH*				pLight;
		TESObjectLIGH*				pMuzzleFlashLight;
		float						fTracerChance;	
		float						fAltProximity;	
		float						fAltTimer;		
		BGSExplosion*				pExplosionForm;	
		TESSound*					pSoundProjectile;
		float						fMuzzleFlashDuration;	
		float						fFadeDuration;	
		float						fImpactForce;	
		TESSound*					pSoundCountDown;
		TESSound*					pSoundDisable;	
		TESObjectWEAP*				pDefaultWeapSrc;
		NiPoint3					kRotation;		
		float						fBouncyMult;
	};

	Data			kData;
	TESModel		kMuzzleFlash;	
	uint32_t		uiSoundLevel;

	TESFORM_TYPE(BGSProjectile);

	const Data& GetData() const;

	bool IsFlagSet(uint32_t auiFlag) const;

	bool GetHitScan() const;

	bool GetHasExplosion() const;

	bool GetHasExplosionAltTrigger() const;

	bool GetHasMuzzleFlash() const;

	bool GetCanTurnOff() const;

	bool GetCanPickup() const;

	bool GetSupersonic() const;

	bool GetPinsLimbs() const;
	
	bool GetPassThroughSmallTransparent() const;

	bool GetDetonates() const;

	bool GetRotates() const;

	TESObjectLIGH* GetLight() const;
	
	TESObjectLIGH* GetMuzzleFlashLight() const;

	float GetMuzzleFlashDuration() const;

	BGSExplosion* GetExplosion() const;
};

ASSERT_SIZE(BGSProjectile, 0xD0);