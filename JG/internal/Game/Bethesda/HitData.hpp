#pragma once

#include "ActorValue.hpp"
#include "Gamebryo/NiPoint3.hpp"

class Actor;
class Projectile;
class Explosion;
class TESObjectWEAP;
class SpellItem;
class VATS_COMMAND;

class SPEC_EMPTY_BASES HitData : public BSMemObject {
public:
	HitData();
	~HitData();

	struct ALIGN4 _HitDataFlags {
		enum Flags : uint32_t {
			BLOCKED					= 0x1,
			BLOCK_WITH_WEAPON		= 0x2,
			CRITICAL				= 0x4,
			CRITICAL_ON_DEATH		= 0x8,
			FATAL					= 0x10,
			DISMEMBER_LIMB			= 0x20,
			EXPLODE_LIMB			= 0x40,
			CRIPPLE_LIMB			= 0x80,
			DISARM					= 0x100,
			DISABLE_WEAPON			= 0x200,
			SNEAK_ATTACK			= 0x400,
			IGNORE_CRITICAL			= 0x800,
			PREDICT_DAMAGE			= 0x1000,
			EXPLOSION				= 0x2000,
			JIP_ARMOR_PENETRATED	= 0x80000000,
		};

		bool bBlocked				: 1;
		bool bBlockWithWeapon		: 1;
		bool bCritical				: 1;
		bool bCriticalOnDeath		: 1;
		bool bFatal					: 1;
		bool bDismemberLimb			: 1;
		bool bExplodeLimb			: 1;
		bool bCrippleLimb			: 1;
		bool bDisarm				: 1;
		bool bDisableWeapon			: 1;
		bool bSneakAttack			: 1;
		bool bIgnoreCritical		: 1;
		bool bPredictDamage			: 1;
		bool bExplosion				: 1;
		bool						: 8;
		bool						: 7;
		bool bJIPArmorPenetrated	: 1;
	};
	using HitDataFlags = _HitDataFlags::Flags;

	Actor*						pSource;
	Actor*						pTarget;
	union {
		Projectile* __restrict	pProjectile;
		Explosion*  __restrict	pExplosion;
	};
	ActorValue::Index			eWeaponSkill;
	int32_t						eDamageLimb;
	float						fHealthDamage;
	float						fBaseWeaponDamage;
	float						fFatigueDamage;
	float						fLimbDamage;
	float						fBlockDTMod;
	float						fArmorDamage;
	float						fDamageToWeapon;
	TESObjectWEAP*				pWeapon;
	float						fHealthPercent;
	NiPoint3					kImpactPos;
	NiPoint3					kImpactAngle;
	SpellItem*					pCriticalEffect;
	VATS_COMMAND*				pVATSAction;
	Bitfield<_HitDataFlags>		uiFlags;
	float						fDamageMult;
	uint32_t					uiRefCount;

	void ClearData();
	void Copy(const HitData& arOther);
	HitData& operator=(const HitData& arOther);

	// GAME - 0x87ADF0
	inline void IncRefCount() {
		InterlockedIncrement(&uiRefCount);
	}

	// GAME - 0x87CEA0
	inline void DecRefCount() {
		if (!InterlockedDecrement(&uiRefCount))
			delete this;
	}
};

ASSERT_SIZE(HitData, 0x64);