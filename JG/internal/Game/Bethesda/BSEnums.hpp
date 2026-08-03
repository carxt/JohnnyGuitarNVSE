#pragma once

#pragma region Forms

using FormID	= uint32_t;
using RefID		= uint32_t;

struct _FormType {
	enum Type : uint32_t {
		NONE = 0,
		TES4,
		Group,
		GameSetting,
		BGSTextureSet,
		BGSMenuIcon,
		TESGlobal,
		TESClass,
		TESFaction,
		BGSHeadPart,
		TESHair,
		TESEyes,
		TESRace,
		TESSound,
		BGSAcousticSpace,
		TESSkill,
		EffectSetting,
		Script,
		TESLandTexture,
		EnchantmentItem,
		SpellItem,
		TESObjectACTI,
		BGSTalkingActivator,
		BGSTerminal,
		TESObjectARMO,
		TESObjectBOOK,
		TESObjectCLOT,
		TESObjectCONT,
		TESObjectDOOR,
		IngredientItem,
		TESObjectLIGH,
		TESObjectMISC,
		TESObjectSTAT,
		BGSStaticCollection,
		BGSMovableStatic,
		BGSPlaceableWater,
		TESGrass,
		TESObjectTREE,
		TESFlora,
		TESFurniture,
		TESObjectWEAP,
		TESAmmo,
		TESNPC,
		TESCreature,
		TESLevCreature,
		TESLevCharacter,
		TESKey,
		AlchemyItem,
		BGSIdleMarker,
		BGSNote,
		BGSConstructibleObject,
		BGSProjectile,
		TESLevItem,
		TESWeather,
		TESClimate,
		TESRegion,
		NavMeshInfoMap,
		TESObjectCELL,
		TESObjectREFR,
		Character,
		Creature,
		MissileProjectile,
		GrenadeProjectile,
		BeamProjectile,
		FlameProjectile,
		TESWorldSpace,
		TESObjectLAND,
		NavMesh,
		TLOD,
		TESTopic,
		TESTopicInfo,
		TESQuest,
		TESIdleForm,
		TESPackage,
		TESCombatStyle,
		TESLoadScreen,
		TESLevSpell,
		TESObjectANIO,
		TESWaterForm,
		TESEffectShader,
		TOFT,
		BGSExplosion,
		BGSDebris,
		TESImageSpace,
		TESImageSpaceModifier,
		BGSListForm,
		BGSPerk,
		BGSBodyPartData,
		BGSAddonNode,
		ActorValueInfo,
		BGSRadiationStage,
		BGSCameraShot,
		BGSCameraPath,
		BGSVoiceType,
		BGSImpactData,
		BGSImpactDataSet,
		TESObjectARMA,
		BGSEncounterZone,
		BGSMessage,
		BGSRagdoll,
		BGSDefaultObjectManager,
		BGSLightingTemplate,
		BGSMusicType,
		TESObjectIMOD,
		TESReputation,
		ContinuousBeamProjectile,
		TESRecipe,
		TESRecipeCategory,
		TESCasinoChips,
		TESCasino,
		TESLoadScreenType,
		MediaSet,
		MediaLocationController,
		TESChallenge,
		TESAmmoEffect,
		TESCaravanCard,
		TESCaravanMoney,
		TESCaravanDeck,
		BGSDehydrationStage,
		BGSHungerStage,
		BGSSleepDeprevationStage,
		COUNT
	};
};
using FORM_TYPE = _FormType::Type;

#define TESFORM_TYPE(data) static constexpr FORM_TYPE _TYPE = FORM_TYPE::data;

#pragma endregion

#pragma region ExtraData

struct _ExtraDataType {
	enum Type : uint8_t {
		NONE							= 0,
		ExtraHavok						= 1,
		ExtraCell3D						= 2,
		ExtraCellWaterType				= 3,
		ExtraRegionList					= 4,
		ExtraSeenData					= 5,
		ExtraEditorID					= 6,
		ExtraCellMusicType				= 7,
		ExtraCellClimate				= 8,
		ExtraProcessMiddleLow			= 9,
		ExtraCellCanopyShadowMask		= 10,
		ExtraDetachTime					= 11,
		ExtraPersistentCell				= 12,
		ExtraScript						= 13,
		ExtraAction						= 14,
		ExtraStartingPosition			= 15,
		ExtraAnim						= 16,
		ExtraUsedMarkers				= 18,
		ExtraDistantData				= 19,
		ExtraRagDollData				= 20,
		ExtraContainerChanges			= 21,
		ExtraWorn						= 22,
		ExtraWornLeft					= 23,
		ExtraPackageStartLocation		= 24,
		ExtraPackage					= 25,
		ExtraTresPassPackage			= 26,
		ExtraRunOncePacks				= 27,
		ExtraReferencePointer			= 28,
		ExtraFollower					= 29,
		ExtraLevCreaModifier			= 30,
		ExtraGhost						= 31,
		ExtraOriginalReference			= 32,
		ExtraOwnership					= 33,
		ExtraGlobal						= 34,
		ExtraRank						= 35,
		ExtraCount						= 36,
		ExtraHealth						= 37,
		ExtraUses						= 38,
		ExtraTimeLeft					= 39,
		ExtraCharge						= 40,
		ExtraLight						= 41,
		ExtraLock						= 42,
		ExtraTeleport					= 43,
		ExtraMapMarker					= 44,
		ExtraAnimSave					= 45,
		ExtraLeveledCreature			= 46,
		ExtraLeveledItem				= 47,
		ExtraScale						= 48,
		ExtraSeed						= 49,
		NonActorMagicCaster				= 50,
		NonActorMagicTarget				= 51,
		ExtraMasterFileCell				= 52,
		ExtraPlayerCrimeList			= 53,
		//								  54,
		ExtraEnableStateParent			= 55,
		ExtraEnableStateChildren		= 56,
		ExtraItemDropper				= 57,
		ExtraDroppedItemList			= 58,
		ExtraRandomTeleportMarker		= 59,
		ExtraMerchantContainer			= 60,
		ExtraSavedHavokData				= 61,
		ExtraCannotWear					= 62,
		ExtraPoison						= 63,
		ExtraMagicLight					= 64, // Oblivion leftover, unused
		ExtraLastFinishedSequence		= 65,
		ExtraSavedAnimation				= 66,
		ExtraNorthRotation				= 67,
		ExtraXTarget					= 68,
		ExtraFriendHits					= 69,
		ExtraHeadingTarget				= 70,
		ExtraBoundArmor					= 71, // Oblivion leftover, unused
		ExtraRefractionProperty			= 72,
		ExtraStartingWorldOrCell		= 73,
		ExtraHotkey						= 74,
		ExtraEditorRef3DData			= 75,
		ExtraEditorRefMoveData			= 76,
		ExtraInfoGeneralTopic			= 77,
		ExtraHasNoRumors				= 78,
		ExtraSound						= 79,
		ExtraTerminalState				= 80,
		ExtraLinkedRef					= 81,
		ExtraLinkedRefChildren			= 82,
		ExtraActivateRef				= 83,
		ExtraActivateRefChildren		= 84,
		ExtraTalkingActor				= 85,
		ExtraObjectHealth				= 86,
		ExtraDecalRefs					= 87,
		ExtraCellImageSpace				= 89,
		ExtraNavMeshPortal				= 90,
		ExtraModelSwap					= 91,
		ExtraRadius						= 92,
		ExtraRadiation					= 93,
		ExtraFactionChanges				= 94,
		ExtraDismemberedLimbs			= 95,
		ExtraMultiBound					= 97,
		ExtraMultiBoundData				= 98,
		ExtraMultiBoundRef				= 99,
		ExtraCellEnviroType				= 100, // Oblivion leftover, unused
		ExtraReflectedRefs				= 101,
		ExtraReflectorRefs				= 102,
		ExtraEmittanceSource			= 103,
		ExtraRadioData					= 104,
		ExtraCombatStyle				= 105,
		ExtraPrimitive					= 107,
		ExtraOpenCloseActivateRef		= 108,
		ExtraAnimNoteReceiver			= 109,
		ExtraAmmo						= 110,
		ExtraPatrolRefData				= 111,
		ExtraPackageData				= 112,
		ExtraOcclusionPlane				= 113,
		ExtraCollisionData				= 114,
		ExtraSayTopicInfoOnceADay		= 115,
		ExtraEncounterZone				= 116,
		ExtraSayToTopicInfo				= 117,
		ExtraOcclusionPlaneRefData		= 118,
		ExtraPortalRefData				= 119,
		ExtraPortal						= 120,
		ExtraRoom						= 121,
		ExtraHealthPerc					= 122,
		ExtraRoomRefData				= 123,
		ExtraGuardedRefData				= 124,
		ExtraCreatureAwakeSound			= 125,
		ExtraWaterZoneMap				= 126,
		//								  127,
		ExtraIgnoredBySandbox			= 128,
		ExtraCellAcousticSpace			= 129,
		ExtraReservedMarkers			= 130,
		ExtraWeaponIdleSound			= 131,
		ExtraWaterLightRefs				= 132,
		ExtraLitWaterRefs				= 133,
		ExtraWeaponAttackSound			= 134,
		ExtraActivateLoopSound			= 135,
		ExtraPatrolRefInUseData			= 136,
		ExtraAshPileRef					= 137,
		ExtraCreatureMovementSound		= 138,
		ExtraFollowerSwimBreadcrumbs	= 139,
		ExtraCellImpactSwap				= 140,
		ExtraWeaponModFlags				= 141,
		ExtraModdingItem				= 142,
		ExtraSecuritronFace				= 143,
		ExtraAudioMarker				= 144,
		ExtraAudioBuoyMarker			= 145,
		ExtraSpecialRenderFlags			= 146,
		COUNT,
	};
};
using EXTRA_DATA_TYPE = _ExtraDataType::Type;

#define BSEXTRA_TYPE(data) static constexpr EXTRA_DATA_TYPE _TYPE = EXTRA_DATA_TYPE::data;

#pragma endregion

#pragma region AI

struct _ProcessType {
	enum Type {
		INVALID			= -1,
		HIGH			= 0,
		MIDDLE_HIGH		= 1,
		MIDDLE_LOW		= 2,
		LOW				= 3,
		COUNT,
	};
};
using PROCESS_TYPE = _ProcessType::Type;
using PROCESS_LEVEL = _ProcessType::Type;

struct _Confidence {
	enum Type : uint8_t {
		COWARDLY	= 0,
		CAUTIOUS	= 1,
		AVERAGE		= 2,
		BRAVE		= 3,
		FOOLHARDY	= 4,
		COUNT,
	};
};
using CONFIDENCE = _Confidence::Type;

struct _SitSleepState {
	enum State : uint32_t {
		NORMAL					= 0,
		LOAD_SIT_IDLE			= 1,
		WANT_TO_SIT				= 2,
		WAITING_FOR_SIT_ANIM	= 3,
		SITTING					= 4,
		WANT_TO_STAND			= 5,
		LOADING_SLEEP_IDLE		= 6,
		WANT_TO_SLEEP			= 7,
		WAITING_FOR_SLEEP_ANIM	= 8,
		SLEEPING				= 9,
		WANT_TO_WAKE			= 10,
	};
};
using SIT_SLEEP_STATE = _SitSleepState::State;

struct _LifeState {
	enum State {
		ALIVE			= 0,
		DYING			= 1,
		DEAD			= 2,
		UNCONSCIOUS		= 3,
		REANIMATE		= 4,
		RESTRAINED		= 5,
		ESSENTIAL_DOWN	= 6,
	};
};
using ACTOR_LIFE_STATE = _LifeState::State;

struct _CriticalStage {
	enum Stage {
		NONE				= 0,
		GOO_START			= 1,
		GOO_END				= 2,
		DISINTEGRATE_START	= 3,
		DISINTEGRATE_END	= 4,
		COUNT				= 5,
	};
};
using ACTOR_CRITICAL_STAGE = _CriticalStage::Stage;

struct _FightReaction {
	enum Type : uint32_t {
		NEUTRAL	= 0,
		ENEMY	= 1,
		ALLY	= 2,
		FRIEND	= 3,
		COUNT,
	};
};
using FIGHT_REACTION = _FightReaction::Type;

