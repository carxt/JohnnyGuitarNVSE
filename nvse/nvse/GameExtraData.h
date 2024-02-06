#pragma once

#include "Utilities.h"
#include "GameBSExtraData.h"
#include "GameForms.h"

/*    Class							     vtbl	  Type  Size
 *   ----------------------------		------		--  --
 *	ExtraAction                        ????????		0E	14
 *	ExtraActivateLoopSound             ????????		87	18
 *	ExtraActivateRef                   ????????		53	18
 *	ExtraActivateRefChildren           ????????		54	18
 *	ExtraAmmo                          ????????		6E	14
 *	ExtraAnim                          ????????		10	10
 *	ExtraAshPileRef                    ????????		89	10
 *	ExtraCannotWear                    ????????		3E	0C	// no data
 *	ExtraCell3D                        ????????		2	10
 *	ExtraCellAcousticSpace             ????????		81	10
 *	ExtraCellCanopyShadowMask          ????????		0A	1C
 *	ExtraCellClimate                   ????????		8	10
 *	ExtraCellImageSpace                ????????		59	10
 *	ExtraCellMusicType                 ????????		7	10
 *	ExtraCellWaterType                 ????????		3	10
 *	ExtraCharge                        ????????		28	10
 *	ExtraCollisionData                 ????????		72	10
 *	ExtraCombatStyle                   ????????		69	10
 *	ExtraContainerChanges              ????????		15	10
 *	ExtraCount                         ????????		24	10
 *	ExtraCreatureAwakeSound            ????????		7D	18
 *	ExtraCreatureMovementSound         ????????		8A	18
 *	ExtraDecalRefs                     ????????		57	14
 *	ExtraDetachTime                    ????????		0B	10
 *	ExtraDismemberedLimbs              ????????		5F	30
 *	ExtraDistantData                   ????????		13	18
 *	ExtraDroppedItemList               ????????		3A	14
 *	ExtraEditorRefMovedData            ????????		4C	30
 *	ExtraEmittanceSource               ????????		67	10
 *	ExtraEnableStateChildren           ????????		38	14
 *	ExtraEnableStateParent             ????????		37	14
 *	ExtraEncounterZone                 ????????		74	10
 *	ExtraFactionChanges                ????????		5E	10
 *	ExtraFollower                      ????????		1D	10
 *	ExtraFollowerSwimBreadcrumbs       ????????		8B	28
 *	ExtraFriendHits                    ????????		45	1C
 *	ExtraGhost                         ????????		1F	0C	// no data
 *	ExtraGlobal                        ????????		22	10
 *	ExtraGuardedRefData                ????????		7C	1C
 *	ExtraHasNoRumors                   ????????		4E	10
 *	ExtraHavok                         ????????		1	14
 *	ExtraHeadingTarget                 ????????		46	10
 *	ExtraHealth                        ????????		25	10
 *	ExtraHealthPerc                    ????????		7A	10
 *	ExtraHotkey                        ????????		4A	10
 *	ExtraIgnoredBySandbox              ????????		80	0C	// no data
 *	ExtraInfoGeneralTopic              ????????		4D	10
 *	ExtraItemDropper                   ????????		39	10
 *	ExtraLastFinishedSequence          ????????		41	10
 *	ExtraLevCreaModifier               ????????		1E	10
 *	ExtraLeveledCreature               ????????		2E	14
 *	ExtraLeveledItem                   ????????		2F	14
 *	ExtraLight                         ????????		29	10
 *	ExtraLinkedRef                     ????????		51	10
 *	ExtraLinkedRefChildren             ????????		52	14
 *	ExtraLitWaterRefs                  ????????		85	14
 *	ExtraLock                          ????????		2A	10
 *	ExtraMapMarker                     ????????		2C	10
 *	ExtraMerchantContainer             ????????		3C	10
 *	ExtraModelSwap                     ????????		5B	14
 *	ExtraMultiBound                    ????????		61	10
 *	ExtraMultiBoundData                ????????		62	10
 *	ExtraMultiBoundRef                 ????????		63	10
 *	ExtraNavMeshPortal                 ????????		5A	14
 *	ExtraNorthRotation                 ????????		43	10
 *	ExtraObjectHealth                  ????????		56	10
 *	ExtraOcclusionPlane                ????????		71	10
 *	ExtraOcclusionPlaneRefData         ????????		76	10
 *	ExtraOpenCloseActivateRef          ????????		6C	10
 *	ExtraOriginalReference             ????????		20	10
 *	ExtraOwnership                     ????????		21	10
 *	ExtraPackage                       ????????		19	1C
 *	ExtraPackageData                   ????????		70	10
 *	ExtraPackageStartLocation          ????????		18	1C
 *	ExtraPatrolRefData                 ????????		6F	10
 *	ExtraPatrolRefInUseData            ????????		88	10
 *	ExtraPersistentCell                ????????		0C	10
 *	ExtraPlayerCrimeList               ????????		35	10
 *	ExtraPoison                        ????????		3F	10
 *	ExtraPortal                        ????????		78	10
 *	ExtraPortalRefData                 ????????		77	10
 *	ExtraPrimitive                     ????????		6B	10
 *	ExtraProcessMiddleLow              ????????		9	10
 *	ExtraRadiation                     ????????		5D	10
 *	ExtraRadioData                     ????????		68	1C
 *	ExtraRadius                        ????????		5C	10
 *	ExtraRagdollData                   ????????		14	10
 *	ExtraRandomTeleportMarker          ????????		3B	10
 *	ExtraRank                          ????????		23	10
 *	ExtraReferencePointer              ????????		1C	10
 *	ExtraReflectedRefs                 ????????		65	14
 *	ExtraReflectorRefs                 ????????		66	14
 *	ExtraRefractionProperty            ????????		48	10
 *	ExtraRegionList                    ????????		4	10
 *	ExtraReservedMarkers               ????????		82	10
 *	ExtraRoom                          ????????		79	10
 *	ExtraRoomRefData                   ????????		7B	10
 *	ExtraRunOncePacks                  ????????		1B	10
 *	ExtraSavedAnimation                ????????		42	10
 *	ExtraSavedHavokData                ????????		3D	10
 *	ExtraSayToTopicInfo                ????????		75	18
 *	ExtraSayTopicInfoOnceADay          ????????		73	10
 *	ExtraScale                         ????????		30	10
 *	ExtraScript                        ????????		0D	14
 *	ExtraSeed                          ????????		31	10
 *	ExtraSeenData                      ????????		5	10
 *	ExtraSound                         ????????		4F	18
 *	ExtraStartingPosition              ????????		0F	24
 *	ExtraStartingWorldOrCell           ????????		49	10
 *	ExtraTalkingActor                  ????????		55	10
 *	ExtraTeleport                      ????????		2B	10
 *	ExtraTerminalState                 ????????		50	10
 *	ExtraTimeLeft                      ????????		27	10
 *	ExtraTrespassPackage               ????????		1A	10
 *	ExtraUsedMarkers                   ????????		12	10
 *	ExtraUses                          ????????		26	10
 *	ExtraWaterLightRefs                ????????		84	14
 *	ExtraWaterZoneMap                  ????????		7E	20
 *	ExtraWeaponAttackSound             ????????		86	18
 *	ExtraWeaponIdleSound               ????????		83	18
 *	ExtraWeaponModFlags                ????????		8D	10
 *	ExtraWorn                          ????????		16	0C	// no data
 *	ExtraWornLeft                      ????????		17	0C	// no data
 *	ExtraXTarget                       ????????		44	10
 */

 /* BaseExtraList methods:
	 AddExtra		0x0040A180
	 GetByType		0x0040A320, pass typeID
	 ItemsInList		0x0040A130
	 RemoveExtra		0x0040A250

   ExtraDataList methods:
	 DuplicateExtraListForContainer	0x0041B090
 */

