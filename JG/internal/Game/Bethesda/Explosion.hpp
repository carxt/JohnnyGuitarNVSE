#pragma once

#include "MobileObject.hpp"

class NiLight;
class NonActorMagicCaster;
class bhkSimpleShapePhantom;
class ActorCause;
class BGSExplosion;

class Explosion : public MobileObject {
public:
	virtual void Initialize();

	struct ExplodedLimb {
		LIMB_TYPE	eLimb;
		float		fDistance;
	};

	struct ExplosionTarget {
		TESObjectREFR*				pRef;
		bool						bHitWeakPoint;
		bool						bMobile;
		bool						bProcessed;
		BSSimpleList<ExplodedLimb*> kLimbs;
	};
	
	float								fAge;
	float								f3DLifetime;
	float								fInnerRadius;
	float								fOuterRadius;
	float								fImageSpaceRadius;
	float								fWeaponCondition;
	NiPointer<bhkSimpleShapePhantom>	spPhantom;
	BSSimpleList<ExplosionTarget*>		kTargets;
	BSSoundHandle						kSoundHandles[2];
	NiPointer<NiLight>					spLight;
	TESObjectREFR*						pOwnerRef;
	TESObjectREFR*						pExplodedRef;
	NiPointer<ActorCause>				spActorCause;
	bool								bDecalsPlaced;
	bool								bTargetsFound;
	bool								bTargetsProcessed;
	bool								bForcesApplied;
	bool								bIgnoreImageSpaceSwap;
	bool								bUnderwater;
	NonActorMagicCaster*				pCaster;
	TESObjectWEAP*						pWeaponSource;
	int									iFrameCount;
	NiPoint3							kClosestPoint;
	NiPoint3							kClosestPointNormal;
	float								fCalculatedDamage;

	BGSExplosion* GetExplosionBase() const;
};

ASSERT_SIZE(Explosion, 0x104)