#pragma endregion

#pragma region Packages

struct _PackageLocationType {
	enum Type {
		NONE				= -1,
		REFERENCE			= 0,
		CELL				= 1,
		CURRENT_LOCATION	= 2,
		EDITOR_LOCATION		= 3,
		OBJECT				= 4,
		TYPE				= 5,
		LINKED_REFERENCE	= 6,
		COUNT,
	};
};
using PACKAGE_LOCATION_TYPE = _PackageLocationType::Type;

struct _PackageTargetType {
	enum Type {
		NONE			= -1,
		REFERENCE		= 0,
		OBJECT			= 1,
		TYPE			= 2,
		LINKEDREF		= 3,
	};
};
using PACKAGE_TARGET_TYPE = _PackageTargetType::Type;

struct _PackageObjectType {
	enum Type {
		NONE = 0,
		ACTIVATOR,
		ARMOR,
		BOOK,
		CLOTHING_OLD,
		CONTAINER,
		DOOR,
		INGREDIENT,
		LIGHT,
		MISC,
		FLORA,
		FURNITURE,
		WEAPON,
		AMMO,
		NPC,
		CREATURE,
		KEY,
		ALCHEMY,
		FOOD,
		CLOTHING,
		WEAR,
		WEAPON_RANGED,
		WEAPON_MELEE,
		WEAPON_NONE,
		SPELL,
		SPELL_RANGED,
		SPELL_TOUCH,
		SPELL_SELF,
		ACTOR,
		COUNT,
	};
};
using PACKAGE_OBJECT_TYPE = _PackageObjectType::Type;

struct _PackageType {
	enum Type {
		NONE						= -1,
		EXPLORE						= 0,
		FOLLOW						= 1,
		ESCORT						= 2,
		EAT							= 3,
		SLEEP						= 4,
		WANDER						= 5,
		TRAVEL						= 6,
		ACCOMPANY					= 7,
		USE_ITEM_AT					= 8,
		AMBUSH						= 9,
		FLEE_NON_COMBAT				= 10,
		CAST_MAGIC					= 11,
		SANDBOX						= 12,
		PATROL						= 13,
		GUARD						= 14,
		DIALOGUE					= 15,
		USE_WEAPON					= 16,
		FIND						= 17,
		COMBAT						= 18,
		COMBAT_LOW					= 19,
		ACTIVATE					= 20,
		ALARM						= 21,
		FLEE						= 22,
		TRESPASS					= 23,
		SPECTATOR					= 24,
		REACT_TO_DEAD				= 25,
		GET_UP						= 26,
		DO_NOTHING					= 27,
		IN_GAME_DIALOGUE			= 28,
		SURFACE						= 29,
		SEARCH_FOR_ATTACKER			= 30,
		AVOID_RADIATION				= 31,
		REACT_TO_DESTROYED_OBJECT	= 32,
		REACT_TO_GRENADE_OR_MINE	= 33,
		STEAL_WARNING				= 34,
		PICKPOCKET_WARNING			= 35,
		MOVEMENT_BLOCKED			= 36,
		SANDMAN						= 37,
		CANNIBAL					= 38,
		BACKUP						= 39,
		COUNT,
	};
};
using PACKAGE_TYPE = _PackageType::Type;

struct _PackageProcedureType {
	enum Type {
		NONE					= -1,
		EXPLORE_TRAVEL			= 0,
		EXPLORE_WANDER			= 1,
		EXPLORE_ACTIVATE		= 2,
		EXPLORE_ACQUIRE			= 3,
		SLEEP					= 4,
		EAT						= 5,
		FOLLOW_WITH_ESCORT		= 6,
		AMBUSH_FOLLOW			= 7,
		ESCORT_ACTOR			= 8,
		ESCORT_OBJECT			= 9,
		DIALOGUE				= 10,
		ALARM					= 11,
		COMBAT					= 12,
		ACTIVATE				= 13,
		GREET					= 14,
		OBSERVE_COMBAT			= 15,
		OBSERVE_DIALOGUE		= 16,
		GREET_DEAD				= 17,
		PURSUE_COMBAT			= 18,
		FLEE					= 19,
		TRESPASS				= 20,
		GET_UP					= 21,
		EXPLORE_NPC				= 22,
		MOUNT					= 23,
		DISMOUNT				= 24,
		DO_NOTHING				= 25,
		EXPLORE_ACQUIRE_GENERIC	= 26,
		ACCOMPANY				= 27,
		USEITEMAT				= 28,
		VAMPIRE_FEED			= 29,
		AMBUSH					= 30,
		SURFACE					= 31,
		FLEE_NON_COMBAT			= 32,
		SEARCH					= 33,
		CLEAR_MOUNT_POSITION	= 34,
		SUMMON_CREATURE_DEFEND	= 35,
		AVOID_RADIATION			= 36,
		SANDBOX					= 37,
		PATROL					= 38,
		BUMP_REACTION			= 39,
		GRENADE_MINE_REACTION	= 40,
		GUARD					= 41,
		STEAL_WARN				= 42,
		PICKPOCKET_WARN			= 43,
		USEWEAPON				= 44,
		FOLLOW_WITHOUT_ESCORT	= 45,
		MOVEMENT_BLOCKED		= 46,
		CANNIBAL				= 47,
		BACKUP					= 48,
		COUNT,
	};
};
using PACKAGE_PROCEDURE_TYPE = _PackageProcedureType::Type;

struct _Procedure {
	enum Type {
		NONE						= -1,
		TRAVEL						= 0,
		WANDER						= 1,
		ACTIVATE					= 2,
		ACQUIRE						= 3,
		SLEEP						= 4,
		EAT							= 5,
		FOLLOW						= 6,
		ESCORT						= 7,
		ALARM						= 8,
		COMBAT						= 9,
		FLEE						= 10,
		YIELD						= 11,
		DIALOGUE					= 12,
		WAIT						= 13,
		TRAVEL_TARGET				= 14,
		PURSUE						= 15,
		GREET						= 16,
		CREATE_FOLLOW				= 17,
		OBSERVE_COMBAT				= 18,
		OBSERVE_DIALOGUE			= 19,
		GREET_DEAD					= 20,
		WARN						= 21,
		GET_UP						= 22,
		MOUNT_HORSE					= 23,
		DISMOUNT_HORSE				= 24,
		DO_NOTHING					= 25,
		NOTIFY						= 26,
		ACCOMPANY					= 27,
		USE_ITEM_AT					= 28,
		FEED						= 29,
		AMBUSH_WAIT					= 30,
		SURFACE						= 31,
		WAIT_FOR_SPELL				= 32,
		CHOOSE_CAST					= 33,
		FLEE_NON_COMBAT				= 34,
		REMOVE_WORN_ITEMS			= 35,
		SEARCH						= 36,
		CLEAR_MOUNT_POSITION		= 37,
		SUMMON_CREATURE_DEFEND		= 38,
		AVOID_RADIATION				= 39,
		UNEQUIP_ARMOR				= 40,
		TAKE_BACK_ITEM				= 41,
		SANDBOX						= 42,
		USE_IDLE_MARKER				= 43,
		PATROL						= 44,
		EXPLOSION_REACTION			= 45,
		GRENADE_MINE_PICKUP_THROW	= 46,
		GUARD						= 47,
		ALERT_SEARCH				= 48,
		DIALOGUE_ACTIVATE			= 49,
		USE_WEAPON					= 50,
		MOVEMENT_BLOCKED			= 51,
		CANNIBAL_FEED				= 52,
		BACK_UP						= 53,
		DONE						= 54,
		COUNT						= 54
	};
};
using PROCEDURE = _Procedure::Type;

#pragma endregion

#pragma region Animations

struct _AnimationAction {
	enum Action {
		NONE = -1,
		EQUIP_WEAPON,
		UNEQUIP_WEAPON,
		ATTACK,
		ATTACK_EJECT,
		ATTACK_FOLLOW_THROUGH,
		ATTACK_THROW,
		ATTACK_THROW_ATTACH,
		BLOCK,
		RECOIL,
		RELOAD,
		STAGGER,
		DODGE,
		LOWER_BODY_ANIM,
		SPECIAL_IDLE,
		SCRIPT_ANIMATION,
		RELOAD_LOOP_START,
		RELOAD_LOOP_END,
		RELOAD_LOOP,
		COUNT,
	};
};
using ANIMATION_ACTION = _AnimationAction::Action;

struct _AnimationState {
	enum State {
		NO_ANIM				= -1,
		NONE				= 0,
		PLAYING				= 1,
		GRABBING			= 2,
		FINISHING_PLAYING	= 3,
	};
};
using ANIMATION_STATE = _AnimationState::State;

struct _AnimGroupMove {
	enum Move : uint16_t {
		NONE	= 0,
		WALK	= 0,
		SNEAK	= 1,
		SWIM	= 2,
		FLY		= 3,
		COUNT,
	};
};
using ANIM_GROUP_MOVE = _AnimGroupMove::Move;

struct _AnimGroupWeapon {
	enum Weapon : uint16_t {
		NONE					= 0,
		HAND_TO_HAND			= 1,
		ONE_HAND_MELEE			= 2,
		TWO_HAND_MELEE			= 3,
		ONE_HAND_PISTOL			= 4,
		TWO_HAND_RIFLE			= 5,
		TWO_HAND_AUTOMATIC		= 6,
		TWO_HAND_HANDLE			= 7,
		TWO_HAND_LAUNCHER		= 8,
		ONE_HAND_GRENADE		= 9,
		ONE_HAND_MINE			= 10,
		ONE_HAND_LUNCHBOX_MINE	= 11,
		COUNT,
	};
};
using ANIM_GROUP_WEAPON = _AnimGroupWeapon::Weapon;

struct _AnimGroup {
	enum Group : uint16_t {
		NONE = 255,
		IDLE = 0,
		DYNAMIC_IDLE,
		SPECIAL_IDLE,

		MOVE_FORWARD,
		MOVE_BACK,
		MOVE_LEFT,
		MOVE_RIGHT,
		FAST_FORWARD,
		FAST_BACK,
		FAST_LEFT,
		FAST_RIGHT,
		DODGE_FORWARD,
		DODGE_BACK,
		DODGE_LEFT,
		DODGE_RIGHT,
		TURN_LEFT,
		TURN_RIGHT,
		
		_MOVEMENT_START = MOVE_FORWARD,
		_MOVEMENT_END = TURN_RIGHT,

		AIM,
		AIM_UP,
		AIM_DOWN,
		AIM_IS,
		AIM_IS_UP,
		AIM_IS_DOWN,

		_AIM_START	= AIM,
		_AIM_END	= AIM_IS_DOWN,