enum {
	kExtraData_Unknown00,
	kExtraData_Havok,
	kExtraData_Cell3D,
	kExtraData_CellWaterType,
	kExtraData_RegionList,
	kExtraData_SeenData,
	kExtraData_EditorID,
	kExtraData_CellMusicType,
	kExtraData_CellClimate,
	kExtraData_ProcessMiddleLow,
	kExtraData_CellCanopyShadowMask,
	kExtraData_DetachTime,
	kExtraData_PersistentCell,
	kExtraData_Script,
	kExtraData_Action,
	kExtraData_StartingPosition,
	kExtraData_Anim,
	kExtraData_Unknown11,
	kExtraData_UsedMarkers,
	kExtraData_DistantData,
	kExtraData_RagdollData,
	kExtraData_ContainerChanges,
	kExtraData_Worn,
	kExtraData_WornLeft,
	kExtraData_PackageStartLocation,
	kExtraData_Package,
	kExtraData_TrespassPackage,
	kExtraData_RunOncePacks,
	kExtraData_ReferencePointer,
	kExtraData_Follower,
	kExtraData_LevCreaModifier,
	kExtraData_Ghost,
	kExtraData_OriginalReference,
	kExtraData_Ownership,
	kExtraData_Global,
	kExtraData_Rank,
	kExtraData_Count,
	kExtraData_Health,
	kExtraData_Uses,
	kExtraData_TimeLeft,
	kExtraData_Charge,
	kExtraData_Light,
	kExtraData_Lock,
	kExtraData_Teleport,
	kExtraData_MapMarker,
	kExtraData_Unknown2D,
	kExtraData_LeveledCreature,
	kExtraData_LeveledItem,
	kExtraData_Scale,
	kExtraData_Seed,
	kExtraData_NonActorMagicCaster,
	kExtraData_NonActorMagicTarget,
	kExtraData_Unknown34,
	kExtraData_PlayerCrimeList,
	kExtraData_Unknown36,
	kExtraData_EnableStateParent,
	kExtraData_EnableStateChildren,
	kExtraData_ItemDropper,
	kExtraData_DroppedItemList,
	kExtraData_RandomTeleportMarker,
	kExtraData_MerchantContainer,
	kExtraData_SavedHavokData,
	kExtraData_CannotWear,
	kExtraData_Poison,
	kExtraData_Unknown40,
	kExtraData_LastFinishedSequence,
	kExtraData_SavedAnimation,
	kExtraData_NorthRotation,
	kExtraData_XTarget,
	kExtraData_FriendHits,
	kExtraData_HeadingTarget,
	kExtraData_Unknown47,
	kExtraData_RefractionProperty,
	kExtraData_StartingWorldOrCell,
	kExtraData_Hotkey,
	kExtraData_Unknown4B,
	kExtraData_EditorRefMovedData,
	kExtraData_InfoGeneralTopic,
	kExtraData_HasNoRumors,
	kExtraData_Sound,
	kExtraData_TerminalState,
	kExtraData_LinkedRef,
	kExtraData_LinkedRefChildren,
	kExtraData_ActivateRef,
	kExtraData_ActivateRefChildren,
	kExtraData_TalkingActor,
	kExtraData_ObjectHealth,
	kExtraData_DecalRefs,
	kExtraData_Unknown58,
	kExtraData_CellImageSpace,
	kExtraData_NavMeshPortal,
	kExtraData_ModelSwap,
	kExtraData_Radius,
	kExtraData_Radiation,
	kExtraData_FactionChanges,
	kExtraData_DismemberedLimbs,
	kExtraData_ActorCause,
	kExtraData_MultiBound,
	kExtraData_MultiBoundData,
	kExtraData_MultiBoundRef,
	kExtraData_Unknown64,
	kExtraData_ReflectedRefs,
	kExtraData_ReflectorRefs,
	kExtraData_EmittanceSource,
	kExtraData_RadioData,
	kExtraData_CombatStyle,
	kExtraData_Unknown6A,
	kExtraData_Primitive,
	kExtraData_OpenCloseActivateRef,
	kExtraData_AnimNoteReciever,
	kExtraData_Ammo,
	kExtraData_PatrolRefData,
	kExtraData_PackageData,
	kExtraData_OcclusionPlane,
	kExtraData_CollisionData,
	kExtraData_SayTopicInfoOnceADay,
	kExtraData_EncounterZone,
	kExtraData_SayToTopicInfo,
	kExtraData_OcclusionPlaneRefData,
	kExtraData_PortalRefData,
	kExtraData_Portal,
	kExtraData_Room,
	kExtraData_HealthPerc,
	kExtraData_RoomRefData,
	kExtraData_GuardedRefData,
	kExtraData_CreatureAwakeSound,
	kExtraData_WaterZoneMap,
	kExtraData_Unknown7F,
	kExtraData_IgnoredBySandbox,
	kExtraData_CellAcousticSpace,
	kExtraData_ReservedMarkers,
	kExtraData_WeaponIdleSound,
	kExtraData_WaterLightRefs,
	kExtraData_LitWaterRefs,
	kExtraData_WeaponAttackSound,
	kExtraData_ActivateLoopSound,
	kExtraData_PatrolRefInUseData,
	kExtraData_AshPileRef,
	kExtraData_CreatureMovementSound,
	kExtraData_FollowerSwimBreadcrumbs,
	kExtraData_CellImpactSwap,
	kExtraData_WeaponModFlags,
	kExtraData_ModdingItem,
	kExtraData_SecuritronFace,
	kExtraData_AudioMarker,
	kExtraData_AudioBuoyMarker,
	kExtraData_SpecialRenderFlags,
	kExtraData_Max
};

