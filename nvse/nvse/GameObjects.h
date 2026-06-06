#pragma once

#include "GameForms.h"
#include "GameBSExtraData.h"
#include "GameExtraData.h"
#include "Obsidian/AudioMarkerInfo.hpp"

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
// 68
class TESObjectREFR : public TESForm {
public:
	MEMBER_FN_PREFIX(TESObjectREFR);

	TESObjectREFR();
	~TESObjectREFR();

	virtual void		Unk_4E(void);	// GetStartingPosition(Position, Rotation, WorldOrCell)
	virtual void		Unk_4F(void);
	virtual void		Unk_50(void);
	virtual void		Unk_51(void);
	virtual bool		CastShadows();
	virtual void		Unk_53(void);
	virtual void		Unk_54(void);
	virtual void		Unk_55(void);
	virtual void		Unk_56(void);
	virtual bool		IsObstacle();
	virtual void		Unk_58(void);
	virtual void		Unk_59(void);
	virtual void		Unk_5A(void);
	virtual void		Unk_5B(void);
	virtual void		Unk_5C(void);
	virtual void		Unk_5D(void);
	virtual void		Unk_5E(void);
	virtual TESObjectREFR* RemoveItem(TESBoundObject* apObject, ExtraDataList* apExtraList, uint32_t auiCount, bool abStealing, bool abDropWorld, TESObjectREFR* apOtherContainer, NiPoint3* apPoint, NiPoint3* apRotate, bool abDeleteExtra, bool abPreferStolen);
	virtual void		Unk_60(void);
	virtual bool		EquipObject(TESForm* item, uint32_t count, ExtraDataList* xData, bool lockEquip);
	virtual void		Unk_62(void);
	virtual void		Unk_63(void);
	virtual void		AddItem(TESForm* item, ExtraDataList* xDataList, uint32_t quantity);
	virtual void		Unk_65(void);
	virtual void		Unk_66(void);
	virtual void		Unk_67(void);					// Actor: GetMagicEffectList
	virtual bool		GetIsChildSize(bool checkHeight);		// 068 Actor: GetIsChildSize
	virtual uint32_t		GetActorUnk0148();			// result can be interchanged with baseForm, so TESForm* ?
	virtual void		SetActorUnk0148(uint32_t arg0);
	virtual void		Unk_6B(void);
	virtual void		Unk_6C(void);	// REFR: GetBSFaceGenNiNodeSkinned
	virtual void		Unk_6D(void);	// REFR: calls 006C
	virtual void		Unk_6E(void);	// MobileActor: calls 006D then NiNode::Func0040
	virtual void		Unk_6F(void);
	virtual bool		DetachHavok();
	virtual void		InitHavok();
	virtual NiAVObject*	Load3D(bool abBackgroundLoad);
	virtual void		Set3D(NiAVObject* apObject, bool abTestProcessLevel = false);
	virtual NiNode*		Get3D() const;
	virtual void		Unk_75(void);
	virtual void		Unk_76(void);
	virtual void		Unk_77(void);
	virtual void		Unk_78(void);
	virtual Animation*	GetAnimation() const;			// 0079
	virtual BipedAnim*	GetBiped() const;	// 007A	Character only
	virtual BipedAnim*	GetCurrentBiped() const;
	virtual void		SetValidBip01Names(BipedAnim* validBip01Names);
	virtual const NiPoint3& GetPos() const;				// GetPos or GetDistance
	virtual void		Unk_7E(uint32_t arg0);
	virtual void		Unk_7F(void);
	virtual void		Unk_80(uint32_t arg0);
	virtual void		Unk_81(uint32_t arg0);
	virtual void		Unk_82(void);
	virtual uint32_t		Unk_83(void);
	virtual void		Unk_84(uint32_t arg0);
	virtual uint32_t		Unk_85(void);
	virtual bool		IsCharacter();			// return false for Actor and Creature, true for character and PlayerCharacter
	virtual bool		IsCreature();
	virtual bool		IsExplosion();
	virtual bool		IsProjectile();
	virtual void		Unk_8A(void);			// SetParentCell (Interior only ?)
	virtual bool		HasHealth(bool arg0);	// HasHealth (baseForm health > 0 or Flags bit23 set)
	virtual bool		Unk_8C(void);
	virtual bool		Unk_8D(void);
	virtual void		Unk_8E(void);
	virtual void		Unk_8F(void);
	virtual void		Unk_90(void);