		HOLSTER,
		EQUIP,
		UNEQUIP,
		ATTACK_LEFT,
		ATTACK_LEFT_UP,
		ATTACK_LEFT_DOWN,
		ATTACK_LEFT_IS,
		ATTACK_LEFT_IS_UP,
		ATTACK_LEFT_IS_DOWN,
		ATTACK_RIGHT,
		ATTACK_RIGHT_UP,
		ATTACK_RIGHT_DOWN,
		ATTACK_RIGHT_IS,
		ATTACK_RIGHT_IS_UP,
		ATTACK_RIGHT_IS_DOWN,
		ATTACK_3,
		ATTACK_3_UP,
		ATTACK_3_DOWN,
		ATTACK_3_IS,
		ATTACK_3_IS_UP,
		ATTACK_3_IS_DOWN,
		ATTACK_4,
		ATTACK_4_UP,
		ATTACK_4_DOWN,
		ATTACK_4_IS,
		ATTACK_4_IS_UP,
		ATTACK_4_IS_DOWN,
		ATTACK_5,
		ATTACK_5_UP,
		ATTACK_5_DOWN,
		ATTACK_5_IS,
		ATTACK_5_IS_UP,
		ATTACK_5_IS_DOWN,
		ATTACK_6,
		ATTACK_6_UP,
		ATTACK_6_DOWN,
		ATTACK_6_IS,
		ATTACK_6_IS_UP,
		ATTACK_6_IS_DOWN,
		ATTACK_7,
		ATTACK_7_UP,
		ATTACK_7_DOWN,
		ATTACK_7_IS,
		ATTACK_7_IS_UP,
		ATTACK_7_IS_DOWN,
		ATTACK_8,
		ATTACK_8_UP,
		ATTACK_8_DOWN,
		ATTACK_8_IS,
		ATTACK_8_IS_UP,
		ATTACK_8_IS_DOWN,
		ATTACK_LOOP,
		ATTACK_LOOP_UP,
		ATTACK_LOOP_DOWN,
		ATTACK_LOOP_IS,
		ATTACK_LOOP_IS_UP,
		ATTACK_LOOP_IS_DOWN,
		ATTACK_SPIN,
		ATTACK_SPIN_UP,
		ATTACK_SPIN_DOWN,
		ATTACK_SPIN_IS,
		ATTACK_SPIN_IS_UP,
		ATTACK_SPIN_IS_DOWN,
		ATTACK_SPIN_2,
		ATTACK_SPIN_2_UP,
		ATTACK_SPIN_2_DOWN,
		ATTACK_SPIN_2_IS,
		ATTACK_SPIN_2_IS_UP,
		ATTACK_SPIN_2_IS_DOWN,
		ATTACK_POWER,
		ATTACK_FORWARD_POWER,
		ATTACK_BACK_POWER,
		ATTACK_LEFT_POWER,
		ATTACK_RIGHT_POWER,
		ATTACK_CUSTOM_1_POWER,
		ATTACK_CUSTOM_2_POWER,
		ATTACK_CUSTOM_3_POWER,
		ATTACK_CUSTOM_4_POWER,
		ATTACK_CUSTOM_5_POWER,
		PLACE_MINE,
		PLACE_MINE_UP,
		PLACE_MINE_DOWN,
		PLACE_MINE_IS,
		PLACE_MINE_IS_UP,
		PLACE_MINE_IS_DOWN,
		PLACE_MINE_2,
		PLACE_MINE_2_UP,
		PLACE_MINE_2_DOWN,
		PLACE_MINE_2_IS,
		PLACE_MINE_2_IS_UP,
		PLACE_MINE_2_IS_DOWN,
		ATTACK_THROW,
		ATTACK_THROW_UP,
		ATTACK_THROW_DOWN,
		ATTACK_THROW_IS,
		ATTACK_THROW_IS_UP,
		ATTACK_THROW_IS_DOWN,
		ATTACK_THROW_2,
		ATTACK_THROW_2_UP,
		ATTACK_THROW_2_DOWN,
		ATTACK_THROW_2_IS,
		ATTACK_THROW_2_IS_UP,
		ATTACK_THROW_2_IS_DOWN,
		ATTACK_THROW_3,
		ATTACK_THROW_3_UP,
		ATTACK_THROW_3_DOWN,
		ATTACK_THROW_3_IS,
		ATTACK_THROW_3_IS_UP,
		ATTACK_THROW_3_IS_DOWN,
		ATTACK_THROW_4,
		ATTACK_THROW_4_UP,
		ATTACK_THROW_4_DOWN,
		ATTACK_THROW_4_IS,
		ATTACK_THROW_4_IS_UP,
		ATTACK_THROW_4_IS_DOWN,
		ATTACK_THROW_5,
		ATTACK_THROW_5_UP,
		ATTACK_THROW_5_DOWN,
		ATTACK_THROW_5_IS,
		ATTACK_THROW_5_IS_UP,
		ATTACK_THROW_5_IS_DOWN,
		ATTACK_9,
		ATTACK_9_UP,
		ATTACK_9_DOWN,
		ATTACK_9_IS,
		ATTACK_9_IS_UP,
		ATTACK_9_IS_DOWN,
		ATTACK_THROW_6,
		ATTACK_THROW_6_UP,
		ATTACK_THROW_6_DOWN,
		ATTACK_THROW_6_IS,
		ATTACK_THROW_6_IS_UP,
		ATTACK_THROW_6_IS_DOWN,
		ATTACK_THROW_7,
		ATTACK_THROW_7_UP,
		ATTACK_THROW_7_DOWN,
		ATTACK_THROW_7_IS,
		ATTACK_THROW_7_IS_UP,
		ATTACK_THROW_7_IS_DOWN,
		ATTACK_THROW_8,
		ATTACK_THROW_8_UP,
		ATTACK_THROW_8_DOWN,
		ATTACK_THROW_8_IS,
		ATTACK_THROW_8_IS_UP,
		ATTACK_THROW_8_IS_DOWN,
		COUNTER_ATTACK,

		_WEAPONS_START	= EQUIP,
		_WEAPONS_END	= COUNTER_ATTACK,

		STOMP,
		BLOCK_IDLE,
		BLOCK_HIT,
		RECOIL,

		RELOAD_W_START,
		RELOAD_X_START,
		RELOAD_Y_START,
		RELOAD_Z_START,
		RELOAD_A,
		RELOAD_B,
		RELOAD_C,
		RELOAD_D,
		RELOAD_E,
		RELOAD_F,
		RELOAD_G,
		RELOAD_H,
		RELOAD_I,
		RELOAD_J,
		RELOAD_K,
		RELOAD_L,
		RELOAD_M,
		RELOAD_N,
		RELOAD_O,
		RELOAD_P,
		RELOAD_Q,
		RELOAD_R,
		RELOAD_S,
		RELOAD_W,
		RELOAD_X,
		RELOAD_Y,
		RELOAD_Z,

		_RELOAD_START	= RELOAD_W_START,
		_RELOAD_END		= RELOAD_Z,

		JAM_A,
		JAM_B,
		JAM_C,
		JAM_D,
		JAM_E,
		JAM_F,
		JAM_G,
		JAM_H,
		JAM_I,
		JAM_J,
		JAM_K,
		JAM_L,
		JAM_M,
		JAM_N,
		JAM_O,
		JAM_P,
		JAM_Q,
		JAM_R,
		JAM_S,
		JAM_W,
		JAM_X,
		JAM_Y,
		JAM_Z,

		_WEAPON_JAM_START	= JAM_A,
		_WEAPON_JAM_END		= JAM_Z,

		STAGGER,
		DEATH,
		TALKING,
		PIPBOY,
		
		JUMP_START,
		JUMP_LOOP,
		JUMP_LAND,

		HAND_GRIP_1,
		HAND_GRIP_2,
		HAND_GRIP_3,
		HAND_GRIP_4,
		HAND_GRIP_5,
		HAND_GRIP_6,
		
		JUMP_LOOP_FORWARD,
		JUMP_LOOP_BACKWARD,
		JUMP_LOOP_LEFT,
		JUMP_LOOP_RIGHT,
		
		PIPBOY_CHILD,
		
		JUMP_LAND_FORWARD,
		JUMP_LAND_BACKWARD,
		JUMP_LAND_LEFT,
		JUMP_LAND_RIGHT,

		COUNT,
	};
};
using ANIM_GROUP_TYPE = _AnimGroup::Group;

enum ANIM_GROUP_ACTION {
	AGA_NONE					= -1,

	AGA_START					= 0,
	AGA_STOP					= 1,

	AGA_LOOP_START				= 0,
	AGA_LOOP_STOP				= 1,

	AGA_SPECIAL_IDLE_START		= 0,
	AGA_SPECIAL_IDLE_LOOP_START	= 1,
	AGA_SPECIAL_IDLE_LOOP_STOP	= 2,
	AGA_SPECIAL_IDLE_STOP		= 3,

	AGA_LOOPING_RELOAD_START	= 0,
	AGA_LOOPING_RELOAD_LOOP		= 1,
	AGA_LOOPING_RELOAD_STOP		= 2,

	AGA_ATTACK_START			= 0,
	AGA_ATTACK_HIT				= 1,
	AGA_ATTACK_EJECT			= 2,
	AGA_ATTACK_POWER_STOP		= 2,
	AGA_ATTACK_SWITCH			= 3,
	AGA_ATTACK_STOP				= 4,

	AGA_ATTACK_MINE_START		= 0,
	AGA_ATTACK_MINE_RELEASE		= 1,
	AGA_ATTACK_MINE_ATTACH		= 2,
	AGA_ATTACK_MINE_STOP		= 3,

	AGA_ATTACK_SPIN_START		= 0,
	AGA_ATTACK_SPIN_FIRE		= 1,
	AGA_ATTACK_SPIN_LOOP		= 2,
	AGA_ATTACK_SPIN_STOP		= 3,

	AGA_ATTACK_THROW_START		= 0,
	AGA_ATTACK_THROW_HOLD		= 1,
	AGA_ATTACK_THROW_RELEASE	= 2,
	AGA_ATTACK_THROW_ATTACH		= 3,
	AGA_ATTACK_THROW_STOP		= 4,
	ANIM_GROUP_ACTION_COUNT		= 5,

	AGA_BLOCK_START				= 0,
	AGA_BLOCK_ATTACK			= 1,
	AGA_BLOCK_STOP				= 2,

	AGA_EQUIP_START				= 0,
	AGA_EQUIP_ATTACH			= 1,
	AGA_EQUIP_STOP				= 2,

	AGA_UNEQUIP_START			= 0,
	AGA_UNEQUIP_DETACH			= 1,
	AGA_UNEQUIP_STOP			= 2,

	AGA_CAST_START				= 0,
	AGA_CAST_HIT				= 1,
	AGA_CAST_STOP				= 2,
};

struct _AnimationGroupActionType {
	enum Type : uint32_t {
		START_STOP,
		LOOP,
		SPECIAL_IDLE,
		EQUIP,
		UNEQUIP,
		ATTACK,
		ATTACK_POWER,
		ATTACK_THROW,
		ATTACK_THROW_ATTACH,
		ATTACK_SPIN,
		COUNT
	};
};
using ANIM_GROUP_ACTION_TYPE = _AnimationGroupActionType::Type;

struct _AnimationGroupSection {
	enum Section : int32_t {
		NONE			= -1,
		IDLE			= 0,
		MOVEMENT		= 1,
		LEFT_ARM		= 2,
		TALKING			= 3,
		WEAPON			= 4,
		WEAPON_UP		= 5,
		WEAPON_DOWN		= 6,
		SPECIAL_IDLE	= 7,
		COUNT			= 8,
		WHOLE_BODY		= 20,
		UPPER_BODY		= 21,
		TOTAL_COUNT,
		SKIP_ALL_BUT_SPECIAL_IDLE = 23,
	};
};
using ANIM_GROUP_SECTION = _AnimationGroupSection::Section;

struct _AnimationActionFlags {
	enum Action : uint32_t {
		NORMAL			= 0,
		IMMEDIATE_START = 1,
		IMMEDIATE_LOOP	= 2,
	};
};
using ANIM_ACTION_FLAGS = _AnimationActionFlags::Action;

struct _AnimationIdleState {
	enum State : uint32_t {
		NONE			= 0,
		QUEUED			= 1,
		LOADED			= 2,
		PLAYING			= 3,
		DONE_PLAYING	= 4,
	};
};
using ANIM_IDLE_STATE = _AnimationIdleState::State;

struct _AnimationIdlePlayType {
	enum Type : uint32_t {
		REPLACE			= 0,
		QUEUE			= 1,
		AUTO			= 2,
		AUTO_EXCLUSIVE	= 3,
	};
};
using ANIM_IDLE_PLAY_TYPE = _AnimationIdlePlayType::Type;

struct _AttackAnimation {
	enum Animation {
		DEFAULT				= 255,
		ATTACK_3			= 38,
		ATTACK_4			= 44,
		ATTACK_5			= 50,
		ATTACK_6			= 56,
		ATTACK_7			= 62,
		ATTACK_8			= 68,
		ATTACK_9			= 144,
		ATTACK_LEFT			= 26,
		ATTACK_LOOP			= 74,
		ATTACK_RIGHT		= 32,
		ATTACK_SPIN			= 80,
		ATTACK_SPIN_2		= 86,
		ATTACK_THROW		= 114,
		ATTACK_THROW_2		= 120,
		ATTACK_THROW_3		= 126,
		ATTACK_THROW_4		= 132,
		ATTACK_THROW_5		= 138,
		ATTACK_THROW_6		= 150,
		ATTACK_THROW_7		= 156,
		ATTACK_THROW_8		= 162,
		PLACE_MINE			= 102,
		PLACE_MINE_2		= 108,
		COUNT				= 23,
	};
};
using ATTACK_ANIMATION = _AttackAnimation::Animation;