#define GetExtraType(xDataList, Type) (Extra ## Type*)(xDataList).GetByType(kExtraData_ ## Type)

// 014
class ExtraAction : public BSExtraData {
public:
	ExtraAction();
	virtual ~ExtraAction();

	UInt8			byte0C;		// 00C	some kind of status or flags
	UInt8			fill0D[3];	// 00D
	TESObjectREFR* actionRef;	// 010

	static ExtraAction* __stdcall Create(TESObjectREFR* _actionRef = NULL);
};

// 014
class ExtraScript : public BSExtraData {
public:
	ExtraScript();
	virtual ~ExtraScript();

	Script* script;		// 00C
	ScriptEventList* eventList;	// 010

	static ExtraScript* __stdcall Create(TESForm* baseForm = NULL, bool create = true, TESObjectREFR* container = NULL);
};

UInt32 GetCountForExtraDataList(ExtraDataList* list);

// 010
class ExtraContainerChanges : public BSExtraData {
public:
	ExtraContainerChanges();
	virtual ~ExtraContainerChanges();

	class ExtendDataList : public tList<ExtraDataList> {
	public:
		void Clear();
		ExtraDataList* RemoveExtra(ExtraDataList* xDataList, BSExtraData* xData);
		ExtraDataList* RemoveByType(ExtraDataList* xDataList, UInt32 type);
		void CleanEmpty();
	};