	enum {
		kFlags_Unk00000002 = 0x00000002,
		kFlags_Deleted = 0x00000020,		// refr removed from .esp or savegame
		kFlags_Taken = kFlags_Deleted | kFlags_Unk00000002,
		kFlags_Persistent = 0x00000400,		//shared bit with kFormFlags_QuestItem
		kFlags_Temporary = 0x00004000,
		kFlags_IgnoreFriendlyHits = 0x00100000,
		kFlags_Destroyed = 0x00800000,

		kChanged_Inventory = 0x08000000,
	};

	struct RenderState {
		TESObjectREFR*	waterRef;		// 00
		uint32_t			unk04;			// 04	0-0x13 when fully-underwater; exterior only
		float			waterLevel;		// 08
		float			unk0C;			// 0C
		uint32_t			unk10;			// 10
		NiNode*			rootNode;		// 14
		NiNode*			niNode18;		// 18
	};

	struct EditorData {
		uint32_t	unk00;	// 00
	};
	// 0C

#ifdef EDITOR
	EditorData	editorData;			// +04
#endif

	TESChildCell	childCell;				// 018

	TESSound* loopSound;				// 01C

	TESForm* baseForm;				// 020

	NiPoint3		rot;		// 024 - either public or accessed via simple inline accessor common to all child classes
	NiPoint3		pos;		// 030 - seems to be private
	float			scale;					// 03C

	TESObjectCELL* parentCell;			// 040
	ExtraDataList	extraDataList;			// 044
	RenderState* renderState;			// 064

	ScriptLocals* GetScriptLocals() const;

	bool IsTaken() const { return uiFormFlags.Get(FormFlags::TAKEN); } // Need to implement
	__forceinline NiNode* Get3DSimple() const{ return renderState ? renderState->rootNode : nullptr; }
	const char* hk_GetName();
	const char* GetFullName() const;
	NiPoint3* PosVector() { return &pos; }
	NiPoint2* PosXY() { return (NiPoint2*)&pos; }

	void Update3D();
	TESContainer* GetContainer();
	bool IsMapMarker();

	TESForm* GetBaseForm();
	bool GetDisabled(bool checkQueue = true) const;
	ExtraContainerChanges* GetOrCreateContainerChanges();
	BSSimpleList<ItemChange*>* GetContainerChangesList();
	
	TESObjectCELL* GetParentCell();
	NiAVObject* GetNiBlock(const char* blockName);
	NiNode* GetNode(const char* nodeName);
	hkpRigidBody* GetRigidBody(const char* nodeName);
	bool IsInInterior() { return ThisCall<bool>(0x575D10, this); }
	static TESObjectREFR* __stdcall Create(bool bTemp = false);

	float GetHealth() { return ThisCall<float>(0x568AD0, this); }

	void ReplaceModel() { ThisCall(0x5710C0, this); }

	void Update3DPosition() { ThisCall(0x562020, this); 	}

	void Set3DVerySimple(NiAVObject* apObject) { ThisCall(0x571080, this, apObject); }

	float GetRawScale() const { return scale; }
	float GetScale() const { return ThisCall<float>(0x567400, this); }
	void SetScale(float afScale) { ThisCall(0x567490, this, afScale); }

	void SetRefPersists(bool abVal) { ThisCall(0x565480, this, abVal); }