enum RELOAD_ANIM {
	RELOAD_ANIM_A = 0,
	RELOAD_ANIM_B,
	RELOAD_ANIM_C,
	RELOAD_ANIM_D,
	RELOAD_ANIM_E,
	RELOAD_ANIM_F,
	RELOAD_ANIM_G,
	RELOAD_ANIM_H,
	RELOAD_ANIM_I,
	RELOAD_ANIM_J,
	RELOAD_ANIM_K,
	RELOAD_ANIM_L,
	RELOAD_ANIM_M,
	RELOAD_ANIM_N,
	RELOAD_ANIM_O,
	RELOAD_ANIM_P,
	RELOAD_ANIM_Q,
	RELOAD_ANIM_R,
	RELOAD_ANIM_S,
	RELOAD_ANIM_W,
	RELOAD_ANIM_X,
	RELOAD_ANIM_Y,
	RELOAD_ANIM_Z,
	RELOAD_ANIM_COUNT,
};

#pragma endregion

#pragma region Weapons

struct _WeaponType {
	enum Type {
		HAND_TO_HAND_MELEE		= 0,
		ONE_HAND_MELEE			= 1,
		TWO_HAND_MELEE			= 2,
		ONE_HAND_PISTOL			= 3,
		ONE_HAND_PISTOL_ENERGY	= 4,
		TWO_HAND_RIFLE			= 5,
		TWO_HAND_AUTOMATIC		= 6,
		TWO_HAND_RIFLE_ENERGY	= 7,
		TWO_HAND_HANDLE			= 8,
		TWO_HAND_LAUNCHER		= 9,
		ONE_HAND_GRENADE		= 10,
		ONE_HAND_MINE			= 11,
		ONE_HAND_LUNCHBOX_MINE	= 12,
		ONE_HAND_THROWN			= 13,
		COUNT,
	};
};
using WEAPON_TYPE = _WeaponType::Type;

struct _WeaponSound {
	enum Sound {
		SHOOT_3D = 0,
		SHOOT_2D,
		SHOOT_3D_LOOPING,
		NO_AMMO,
		SWING = NO_AMMO,
		BLOCK,
		IDLE,
		EQUIP,
		UNEQUIP
	};
};
using WEAPON_SOUND = _WeaponSound::Sound;

struct _WeaponRumblePattern {
	enum Pattern {
		CONSTANT = 0,
		SQUARE,
		TRIANGLE,
		SAWTOOTH
	};
};
using WEAPON_RUMBLE_PATTERN = _WeaponRumblePattern::Pattern;

struct _WeaponModEffectType {
	enum Type : uint32_t {
		NONE					= 0,
		INCREASE_WEAPON_DAMAGE	= 1,
		INCREASE_CLIP_SIZE		= 2,
		DECREASE_SPREAD			= 3,
		DECREASE_WEIGHT			= 4,
		AMMO_REGEN_SHOT			= 5,
		AMMO_REGEN_SECONDS		= 6,
		EQUIP_SPEED				= 7,
		FIRE_SPEED				= 8,
		PROJECTILE_SPEED		= 9,
		MAX_HEALTH				= 10,
		SILENCE					= 11,
		SPLIT_BEAM				= 12,
		VATS_BONUS				= 13,
		IRON_SITES				= 14,
		VATS_SPECIAL_ATTACK		= 15,
		COUNT,
	};
};
using WEAPON_MOD_EFFECT_TYPE = _WeaponModEffectType::Type;

#pragma endregion

#pragma region Combat

struct _CombatLowState {
	enum State : uint32_t {
		NONE			= 0,
		ATTACKING		= 1,
		PURSUING		= 2,
		INVESTIGATING	= 3,
		SEARCHING		= 4,
		FLEEING			= 5,
		COUNT			= 6,
	};
};
using COMBAT_LOW_STATE = _CombatLowState::State;

enum COMBAT_VARIABLE : uint32_t {
	TARGET_LOCATION				= 0,
	NEAR_TARGET_LOCATION		= 1,
	COVER_LOCATION				= 2,
	DODGE_LOCATION				= 3,
	FLANK_LOCATION				= 4,
	FALLBACK_LOCATION			= 5,
	ADVANCE_LOCATION			= 6,
	DESTINATION_LOCATION		= 7,
	GUARD_LOCATION				= 8,
	CLUSTER_LOCATION			= 9,
	HIDE_LOCATION				= 10,
	GRENADE_LOCATION			= 11,
	FLEE_LOCATION				= 12,
	LOS_LOCATION				= 13,
	SAFE_LOCATION				= 14,
	INVESTIGATE_LOCATION		= 15,
	COMBAT_AREA_LOCATION		= 16,
	COMBAT_LOCATION_COUNT		= 17,

	COMBAT_ITEM_RESTORE			= 17,
	COMBAT_ITEM_BUFF			= 18,
	COMBAT_ITEM_TARGET_OBJECT	= 19,
	COMBAT_ITEM_AMMO			= 20,
	COMBAT_ITEM_WEAPON			= 21,
	COMBAT_ITEM_END				= 22,
	COMBAT_ITEM_COUNT			= 5,

	COMBAT_ITEM_START			= COMBAT_ITEM_RESTORE,
	COMBAT_ITEM_USABLE_END		= COMBAT_ITEM_TARGET_OBJECT,
	COMBAT_ITEM_USABLE_COUNT	= 2,

	TOTAL_COMBAT_LOCATION_COUNT	= 22,

	SPECIFIED_VARIABLE_START	= 0xFFFF0016,
	ACTIVATE_COMBAT_ITEM		= 0xFFFF0016,
	USE_COMBAT_ITEM				= 0xFFFF0017,
	EQUIPPED_WEAPON_TYPE		= 0xFFFF0018,
	SPECIFIED_VARIABLE_END		= 0xFFFF0019,
	SPECIFIED_VARIABLE_COUNT	= 3,
	COMBAT_VARIABLE_COUNT		= 25,

	ANY_LOCATION				= 0xFFFFFFFF,
	ANY_COMBAT_ITEM				= 0xFFFFFFFF,
	ANY_WEAPON_TYPE				= 0xFFFFFFFF,
	ANY_VALUE					= 0xFFFFFFFF,
};

struct _CombatMoveMode {
	enum Mode : uint32_t {
		WALK		= 0,
		FAST_WALK	= 1,
		SNEAK		= 2,
		RUN			= 3,
		SLOW_RUN	= 4,
		COUNT		= 5,
	};
};
using COMBAT_MOVE_MODE = _CombatMoveMode::Mode;

enum COMBAT_LOCATION_FLAGS : uint32_t {
	COMBAT_LOCATION_USE_EVADE	= 1,
	COMBAT_LOCATION_HARD_RADIUS = 2,
};

struct _CombatWorldState {
	enum State {
		TARGET_DEAD						= 0,
		AT_LOCATION						= 1, // -> COMBAT_LOCATION_TYPE
		NOT_AT_LOCATION					= 2, // -> COMBAT_LOCATION_TYPE
		TARGET_LOST						= 3,
		TARGET_DETECTED					= 4,
		TARGET_360_LOS					= 5,
		TARGET_BLOCKED					= 6,
		TARGET_SPACE_DIFFERENT			= 7,
		EXPLOSIVE_PROJECTILE_BLOCKED	= 8,
		TARGET_FLUSHED					= 9,
		WEAPON_DRAWN					= 10, // -> COMBAT_WEAPON_TYPE
		WEAPON_TYPE_EQUIPPED			= 11, // -> COMBAT_WEAPON_TYPE
		HAS_WEAPON_TYPE					= 12, // -> COMBAT_WEAPON_TYPE
		HAS_COMBAT_ITEM					= 13, // -> COMBAT_LOCATION_TYPE
		THREATENED						= 14,
		WANTS_TO_FLEE					= 15,
		USED_COMBAT_ITEM				= 16,
		HIDING							= 17,
		EXECUTION_FLAGS					= 18, // -> COMBAT_PERMISSIONS
		GROUP_STRATEGY_ASSIGNMENT		= 19,
		COUNT,
	};
};
using COMBAT_WORLD_STATE = _CombatWorldState::State;

enum COMBAT_EXECUTION_FLAGS : uint32_t {
	COMBAT_PERMISSION_USE_COVER				= 0,
	COMBAT_PERMISSION_CAN_USE_COVER			= 1,
	COMBAT_PERMISSION_LOW_COUNT				= 2,

	COMBAT_PERMISSION_AVOID_THREATS			= 8,
	COMBAT_PERMISSION_HIGH_START			= COMBAT_PERMISSION_AVOID_THREATS,
	COMBAT_PERMISSION_HIGH_END				= 9,
	COMBAT_PERMISSION_HIGH_COUNT			= 1,

	COMBAT_EXECUTION_FLAG_GROUP_SEARCHING	= 16,
	COMBAT_EXECUTION_FLAG_CAN_MOVE			= 17,
	COMBAT_EXECUTION_FLAG_CAN_MELEE_TARGET	= 18,
	COMBAT_EXECUTION_FLAG_START				= COMBAT_EXECUTION_FLAG_GROUP_SEARCHING,
	COMBAT_EXECUTION_FLAG_COUNT				= 19,
};

struct _CombatItemType {
	enum Type {
		RESTORE,
		BUFF,
		COUNT,
	};
};
using COMBAT_ITEM_TYPE = _CombatItemType::Type;

struct _LocationTargetType {
	enum Type : uint8_t {
		DESTINATION,
		GUARD,
		CLUSTER,
		COMBAT_AREA,
	};
};
using LOCATION_TARGET_TYPE = _LocationTargetType::Type;

struct _CombatProcedureType {
	enum Type {
		ATTACK_RANGED		= 0,
		ATTACK_MELEE		= 1,
		ATTACK_GRENADE		= 2,
		ATTACK_LOW			= 3,
		EVADE				= 4,
		SWITCH_WEAPON		= 5,
		MOVE				= 6,
		BE_IN_COVER			= 7,
		ACTIVATE_OBJECT		= 8,
		HIDE_FROM_TARGET	= 9,
		SEARCH				= 10,
		USE_COMBAT_ITEM		= 11,
		ENGAGE_TARGET		= 12,
	};
};
using COMBAT_PROCEDURE_TYPE = _CombatProcedureType::Type;

struct _CombatActionType {
	enum Type {
		ATTACK_RANGED_EXPLOSIVE,
		ATTACK_RANGED_EXPLOSIVE_COVER,
		ATTACK_RANGED,
		ATTACK_RANGED_COVER,
		ATTACK_GRENADE,
		ATTACK_GRENADE_FLUSH_TARGET,
		ATTACK_GRENADE_COVER,
		ATTACK_MELEE,
		ATTACK_HAND_TO_HAND,
		MOVE,
		MOVE_SWITCH_TO_MELEE,
		MOVE_ATTACK_RANGED,
		MOVE_ATTACK_EXPLOSIVE,
		MOVE_ATTACK_GRENADE,
		DRAW_WEAPON,
		SWITCH_WEAPON,
		AVOID_THREAT,
		SEARCH,
		INVESTIGATE,
		DODGE,
		IGNORE_BLOCKED_TARGET,
		FLEE,
		ACTIVATE_COMBAT_ITEM,
		USE_COMBAT_ITEM,
		ACQUIRE_LOS,
		HIDE,
		APPROACH_TARGET,
	};
};
using COMBAT_ACTION_TYPE = _CombatActionType::Type;

struct _CombatGroupStrategy {
	enum Type {
		FALLBACK	= 0,
		ADVANCE		= 1,
		FLANK		= 2,
		AMBUSH		= 3,
		COUNT,
	};
};
using COMBAT_GROUP_STRATEGY = _CombatGroupStrategy::Type;

struct _CombatWeaponType {
	enum Type {
		RANGED_EXPLOSIVE	= 0,
		RANGED				= 1,
		MELEE				= 2,
		GRENADE				= 3,
		MINE				= 4,
		THROWN				= 5,
		NONE				= 6,
		INVALID				= 7,

		COUNT = NONE,
	};
};
using COMBAT_WEAPON_TYPE = _CombatWeaponType::Type;

#pragma endregion

