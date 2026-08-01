#pragma once

#include "GameForms.h"
#include "Obsidian/AudioMarkerInfo.hpp"
#include "Bethesda/TESRegionList.hpp"
#include "Bethesda/Character.hpp"
#include "Bethesda/Creature.hpp"

class ScriptLocals;
class ActiveEffect;
class Animation;
class MapMarkerData;

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

class bhkRigidBody;
struct ParentSpaceNode;
struct TeleportLink;
class ItemChange;
class NiObject;
class AudioMarkerInfo;

struct PerkRank {
	BGSPerk* perk;
	uint8_t		rank;
	uint8_t		pad05[3];
};

// E50
class PlayerCharacter : public Character {
public:
	PlayerCharacter();
	~PlayerCharacter();

	// used to flag controls as disabled in disabledControlFlags
	enum {
		kControlFlag_Movement = 1 << 0,
		kControlFlag_Look = 1 << 1,
		kControlFlag_Pipboy = 1 << 2,
		kControlFlag_Fight = 1 << 3,
		kControlFlag_POVSwitch = 1 << 4,
		kControlFlag_RolloverText = 1 << 5,
		kControlFlag_Sneak = 1 << 6,
	};

	virtual void		Unk_139(void);
	virtual void		Unk_13A(void);

	struct MapMarkerInfo {
		MapMarkerData* markerData;
		TESObjectREFR* markerRef;
	};

	struct CompassTarget {
		Actor* target;
		uint8_t		isHostile;
		uint8_t		isDetected;
		uint8_t		pad06[2];
	};