	MEMBER_FN_PREFIX(TESObjectREFR);
#if 1
	DEFINE_MEMBER_FN(Activate, bool, 0x00573170, TESObjectREFR*, uint32_t, uint32_t, uint32_t);	// Usage Activate(actionRef, 0, 0, 1); found inside Cmd_Activate_Execute as the last call (190 bytes)
#elif EDITOR
#else
#error
#endif
};

static_assert(sizeof(TESObjectREFR) == 0x068);




TESForm* GetPermanentBaseForm(TESObjectREFR* thisObj);	// For LevelledForm, find real baseForm, not temporary one.

class BaseProcess;

// 88
class MobileObject : public TESObjectREFR {
public:
	MobileObject();
	~MobileObject();

	virtual void		Unk_91(void);
	virtual void		Unk_92(void);
	virtual void		Unk_93(void);
	virtual void		Unk_94(void);
	virtual void		Unk_95(void);
	virtual void		Unk_96(void);
	virtual void		Unk_97(void);
	virtual void		Unk_98(void);
	virtual void		Unk_99(void);
	virtual void		Unk_9A(void);
	virtual void		Unk_9B(void);
	virtual void		Unk_9C(void);
	virtual void		Unk_9D(void);
	virtual void		Unk_9E(void);
	virtual void		Unk_9F(void);
	virtual void		Unk_A0(void);
	virtual void		Unk_A1(void);
	virtual void		Unk_A2(void);
	virtual void		Unk_A3(void);
	virtual void		Unk_A4(void);
	virtual void		Unk_A5(void);
	virtual void		Unk_A6(void);
	virtual void		Unk_A7(void);
	virtual void		Unk_A8(void);
	virtual void		Unk_A9(void);
	virtual void		Unk_AA(void);
	virtual void		Unk_AB(void);
	virtual void		Unk_AC(void);
	virtual void		Unk_AD(void);
	virtual void		Unk_AE(void);
	virtual float		GetZRotation(bool arg1);
	virtual void		Unk_B0(void);
	virtual void		Unk_B1(void);
	virtual void		Unk_B2(void);
	virtual void		Unk_B3(void);
	virtual void		Unk_B4(void);
	virtual void		Unk_B5(void);
	virtual void		Unk_B6(void);
	virtual void		Unk_B7(void);
	virtual void		Unk_B8(void);
	virtual void		Unk_B9(void);
	virtual void		Unk_BA(void);
	virtual void		Unk_BB(void);
	virtual void		Unk_BC(void);
	virtual void		Unk_BD(void);
	virtual void		Unk_BE(void);
	virtual void		Unk_BF(void);
	virtual void		Unk_C0(void);

	BaseProcess* baseProcess;	// 68
	uint32_t			unk6C;			// 6C - loaded
	TESObjectREFR* unk70;			// 70 - loaded
	uint32_t			unk74;			// 74 - loaded
	uint32_t			unk78;			// 78 - loaded
	uint8_t			unk7C;			// 7C - loaded
	uint8_t			unk7D;			// 7D - loaded
	uint8_t			unk7E;			// 7E - loaded
	uint8_t			unk7F;			// 7F - loaded
	uint8_t			unk80;			// 80 - loaded
	uint8_t			unk81;			// 81 - loaded
	uint8_t			unk82;			// 82
	uint8_t			unk83;			// 83 - loaded
	uint8_t			unk84;			// 84 - loaded
	uint8_t			unk85;			// 85 - loaded
	uint8_t			unk86;			// 86 - loaded
	uint8_t			unk87;			// 87	Init'd to the inverse of NoLowLevelProcessing
};

static_assert(sizeof(MobileObject) == 0x88);

class MagicTarget;
typedef tList<ActiveEffect> ActiveEffectList;

// 0C
class MagicCaster {
public:
	MagicCaster();
	~MagicCaster();