#pragma region Sex

// Sex
struct _Sex {
	enum Sex : int32_t {
		NONE	= -1,
		MALE	= 0,
		FEMALE	= 1,
		COUNT
	};
};
using SEX = _Sex::Sex;

#pragma endregion

#pragma region Dialogue

struct _DialogueType {
	enum Type {
		TOPIC			= 0,
		CONVERSATION	= 1,
		COMBAT			= 2,
		PERSUASION		= 3,
		DETECTION		= 4,
		SERVICE			= 5,
		MISCELLANEOUS	= 6,
		RADIO			= 7,
		COUNT,
	};
};
using DIALOGUE_TYPE = _DialogueType::Type;

struct _DialogueSpeaker {
	enum Type : uint32_t {
		TARGET	= 0,
		SELF	= 1,
		EITHER	= 2,
		COUNT,
	};
};
using DIALOGUE_SPEAKER = _DialogueSpeaker::Type;

struct _DialogueEmotion {
	enum Emotion {
		NEUTRAL		= 0,
		ANGER		= 1,
		DISGUST		= 2,
		FEAR		= 3,
		SAD			= 4,
		HAPPY		= 5,
		SURPRISE	= 6,
		PAINED		= 7,
		COUNT
	};
};
using DIALOGUE_EMOTION = _DialogueEmotion::Emotion;

struct _DialogueScriptType {
	enum Type : uint32_t {
		BEGIN = 0,
		END = 1,
		COUNT,
	};
};
using DIALOGUE_SCRIPT_TYPE = _DialogueScriptType::Type;

#pragma endregion

struct _ActorSegmentInView {
	enum Type : uint32_t {
		BOTTOM	= 0,
		MIDDLE	= 1,
		TOP		= 2,
		NONE	= 3,
	};
};
using ACTOR_SEGMENT_IN_VIEW = _ActorSegmentInView::Type;

enum HavokMaterialType {
	BHK_MATERIAL_STONE				= 0,
	BHK_MATERIAL_CLOTH				= 1,
	BHK_MATERIAL_DIRT				= 2,
	BHK_MATERIAL_GLASS				= 3,
	BHK_MATERIAL_GRASS				= 4,
	BHK_MATERIAL_METAL				= 5,
	BHK_MATERIAL_ORGANIC			= 6,
	BHK_MATERIAL_SKIN				= 7,
	BHK_MATERIAL_WATER				= 8,
	BHK_MATERIAL_WOOD				= 9,
	BHK_MATERIAL_HEAVYSTONE			= 10,
	BHK_MATERIAL_HEAVYMETAL			= 11,
	BHK_MATERIAL_HEAVYWOOD			= 12,
	BHK_MATERIAL_CHAIN				= 13,
	BHK_MATERIAL_SNOW				= 14,
	BHK_MATERIAL_ELEVATOR			= 15,
	BHK_MATERIAL_HOLLOWMETAL		= 16,
	BHK_MATERIAL_SHEETMETAL			= 17,
	BHK_MATERIAL_SAND				= 18,
	BHK_MATERIAL_BROKENCONCRETE		= 19,
	BHK_MATERIAL_VEHICLEBODY		= 20,
	BHK_MATERIAL_VEHICLEPARTSOLID	= 21,
	BHK_MATERIAL_VEHICLEPARTHOLLOW	= 22,
	BHK_MATERIAL_BARREL				= 23,
	BHK_MATERIAL_BOTTLE				= 24,
	BHK_MATERIAL_SODACAN			= 25,
	BHK_MATERIAL_PISTOL				= 26,
	BHK_MATERIAL_RIFLE				= 27,
	BHK_MATERIAL_SHOPPINGCART		= 28,
	BHK_MATERIAL_LUNCHBOX			= 29,
	BHK_MATERIAL_BABYRATTLE			= 30,
	BHK_MATERIAL_RUBBERBALL			= 31,
	BHK_MATERIAL_CHAINLINK			= 32,
	BHK_MATERIAL_TILE				= 33,
	BHK_MATERIAL_CARPET				= 34,
	BHK_MATERIAL_TUMBLEWEED			= 35,
	BHK_MATERIAL_MAX,

	BHK_MATERIAL_FLAG_PLATFORM		= 0x20, // FO3 only
	BHK_MATERIAL_FLAG_STAIRS		= 0x40,

	BHK_MATERIAL_MASK				= 0x1F,
	BHK_MATERIAL_MASK_FIXED			= 0x3F,
};

enum SoundMessageType : uint32_t {
	SM_PLAY						= 0x1,
	SM_UNPAUSE					= 0x2,
	SM_PAUSE					= 0x3,
	SM_STOP						= 0x4,
	SM_PLAY_AFTER				= 0x5,
	//							  0x6
	SM_MUTE						= 0x7,
	SM_UNMUTE					= 0x8,
	SM_FADE_OUT_TARGET			= 0x9, // What's the difference?
	SM_FADE_OUT					= 0xA, // What's the difference? Used by Fade Dialogue
	SM_FADE_IN_TARGET			= 0xB, // What's the difference?
	SM_FADE_IN					= 0xC, // What's the difference? Used by Fade Dialogue
	SM_FADE_DIALOGUE			= 0xD,
	SM_VOLUME_CHANGED			= 0xE,
	SM_SET_VOLUME				= 0x10,
	//							  0x11
	//							  0x12
	SM_SET_FREQUENCY			= 0x13,
	SM_SET_FREQUENCY_VARIANCE	= 0x14,
	//							  0x15
	//							  0x16
	//							  0x17
	SM_FADE_OUT_SELECTED		= 0x18,
	SM_FADE_IN_SELECTED			= 0x19,
	SM_STOP_SELECTED			= 0x1A, // Flags stuff in pPauseEntries. Stops/mutes sounds based on given flags. Doesn't apply to music/radio. AUDIOFLAG_UNKBIT22 is muted instead of stopped.
	SM_START_SELECTED			= 0x1B, // Reverts above
	SM_STOP_SUBMERGED_1C		= 0x1C, // Similar to 1A, but checks water submersion flags
	SM_START_SUBMERGED_1D		= 0x1D, // Reverts above
	SM_SET_POS					= 0x1E,
	SM_SET_BEAM_END				= 0x1F,
	//							  0x20
	SM_SET_STATIC_ATTENUATION	= 0x21,
	SM_SET_REVERB_ATTENUATION	= 0x22,
	SM_SET_MINMAX_DISTANCE		= 0x23,
	SM_SET_ATTENUATION_CURVE	= 0x24,
	SM_PRECACHE					= 0x25,
	SM_RELEASE					= 0x26,
	SM_REGISTER_MOVING_SOUND	= 0x27,
	SM_RELEASE_MOVING_SOUNDS	= 0x28,
	SM_STOP_MOVING_SOUNDS		= 0x29, // Filtered, per ref
	SM_RELEASE_SELECTED			= 0x2A, // Filtered
	//							  0x2B
	//							  0x2C
	SM_UNUSED_2D				= 0x2D,
	//							  0x2E
	//							  0x2F
	//							  0x30
	//							  0x31
	//							  0x32
	SM_CACHE					= 0x33,
	SM_STOP_AUDIO_THREAD		= 0x34,
	SM_SUSPEND_AUDIO_THREAD		= 0x35,
	//							  0x36
	SM_UPDATE_UNDERWATER		= 0x37,
	SM_SET_LISTENER_POS			= 0x38,
	SM_UNKNOWN_39				= 0x39, // Calls ProcessDataRequest if STATE_UNK_11 and STATE_UNK_8 (ProcessDataRequest is stubbed)
	SM_SET_COMPLETION_CALLBACK	= 0x3A,
	SM_SET_PLAY_CALLBACK		= 0x3B,
	SM_UNKNOWN_3C				= 0x3C, // if STATE_UNK_8, sets unk15C and AUDIOFLAG_UNKBIT24. Used by radio
	SM_UNKNOWN_3D				= 0x3D, // Undoes above. Unused
	SM_SET_START_END			= 0x3E,
	SM_SEEK_MUSIC				= 0x3F,
	SM_SET_1ST_PERSON_SOUND		= 0x40,
	SM_SET_PRIORITY				= 0x41,
	SM_SET_SPEED				= 0x42,
};

struct _RayCastPathRequestType {
	enum Type : uint32_t {
		START	= 0,
		GOAL	= 1,
		NO_MESH = 2
	};
};
using RAYCAST_PATH_REQUEST_TYPE = _RayCastPathRequestType::Type;

struct _RayCastPathResult {
	enum Result : uint32_t {
		NONE	= 0,
		SUCCESS = 1,
		FAILED	= 2,
	};
};
using RAYCAST_PATH_RESULT = _RayCastPathResult::Result;

#pragma region Archives

struct _ArchiveTypeIndex {
	enum Index : uint32_t {
		MESHES		= 0,
		TEXTURES	= 1,
		MENUS		= 2,
		SOUNDS		= 3,
		VOICES		= 4,
		SHADERS		= 5,
		TREES		= 6,
		FONTS		= 7,
		MISC		= 8,
		COUNT		= 9,
	};
};
using ARCHIVE_TYPE_INDEX = _ArchiveTypeIndex::Index;

struct _ArchiveType {
	enum Type {
		ALL_		= UINT32_MAX,
		ALL			= UINT16_MAX,
		MESHES		= 1u << ARCHIVE_TYPE_INDEX::MESHES,
		TEXTURES	= 1u << ARCHIVE_TYPE_INDEX::TEXTURES,
		MENUS		= 1u << ARCHIVE_TYPE_INDEX::MENUS,
		SOUNDS		= 1u << ARCHIVE_TYPE_INDEX::SOUNDS,
		VOICES		= 1u << ARCHIVE_TYPE_INDEX::VOICES,
		SHADERS		= 1u << ARCHIVE_TYPE_INDEX::SHADERS,
		TREES		= 1u << ARCHIVE_TYPE_INDEX::TREES,
		FONTS		= 1u << ARCHIVE_TYPE_INDEX::FONTS,
		MISC		= 1u << ARCHIVE_TYPE_INDEX::MISC,
		COUNT		= 9,
	};
};
using ARCHIVE_TYPE = _ArchiveType::Type;

#pragma endregion

struct _BodyPartType {
	enum Type : int32_t {
		NONE = -1,
		TORSO,
		HEAD_1,
		HEAD_2,
		LEFT_ARM_1,
		LEFT_ARM_2,
		RIGHT_ARM_1,
		RIGHT_ARM_2,
		LEFT_LEG_1,
		LEFT_LEG_2,
		LEFT_LEG_3,
		RIGHT_LEG_1,
		RIGHT_LEG_2,
		RIGHT_LEG_3,
		BRAIN,
		WEAPON,
		COUNT,
	};
};
using BODY_PART_TYPE = _BodyPartType::Type;
using LIMB_TYPE = _BodyPartType::Type;

struct _DetectionLevel {
	enum Level : uint32_t {
		LOST	= 0,
		UNSEEN	= 1,
		NOTICED	= 2,
		SEEN	= 3,
		COUNT	= 4,
	};
};
using DETECTION_LEVEL = _DetectionLevel::Level;

struct _ActorType {
	enum Type {
		CREATURE	= 0,
		CHARACTER	= 1,
		PLAYER		= 2,
	};
};
using ACTOR_TYPE = _ActorType::Type;

struct _CreatureType {
	enum Type {
		ANIMAL			= 0,
		MUTATED_ANIMAL	= 1,
		MUTATED_INSECT	= 2,
		ABOMINATION		= 3,
		SUPER_MUTANT	= 4,
		FERAL_GHOUL		= 5,
		ROBOT			= 6,
		GIANT			= 7,
		COUNT,
	};
};
using CREATURE_TYPE = _CreatureType::Type;

#pragma region Ammo

struct _AmmoEffectType {
	enum Type : uint32_t {
		DAMAGE				= 0,
		DAMAGE_RESISTANCE	= 1,
		DAMAGE_THRESHOLD	= 2,
		SPREAD				= 3,
		CONDITION			= 4,
		FATIGUE				= 5,
		COUNT
	};
};
using AMMO_EFFECT_TYPE = _AmmoEffectType::Type;