	uint32_t								unk1C8[16];				// 1C8	208 could be a DialogPackage
	TESForm* form208;				// 208 TESTING
	void* unk20C;				// 20C
	tList<ActiveEffect>* activeEffects;			// 210
	TESForm* form214;				// 214 TESTING
	TESForm* form218;				// 218 TESTING
	void* unk21C;				// 21C
	uint32_t								unk220[8];				// 220	224 is a package of type 1C
	bool								showQuestItems;			// 240
	uint8_t								byte241;				// 241
	uint8_t								byte242;				// 242
	uint8_t								byte243;				// 243
	float								unk244[77];				// 244	have to be a set of ActorValue
	float								permAVMods[77];			// 378	have to be a set of ActorValue
	float								flt4AC;					// 4AC
	float								actorValues4B0[77];		// 4B0	have to be a set of ActorValue
	tList<BGSNote>						notes;					// 5E4
	ImageSpaceModifierInstanceDOF* unk5EC;				// 5EC
	ImageSpaceModifierInstanceDOF* unk5F0;				// 5F0
	ImageSpaceModifierInstanceDRB* unk5F4;				// 5F4
	uint8_t								byte5F8;				// 5F8
	uint8_t								byte5F9;				// 5F9
	uint8_t								byte5FA;				// 5FA
	uint8_t								byte5FB;				// 5FB
	tList<TESObjectREFR>				teammates;				// 5FC
	TESObjectREFR* lastExteriorDoor;		// 604
	void* unk608;				// 608
	void* unk60C;				// 60C
	BSSimpleList<CasinoStats*>* casinoDataList;				// 610
	tList<TESCaravanCard>* caravanCards1;			// 614
	tList<TESCaravanCard>* caravanCards2;			// 618
	uint32_t								unk61C[7];				// 61C
	TESObjectREFR* grabbedRef;			// 638
	uint32_t								unk63C[3];				// 63C
	uint8_t								byte648;				// 648
	uint8_t								byte649;				// 649
	bool								bIs3rdPersonVisible;				// 64A	= not FirstPerson
	bool								is3rdPerson;			// 64B
	bool								bThirdPerson;			// 64C
	uint8_t								bTemp3rdPerson;				// 64D
	uint8_t								byte64E;				// 64E
	bool								isUsingScope;			// 64F
	uint8_t								byte650;				// 650
	bool								alwaysRun;				// 651
	bool								autoMove;				// 652
	uint8_t								byte653;				// 653
	uint32_t								sleepHours;				// 654
	uint8_t								byte658;				// 658	Something to do with SleepDeprivation; see 0x969DCF
	uint8_t								byte659;				// 659
	uint8_t								byte65A;				// 65A
	uint8_t								byte65B;				// 65B
	uint32_t								unk65C[4];				// 65C
	uint8_t								byte66C;				// 66C
	uint8_t								byte66D;				// 66D
	uint8_t								byte66E;				// 66E
	uint8_t								byte66F;				// 66F
	//uint32_t								unk670[4];				// 670
	float                               worldFOV;				//670
	float								firstPersonFOV;
	float								unk678;
	float								unk67C;
	uint8_t								pcControlFlags;			// 680
	uint8_t								byte681;				// 681
	uint8_t								byte682;				// 682
	uint8_t								byte683;				// 683
	uint32_t								unk684[2];				// 684
	BipedAnim*							p1stPersonBipedAnim;		// 68C
	Animation*							p1stPersonAnimation;				// 690
	NiNode* playerNode;			// 694 used as node if unk64A is true
	uint32_t								unk698[4];				// 698
	tList<TESTopic>						topicList;				// 6A8
	uint32_t								unk6B0[2];				// 6B0
	TESQuest* activeQuest;			// 6B8
	tList<BGSQuestObjective>			questObjectiveList;		// 6BC
	tList<TESQuestTarget>	questTargetList;		// 6C4
	uint32_t								unk6CC[8];				// 6CC
	TESForm* form6EC;				// 6EC TESTING
	TESForm* form6F0;				// 6F0 TESTING
	uint32_t								unk6F4;					// 6F4;
	BSSimpleArray<ParentSpaceNode*>		parentSpaceNodes;		// 6F8
	BSSimpleArray<TeleportLink*>			teleportLinks;			// 708
	uint32_t								unk718[6];				// 718
	float								timeGrenadeHeld;		// 730
	uint32_t								unk734[2];				// 734
	TESForm* form73C;				// 73C	TESTING
	uint32_t								unk740[6];				// 740
	TESForm* tempWeaponPoisonRef;	// 758 TESTING
	bool								inCharGen;				// 75C
	uint8_t								byte75D;				// 75D
	uint8_t								byte75E;				// 75E
	uint8_t								byte75F;				// 75F
	TESRegion* currentRegion;			// 760
	TESRegionList						regionsList;			// 764
	uint32_t								unk774[14];				// 774
	TESForm* pcWorldOrCell;			// 7AC
	uint32_t								unk7B0;					// 7B0
	BGSMusicType* musicType;				// 7B4
	uint8_t								gameDifficulty;			// 7B8
	uint8_t								byte7B9;				// 7B9
	uint8_t								byte7BA;				// 7BA
	uint8_t								byte7BB;				// 7BB
	bool								isHardcore;				// 7BC
	uint8_t								byte7BD;				// 7BD
	uint8_t								byte7BE;				// 7BE
	uint8_t								byte7BF;				// 7BF
	uint32_t								killCamMode;			// 7C0
	uint8_t								byte7C4;				// 7C4
	uint8_t								byte7C5;				// 7C5
	bool								isToddler;				// 7C6
	bool								canUsePA;				// 7C7
	tList<MapMarkerInfo>				mapMarkers;				// 7C8
	TESWorldSpace* worldSpc7D0;			// 7D0
	tList<AudioMarkerInfo>					musicMarkers;			// 7D4
	AudioMarkerInfo* currMusicMarker;		// 7DC
	uint32_t								unk7E0[39];				// 7E0
	tList<PerkRank>						perkRanksPC;			// 87C
	tList<BGSEntryPointPerkEntry>		perkEntriesPC[74];		// 884
	tList<PerkRank>						perkRanksTM;			// AD4
	tList<BGSEntryPointPerkEntry>		perkEntriesTM[74];		// ADC
	uint32_t								unkD2C[4];				// D2C
	NiObject* unkD3C;				// D3C
	uint32_t								unkD40;					// D40
	Actor* reticleActor;			// D44
	BSSimpleList<CompassTarget*>* compassTargets;				// D48
	uint32_t								unkD4C[6];				// D4C
	CombatActors* combatActors;			// D64
	uint32_t								teammateCount;			// D68
	float								fCombatTimer;
	float								fYieldTimer;
	NiAVObject*							pWobbleNodes[2][12];
	NiPoint3							vectorDD4;				// DD4
	NiPoint3							cameraPos;				// DE0
	bhkRigidBody* rigidBody;				// DEC
	bool								pcInCombat;				// DF0
	bool								pcUnseen;				// DF1
	uint8_t								byteDF2;				// DF2
	uint8_t								byteDF3;				// DF3
	BSSimpleArray<ItemChange*>			itemChanges;			// DF4
	uint32_t								unkE04[5];				// E04
	float								killCamTimer;			// E18
	float								killCamCooldown;		// E1C
	uint8_t								byteE20;				// E20
	uint8_t								byteE21;				// E21
	uint8_t								byteE22;				// E22
	uint8_t								byteE23;				// E23
	float								fltE24;					// E24
	float								counterAttackTimer;		// E28
	uint32_t								unkE2C;					// E2C
	uint32_t								unkE30;					// E30
	NiNode* ironSightNode;			// E34
	bool								noHardcoreTracking;		// E38	Appears to be unused
	bool								skipHCNeedsUpdate;		// E39
	uint8_t								byteE3A;				// E3A
	uint8_t								byteE3B;				// E3B
	BSSimpleArray<TESAmmo*>				pcAmmo;					// E3C
	uint32_t								unkE4C;					// E4C
		// 7C6 is a boolean meaning toddler,
		// 7C7 byte bool PCCanUsePowerArmor, Byt0E39 referenced during LoadGame
		// Used by TFC : 7E8/EC/F0 stores Pos, 7F0 adjusted by scaledHeight , 7E0 stores RotZ, 7E4 RotX
		// Quest Stage LogEntry at 6B0.
		// tList at 6C4 is cleared when there is no current quest. There is another NiNode at 069C
		// 086C is cleared after equipement change.