	virtual void	Unk_00(void);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	CastSpell(MagicItem* spell, bool arg2, MagicTarget* target, float arg4, bool arg5);
	virtual void	Unk_04(void);
	virtual void	AddEffect(MagicItem* magItem, TESForm* itemForm, bool arg3);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual Actor* GetActor(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(MagicItem* spell);
	virtual void	Unk_11(void);
	virtual void	Unk_12(MagicTarget* magicTarget);
	virtual void	Unk_13(void);

	uint32_t	unk04[2];	// 04
};
static_assert(sizeof(MagicCaster) == 0xC);

// 10
class MagicTarget {
public:
	MagicTarget();
	~MagicTarget();

	virtual bool	ApplyEffect(MagicCaster* magicCaster, MagicItem* magicItem, ActiveEffect* activeEffect, bool arg4);
	virtual Actor* GetActor(void);
	virtual ActiveEffectList* GetEffectList(void);
	virtual void	Unk_03(void);
	virtual bool	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual float	Unk_09(MagicCaster* magicCaster, MagicItem* magicItem, ActiveEffect* activeEffect);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);

	uint32_t	unk04[3];	// 04

	void RemoveEffect(EffectItem* effItem);
};
static_assert(sizeof(MagicTarget) == 0x10);

class bhkRagdollController;
class bhkRagdollPenetrationUtil;
class ImageSpaceModifierInstanceDOF;
class ImageSpaceModifierInstanceDRB;

class PathingRequest;
class PathingSolution;
class DetailedActorPathHandler;
class ActorPathingMessageQueue;

// 28
class PathingLocation {
public:
	virtual void	Unk_00(void);
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);

	uint32_t			unk04[9];	// 04
};

// 88
class ActorMover {
public:
	ActorMover();
	virtual				~ActorMover();
	virtual void		SetMoveModePreference(uint16_t ausFlag);
	virtual void		ClearMoveModePreference(uint16_t ausFlag);
	virtual void		ForceMoveMode(uint16_t ausFlag);
	virtual void		ClearForcedMoveMode();
	virtual void		Update(float afDelta);
	virtual void		UpdateTurnTimer(float timePassed);
	virtual uint32_t	GetPreferredMoveMode() const;
	virtual uint32_t	GetMoveMode() const;
	virtual bool		GetMoveDelta(NiPoint3& arDelta);
	virtual void		SaveGame(BGSSaveFormBuffer* apBuffer);
	virtual void		LoadGame(BGSLoadFormBuffer* apBuffer);
	virtual void		InitLoadGame(BGSLoadFormBuffer* apBuffer);
	virtual void		FinishLoadGame(BGSLoadFormBuffer* apBuffer);
	virtual void		Revert(BGSLoadFormBuffer* apBuffer);

	uint32_t						unk04[6];			// 04
	PathingRequest* pathingRequest;	// 1C
	PathingSolution* pathingSolution;	// 20
	DetailedActorPathHandler* pathHandler;		// 24
	Actor* actor;				// 28
	uint32_t						unk2C;				// 2C
	ActorPathingMessageQueue* pathingMsgQueue;	// 30
	uint32_t						movementFlags1;		// 34
	uint32_t						unk38;				// 38
	uint32_t						movementFlags2;		// 3C
	uint32_t						unk40;				// 40
	PathingLocation				pathingLocation;	// 44
	uint32_t						unk6C;				// 6C
	uint8_t						unk70[4];			// 70
	uint32_t						unk74;				// 74
	uint32_t						unk78;				// 78
	uint32_t						unk7C;				// 7C
	uint32_t						unk80;				// 80
	uint32_t						unk84;				// 84
};

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
struct ItemEntryData;
class BSAnimGroupSequence;
class BackUpPackage;
class PathingAvoidNodeArray;

typedef ActiveEffect* (*ActiveEffectCreate)(MagicCaster* magCaster, MagicItem* magItem, EffectItem* effItem);

class Actor : public MobileObject {
public:
	Actor();
	~Actor();

