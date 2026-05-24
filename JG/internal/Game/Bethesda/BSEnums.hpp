#pragma once

#pragma region Forms

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
using ANIM_GROUP = _AnimGroup::Group;

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

#pragma endregion

#pragma region Weapons

enum WEAPON_TYPE {
	WEAPON_TYPE_HAND_TO_HAND_MELEE		= 0,
	WEAPON_TYPE_ONE_HAND_MELEE			= 1,
	WEAPON_TYPE_TWO_HAND_MELEE			= 2,
	WEAPON_TYPE_ONE_HAND_PISTOL			= 3,
	WEAPON_TYPE_ONE_HAND_PISTOL_ENERGY	= 4,
	WEAPON_TYPE_TWO_HAND_RIFLE			= 5,
	WEAPON_TYPE_TWO_HAND_AUTOMATIC		= 6,
	WEAPON_TYPE_TWO_HAND_RIFLE_ENERGY	= 7,
	WEAPON_TYPE_TWO_HAND_HANDLE			= 8,
	WEAPON_TYPE_TWO_HAND_LAUNCHER		= 9,
	WEAPON_TYPE_ONE_HAND_GRENADE		= 10,
	WEAPON_TYPE_ONE_HAND_MINE			= 11,
	WEAPON_TYPE_ONE_HAND_LUNCHBOX_MINE	= 12,
	WEAPON_TYPE_ONE_HAND_THROWN			= 13,
	WEAPON_TYPE_COUNT,
};

enum COMBAT_WEAPON_TYPE {
	COMBAT_WEAPON_TYPE_RANGED_EXPLOSIVE = 0,
	COMBAT_WEAPON_TYPE_RANGED			= 1,
	COMBAT_WEAPON_TYPE_MELEE			= 2,
	COMBAT_WEAPON_TYPE_GRENADE			= 3,
	COMBAT_WEAPON_TYPE_MINE				= 4,
	COMBAT_WEAPON_TYPE_THROWN			= 5,
	COMBAT_WEAPON_TYPE_NONE				= 6,
	COMBAT_WEAPON_TYPE_INVALID			= 7,

	COMBAT_WEAPON_TYPE_COUNT = COMBAT_WEAPON_TYPE_NONE,
};

enum WEAPON_SOUND {
	WEAPON_SOUND_SHOOT_3D = 0,
	WEAPON_SOUND_SHOOT_2D,
	WEAPON_SOUND_SHOOT_3D_LOOPING,
	WEAPON_SOUND_NO_AMMO,
	WEAPON_SOUND_SWING = WEAPON_SOUND_NO_AMMO,
	WEAPON_SOUND_BLOCK,
	WEAPON_SOUND_IDLE,
	WEAPON_SOUND_EQUIP,
	WEAPON_SOUND_UNEQUIP
};

enum ATTACK_ANIMATION {
	ATTACK_ANIMATION_DEFAULT		= 255,
	ATTACK_ANIMATION_ATTACK_3		= 38,
	ATTACK_ANIMATION_ATTACK_4		= 44,
	ATTACK_ANIMATION_ATTACK_5		= 50,
	ATTACK_ANIMATION_ATTACK_6		= 56,
	ATTACK_ANIMATION_ATTACK_7		= 62,
	ATTACK_ANIMATION_ATTACK_8		= 68,
	ATTACK_ANIMATION_ATTACK_9		= 144,
	ATTACK_ANIMATION_ATTACK_LEFT	= 26,
	ATTACK_ANIMATION_ATTACK_LOOP	= 74,
	ATTACK_ANIMATION_ATTACK_RIGHT	= 32,
	ATTACK_ANIMATION_ATTACK_SPIN	= 80,
	ATTACK_ANIMATION_ATTACK_SPIN_2	= 86,
	ATTACK_ANIMATION_ATTACK_THROW	= 114,
	ATTACK_ANIMATION_ATTACK_THROW_2 = 120,
	ATTACK_ANIMATION_ATTACK_THROW_3 = 126,
	ATTACK_ANIMATION_ATTACK_THROW_4 = 132,
	ATTACK_ANIMATION_ATTACK_THROW_5 = 138,
	ATTACK_ANIMATION_ATTACK_THROW_6 = 150,
	ATTACK_ANIMATION_ATTACK_THROW_7 = 156,
	ATTACK_ANIMATION_ATTACK_THROW_8 = 162,
	ATTACK_ANIMATION_PLACE_MINE		= 102,
	ATTACK_ANIMATION_PLACE_MINE_2	= 108,
	ATTACK_ANIMATION_COUNT			= 23,
};

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
static_assert(RELOAD_ANIM_COUNT == 23);

enum WEAPON_RUMBLE_PATTERN {
	WEAPON_RUMBLE_PATTERN_CONSTANT = 0,
	WEAPON_RUMBLE_PATTERN_SQUARE,
	WEAPON_RUMBLE_PATTERN_TRIANGLE,
	WEAPON_RUMBLE_PATTERN_SAWTOOTH
};

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

enum COMBAT_ITEM_TYPE {
	COMBAT_ITEM_TYPE_RESTORE	= 0,
	COMBAT_ITEM_TYPE_BUFF		= 1,
	COMBAT_ITEM_TYPE_COUNT,
};

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

struct _FactionRelation {
	enum Type : uint32_t {
		ENEMY	= 0,
		NEUTRAL	= 1,
		ALLY	= 2,
		FRIEND	= 3,
	};
};
using FACTION_RELATION = _FactionRelation::Type;

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

enum SCRIPT_COMPILER_NAME : uint32_t {
	DEFAULT_COMPILER		= 0,
	SYSTEM_WINDOW_COMPILER	= 1,
	DIALOGUE_COMPILER		= 2,
	COMPILER_NAME_COUNT,
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
		GIANT			= 7
	};
};
using CREATURE_TYPE = _CreatureType::Type;

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

struct _BSIntersectResult {
	enum Result : uint32_t {
		NONE			= 0,
		PARTIAL			= 1,
		CONTAINS_TARGET = 2
	};
};
using BS_INTERSECT_RESULT = _BSIntersectResult::Result;