#pragma once

#include "Utilities.h"
#include "GameBSExtraData.h"
#include "GameForms.h"
#include "Bethesda/BSSimpleList.hpp"
#include "Bethesda/InventoryChanges.hpp"
#include "Bethesda/ItemChange.hpp"
#include "Bethesda/ExtraCellAcousticSpace.hpp"
#include "Bethesda/ExtraEncounterZone.hpp"
#include "Bethesda/ExtraRadius.hpp"
#include "Bethesda/ExtraPoison.hpp"
#include "Bethesda/ExtraPersistentCell.hpp"
#include "Bethesda/ExtraOwnership.hpp"
#include "Bethesda/ExtraPrimitive.hpp"
#include "Bethesda/ExtraHotkey.hpp"
#include "Bethesda/ExtraSeenData.hpp"
#include "Bethesda/ExtraDetachTime.hpp"

class BGSPrimitive;
struct AnimData;
class SeenData;

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

#define GetExtraType(xDataList, Type) (Extra ## Type*)(xDataList).GetExtraData(kExtraData_ ## Type)

// 014
class ExtraAction : public BSExtraData {
public:
	ExtraAction();
	virtual ~ExtraAction();

	uint8_t			byte0C;		// 00C	some kind of status or flags
	uint8_t			fill0D[3];	// 00D
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

uint32_t GetCountForExtraDataList(ExtraDataList* list);

// 010
class ExtraContainerChanges : public BSExtraData {
public:
	ExtraContainerChanges();
	virtual ~ExtraContainerChanges();

	InventoryChanges* pChanges;

	ItemChange* GetByType(TESForm* type);

	static ExtraContainerChanges* Create();

	BSSimpleList<ItemChange*>* GetEntryDataList() const {
		return pChanges ? pChanges->pItems : NULL;
	}
};

// 010
class ExtraLock : public BSExtraData {
public:
	ExtraLock();
	virtual ~ExtraLock();

	struct Data {
		uint32_t	lockLevel;	// 00
		TESKey* key;		// 04
		uint8_t	flags;		// 08
		uint8_t	pad[3];
		uint32_t  unk0C;		// 0C introduced since form version 0x10
		uint32_t	unk10;		// 10
	};

	Data* data;		// 00C

	static ExtraLock* Create();
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
		uint8_t			unk01C;		// 1C
		uint8_t			pad01D[3];	// 1D
	};

	Data* data;

	static ExtraTeleport* Create();
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

static_assert(sizeof(ExtraFactionChanges) == 0x10);

class ExtraFactionChangesMatcher {
	TESFaction* pFaction;
	ExtraFactionChanges* xFactionChanges;
public:
	ExtraFactionChangesMatcher(TESFaction* faction, ExtraFactionChanges* FactionChanges) : pFaction(faction), xFactionChanges(FactionChanges) {}
	bool Accept(const FactionListData* data) const {
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

static_assert(sizeof(ExtraLeveledCreature) == 0x14);

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
		uint16_t flags;
		uint16_t type;
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

// 10
class ExtraAnim : public BSExtraData {
public:
	ExtraAnim();
	virtual ~ExtraAnim();

	AnimData* animData;	// 0C
};

// 10
class ExtraFollower : public BSExtraData {
public:
	ExtraFollower();
	virtual ~ExtraFollower();

	tList<Actor>* followers;		// 0C
};

// 14
class ExtraEnableStateChildren : public BSExtraData {
public:
	ExtraEnableStateChildren();
	virtual ~ExtraEnableStateChildren();

	tList<TESObjectREFR>	children;	// 0C
};

// 14
class ExtraDroppedItemList : public BSExtraData {
public:
	ExtraDroppedItemList();
	virtual ~ExtraDroppedItemList();

	tList<TESObjectREFR>	itemRefs;	// 0C
};

// 14
class ExtraLinkedRefChildren : public BSExtraData {
public:
	ExtraLinkedRefChildren();
	virtual ~ExtraLinkedRefChildren();

	tList<TESObjectREFR>	children;	// 0C
};

// 20
class ExtraActivateRef : public BSExtraData {
public:
	ExtraActivateRef();
	virtual ~ExtraActivateRef();

	struct parentRef {
		TESObjectREFR* ref;
		float			delay;
	};
	tList<parentRef>	parentRefs;
	uint8_t				flags;
	BSString				activationPromptOverride;
};

// 30
class ExtraDismemberedLimbs : public BSExtraData {
public:
	ExtraDismemberedLimbs();
	virtual ~ExtraDismemberedLimbs();

	struct DismemberedLimb {
		uint8_t				bodyPartID;
		uint8_t				explodeChance;
		bool				explodeOnly;
		uint8_t				byte03;
		BSSimpleArray<void*>* array04;
	};

	uint16_t							dismemberedMask;	// 0C
	uint8_t							pad0E[2];			// 0E
	int								unk10;				// 10
	TESObjectWEAP* weapon;			// 14
	int								unk18;				// 18
	bool							wasEaten;			// 1C
	uint8_t							pad1D[3];			// 1D
	BSSimpleArray<DismemberedLimb*>	dismemberedLimbs;	// 20
};

// 28
class ExtraFollowerSwimBreadcrumbs : public BSExtraData {
public:
	ExtraFollowerSwimBreadcrumbs();
	virtual ~ExtraFollowerSwimBreadcrumbs();
	struct ExtraFollowerSwimBreadcrumb {
		NiPoint3 StartLocation;
		uint32_t StartNavMeshID;
		NiPoint3 EndLocation;
		uint32_t EndNavMeshID;
		bool bEnteringWater;
	};
	uint32_t			leaderState;
	NiPoint3		leaderLocation;
	uint32_t			leaderNavmeshID;
	tList<ExtraFollowerSwimBreadcrumb*>		crumbList;
};
static_assert(sizeof(ExtraFollowerSwimBreadcrumbs) == 0x28);
// 34
struct ExtraAudioMarkerData {
	TESFullName		fullName;
	float			layer2TriggerPerc;
	float			layer3TriggerPerc;
	uint32_t			unk14[4];
	uint32_t			mediaLocCtrlID;
	uint32_t			flags;
	uint32_t			unk2C[2];
};
// 10
class ExtraAudioMarker : public BSExtraData {
public:
	ExtraAudioMarker();
	virtual ~ExtraAudioMarker();

	ExtraAudioMarkerData* data;
};