	virtual void		Unk_C1(void);
	virtual void		Unk_C2(void);
	virtual void		Unk_C3(void);
	virtual void		Unk_C4(void);
	virtual void		Unk_C5(void);
	virtual void		Unk_C6(void);
	virtual void		SetIgnoreCrime(bool ignoreCrime);
	virtual bool		GetIgnoreCrime(void);
	virtual void		Unk_C9(void);
	virtual void		Unk_CA(void);
	virtual void		Unk_CB(void);
	virtual void		Unk_CC(void);
	virtual void		Unk_CD(void);
	virtual void		Unk_CE(void);
	virtual void		Unk_CF(void);
	virtual void		Unk_D0(void);
	virtual void		Unk_D1(void);
	virtual void		Unk_D2(void);
	virtual void		Unk_D3(void);
	virtual void		Unk_D4(void);
	virtual void		Unk_D5(void);
	virtual void		Unk_D6(void);
	virtual void		Unk_D7(void);
	virtual bool		IsPlayerRef(void);
	virtual void		Unk_D9(void);
	virtual void		Unk_DA(void);
	virtual void		Unk_DB(void);
	virtual void		Unk_DC(void);
	virtual void		Unk_DD(void);
	virtual void		Unk_DE(void);
	virtual void		Unk_DF(void);
	virtual void		Unk_E0(void);
	virtual void		Unk_E1(void);
	virtual void		Unk_E2(void);
	virtual void		Unk_E3(void);
	virtual uint32_t		GetActorType(void);	// Creature = 0, Character = 1, PlayerCharacter = 2
	virtual void		SetActorValue(uint32_t avCode, float value);
	virtual void		SetActorValueInt(uint32_t avCode, uint32_t value);
	virtual void		Unk_E7(void);
	virtual void		Unk_E8(void);
	virtual void		Unk_E9(void);
	virtual void		ModActorValue(uint32_t avCode, int modifier, uint32_t arg3);
	virtual void		DamageActorValue(uint32_t avCode, float damage, Actor* attacker);
	virtual void		Unk_EC(void);
	virtual void		Unk_ED(void);
	virtual void		Unk_EE(void);
	virtual ItemChange* GetPreferedWeapon(uint32_t unk);
	virtual void		Unk_F0(void);
	virtual void		Unk_F1(void);
	virtual void		Unk_F2(void);
	virtual void		Unk_F3(void);
	virtual void		Unk_F4(void);
	virtual void		Unk_F5(void);
	virtual void		Unk_F6(void);
	virtual void		Unk_F7(void);
	virtual void		Unk_F8(void);
	virtual void		Unk_F9(void);
	virtual void		Unk_FA(void);
	virtual void		Unk_FB(TESForm* form, uint32_t arg2, uint8_t arg3, uint8_t arg4);
	virtual void		Unk_FC(void);
	virtual void		Unk_FD(void);
	virtual void		Unk_FE(void);
	virtual void		Unk_FF(void);
	virtual void		Unk_100(void);
	virtual void		Unk_101(void);
	virtual void		Unk_102(void);
	virtual void		Unk_103(void);
	virtual void		Unk_104(void);
	virtual void		Unk_105(void);
	virtual void		Unk_106(void);
	virtual void		Unk_107(void);
	virtual void		Unk_108(void);
	virtual void		Unk_109(void);
	virtual CombatController* GetCombatController(void);
	virtual Actor* GetCombatTarget(void);
	virtual void		Unk_10C(void);
	virtual void		Unk_10D(void);
	virtual void		Unk_10E(void);
	virtual float		GetTotalArmorDR(void);
	virtual float		GetTotalArmorDT(void);
	virtual uint32_t		Unk_111(void);
	virtual void		Unk_112(void);
	virtual void		Unk_113(void);
	virtual void		Unk_114(void);
	virtual void		Unk_115(void);
	virtual float		CalcSpeedMult(void);
	virtual void		Unk_117(void);
	virtual void		Unk_118(void);
	virtual void		Unk_119(void);
	virtual void		Unk_11A(void);
	virtual void		Unk_11B(void);
	virtual void		Unk_11C(void);
	virtual void		Unk_11D(void);
	virtual void		Unk_11E(void);
	virtual void		Unk_11F(void);
	virtual void		Unk_120(void);
	virtual void		Unk_121(void);
	virtual void		RewardXP(uint32_t amount);
	virtual void		Unk_123(void);
	virtual void		Unk_124(void);
	virtual void		Unk_125(void);
	virtual void		SetPerkRank(BGSPerk* perk, uint8_t rank, bool alt);
	virtual void		RemovePerk(BGSPerk* perk, bool alt);
	virtual uint8_t		GetPerkRank(BGSPerk* perk, bool alt);
	virtual void		Unk_129(void);
	virtual void		Unk_12A(void);
	virtual void		Unk_12B(void);
	virtual void		Unk_12C(void);
	virtual void		Unk_12D(void);
	virtual void		DoHealthDamage(Actor* attacker, float damage);
	virtual void		Unk_12F(void);
	virtual void		Unk_130(void);
	virtual float		Unk_131(void);
	virtual void		Unk_132(void);
	virtual void		Unk_133(void);
	virtual void		Unk_134(void);
	virtual void		Unk_135(void);
	virtual void		Unk_136(void);