	bool IsThirdPerson() const { return bThirdPerson; }
	bool Is3rdPersonVisible() const { return bIs3rdPersonVisible; }
	uint32_t GetMovementFlags() const { return pActorMover->GetMoveMode(); }	// 11: IsSwimming, 9: IsSneaking, 8: IsRunning, 7: IsWalking, 0: keep moving
	bool IsPlayerSwimming() const { return (GetMovementFlags() >> 11) & 1; }

	static PlayerCharacter* GetSingleton();
	bool SetSkeletonPath(const char* newPath);
	static void UpdateHead(void);

	bool ToggleFirstPerson(bool toggleON);
	char GetDetectionState();

	NiAVObject* Get3D(bool abFirstPerson) const;
	BipedAnim* GetBiped(bool abFirstPerson) const;
	Animation* GetAnimation(bool abFirstPerson) const;

	void SetPlayerMapMarker(NiPoint3 akLocation, TESForm* apSpace) {
		ThisCall(0x952E60, this, akLocation, apSpace);
	}

	void RemovePlayerMapMarker() {
		ThisCall(0x952F90, this);
	}

	static constexpr AddressPtr<bool, 0x11E07B8> bIsVanityMode;
	static constexpr AddressPtr<bool, 0x11E07B9> bIsAutoVanityMode;
	static constexpr AddressPtr<NiPoint3, 0x11E0B58> kVanityModePos;
};
static_assert(sizeof(PlayerCharacter) == 0xE50);


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
static_assert(sizeof(Projectile) == 0x150);

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
static_assert(sizeof(Explosion) == 0x104);
