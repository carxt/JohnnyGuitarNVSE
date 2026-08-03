#pragma once

#include "MobileObject.hpp"
#include "BSSoundHandle.hpp"
#include "Gamebryo/NiTransform.hpp"

class NiLight;
class ActorCause;
class BGSProjectile;
class hkpWorldObject;
class hkpCollidable;
class ProjectileTarget;
class TESFaction;

class Projectile : public MobileObject {
public:
	struct _Type {
		enum Type {
			UNKNOWN,
			BEAM,
			FLAME,
			GRENADE,
			MISSILE,
			CONTINUOUS_BEAM,
		};
	};
	using Type = _Type::Type;

	virtual Type	GetProjectileType() const;
	virtual void	Initialize();
	virtual void	Process3D();
	virtual void	UpdateProjectile(float afTimeDelta);
	virtual bool	ProcessImpacts();
	virtual bool 	IsMine() const;
	virtual void	ReportHavokDeactivation();
	virtual bool	TurnOff(Actor* apActor, bool abSilent);
	virtual bool	IsPermanent() const;
	virtual bool	RunTargetPick();
	virtual bool	AddImpact(Actor* apActor, const NiPoint3& arContactPoint, const NiPoint3& arContactNormal, hkpCollidable* apCollidable, uint32_t auiCollisionShapeKey, uint32_t aeHitMaterial);

	struct ImpactData {
		TESObjectREFR*  pCollidee;
		NiPoint3		kLocation;
		NiPoint3		kNormal;
		hkpWorldObject* pTargetWorldObject;
		uint32_t		eMaterial;
		uint32_t		eDamageLimb;
		bool			bProcessed;
		bool			bDoDamage;
		int16_t			sTargetWorldObjectCount;
		int16_t			sTargetWorldObjectIndex;
	};

	struct ALIGN4 _ProjectileFlags {
		enum Flags {
			HITSCAN_MODE				= 1u << 0,
			NO_3D						= 1u << 1,
			NO_CHAR_CONTROLLER			= 1u << 2,
			NO_COLLISION				= 1u << 3,
			TRACER						= 1u << 4,
			FADING						= 1u << 5,
			REORIENT					= 1u << 6,
			POST_PROCESS				= 1u << 7,
			CHECK_BEHIND_WALL			= 1u << 8,
			TURNED_OFF					= 1u << 9,
			ACTIVE_IN_INVENTORY			= 1u << 10,
			INVENTORY_FREAKOUT			= 1u << 11,
			ALWAYS_HIT_TARGET			= 1u << 12,
			SPAWN_EXPLOSION_AT_IMPACT	= 1u << 13,
			NO_PLAYER_PROXIMITY			= 1u << 14,
			KILL_ON_EXPLOSION			= 1u << 15,
			INITIALIZED					= 1u << 16,
			FAKE_SHOT					= 1u << 17,
			WHOLE_BODY_TARGETED			= 1u << 18,
			SHOOTER_IN_COMBAT			= 1u << 19,
			DETONATE					= 1u << 20
		};
	};
	using ProjectileFlags = _ProjectileFlags::Flags;

	BSSimpleList<ImpactData*>	kImpacts;
	bool						bImpactProcessed;
	NiTransform					kFollowOffset;
	Bitfield<_ProjectileFlags>	uiProjectileFlags;
	float						fPower;
	float						fSpeedMult;
	float						fRange;
	float						fAge;
	float						fDamage;
	float						fAlpha;
	float						fExplosionTimer;
	float						fBlinkTimer;
	float						fSpreadHeading;
	float						fSpreadLooking;
	float						fWeaponCondition;
	TESObjectWEAP*				pSourceWeapon;
	TESObjectREFR*				pShooter;
	TESObjectREFR*				pDesiredTarget;
	NiPoint3					kMovementDirection;
	float						fDistanceMoveds;
	NiPointer<NiLight>			spLight;
	bool						bSendAlarm;
	NiPointer<NiRefObject>		spPickCache;
	NiPointer<ActorCause>		spActorCause;
	float						fDecalSize;
	BSSoundHandle				kSound;
	BSSoundHandle				kCountdownSound;
	ProjectileTarget*			pProjectileTarget;
	ItemChange*					pRockItLauncherEntry;
	bool						bSoundFired;
	float						fSoundDistance;

	BGSProjectile* GetProjectileBase() const;

	bool IsFlagSet(uint32_t auiFlag) const;

	NiPoint3 GetMovementDirection() const;

	bool GetMineReactsToTarget(const Actor* apTarget, const Actor* apShooterActor, const TESFaction* apOwnerFaction) const;
};

ASSERT_SIZE(Projectile, 0x150);
ASSERT_SIZE(Projectile::ImpactData, 0x30);