	MagicCaster			magicCaster;			// 088
	MagicTarget			magicTarget;			// 094
	ActorValueOwner		avOwner;				// 0A4
	CachedValuesOwner	cvOwner;				// 0A8

	bhkRagdollController* ragDollController;			// 0AC
	bhkRagdollPenetrationUtil* ragDollPentrationUtil;		// 0B0
	uint32_t								unk0B4;						// 0B4-
	float								flt0B8;						// 0B8
	uint8_t								byte0BC;					// 0BC-
	uint8_t								byte0BD;					// 0BD
	uint8_t								byte0BE;					// 0BE
	uint8_t								byte0BF;					// 0BF
	Actor* killer;					// 0C0
	uint8_t								byte0C4;					// 0C4-
	uint8_t								byte0C5;					// 0C5
	uint8_t								byte0C6;					// 0C6
	uint8_t								byte0C7;					// 0C7
	float								flt0C8;						// 0C8
	float								flt0CC;						// 0CC
	tList<void>							list0D0;					// 0D0
	uint8_t								byte0D8;					// 0D8
	uint8_t								byte0D9;					// 0D9
	uint8_t								byte0DA;					// 0DA
	uint8_t								byte0DB;					// 0DB
	uint32_t								unk0DC;						// 0DC
	tList<void>							list0E0;					// 0E0
	uint8_t								byte0E8;					// 0E8	const 1
	uint8_t								byte0E9;					// 0E9
	uint8_t								byte0EA;					// 0EA
	uint8_t								byte0EB;					// 0EB
	uint32_t								unk0EC;						// 0EC
	uint8_t								byte0F0;					// 0F0-
	uint8_t								byte0F1;					// 0F1-
	uint8_t								byte0F2;					// 0F2
	uint8_t								byte0F3;					// 0F3
	tList<void>							list0F4;					// 0F4
	tList<void>							list0FC;					// 0FC
	bool								isInCombat;					// 104
	uint8_t								jipActorFlags1;				// 105
	uint8_t								jipActorFlags2;				// 106
	uint8_t								jipActorFlags3;				// 107
	uint32_t								lifeState;					// 108	saved as byte HasHealth = 1 or 2, optionally 6, 5 = IsRestrained
	uint32_t								criticalStage;				// 10C
	uint32_t								unk110;						// 110-
	float								flt114;						// 114
	uint8_t								byte118;					// 118-
	uint8_t								byte119;					// 119+
	uint16_t								jip11A;						// 11A+
	uint32_t								unk11C;						// 11C-
	uint32_t								unk120;						// 120-
	bool								forceRun;					// 124
	bool								forceSneak;					// 125
	uint8_t								byte126;					// 126-
	uint8_t								byte127;					// 127-
	Actor* combatTarget;				// 128
	BSSimpleArray<Actor*>* combatTargets;				// 12C
	BSSimpleArray<Actor*>* combatAllies;				// 130
	uint8_t								byte134;					// 134-
	uint8_t								byte135;					// 135+
	uint16_t								jip136;						// 136+
	uint32_t								unk138;						// 138-
	uint32_t								unk13C;						// 13C-
	uint32_t								actorFlags;					// 140	0x80000000 - IsEssential
	bool								ignoreCrime;				// 144
	uint8_t								byte145;					// 145	Has to do with package evaluation
	uint8_t								byte146;					// 146	Has to do with package evaluation
	uint8_t								byte147;					// 147
	uint32_t								unk148;						// 148-
	uint8_t								inWater;					// 14C
	uint8_t								isSwimming;					// 14D
	uint16_t								jip14E;						// 14E+
	uint32_t								unk150;						// 150-
	float								flt154;						// 154
	float								flt158;						// 158
	uint8_t								byte15C;					// 15C-
	uint8_t								byte15D;					// 15D-
	uint16_t								jip15E;						// 15E+
	NiPoint3							startingPos;				// 160
	float								flt16C;						// 16C
	TESForm* startingWorldOrCell;		// 170
	uint8_t								byte174;					// 174-
	uint8_t								byte175;					// 175-
	uint16_t								jip176;						// 176+
	float								flt178;						// 178
	float								flt17C;						// 17C
	float								flt180;						// 180
	float								flt184;						// 184
	float								flt188;						// 188
	uint8_t								byte18C;					// 18C-
	bool								isTeammate;					// 18D
	uint8_t								byte18E;					// 18E-
	uint8_t								byte18F;					// 18F
	ActorMover* actorMover;				// 190
	uint32_t								unk194;						// 194-
	uint32_t								unk198;						// 198-
	float								flt19C;						// 19C
	uint32_t								unk1A0;						// 1A0-
	uint32_t								unk1A4;						// 1A4-
	uint32_t								unk1A8;						// 1A8-
	uint32_t								unk1AC;						// 1AC-
	uint8_t								byte1B0;					// 1B0-
	bool								forceHit;					// 1B1-
	uint8_t								byte1B2;					// 1B2
	uint8_t								byte1B3;					// 1B3

