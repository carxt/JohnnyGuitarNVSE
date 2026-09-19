#pragma once

#include "GameForms.h"
#include "GameSound.h"
#include "Bethesda/BGSEntryPointPerkEntry.hpp"
#ifdef GAME
#include "Bethesda/PlayerCharacter.hpp"
#include "Bethesda/Creature.hpp"
#else
#include "Bethesda/TESObjectREFR.hpp"
#endif
#include "Obsidian/AudioMarkerInfo.hpp"

class ScriptLocals;
class ActiveEffect;
class Animation;
class MapMarkerData;
class ExtraContainerChanges;
class ItemChange;

#if 1
static const uint32_t s_TESObject_REFR_init = 0x55A2F0;			// TESObject_REFR initialization routine (first reference to s_TESObject_REFR_vtbl)
static const uint32_t	s_Actor_EquipItem = 0x88C650;				// maybe, also, would be: 007198E0 for FOSE	4th call from the end of TESObjectREFR::RemoveItem (func5F)
static const uint32_t	s_Actor_UnequipItem = 0x88C790;				// maybe, also, would be: 007133E0 for FOSE next sub after EquipItem
static const uint32_t s_TESObjectREFR__GetContainer = 0x55D310;	// First call in REFR::RemoveItem
static const uint32_t s_TESObjectREFR_Set3D = 0x5702E0;			// void : (const char*)
#elif EDITOR
#else
#error
#endif
const uint32_t kUpdateAppearanceAddr = 0x8D3FA0;
class NiPoint3;

class BSAnimNoteReceiver;
class ActorCause;
class TrapEntry;
class TargetEntry;
class BSFaceGenAnimationData;
class MagicCaster;
class MagicTarget;
class TESTopic;
class Actor;
class TESObjectCELL;

#ifdef GAME
void __fastcall UpdateReference3D(TESObjectREFR* apReference);

class BaseProcess;

class MagicTarget;
typedef tList<ActiveEffect> ActiveEffectList;

class bhkRagdollController;
class bhkRagdollPenetrationUtil;
class ImageSpaceModifierInstanceDOF;
class ImageSpaceModifierInstanceDRB;

class PathingRequest;
class PathingSolution;
class DetailedActorPathHandler;
class ActorPathingMessageQueue;

// A0
class PlayerMover : public ActorMover {
public:
	PlayerMover();
	~PlayerMover();

	uint32_t			unk88;				// 88
	uint32_t			unk8C;				// 8C
	uint32_t			unk90;				// 90
	uint32_t			pcMovementFlags;	// 94
	uint32_t			unk98;				// 98
	uint32_t			unk9C;				// 9C
};

class CombatController;
struct PackageInfo;
struct CombatActors;
class BSAnimGroupSequence;
class BackUpPackage;
class PathingAvoidNodeArray;

typedef ActiveEffect* (*ActiveEffectCreate)(MagicCaster* magCaster, MagicItem* magItem, EffectItem* effItem);

// 150
class Projectile : public MobileObject {
public:
	Projectile();
	~Projectile();

	enum {
		kProjType_Beam = 1,
		kProjType_Flame,
		kProjType_Grenade,
		kProjType_Missile,
		kProjType_ContinuousBeam
	};

	virtual uint32_t	GetProjectileType();
	virtual void	Unk_C2(void);
	virtual void	Unk_C3(void);
	virtual void	Unk_C4(void);
	virtual bool	ProcessImpact();
	virtual bool	IsProximityTriggered();
	virtual void	Unk_C7(void);
	virtual bool	DisarmPlacedExplosives(TESObjectREFR* refr, bool unk);
	virtual void	Unk_C9(void);
	virtual void	Unk_CA(void);
	virtual void	Unk_CB(void);

	enum {
		kProjFlag_Bit00Unk = 0x1,
		kProjFlag_Bit01Unk = 0x2,
		kProjFlag_Bit02Unk = 0x4,
		kProjFlag_Bit03Unk = 0x8,
		kProjFlag_Bit04Unk = 0x10,
		kProjFlag_Bit05Unk = 0x20,
		kProjFlag_Bit06Unk = 0x40,
		kProjFlag_Bit07Unk = 0x80,
		kProjFlag_Bit08Unk = 0x100,
		kProjFlag_MineDisarmed = 0x200,
		kProjFlag_Bit0AUnk = 0x400,
		kProjFlag_Bit0BUnk = 0x800,
		kProjFlag_Bit0CUnk = 0x1000,
		kProjFlag_Bit0DUnk = 0x2000,
		kProjFlag_Bit0EUnk = 0x4000,
		kProjFlag_Bit0FUnk = 0x8000,		// Don't apply source-weapon's damage upon impact
		kProjFlag_Bit10Unk = 0x10000,
		kProjFlag_Bit11Unk = 0x20000,
		kProjFlag_Bit12Unk = 0x40000,
		kProjFlag_Bit13Unk = 0x80000,
		kProjFlag_Bit14Unk = 0x100000,
	};