struct _AmmoOperationType {
	enum Type : uint32_t {
		ADD			= 0,
		MULTIPLY	= 1,
		SUBTRACT	= 2,
		COUNT
	};
};
using AMMO_OPERATION_TYPE = _AmmoOperationType::Type;

#pragma endregion

#pragma region Biped

struct _BipedObject {
	enum Object : int32_t {
		NONE		= -1,
		HEAD,
		HAIR,
		UPPER_BODY,
		LEFT_HAND,
		RIGHT_HAND,
		WEAPON,
		PIPBOY,
		BACKPACK,
		NECKLACE,
		HEADBAND,
		HAT,
		EYE_GLASSES,
		NOSE_RING,
		EARRINGS,
		MASK,
		CHOKER,
		MOUTH_OBJECT,
		BODY_ADDON_1,
		BODY_ADDON_2,
		BODY_ADDON_3,
		COUNT
	};
};
using BIPED_OBJECT = _BipedObject::Object;

struct _BipedBone {
	enum Bone : int32_t {
		NONE	= -1,
		HEAD	= 0,
		WEAPON	= 1,
		PIPBOY	= 2,
		SPINE	= 3,
		NECK	= 4,
		COUNT,
	};
};
using BIPED_BONE = _BipedBone::Bone;

#pragma endregion

struct _IOTaskPriority {
	enum Priority {
		CRITICAL		= 0,
		VERY_HIGH		= 1,
		HIGH			= 2,
		MID				= 3,
		LOW				= 4,
		VERY_LOW		= 5,
		COUNT			= 6,
		INVALID			= 7,

		HIGHEST			= CRITICAL,
		LOWEST			= VERY_LOW,
	};
};
using IO_TASK_PRIORITY = _IOTaskPriority::Priority;

#pragma region Culling

struct _BSCullingType {
	enum Type : uint32_t {
		NORMAL						= 0, // Normal culling
		ALL_PASS					= 1, // Everything is visible, but frustum culling still applies
		ALL_FAIL					= 2, // Everything is culled
		IGNORE_MULTIBOUNDS			= 3, // Doesn't cull using multibounds, frustum still applies
		FORCE_MULTIBOUNDS_NO_UPDATE	= 4, // Culls, but doesn't save the result
	};
};
using BS_CULLING_TYPE = _BSCullingType::Type;

struct _BSCullResult {
	enum Result : uint32_t {
		UNTESTED	= 0,
		VISIBLE		= 1,
		CULLED		= 2,
		OCCLUDED	= 3,
	};
};
using BS_CULL_RESULT = _BSCullResult::Result;

#pragma endregion

struct _BSIntersectResult {
	enum Result : uint32_t {
		NONE			= 0,
		PARTIAL			= 1,
		CONTAINS_TARGET = 2
	};
};
using BS_INTERSECT_RESULT = _BSIntersectResult::Result;

struct _PathHandlerResult {
	enum Result : int32_t {
		NONE				= -1,
		OK					= 0,
		CANT_MOVE			= 0,
		CANT_REACH_Z		= 0,
		CANT_USE_DOOR		= 0,
		FELL_OFF_PATH		= 0,
		DONE				= 0,
		DONE_SLEEP_SPECIAL	= 0,
	};
};
using PATH_HANDLER_RESULT = _PathHandlerResult::Result;

struct _RegionDataType {
	enum Type {
		NONE		= 0,
		GENERAL		= 1,
		OBJECTS		= 2,
		WEATHER		= 3,
		MAP			= 4,
		LANDSCAPE	= 5,
		GRASS		= 6,
		SOUND		= 7,
		IMPOSTER	= 8,
		COUNT		= 9,
	};
};
using REGION_DATA_ID = _RegionDataType::Type;

struct _LODMult {
	enum Mult : uint32_t {
		NONE = 0,
		OBJECTS = 1,
		ITEMS = 2,
		ACTORS = 3,
		TREES = 4,
		LANDSCAPE = 5,
		DISTANT_LOD = 6,
		ACTOR_BODY_PART = 7,
		RENDERED_MENU = 8,
		INVISIBLE = 9,
		IMPOSTER = 10,
		COUNT,
	};
};
using LOD_MULT = _LODMult::Mult;

#pragma region Conditions

struct _ConditionRunOn {
	enum RunOn : uint32_t {
		SUBJECT,
		TARGET,
		REFERENCE,
		COMBAT_TARGET,
		LINKED_REFERENCE,
		COUNT,
	};
};
using CONDITION_RUN_ON = _ConditionRunOn::RunOn;

struct _ConditionComparison {
	enum Comparison : uint32_t {
		EQUAL,
		NOT_EQUAL,
		GREATER_THAN,
		GREATER_THAN_OR_EQUAL,
		LESS_THAN,
		LESS_THAN_OR_EQUAL,
		COUNT,
	};
};
using CONDITION_COMPARISON = _ConditionComparison::Comparison;

#pragma endregion

struct _LockLevel {
	enum Level {
		VERY_EASY,
		EASY,
		AVERAGE,
		HARD,
		VERY_HARD,
		IMPOSSIBLE,
		COUNT,
	};
};
using LOCK_LEVEL = _LockLevel::Level;

struct _SoundLevel {
	enum Level {
		LOUD,
		NORMAL,
		SILENT,
		COUNT,
	};
};
using SOUND_LEVEL = _SoundLevel::Level;

struct _CreatureSoundType {
	enum Type {
		LEFT		= 0,
		RIGHT		= 1,
		BACKLEFT	= 2,
		BACKRIGHT	= 3,
		IDLE		= 4,
		AWARE		= 5,
		ATTACK		= 6,
		HIT			= 7,
		DEATH		= 8,
		WEAPON		= 9,
		MOVEMENT	= 10,
		AWAKE		= 11,
		AUX1		= 12,
		AUX2		= 13,
		AUX3		= 14,
		AUX4		= 15,
		AUX5		= 16,
		AUX6		= 17,
		AUX7		= 18,
		AUX8		= 19,
		JUMP		= 20,
		LOOP		= 21,
		COUNT		= 22
	};
};
using CREATURE_SOUND_TYPE = _CreatureSoundType::Type;

#pragma region Script

enum SCRIPT_COMPILER_NAME : uint32_t {
	DEFAULT_COMPILER		= 0,
	SYSTEM_WINDOW_COMPILER	= 1,
	DIALOGUE_COMPILER		= 2,
	COMPILER_NAME_COUNT,
};

struct _ScriptParamType {
	enum Type : uint32_t {
		STRING						= 0x00, // const char*
		INTEGER						= 0x01, // int32_t
		FLOAT						= 0x02, // float
		OBJECT_ID					= 0x03,	// 
		REFERENCE					= 0x04,	// TESObjectREFR
		ACTOR_VALUE					= 0x05,	// ActorValue::Index
		ACTOR						= 0x06,	// Actor
		SPELL_ITEM					= 0x07,	// SpellItem || TESObjectBOOK
		AXIS						= 0x08,	// X Y Z
		CELL						= 0x09,	// TESObjectCELL
		ANIMATION_GROUP				= 0x0A,	// ANIM_GROUP_TYPE
		MAGIC_ITEM					= 0x0B,	// MagicItem
		SOUND						= 0x0C,	// TESSound
		TOPIC						= 0x0D,	// TESTopic
		QUEST						= 0x0E,	// TESQuest
		RACE						= 0x0F,	// TESRace
		CLASS						= 0x10,	// TESClass
		FACTION						= 0x11,	// TESFaction
		SEX							= 0x12,	// SEX
		GLOBAL						= 0x13,	// TESGlobal
		FURNITURE					= 0x14,	// TESFurniture || BGSListForm
		TESOBJECT					= 0x15,	// TESObject
		VARIABLE_NAME				= 0x16,	// 
		QUEST_STAGE					= 0x17,	// 
		MAP_MARKER					= 0x18,	// TESObjectREFR, pMapMarker
		ACTOR_BASE					= 0x19,	// TESActorBase
		CONTAINER					= 0x1A,	// TESObjectREFR, TESObjectREFR::HasContainer
		WORLDSPACE					= 0x1B,	// TESWorldSpace
		CRIME_TYPE					= 0x1C,	// 
		AI_PACKAGE					= 0x1D,	// TESPackage
		COMBAT_STYLE				= 0x1E,	// TESCombatStyle
		MAGIC_EFFECT				= 0x1F,	// EffectSetting
		FORM_TYPE					= 0x20,	// FORM_TYPE
		WEATHER						= 0x21,	// TESWeather
		NPC							= 0x22,	// TESNPC
		OWNER						= 0x23,	// TESNPC || TESFaction
		EFFECT_SHADER				= 0x24,	// TESEffectShader
		FORM_LIST					= 0x25,	// BGSListForm
		MENU_ICON					= 0x26,	// BGSMenuIcon
		PERK						= 0x27,	// BGSPerk
		NOTE						= 0x28,	// BGSNote
		MISCELLANEOUS_STAT			= 0x29,	//
		IMAGESPACE_MODIFIER			= 0x2A,	// TESImageSpaceModifier
		IMAGESPACE					= 0x2B,	// TESImageSpace
		DOUBLE						= 0x2C,	// double
		SCRIPT_VARIABLE				= 0x2D,	// 
		//							= 0x2E, 
		ENCOUNTER_ZONE				= 0x2F,	// BGSEncounterZone
		IDLE_FORM					= 0x30,	// TESIdleForm
		MESSAGE						= 0x31,	// BGSMessage
		INV_OBJ_OR_FORMLIST			= 0x32,	// TESContainer::ContainerCanHoldType || BGSListForm
		KARMA_ALIGNMENT				= 0x33,	// 
		EQUIP_TYPE					= 0x34,	// BGSEquipType::Type
		TESOBJECT_OR_FORMLIST		= 0x35,	// TESObject || BGSListForm
		SOUND_FILE					= 0x36,	// BGSMusicType
		CRITICAL_STAGE				= 0x37,	// ACTOR_CRITICAL_STAGE
		LEVELED_OR_BASE_CHAR		= 0x38,	// TESLevCharacter || TESNPC
		LEVELED_OR_BASE_CREATURE	= 0x39,	// TESLevCreature || TESCreature
		LEVELED_CHAR				= 0x3A,	// TESLevCharacter
		LEVELED_CREATURE			= 0x3B,	// TESLevCreature
		LEVELED_ITEM				= 0x3C,	// TESLevItem
		ANY_FORM					= 0x3D,	// TESForm
		REPUTATION					= 0x3E,	// TESReputation
		CASINO						= 0x3F,	// TESCasino
		CASINO_CHIP					= 0x40,	// TESCasinoChips
		CHALLENGE					= 0x41,	// TESChallenge
		CARAVAN_MONEY				= 0x42,	// TESCaravanMoney
		CARAVAN_CARD				= 0x43,	// TESCaravanCard
		CARAVAN_DECK				= 0x44,	// TESCaravanDeck
		REGION						= 0x45,	// TESRegion
	
		// Custom NVSE types
		STRING_VARIABLE				= 0x01,
		ARRAY						= 0x100,	// only usable with compiler override; StandardCompile() will report unrecognized param type
	};
};
using SCRIPT_PARAMETER_TYPE = _ScriptParamType::Type;

struct _ScriptVarType {
	enum Type : uint8_t {
		FLOAT		= 0,
		REFERENCE	= 0,
		INTEGER		= 1,

		// NVSE, return values only
		STRING,
		ARRAY,
		REF,

		INVALID
	};
};
using SCRIPT_VARIABLE_TYPE = _ScriptVarType::Type;

#pragma endregion