	// OBSE: unk1 looks like quantity, usu. 1; ignored for ammo (equips entire stack). In NVSE, pretty much always forced internally to 1
	// OBSE: itemExtraList is NULL as the container changes entry is not resolved before the call
	// NVSE: Default values are those used by the vanilla script functions.
	void EquipItem(TESForm* objType, uint32_t equipCount = 1, ExtraDataList* itemExtraList = NULL, uint32_t unk3 = 1, bool lockEquip = false, uint32_t unk5 = 1);	// unk3 apply enchantment on player differently
	void UnequipItem(TESForm* objType, uint32_t unequipCount = 1, ExtraDataList* itemExtraList = NULL, uint32_t unk3 = 1, bool lockEquip = false, uint32_t unk5 = 1);

	//EquippedItemsList GetEquippedItems();
	//ExtraContainerDataArray GetEquippedEntryDataList();
	//ExtraContainerExtendDataArray GetEquippedExtendDataList();

	bool GetDead() { return (lifeState == 1) || (lifeState == 2); }
	bool GetRestrained() { return lifeState == 5; }

	TESActorBase* GetActorBase();
	bool GetLOS(Actor* target);
	char GetCurrentAIPackage();
	char GetCurrentAIProcedure();
	bool IsFleeing();
	TESObjectWEAP* GetEquippedWeapon();
	bool IsItemEquipped(TESForm* item);
	bool GetEquippedItemData(uint32_t slotIndex, ItemEntryData& itemData);
	uint8_t EquippedWeaponHasMod(uint8_t modID);
	bool IsSneaking();
	void StopCombat();
	bool IsInCombatWith(Actor* target);
	int GetDetectionValue(Actor* detected);
	TESPackage* GetStablePackage();
	PackageInfo* GetPackageInfo();
	TESObjectREFR* GetPackageTarget();
	TESCombatStyle* GetCombatStyle();
	bool GetKnockedState();
	bool IsWeaponOut();
	void UpdateActiveEffects(MagicItem* magicItem, EffectItem* effItem, ActiveEffectCreate callback, bool addNew);
	bool GetIsGhost();
	float GetRadiationLevel();
	BackUpPackage* AddBackUpPackage(TESObjectREFR* targetRef, TESObjectCELL* targetCell, uint32_t flags);
	void TurnToFaceObject(TESObjectREFR* target);
	void TurnAngle(float angle);
	void HandleSetAnimSequence(int32_t animAction, BSAnimGroupSequence* animGroupSeq);
	void PlayIdle(TESIdleForm* idleAnim);
	float GetKillXP();
	void DismemberLimb(uint32_t bodyPartID, bool explode);
	void EquipItemAlt(ItemChange* itemEntry, bool noUnequip, bool noMessage);
	void EquipContainer(TESContainer* container);
	bool HasNoPath();