	struct EntryData {
		ExtendDataList* extendData;
		SInt32			countDelta;
		TESForm* type;

		EntryData(ListNode<ExtraDataList>* extend, SInt32 count, TESForm* item) :
			extendData((ExtendDataList*)extend), countDelta(count), type(item) {}

		void Cleanup();
		void RemoveCannotWear();
		float GetItemHealthPerc(bool arg1 = true) { return ThisStdCall_F(0x4BCDB0, this, arg1); }
		ExtraDataList* GetEquippedExtra();
		float CalculateWeaponDamage(float condition, TESForm* ammo);
	};

	struct EntryDataList : tList<EntryData> {
		EntryData* FindForItem(TESForm* item);
	};

	struct Data {
		EntryDataList* objList;
		TESObjectREFR* owner;
		float			totalWgCurrent;
		float			totalWgLast;
		UInt8			byte10;	// referenced in relation to scripts in container
		UInt8			pad[3];

		static Data* Create(TESObjectREFR* owner);
		float GetInventoryWeight();
	};

	Data* data;	// 00C

	EntryData* GetByType(TESForm* type);

	void DebugDump();
	void Cleanup();	// clean up unneeded extra data from each EntryData

	static ExtraContainerChanges* Create();

	// find the equipped item whose form matches the passed matcher
	struct FoundEquipData {
		TESForm* pForm;
		ExtraDataList* pExtraData;
	};
	FoundEquipData FindEquipped(FormMatcher& matcher) const;