	struct ImpactData {
		TESObjectREFR* refr;			// 00
		uint32_t			unk04[2];		// 04
		float			unk0C;			// 0C
		uint32_t			unk10[2];		// 10
		float			unk18;			// 18
		hkpRigidBody* rigidBody;		// 1C
		uint32_t			unk20;			// 20
		int32_t			hitLocation;	// 24
		uint32_t			unk28;			// 28
		uint32_t			unk2C;			// 2C
	};

	struct Struct128 {
		uint32_t			unk00;
		uint8_t			byte04;
		uint8_t			pad05[3];
		uint32_t			status;		//	0 - Not triggered, 1 - Triggered, 2 - Disarmed
	};

	tList<ImpactData>	impactDataList;	// 088
	uint8_t				hasImpacted;	// 090
	uint8_t				pad091[3];		// 091
	float				unk094[13];		// 094
	uint32_t				projFlags;		// 0C8
	float				speedMult1;		// 0CC
	float				speedMult2;		// 0D0
	float				flt0D4;			// 0D4
	float				elapsedTime;	// 0D8
	float				hitDamage;		// 0DC
	float				flt0E0;			// 0E0
	float				detonationTime;	// 0E4
	float				flt0E8;			// 0E8
	float				flt0EC;			// 0EC
	float				flt0F0;			// 0F0
	float				wpnHealthPerc;	// 0F4
	TESObjectWEAP* sourceWeap;	// 0F8
	TESObjectREFR* sourceRef;		// 0FC
	uint32_t				unk100;			// 100
	float				flt104;			// 104
	float				flt108;			// 108
	float				flt10C;			// 10C
	float				distTravelled;	// 110
	NiPointer<NiLight> spLight;		// 114
	uint8_t				byte118;		// 118
	uint8_t				pad119[3];		// 119
	NiNode* node11C;		// 11C
	uint32_t				unk120;			// 120
	float				flt124;			// 124
	Struct128			unk128;			// 128
	Struct128			unk134;			// 134
	uint32_t				unk140;			// 140
	uint32_t				unk144;			// 144
	uint8_t				byte148;		// 148
	uint8_t				pad149[3];		// 149
	float				range;			// 14C
};
#ifdef GAME
static_assert(sizeof(Projectile) == 0x150);
#endif

class MuzzleFlash {
public:
	bool					bEnabled;
	bool					bMPSEnabled;
	bool					bUpdateLight;
	float					fEnableTimer;
	float					fDurationTimer;
	NiPointer<NiNode>		spNode;
	NiPointer<NiPointLight>	spLight;
	BGSProjectile*			pProjectile;
	TESObjectWEAP*			pSourceWeapon;
	Actor*					pSourceActor;
};

// 154
class BeamProjectile : public Projectile {
public:
	BeamProjectile();
	~BeamProjectile();

	NiRefObject* object150;		// 150
};

// 158
class ContinuousBeamProjectile : public Projectile {
public:
	ContinuousBeamProjectile();
	~ContinuousBeamProjectile();

	NiRefObject* object150;		// 150
	uint32_t			unk154;			// 154
};

// 158
class FlameProjectile : public Projectile {
public:
	FlameProjectile();
	~FlameProjectile();

	virtual void	Unk_CC(void);

	float		fExpirationTimer;		// 150
	float		fConeAngle;		// 154
};

// 154
class GrenadeProjectile : public Projectile {
public:
	GrenadeProjectile();
	~GrenadeProjectile();

	virtual void	Unk_CC(void);

	uint8_t		byte150;		// 150
	uint8_t		pad151[3];		// 151
};

// 160
class MissileProjectile : public Projectile {
public:
	MissileProjectile();
	~MissileProjectile();

	virtual void	Unk_CC(void);

	uint32_t		unk150;			// 150
	uint8_t		byte154;		// 154
	uint8_t		pad155[3];		// 155
	float		flt158;			// 158
	float		flt15C;			// 15C
};

// 104
class Explosion : public MobileObject {
public:
	Explosion();
	~Explosion();

	virtual void	Unk_C1(void);

	float			unk088;			// 088
	float			unk08C;			// 08C
	float			unk090;			// 090
	float			unk094;			// 094
	float			unk098;			// 098
	float			unk09C;			// 09C
	NiRefObject* object0A0;		// 0A0
	tList<void>		list0A4;		// 0A4
	uint32_t			unk0AC[6];		// 0AC
	NiRefObject* object0C4;		// 0C4
	uint32_t			unk0C8[2];		// 0C8
	NiRefObject* object0D0;		// 0D0
	uint32_t			unk0D4[11];		// 0D4
	float			unk100;			// 100
};
#ifdef GAME
static_assert(sizeof(Explosion) == 0x104);
#endif
#endif