struct _ChunkID {
	enum ID {
		NO_CHUNK = 0x0,
		HEDR_ID = 0x52444548,
		MAST_ID = 0x5453414D,
		DELE_ID = 0x454C4544,
		SCRD_ID = 0x44524353,
		SCRS_ID = 0x53524353,
		NAME_ID = 0x454D414E,
		OBND_ID = 0x444E424F,
		MODL_ID = 0x4C444F4D,
		MODD_ID = 0x44444F4D,
		MOSD_ID = 0x44534F4D,
		MOD2_ID = 0x32444F4D,
		MOD3_ID = 0x33444F4D,
		MOD4_ID = 0x34444F4D,
		MODT_ID = 0x54444F4D,
		MO2T_ID = 0x54324F4D,
		MO3T_ID = 0x54334F4D,
		MO4T_ID = 0x54344F4D,
		MODS_ID = 0x53444F4D,
		MO2S_ID = 0x53324F4D,
		MO3S_ID = 0x53334F4D,
		MO4S_ID = 0x53344F4D,
		MWD1_ID = 0x3144574D,
		MWD2_ID = 0x3244574D,
		MWD3_ID = 0x3344574D,
		MWD4_ID = 0x3444574D,
		MWD5_ID = 0x3544574D,
		MWD6_ID = 0x3644574D,
		MWD7_ID = 0x3744574D,
		MWT1_ID = 0x3154574D,
		MWT2_ID = 0x3254574D,
		MWT3_ID = 0x3354574D,
		MWT4_ID = 0x3454574D,
		MWT5_ID = 0x3554574D,
		MWT6_ID = 0x3654574D,
		MWT7_ID = 0x3754574D,
		KFFZ_ID = 0x5A46464B,
		NIFZ_ID = 0x5A46494E,
		NIFT_ID = 0x5446494E,
		ANAM_ID = 0x4D414E41,
		BNAM_ID = 0x4D414E42,
		CNAM_ID = 0x4D414E43,
		DNAM_ID = 0x4D414E44,
		ENAM_ID = 0x4D414E45,
		FNAM_ID = 0x4D414E46,
		GNAM_ID = 0x4D414E47,
		HNAM_ID = 0x4D414E48,
		INAM_ID = 0x4D414E49,
		JNAM_ID = 0x4D414E4A,
		KNAM_ID = 0x4D414E4B,
		LNAM_ID = 0x4D414E4C,
		MNAM_ID = 0x4D414E4D,
		NNAM_ID = 0x4D414E4E,
		ONAM_ID = 0x4D414E4F,
		PNAM_ID = 0x4D414E50,
		CLNM_ID = 0x4D414E51,
		RNAM_ID = 0x4D414E52,
		SNAM_ID = 0x4D414E53,
		TNAM_ID = 0x4D414E54,
		UNAM_ID = 0x4D414E55,
		VNAM_ID = 0x4D414E56,
		WNAM_ID = 0x4D414E57,
		WNM1_ID = 0x314D4E57,
		WNM2_ID = 0x324D4E57,
		WNM3_ID = 0x334D4E57,
		WNM4_ID = 0x344D4E57,
		WNM5_ID = 0x354D4E57,
		WNM6_ID = 0x364D4E57,
		WNM7_ID = 0x374D4E57,
		WMI1_ID = 0x31494D57,
		WMI2_ID = 0x32494D57,
		WMI3_ID = 0x33494D57,
		XNAM_ID = 0x4D414E58,
		YNAM_ID = 0x4D414E59,
		ZNAM_ID = 0x4D414E5A,
		NAM1_ID = 0x314D414E,
		NAM2_ID = 0x324D414E,
		NAM3_ID = 0x334D414E,
		NAM4_ID = 0x344D414E,
		NAM5_ID = 0x354D414E,
		NAM6_ID = 0x364D414E,
		NAM7_ID = 0x374D414E,
		NAM8_ID = 0x384D414E,
		NAM9_ID = 0x394D414E,
		NAM0_ID = 0x304D414E,
		WMS1_ID = 0x31534D57,
		WMS2_ID = 0x32534D57,
		RCLR_ID = 0x524C4352,
		RPLD_ID = 0x444C5052,
		RPLI_ID = 0x494C5052,
		RDAT_ID = 0x54414452,
		RDOB_ID = 0x424F4452,
		RDOJ_ID = 0x4A4F4452,
		RDOT_ID = 0x544F4452,
		RDWT_ID = 0x54574452,
		RDMP_ID = 0x504D4452,
		RDLN_ID = 0x4E4C4452,
		RDGS_ID = 0x53474452,
		RDMD_ID = 0x444D4452,
		RDMO_ID = 0x4F4D4452,
		RDSD_ID = 0x44534452,
		RDSI_ID = 0x49534452,
		RDSB_ID = 0x42534452,
		RDID_ID = 0x44494452,
		XIDX_ID = 0x58444958,
		XACT_ID = 0x54434158,
		XOWN_ID = 0x4E574F58,
		XGLB_ID = 0x424C4758,
		XRNK_ID = 0x4B4E5258,
		XHLT_ID = 0x544C4858,
		XHLP_ID = 0x504C4858,
		XUSE_ID = 0x45535558,
		XTIM_ID = 0x4D495458,
		XCNT_ID = 0x544E4358,
		XCHG_ID = 0x47484358,
		XSOL_ID = 0x4C4F5358,
		XSCL_ID = 0x4C435358,
		XLOC_ID = 0x434F4C58,
		XTEL_ID = 0x4C455458,
		XMRK_ID = 0x4B524D58,
		MMRK_ID = 0x4B524D4D,
		AMRK_ID = 0x4B524D41,
		XEDL_ID = 0x4C444558,
		XPSL_ID = 0x4C535058,
		XSED_ID = 0x44455358,
		XPCI_ID = 0x49435058,
		XRGD_ID = 0x44475258,
		XRGB_ID = 0x42475258,
		XLOD_ID = 0x444F4C58,
		XESP_ID = 0x50534558,
		XRTM_ID = 0x4D545258,
		XLKR_ID = 0x524B4C58,
		XACR_ID = 0x52434158,
		XAPD_ID = 0x44504158,
		XAPR_ID = 0x52504158,
		XATO_ID = 0x4F544158,
		XMRC_ID = 0x43524D58,
		XHRS_ID = 0x53524858,
		XPSN_ID = 0x4E535058,
		XTRG_ID = 0x47525458,
		XLCM_ID = 0x4D434C58,
		XDCR_ID = 0x52434458,
		XRDS_ID = 0x53445258,
		XRAD_ID = 0x44415258,
		XLMB_ID = 0x424D4C58,
		XMBR_ID = 0x52424D58,
		XMBO_ID = 0x4F424D58,
		XEMI_ID = 0x494D4558,
		XRDO_ID = 0x4F445258,
		XCLC_ID = 0x434C4358,
		XCLL_ID = 0x4C4C4358,
		XCLW_ID = 0x574C4358,
		XCWT_ID = 0x54574358,
		XCLR_ID = 0x524C4358,
		XCLM_ID = 0x4D4C4358,
		XCMT_ID = 0x544D4358,
		XCMO_ID = 0x4F4D4358,
		XCET_ID = 0x54454358,
		XCCM_ID = 0x4D434358,
		XCIM_ID = 0x4D494358,
		XCAS_ID = 0x53414358,
		XPWR_ID = 0x52575058,
		XRFB_ID = 0x42465258,
		XWLT_ID = 0x544C5758,
		XLTW_ID = 0x57544C58,
		XNVP_ID = 0x50564E58,
		XNDP_ID = 0x50444E58,
		XLCR_ID = 0x504C4358,
		XPRM_ID = 0x4D525058,
		XPRD_ID = 0x44525058,
		XPPA_ID = 0x41505058,
		XOCP_ID = 0x50434F58,
		XORD_ID = 0x44524F58,
		XPOD_ID = 0x444F5058,
		XPTL_ID = 0x4C545058,
		XROO_ID = 0x4F4F5258,
		XRMR_ID = 0x524D5258,
		XLRM_ID = 0x4D524C58,
		XMBP_ID = 0x50424D58,
		XTRI_ID = 0x49525458,
		XAMC_ID = 0x434D4158,
		XAMT_ID = 0x544D4158,
		XEZN_ID = 0x4E5A4558,
		XIBS_ID = 0x53424958,
		XWMS_ID = 0x534D5758,
		XSRF_ID = 0x46525358,
		XSRD_ID = 0x44525358,
		ACTN_ID = 0x4E544341,
		STPR_ID = 0x52505453,
		SOUL_ID = 0x4C554F53,
		SLCP_ID = 0x50434C53,
		CIDA_ID = 0x41445443,
		TRDT_ID = 0x54445254,
		TCLT_ID = 0x544C4354,
		TCLF_ID = 0x464C4354,
		TCFU_ID = 0x55464354,
		TDUM_ID = 0x4D554454,
		ESCE_ID = 0x45435345,
		ESCS_ID = 0x53435345,
		ESBS_ID = 0x53425345,
		ESHS_ID = 0x53485345,
		ESAS_ID = 0x53415345,
		WIDX_ID = 0x58444957,
		MODQ_ID = 0x51444F4D,
		DATA_ID = 0x41544144,
		ATDM_ID = 0x4D445441,
		ACBS_ID = 0x53424341,
		ATTR_ID = 0x52545441,
		DESC_ID = 0x43534544,
		INDX_ID = 0x58444E49,
		STRV_ID = 0x56525453,
		INTV_ID = 0x56544E49,
		FLTV_ID = 0x56544C46,
		DODT_ID = 0x54444F44,
		NPAC_ID = 0x4341504E,
		ND3D_ID = 0x4433444E,
		ANIS_ID = 0x53494E41,
		CNTO_ID = 0x4F544E43,
		SPLO_ID = 0x4F4C5053,
		REPL_ID = 0x4C504552,
		BIPL_ID = 0x4C504942,
		LVLO_ID = 0x4F4C564C,
		LVLD_ID = 0x444C564C,
		LVLF_ID = 0x464C564C,
		LVLG_ID = 0x474C564C,
		EFID_ID = 0x44494645,
		EFIT_ID = 0x54494645,
		AVIT_ID = 0x54495641,
		SCIT_ID = 0x54494353,
		SPIT_ID = 0x54495053,
		ENIT_ID = 0x54494E45,
		EITM_ID = 0x4D544945,
		EAMT_ID = 0x544D4145,
		PKID_ID = 0x44494B50,
		PKDT_ID = 0x54444B50,
		PLDT_ID = 0x54444C50,
		PLD2_ID = 0x32444C50,
		PSDT_ID = 0x54445350,
		PTDT_ID = 0x54445450,
		PTD2_ID = 0x32445450,
		PKDD_ID = 0x44444B50,
		PKED_ID = 0x44454B50,
		PKND_ID = 0x444E4B50,
		PKFD_ID = 0x44464B50,
		PKW3_ID = 0x33574B50,
		PKW2_ID = 0x32574B50,
		PUID_ID = 0x44495550,
		PKPT_ID = 0x54504B50,
		PKES_ID = 0x32454B50,
		PKAM_ID = 0x4D414B50,
		POBA_ID = 0x41424F50,
		POEA_ID = 0x41454F50,
		POCA_ID = 0x41434F50,
		BIDX_ID = 0x58444942,
		BPTM_ID = 0x4D545042,
		BPTF_ID = 0x46545042,
		BMDT_ID = 0x54444D42,
		BMCT_ID = 0x54434D42,
		PFIG_ID = 0x47494650,
		PFPC_ID = 0x43504650,
		MVRF_ID = 0x4652564D,
		AGTY_ID = 0x59544741,
		AGFD_ID = 0x44464741,
		AGSC_ID = 0x43534741,
		AGSX_ID = 0x58534741,
		ICON_ID = 0x4E4F4349,
		ICO2_ID = 0x324F4349,
		SCRI_ID = 0x49524353,
		SCHR_ID = 0x52484353,
		SCVR_ID = 0x52564353,
		SCTX_ID = 0x58544353,
		SCDA_ID = 0x41444353,
		SCRO_ID = 0x4F524353,
		SCRV_ID = 0x56524353,
		SLCS_ID = 0x53434C53,
		SLSD_ID = 0x44534C53,
		SLLD_ID = 0x444C4C53,
		SLFD_ID = 0x44464C53,
		SLUD_ID = 0x44554C53,
		VHGT_ID = 0x54474856,
		VNML_ID = 0x4C4D4E56,
		VCLR_ID = 0x524C4356,
		BTXT_ID = 0x54585442,
		ATXT_ID = 0x54585441,
		VTXT_ID = 0x54585456,
		MPCD_ID = 0x4443504D,
		AIDT_ID = 0x54444941,
		PGRP_ID = 0x50524750,
		PGRC_ID = 0x52524750,
		PGRI_ID = 0x49524750,
		PGRL_ID = 0x4C524750,
		PGAG_ID = 0x47414750,
		LVCR_ID = 0x5243564C,
		GMDT_ID = 0x54444D47,
		QSTI_ID = 0x49545351,
		INFC_ID = 0x43464E49,
		INFX_ID = 0x58464E49,
		QSDT_ID = 0x54445351,
		QSTA_ID = 0x41545351,
		QOBJ_ID = 0x4A424F51,
		TPIC_ID = 0x43495054,
		QSTR_ID = 0x52545351,
		WHGT_ID = 0x54474857,
		EDID_ID = 0x44494445,
		FULL_ID = 0x4C4C5546,
		LODH_ID = 0x48444F4C,
		LODV_ID = 0x56444F4C,
		LODS_ID = 0x53444F4C,
		LODT_ID = 0x54444F4C,
		LODC_ID = 0x43444F4C,
		LODN_ID = 0x4E444F4C,
		FGGS_ID = 0x53474746,
		FGGA_ID = 0x41474746,
		FGTS_ID = 0x53544746,
		HCLR_ID = 0x524C4348,
		OFST_ID = 0x5453464F,
		SNDD_ID = 0x44444E53,
		SNDX_ID = 0x58444E53,
		CSCR_ID = 0x52435343,
		CSDT_ID = 0x54445343,
		CSDF_ID = 0x46445343,
		CSDI_ID = 0x49445343,
		CSDC_ID = 0x43445343,
		CSTD_ID = 0x44545343,
		CSAD_ID = 0x44415343,
		CSSD_ID = 0x44535343,
		WLST_ID = 0x54534C57,
		LVSR_ID = 0x5053564C,
		EFSD_ID = 0x44534645,
		IDLC_ID = 0x434C4449,
		IDLA_ID = 0x414C4449,
		IDLF_ID = 0x464C4449,
		IDLT_ID = 0x544C4449,
		IDLB_ID = 0x424C4449,
		IDLN_ID = 0x4E4C4449,
		PROD_ID = 0x444F5250,
		NVER_ID = 0x5245564E,
		NVVX_ID = 0x5856564E,
		NVTR_ID = 0x5254564E,
		NVEX_ID = 0x5845564E,
		NVTX_ID = 0x5854564E,
		NVLX_ID = 0x584C564E,
		NVGD_ID = 0x4447564E,
		NVCA_ID = 0x4143564E,
		NVDP_ID = 0x5044564E,
		DEST_ID = 0x54534544,
		DSTD_ID = 0x44545344,
		DSTF_ID = 0x46545344,
		DMDL_ID = 0x4C444D44,
		DMDT_ID = 0x54444D44,
		DMDS_ID = 0x53444D44,
		TX00_ID = 0x30305854,
		TX01_ID = 0x31305854,
		TX02_ID = 0x32305854,
		TX03_ID = 0x33305854,
		TX04_ID = 0x34305854,
		TX05_ID = 0x35305854,
		TX06_ID = 0x36305854,
		TX07_ID = 0x37305854,
		TX08_ID = 0x38305854,
		TX09_ID = 0x39305854,
		DMTL_ID = 0x4C544D44,
		NVMI_ID = 0x494D564E,
		NVCI_ID = 0x4943564E,
		BPTN_ID = 0x4E545042,
		BPNN_ID = 0x4E4E5042,
		BPNT_ID = 0x544E5042,
		BPNI_ID = 0x494E5042,
		BPND_ID = 0x444E5042,
		ETYP_ID = 0x50595445,
		PRKE_ID = 0x454B5250,
		PRKF_ID = 0x464B5250,
		PRKC_ID = 0x434B5250,
		EPFT_ID = 0x54465045,
		EPFD_ID = 0x44465045,
		EPF2_ID = 0x32465045,
		EPF3_ID = 0x33465045,
		ITXT_ID = 0x54585449,
		ISCR_ID = 0x52435349,
		CRDT_ID = 0x54445243,
		COED_ID = 0x44454F43,
		SIAD_ID = 0x44414900,
		EIAD_ID = 0x444149FF,
		VTCK_ID = 0x4B435456,
		TPLT_ID = 0x544C5054,
		MICO_ID = 0x4F43494D,
		MIC2_ID = 0x3243494D,
		NEXT_ID = 0x5458454E,
		IMPS_ID = 0x53504D49,
		IMPF_ID = 0x46504D49,
		LTMP_ID = 0x504D544C,
		RAFD_ID = 0x44464152,
		RAFB_ID = 0x42464152,
		RAFS_ID = 0x53464152,
		RAFL_ID = 0x4C464152,
		RAFN_ID = 0x4E464152,
		RALH_ID = 0x484C4152,
		RALN_ID = 0x4E4C4152,
		RAGA_ID = 0x41474152,
		RAGN_ID = 0x4E474152,
		RAPS_ID = 0x53504152,
		VATS_ID = 0x53544156,
		VANM_ID = 0x4D4E4156,
		RCID_ID = 0x4C494352,
		RCQY_ID = 0x59514352,
		RCCF_ID = 0x46434352,
		RCOD_ID = 0x444F4352,
		CQES_ID = 0x53455143,
		CARD_ID = 0x44524143,
		BRUS_ID = 0x53555242,
		DAT2_ID = 0x32544144,
		XXXX_ID = 0x58585858,
	};
};
using CHUNK_ID = _ChunkID::ID;