	EntryDataList* GetEntryDataList() const {
		return data ? data->objList : NULL;
	}
};
typedef ExtraContainerChanges::EntryData ContChangesEntry;

// Finds an ExtraDataList in an ExtendDataList
class ExtraDataListInExtendDataListMatcher {
	ExtraDataList* m_toMatch;
public:
	ExtraDataListInExtendDataListMatcher(ExtraDataList* match) : m_toMatch(match) {}

	bool Accept(ExtraDataList* match) {
		return (m_toMatch == match);
	}
};

// Finds an ExtraDataList in an ExtendDataList embedded in one of the EntryData from an EntryDataList
class ExtraDataListInEntryDataListMatcher {
	ExtraDataList* m_toMatch;
public:
	ExtraDataListInEntryDataListMatcher(ExtraDataList* match) : m_toMatch(match) {}

	bool Accept(ExtraContainerChanges::EntryData* match) {
		if (match && match->extendData) {
			auto finder = ExtraDataListInExtendDataListMatcher(m_toMatch);
			return match->extendData->GetIndexOf(finder) >= 0;
		}
		else
			return false;
	}
};

// Finds an ExtendDataList in an EntryDataList
class ExtendDataListInEntryDataListMatcher {
	ExtraContainerChanges::ExtendDataList* m_toMatch;
public:
	ExtendDataListInEntryDataListMatcher(ExtraContainerChanges::ExtendDataList* match) : m_toMatch(match) {}

	bool Accept(ExtraContainerChanges::EntryData* match) {
		if (match && match->extendData)
			return (match->extendData == m_toMatch);
		else
			return false;
	}
};

// Finds an EntryData in an EntryDataList
class EntryDataInEntryDataListMatcher {
	ExtraContainerChanges::EntryData* m_toMatch;
public:
	EntryDataInEntryDataListMatcher(ExtraContainerChanges::EntryData* match) : m_toMatch(match) {}

	bool Accept(ExtraContainerChanges::EntryData* match) {
		return (m_toMatch == match);
	}
};

// Finds an Item (type) in an EntryDataList
class ItemInEntryDataListMatcher {
	TESForm* m_toMatch;
public:
	ItemInEntryDataListMatcher(TESForm* match) : m_toMatch(match) {}

	bool Accept(ExtraContainerChanges::EntryData* match) {
		return (match && m_toMatch == match->type);
	}
};

// Finds an Item from its base form in an EntryDataList
class BaseInEntryDataLastMatcher {
	TESForm* m_toMatch;
public:
	BaseInEntryDataLastMatcher(TESForm* match) : m_toMatch(match) {}

	bool Accept(ExtraContainerChanges::EntryData* match) {
		return (match && match->type && m_toMatch == match->type->TryGetREFRParent());
	}
};

// Finds an item by refID in an EntryDataList
class RefIDInEntryDataListMatcher {
	UInt32 m_toMatch;
public:
	RefIDInEntryDataListMatcher(UInt32 match) : m_toMatch(match) {}

	bool Accept(ExtraContainerChanges::EntryData* match) {
		return (match && match->type && m_toMatch == match->type->refID);
	}
};

// Finds an item by the refID of its base form in an EntryDataList
class BaseIDInEntryDataListMatcher {
	UInt32 m_toMatch;
public:
	BaseIDInEntryDataListMatcher(UInt32 match) : m_toMatch(match) {}

	bool Accept(ExtraContainerChanges::EntryData* match) {
		return (match && match->type && match->type->TryGetREFRParent() && m_toMatch == match->type->TryGetREFRParent()->refID);
	}
};

typedef ExtraContainerChanges::FoundEquipData EquipData;