	bool SetPathfindingGoal(TESObjectREFR* apTargetRef, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes = nullptr);
	bool SetPathfindingGoal(const NiPoint3& arGoalLocation, TESObjectCELL* apCell, TESWorldSpace* apWorldSpace, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes = nullptr);
	bool SetPathfindingGoalAndAngle(TESObjectREFR* apTargetRef, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes = nullptr);
	bool SetPathfindingGoalAndAngle(const NiPoint3& arGoalLocation, TESObjectCELL* apCell, TESWorldSpace* apWorldSpace, float afTargetRadius, float afTargetAngle, PathingAvoidNodeArray* apAvoidNodes = nullptr);


	void StopMoving();

	bool IsInDialogueWithPlayer() const;

	bool GetRespawn() const;
};

// 1C0
class Creature : public Actor {
public:
	Creature();
	~Creature();

	virtual void	Unk_137(void);

	uint32_t			unk1B4[3];			// 1B4
};

// 1C8
class Character : public Actor {
public:
	Character();
	~Character();

	virtual void	Unk_137(void);
	virtual void	Unk_138(void);

	BipedAnim* pBipedAnim;	// 1B4
	float			totalArmorDR;		// 1B8
	float			totalArmorDT;		// 1BC
	uint8_t			isTrespassing;		// 1C0
	uint8_t			byt1C1;				// 1C1
	uint16_t			unk1C2;				// 1C2
	float			unk1C4;				// 1C4
};
static_assert(sizeof(Character) == 0x1C8);
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
	tList<CasinoStats>* casinoDataList;				// 610
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
	uint8_t								byte64D;				// 64D
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
	tList<BGSQuestObjective::Target>	questTargetList;		// 6C4
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
	tList<CompassTarget>* compassTargets;				// D48
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
	uint32_t GetMovementFlags() const { return actorMover->GetMoveMode(); }	// 11: IsSwimming, 9: IsSneaking, 8: IsRunning, 7: IsWalking, 0: keep moving
	bool IsPlayerSwimming() const { return (GetMovementFlags() >> 11) & 1; }

	static PlayerCharacter* GetSingleton();
	bool SetSkeletonPath(const char* newPath);
	static void UpdateHead(void);

	bool ToggleFirstPerson(bool toggleON);
	char GetDetectionState();

	NiNode* Get3D(bool abFirstPerson) const;
	BipedAnim* GetBiped(bool abFirstPerson) const;
	Animation* GetAnimation(bool abFirstPerson) const;
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
	NiRefObject* object114;		// 114
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

struct ProjectileData {
	uint8_t byte00;
	uint8_t byte01;
	uint8_t byte02;
	uint8_t gap03;
	float unk04;
	float flashDuration;
	NiNode* muzzleFlash;
	NiPointLight* flashLight;
	BGSProjectile* projectile;
	TESObjectWEAP* sourceWeap;
	Actor* sourceActor;
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