#pragma region Tiles

struct _TileType {
	enum Type {
		NULL_TYPE	= 0x0,
		FIRST_TYPE	= 0x385,
		RECT		= 0x385,
		IMAGE		= 0x386,
		_3D			= 0x388,
		MENU		= 0x389,
		HOTRECT		= 0x38A,
		WINDOW		= 0x38B,
		RADIAL		= 0x38C,
		LAST_TYPE	= 0x38C,
		TEMPLATE	= 0x3E7,
	};
};
using TILE_TYPE = _TileType::Type;

struct _TileTrait {
	enum Trait : int32_t {
		X					= 0xFA1,
		Y,
		VISIBLE,
		CLASS,
		CLIP_WINDOW			= 0xFA6,
		STACKING_TYPE,
		LOCUS,
		ALPHA,
		ID,
		DISABLE_FADE,
		LIST_INDEX,
		DEPTH,
		CLIPS,
		TARGET,
		HEIGHT,
		WIDTH,
		RED,
		GREEN,
		BLUE,
		TILE,
		CHILD_COUNT,
		JUSTIFY,
		ZOOM,
		FONT,
		WRAP_WIDTH,
		WRAP_LIMIT,
		WRAP_LINES,
		PAGE_NUM,
		IS_HTML,
		CROP_OFFSET_Y,
		CROP_Y = CROP_OFFSET_Y,
		CROP_OFFSET_X,
		CROP_X = CROP_OFFSET_X,
		MENU_FADE,
		EXPLORE_FADE,
		MOUSEOVER,
		STRING,
		SHIFT_CLICKED,
		CLICKED				= 0xFC7,
		CLICK_SOUND			= 0xFCB,
		FILE_NAME,
		FILE_WIDTH,
		FILE_HEIGHT,
		REPEAT_VERTICAL,
		REPEAT_HORIZONTAL,
		ANIMATION			= 0xFD2,
		LINE_COUNT			= 0xDD4,
		PAGE_COUNT,
		XDEFAULT,
		X_UP,
		X_DOWN,
		X_LEFT,
		X_RIGHT,
		X_BUTTON_A			= 0xFDD,
		X_BUTTON_B,
		X_BUTTON_X,
		X_BUTTON_Y,
		X_BUTTON_LT,
		X_BUTTON_RT,
		X_BUTTON_LB,
		X_BUTTON_RB,
		X_BUTTON_START		= 0xFE7,
		MOUSEOVER_SOUND,
		DRAGGABLE,
		DRAG_START_X,
		DRAG_START_Y,
		DRAG_OFFSET_X,
		DRAG_OFFSET_Y,
		DRAG_DELTA_X,
		DRAG_DELTA_Y,
		DRAG_X,
		DRAG_Y,
		WHEELABLE,
		WHEEL_MOVED,
		SYSTEM_COLOR,
		BRIGHTNESS,
		LINEGAP				= 0xFF7,
		RESOLUTION_CONVERTER,
		TEX_ATLAS,
		ROTATE_ANGLE,
		ROTATE_AXIS_X,
		ROTATE_AXIS_Y,

		USER0				= 0x1004,
		USER1,
		USER2,
		USER3,
		USER4,
		USER5,
		USER6,
		USER7,
		USER8,
		USER9,
		USER10,
		USER11,
		USER12,
		USER13,
		USER14,
		USER15,
		USER16,

		LAST_TRAIT			= 0x101D,
		
		MENU_LEVEL			= 0x1771,
		DELETE_ON_FADE		= 0x1772,
		MENU_THICKNESS		= 0x1773,
		NO_CLICK_PAST_DONE	= 0x1776,
		MIXED_MENU_DONE		= 0x1777,
		DOES_NOT_STACK		= 0x1778,
		MENU_VISIBLE		= 0x1779,
	};
};
using TILE_TRAIT = _TileTrait::Trait;

struct _TileValueAction {
	enum Type {
		COPY = 0x7D0,
		ADD,
		SUB,
		MUL,
		DIV,
		MIN,
		MAX,
		MOD,
		FLOOR,
		CEIL,
		ABS,
		ROUND,
		GT,
		GTE,
		EQ,
		NEQ,
		LT,
		LTE,
		AND,
		OR,
		NOT,
		ONLY_IF,
		ONLY_IF_NOT,
		REF,
		BEGIN,
		END,
	};
};
using TILE_VALUE_ACTION = _TileValueAction::Type;

#pragma endregion

struct _MemoryContext {
	enum Context : uint32_t {
		STATIC_VARS				= 0,
		EXTERNAL				= 1,
		DEBUG					= 2,
		MEMPOOLS				= 3,
		RENDERER_OVERHEAD		= 4,
		SHADER_OVERHEAD			= 5,
		THREAD_SAFE_STRUCT		= 6,
		EFFECTS					= 7,
		STRINGS					= 8,
		SETTINGS				= 9,
		SYSTEM					= 10,
		AUDIO					= 11,
		FONTS					= 12,
		INTERFACE				= 13,
		LOCAL_MAP				= 14,
		GAMEBRYO				= 15,
		HAVOK					= 16,
		SAVE_LOAD				= 17,
		LOADERS					= 18,
		ARCHIVE_MANAGER			= 19,
		MOVIE_PLAYER			= 20,
		SCRIPT					= 21,
		FILE_TES				= 22,
		FILE_BUFFER				= 23,
		FILE_CACHE				= 24,
		SCENEGRAPH				= 25,
		CELLS					= 26,
		TERRAIN_LAND			= 27,
		TERRAIN_LOD_MANAGER		= 28,
		WATER					= 29,
		TREES_MODELS			= 30,
		TREES_SPEEDTREE			= 31,
		GRIDCELL				= 32,
		SKY						= 33,
		LOD_SYSTEM				= 34,
		LOD_LAND				= 35,
		LOD_OBJECTS				= 36,
		LOD_TREES				= 37,
		SHADERS					= 38,
		IMAGESPACE				= 39,
		HAIR_SHADER				= 40,
		PRECIPITATION			= 41,
		PROCESS_MANAGER			= 42,
		COMBAT_SYSTEM			= 43,
		LOADED_REF_COLLECTION	= 44,
		PATHING					= 45,
		NAVMESH					= 46,
		DATAHANDLER				= 47,
		FORMS					= 48,
		REFERENCES				= 49,
		ACTORS					= 50, // Models, queued models, particles, blood
		ANIMATION				= 51,
		PLAYER					= 52,
		DIALOGUE				= 53,
		INVENTORY				= 54,
		FACEGEN_SYSTEM			= 55,
		FACEGEN_EGM				= 56,
		FACEGEN_EGT				= 57,
		FACEGEN_GEOM			= 58,
		UNKNOWN					= 59,
		UNKNOWN_DIRECTX			= 60,
		DEBUG_A					= 61,
		DEBUG_B					= 62,
		DEBUG_C					= 63,
		DEBUG_D					= 64,
		DEFAULT					= 65,
	};
};
using MEM_CONTEXT = _MemoryContext::Context;