extern ExtraContainerChanges::ExtendDataList* ExtraContainerChangesExtendDataListCreate(ExtraDataList* pExtraDataList = NULL);
extern void ExtraContainerChangesExtendDataListFree(ExtraContainerChanges::ExtendDataList* xData, bool bFreeList = false);

// 010
class ExtraHealth : public BSExtraData {
public:
	ExtraHealth();
	virtual ~ExtraHealth();
	float health;

	static ExtraHealth* __stdcall Create(float _health = 0);
};

// 00C
class ExtraWorn : public BSExtraData	// Item is equipped
{
public:
	ExtraWorn();
	virtual ~ExtraWorn();

	static ExtraWorn* Create();
};

// 00C
class ExtraWornLeft : public BSExtraData	// haven't seen used yet
{
public:
	ExtraWornLeft();
	virtual ~ExtraWornLeft();

	//static ExtraWornLeft* Create();
};

// 00C
class ExtraCannotWear : public BSExtraData	//	Seen used as ForceEquip ! Unused as forceUnequip (bug?)
{
public:
	ExtraCannotWear();
	virtual ~ExtraCannotWear();

	static ExtraCannotWear* Create();
};

// 010
class ExtraHotkey : public BSExtraData {
public:
	ExtraHotkey();
	virtual ~ExtraHotkey();

	UInt8	index;		// 00C (is 0-7)

	static ExtraHotkey* __stdcall Create(UInt8 _index = 0);
};

// 010
class ExtraCount : public BSExtraData {
public:
	ExtraCount();
	virtual ~ExtraCount();

	SInt16	count;	// 00C
	UInt8	pad[2];	// 00E

	static ExtraCount* __stdcall Create(UInt32 count = 0);
};

// 010
class ExtraLock : public BSExtraData {
public:
	ExtraLock();
	virtual ~ExtraLock();

	struct Data {
		UInt32	lockLevel;	// 00
		TESKey* key;		// 04
		UInt8	flags;		// 08
		UInt8	pad[3];
		UInt32  unk0C;		// 0C introduced since form version 0x10
		UInt32	unk10;		// 10
	};

	Data* data;		// 00C

	static ExtraLock* Create();
};

// 010
class ExtraUses : public BSExtraData {
public:
	ExtraUses();
	~ExtraUses();

	UInt32 unk0;

	static ExtraUses* Create();
};

// 010
class ExtraTeleport : public BSExtraData {
public:
	ExtraTeleport();
	~ExtraTeleport();

	struct Data {
		TESObjectREFR* linkedDoor;	// 00
		float			x;			// 04 x, y, z, zRot refer to teleport marker's position and rotation
		float			y;
		float			z;
		float			xRot;		// 10 angles in radians. x generally 0
		float			yRot;		// 14 y generally -0.0, no reason to modify
		float			zRot;		// 18
		UInt8			unk01C;		// 1C
		UInt8			pad01D[3];	// 1D
	};

	Data* data;

	static ExtraTeleport* Create();
};

// 010
class ExtraRandomTeleportMarker : public BSExtraData {
public:
	ExtraRandomTeleportMarker();
	~ExtraRandomTeleportMarker();

	TESObjectREFR* teleportRef;
};

// 014
class ExtraAmmo : public BSExtraData {
public:
	ExtraAmmo();
	~ExtraAmmo();

	TESAmmo* ammo;
	UInt32 unk4;
};

// 010
class ExtraOwnership : public BSExtraData {
public:
	ExtraOwnership();
	virtual ~ExtraOwnership();

	TESForm* owner;	// maybe this should be a union {TESFaction*; TESNPC*} but it would be more unwieldy to access and modify

	static ExtraOwnership* __stdcall Create(TESForm* _owner);
};

// 010
class ExtraRank : public BSExtraData {
public:
	ExtraRank();
	virtual ~ExtraRank();

	SInt32	rank; // 00C

	static ExtraRank* __stdcall Create(UInt32 _rank);
};

// 010
class ExtraGlobal : public BSExtraData {								//ownership data, stored separately from ExtraOwnership
public:
	ExtraGlobal();
	virtual ~ExtraGlobal();

