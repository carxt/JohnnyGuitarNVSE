#pragma once

#include "BGSDestructibleObjectForm.hpp"
#include "BGSPreloadable.hpp"
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

	struct _MotionType {
		enum Type {
			MOTION_MISSILE				= 1u << 16,
			MOTION_GRENADE				= 1u << 17,
			MOTION_BEAM					= 1u << 18,
			MOTION_FLAMETHROWER			= 1u << 19,
			MOTION_CONTINUOUS_BEAM		= 1u << 20,
		};
	};
	using MotionType = _MotionType::Type;

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
			EXPLOSION_DETONATES			= 1u << 10,
			ROTATES						= 1u << 11,

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
		bool bExplosionDetonates			: 1;
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
		float						fExplosionProximity;
		float						fExplosionTimer;
		BGSExplosion*				pExplosionType;
		TESSound*					pActiveSoundLoop;
		float						fMuzzleFlashDuration;	
		float						fFadeOutTime;
		float						fImpactForce;	
		TESSound*					pCountdownSound;
		TESSound*					pDeactivateSound;
		TESObjectWEAP*				pDefaultWeapSrc;
		float						fRotationX;
		float						fRotationY;
		float						fRotationZ;
		float						fBounceMultiplier;
	};

	Data			kData;
	TESModel		kMuzzleFlash;	
	SOUND_LEVEL		eSoundLevel;

	TESFORM_TYPE(BGSProjectile);

	const Data& GetData() const;
	Data& GetData();

	bool GetFlag(uint32_t auiFlag) const;
	void SetFlag(uint32_t auiFlag, bool abVal);

	bool GetHitScan() const;

	bool GetHasExplosion() const;

	bool GetHasExplosionAltTrigger() const;

	bool GetHasMuzzleFlash() const;

	bool GetCanTurnOff() const;

	bool GetCanPickup() const;

	bool GetSupersonic() const;

	bool GetPinsLimbs() const;
	
	bool GetPassThroughSmallTransparent() const;

	bool GetHasExplosionDetonates() const;

	bool GetHasRotation() const;

	MotionType GetMotionType() const;
	void SetMotionType(MotionType aeType);

	float GetGravity() const;
	void SetGravity(float afGravity);

	float GetSpeed() const;
	void SetSpeed(float afSpeed);

	float GetRange() const;
	void SetRange(float afRange);

	TESObjectLIGH* GetLight() const;
	void SetLight(TESObjectLIGH* apLight);

	TESObjectLIGH* GetMuzzleFlashLight() const;
	void SetMuzzleFlashLight(TESObjectLIGH* apLight);

	float GetTracerChance() const;
	void SetTracerChance(float afVal);

	float GetExplosionProximity() const;
	void SetExplosionProximity(float afVal);

	float GetExplosionTimer() const;
	void SetExplosionTimer(float afVal);

	BGSExplosion* GetExplosion() const;
	void SetExplosion(BGSExplosion* apExplosion);

	TESSound* GetActiveSound() const;
	void SetActiveSound(TESSound* apSound);

	float GetMuzzleFlashDuration() const;
	void SetMuzzleFlashDuration(float afVal);

	float GetFadeOutTime() const;
	void SetFadeOutTime(float afVal);

	float GetImpactForce() const;
	void SetImpactForce(float afVal);

	TESSound* GetCountdownSound() const;
	void SetCountdownSound(TESSound* apSound);

	TESSound* GetDeactivateSound() const;
	void SetDeactivateSound(TESSound* apSound);

	TESObjectWEAP* GetDefaultWeaponSource() const;
	void SetDefaultWeaponSource(TESObjectWEAP* apWeapon);

	float GetRotationX() const;
	void SetRotationX(float afVal);

	float GetRotationY() const;
	void SetRotationY(float afVal);

	float GetRotationZ() const;
	void SetRotationZ(float afVal);

	float GetBounceMultiplier() const;
	void SetBounceMultiplier(float afVal);

	const TESModel* GetMuzzleFlashModel() const;
	TESModel* GetMuzzleFlashModel();

	SOUND_LEVEL GetSoundLevel() const;
	void SetSoundLevel(SOUND_LEVEL aeLevel);

#ifdef GAME
	bool DecideIsTracer() const;
#endif
};

#ifdef GAME
ASSERT_SIZE(BGSProjectile, 0xD0);
#else
ASSERT_SIZE(BGSProjectile, 0x10C);
#endif