	TESGlobal* globalVar;	// 00C
};

// 010
class ExtraWeaponModFlags : public BSExtraData {
public:
	ExtraWeaponModFlags();
	~ExtraWeaponModFlags();

	UInt8	flags; // 00C

	static ExtraWeaponModFlags* __stdcall Create(UInt8 _flags = 0);
};

class ExtraFactionChanges : public BSExtraData {
public:
	ExtraFactionChanges();
	virtual ~ExtraFactionChanges();

	typedef tList<FactionListData> FactionListEntry;
	FactionListEntry* data;

	void DebugDump();

	static ExtraFactionChanges* Create();
};

STATIC_ASSERT(sizeof(ExtraFactionChanges) == 0x10);

class ExtraFactionChangesMatcher {
	TESFaction* pFaction;
	ExtraFactionChanges* xFactionChanges;
public:
	ExtraFactionChangesMatcher(TESFaction* faction, ExtraFactionChanges* FactionChanges) : pFaction(faction), xFactionChanges(FactionChanges) {}
	bool Accept(FactionListData* data) {
		return (data->faction == pFaction) ? true : false;
	}
};

ExtraFactionChanges::FactionListEntry* GetExtraFactionList(BaseExtraList& xDataList);
void SetExtraFactionRank(BaseExtraList& xDataList, TESFaction* faction, char rank);

class ExtraLeveledCreature : public BSExtraData {
public:
	ExtraLeveledCreature();
	virtual ~ExtraLeveledCreature();

	TESForm* baseForm;	// 00C
	TESForm* form;		// 010
};

STATIC_ASSERT(sizeof(ExtraLeveledCreature) == 0x14);

// PackageStartLocation = Worldspace or Cell / PosX / PosY / PosZ / and 4 bytes

class ExtraCombatStyle : public BSExtraData {
public:
	ExtraCombatStyle();
	virtual ~ExtraCombatStyle();

	TESCombatStyle* combatStyle;		// 00C
};

class ExtraReferencePointer : public BSExtraData {
public:
	ExtraReferencePointer();
	virtual ~ExtraReferencePointer();

	TESObjectREFR* refr;		// 00C
};

// Provided by "Luthien Anarion"
class ExtraMapMarker : BSExtraData {
public:
	ExtraMapMarker();
	~ExtraMapMarker();

	enum {
		kFlag_Visible = 1 << 0,        // shown on the world map
		kFlag_CanTravel = 1 << 1,        // visited, can fast-travel to it
		kFlag_Hidden = 1 << 2,        // does not appear with Explorer perk
	};
	enum {
		kType_None = 0,                // this determines the icon on the world map
		kType_City,
		kType_Settlement,
		kType_Encampment,
		kType_NaturalLandmark,
		kType_Cave,
		kType_Factory,
		kType_Memorial,
		kType_Military,
		kType_Office,
		kType_TownRuins,
		kType_UrbanRuins,
		kType_SewerRuins,
		kType_Metro,
		kType_Vault,
	};

	struct MarkerData {
		TESFullName fullName;            // not all markers have this
		UInt16 flags;
		UInt16 type;
		TESForm* reputation;            // not all markers have this
	};
	MarkerData* data;

	// flag member functions
	bool IsVisible() { return (data->flags & kFlag_Visible) == kFlag_Visible; }
	bool CanTravel() { return (data->flags & kFlag_CanTravel) == kFlag_CanTravel; }
	bool IsHidden() { return (data->flags & kFlag_Hidden) == kFlag_Hidden; }
	void SetVisible(bool visible) { data->flags = (visible) ? (data->flags | kFlag_Visible) : (data->flags & ~kFlag_Visible); }
	void SetCanTravel(bool travel) { data->flags = (travel) ? (data->flags | kFlag_CanTravel) : (data->flags & ~kFlag_CanTravel); }
	void SetHidden(bool hidden) { data->flags = (hidden) ? (data->flags | kFlag_Hidden) : (data->flags & ~kFlag_Hidden); }
};