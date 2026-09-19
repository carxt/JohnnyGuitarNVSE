#pragma once

#include "Utilities.h"
#include "GameTypes.h"
#include "internal/netimmerse.h"
#include "internal/havok.h"

// Form components
#include "Bethesda/BGSAmmoForm.hpp"
#include "Bethesda/BGSBipedModelList.hpp"
#include "Bethesda/BGSBodyPart.hpp"
#include "Bethesda/BGSClipRoundsForm.hpp"
#include "Bethesda/BGSDestructibleObjectForm.hpp"
#include "Bethesda/BGSEquipType.hpp"
#include "Bethesda/BGSIdleCollection.hpp"
#include "Bethesda/BGSPickupPutdownSounds.hpp"
#include "Bethesda/BGSPreloadable.hpp"
#include "Bethesda/BGSRepairItemList.hpp"
#include "Bethesda/BGSTextureModel.hpp"
#include "Bethesda/BGSTouchSpellForm.hpp"
#include "Bethesda/TESActorBaseData.hpp"
#include "Bethesda/TESAIForm.hpp"
#include "Bethesda/TESAnimation.hpp"
#include "Bethesda/TESAttackDamageForm.hpp"
#include "Bethesda/TESAttributes.hpp"
#include "Bethesda/TESBipedModelForm.hpp"
#include "Bethesda/TESContainer.hpp"
#include "Bethesda/TESDescription.hpp"
#include "Bethesda/TESEnchantableForm.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/TESHealthForm.hpp"
#include "Bethesda/TESIcon.hpp"
#include "Bethesda/TESImageSpaceModifiableForm.hpp"
#include "Bethesda/TESLeveledList.hpp"
#include "Bethesda/TESModelAnim.hpp"
#include "Bethesda/TESModelList.hpp"
#include "Bethesda/TESModelRDT.hpp"
#include "Bethesda/TESModelTextureSwap.hpp"
#include "Bethesda/TESRaceForm.hpp"
#include "Bethesda/TESReactionForm.hpp"
#include "Bethesda/TESScriptableForm.hpp"
#include "Bethesda/TESSoundFile.hpp"
#include "Bethesda/TESSpellList.hpp"
#include "Bethesda/TESTexture1024.hpp"
#include "Bethesda/TESValueForm.hpp"
#include "Bethesda/TESWeightForm.hpp"

// Other form components, that are not BaseFormComponent
#include "Bethesda/ActorValueOwner.hpp"
#include "Bethesda/BGSOpenCloseForm.hpp"
#include "Bethesda/BGSPerkEntry.hpp"
#include "Bethesda/BGSQuestObjective.hpp"
#include "Bethesda/CachedValuesOwner.hpp"
#include "Bethesda/ImpactSwap.hpp"
#include "Bethesda/MagicItem.hpp"
#include "Bethesda/TESCondition.hpp"
#include "Bethesda/TESPatrolPackageData.hpp"
#include "Bethesda/TESRegionDataGrass.hpp"
#include "Bethesda/TESRegionDataLandscape.hpp"
#include "Bethesda/TESRegionDataMap.hpp"
#include "Bethesda/TESRegionDataSound.hpp"
#include "Bethesda/TESRegionDataWeather.hpp"
#include "Bethesda/TESRegionList.hpp"
#include "Obsidian/TESRegionDataImposter.hpp"

// Forms themselves
#include "Bethesda/ActorValueInfo.hpp"
#include "Bethesda/AlchemyItem.hpp"
#include "Bethesda/BGSAcousticSpace.hpp"
#include "Bethesda/BGSAddonNode.hpp"
#include "Bethesda/BGSBodyPartData.hpp"
#include "Bethesda/BGSCameraPath.hpp"
#include "Bethesda/BGSCameraShot.hpp"
#include "Bethesda/BGSDebris.hpp"
#include "Bethesda/BGSDefaultObjectManager.hpp"
#include "Bethesda/BGSEncounterZone.hpp"
#include "Bethesda/BGSExplosion.hpp"
#include "Bethesda/BGSHeadPart.hpp"
#include "Bethesda/BGSIdleMarker.hpp"
#include "Bethesda/BGSImpactData.hpp"
#include "Bethesda/BGSImpactDataSet.hpp"
#include "Bethesda/BGSLightingTemplate.hpp"
#include "Bethesda/BGSListForm.hpp"
#include "Bethesda/BGSMenuIcon.hpp"
#include "Bethesda/BGSMessage.hpp"
#include "Bethesda/BGSMovableStatic.hpp"
#include "Bethesda/BGSMusicType.hpp"
#include "Bethesda/BGSNote.hpp"
#include "Bethesda/BGSPerk.hpp"
#include "Bethesda/BGSPlaceableWater.hpp"
#include "Bethesda/BGSProjectile.hpp"
#include "Bethesda/BGSRadiationStage.hpp"
#include "Bethesda/BGSRagdoll.hpp"
#include "Bethesda/BGSStaticCollection.hpp"
#include "Bethesda/BGSTalkingActivator.hpp"
#include "Bethesda/BGSTerminal.hpp"
#include "Bethesda/BGSTextureSet.hpp"
#include "Bethesda/BGSVoiceType.hpp"
#include "Bethesda/EffectSetting.hpp"
#include "Bethesda/EnchantmentItem.hpp"
#include "Bethesda/MagicItemForm.hpp"
#include "Bethesda/Script.hpp"
#include "Bethesda/SpellItem.hpp"
#include "Bethesda/TESAmmo.hpp"
#include "Bethesda/TESClass.hpp"
#include "Bethesda/TESClimate.hpp"
#include "Bethesda/TESCombatStyle.hpp"
#include "Bethesda/TESCreature.hpp"
#include "Bethesda/TESEffectShader.hpp"
#include "Bethesda/TESEyes.hpp"
#include "Bethesda/TESFaction.hpp"
#include "Bethesda/TESFurniture.hpp"
#include "Bethesda/TESGlobal.hpp"
#include "Bethesda/TESGrass.hpp"
#include "Bethesda/TESHair.hpp"
#include "Bethesda/TESIdleForm.hpp"
#include "Bethesda/TESImageSpace.hpp"
#include "Bethesda/TESKey.hpp"
#include "Bethesda/TESLandTexture.hpp"
#include "Bethesda/TESLevCharacter.hpp"
#include "Bethesda/TESLevCreature.hpp"
#include "Bethesda/TESLevItem.hpp"
#include "Bethesda/TESLoadScreen.hpp"
#include "Bethesda/TESNPC.hpp"
#include "Bethesda/TESObjectACTI.hpp"
#include "Bethesda/TESObjectANIO.hpp"
#include "Bethesda/TESObjectARMA.hpp"
#include "Bethesda/TESObjectBOOK.hpp"
#include "Bethesda/TESObjectCELL.hpp"
#include "Bethesda/TESObjectCONT.hpp"
#include "Bethesda/TESObjectDOOR.hpp"
#include "Bethesda/TESObjectLAND.hpp"
#include "Bethesda/TESObjectLIGH.hpp"
#include "Bethesda/TESObjectMISC.hpp"
#include "Bethesda/TESObjectSTAT.hpp"
#include "Bethesda/TESPackage.hpp"
#include "Bethesda/TESQuest.hpp"
#include "Bethesda/TESRace.hpp"
#include "Bethesda/TESRegion.hpp"
#include "Bethesda/TESSkill.hpp"
#include "Bethesda/TESSound.hpp"
#include "Bethesda/TESTopic.hpp"
#include "Bethesda/TESTopicInfo.hpp"
#include "Bethesda/TESWaterForm.hpp"
#include "Bethesda/TESWeather.hpp"
#include "Bethesda/TESWorldSpace.hpp"
#include "Obsidian/BGSDehydrationStage.hpp"
#include "Obsidian/BGSHungerStage.hpp"
#include "Obsidian/BGSSleepDeprevationStage.hpp"
#include "Obsidian/MediaLocationController.hpp"
#include "Obsidian/MediaSet.hpp"
#include "Obsidian/TESAmmoEffect.hpp"
#include "Obsidian/TESCaravanCard.hpp"
#include "Obsidian/TESCaravanDeck.hpp"
#include "Obsidian/TESCaravanMoney.hpp"
#include "Obsidian/TESCasino.hpp"
#include "Obsidian/TESCasinoChips.hpp"
#include "Obsidian/TESChallenge.hpp"
#include "Obsidian/TESLoadScreenType.hpp"
#include "Obsidian/TESObjectIMOD.hpp"
#include "Obsidian/TESRecipe.hpp"
#include "Obsidian/TESRecipeCategory.hpp"
#include "Obsidian/TESReputation.hpp"

class PathingLocation;
class PathingCoverLocation;
struct UnreachableLocation;
struct UnreachableCoverLocation;
class CombatProcedure;
class CombatAction;
class CombatGoal;
class TESModelTextureSwap;
class TESRegion;
class BGSSaveFormBuffer;
class BGSLoadGameBuffer;

enum ObjectVtbl {
	kVtbl_BGSTextureSet = 0x1033D1C,
	kVtbl_BGSMenuIcon = 0x1033654,
	kVtbl_TESGlobal = 0x1036524,
	kVtbl_TESClass = 0x1048BB4,
	kVtbl_TESFaction = 0x10498DC,
	kVtbl_BGSHeadPart = 0x10464B4,
	kVtbl_TESHair = 0x1049B9C,
	kVtbl_TESEyes = 0x104973C,
	kVtbl_TESRace = 0x104B4BC,
	kVtbl_TESSound = 0x1044FFC,
	kVtbl_BGSAcousticSpace = 0x10320FC,
	kVtbl_TESSkill = 0x104CC0C,
	kVtbl_EffectSetting = 0x1012834,
	kVtbl_Script = 0x1037094,
	kVtbl_TESLandTexture = 0x102E6C4,
	kVtbl_EnchantmentItem = 0x1012EA4,
	kVtbl_SpellItem = 0x1013F8C,
	kVtbl_TESObjectACTI = 0x1029D5C,
	kVtbl_BGSTalkingActivator = 0x1025594,
	kVtbl_BGSTerminal = 0x1025914,
	kVtbl_TESObjectARMO = 0x102A62C,
	kVtbl_TESObjectBOOK = 0x102A9C4,
	kVtbl_TESObjectCLOT = 0x102AC0C,
	kVtbl_TESObjectCONT = 0x102AEB4,
	kVtbl_TESObjectDOOR = 0x102B1FC,
	kVtbl_IngredientItem = 0x1013284,
	kVtbl_TESObjectLIGH = 0x1028EE4,
	kVtbl_TESObjectMISC = 0x102B844,
	kVtbl_TESObjectSTAT = 0x102BA2C,
	kVtbl_BGSStaticCollection = 0x102535C,
	kVtbl_BGSMovableStatic = 0x1024E84,
	kVtbl_BGSPlaceableWater = 0x1024F4C,
	kVtbl_TESGrass = 0x102814C,
	kVtbl_TESObjectTREE = 0x102BC94,
	kVtbl_TESFlora = 0x1026BD0,
	kVtbl_TESFurniture = 0x1026D0C,
	kVtbl_TESObjectWEAP = 0x102C51C,
	kVtbl_TESAmmo = 0x1026064,
	kVtbl_TESNPC = 0x104A2F4,
	kVtbl_TESCreature = 0x1048F5C,
	kVtbl_TESLevCreature = 0x102886C,
	kVtbl_TESLevCharacter = 0x102864C,
	kVtbl_TESKey = 0x1028444,
	kVtbl_AlchemyItem = 0x1011964,
	kVtbl_BGSIdleMarker = 0x104664C,
	kVtbl_BGSNote = 0x1046874,
	kVtbl_BGSConstructibleObject = 0x10245A4,
	kVtbl_BGSProjectile = 0x10251AC,
	kVtbl_TESLevItem = 0x1028A64,
	kVtbl_TESWeather = 0x103168C,
	kVtbl_TESClimate = 0x102D5C4,
	kVtbl_TESRegion = 0x102397C,
	kVtbl_NavMeshInfoMap = 0x106BB8C,
	kVtbl_TESObjectCELL = 0x102E9B4,
	kVtbl_TESObjectREFR = 0x102F55C,
	kVtbl_Character = 0x1086A6C,
	kVtbl_Creature = 0x10870AC,
	kVtbl_MissileProjectile = 0x108FA44,
	kVtbl_GrenadeProjectile = 0x108F674,
	kVtbl_BeamProjectile = 0x108C3C4,
	kVtbl_FlameProjectile = 0x108F2F4,
	kVtbl_Explosion = 0x108EE04,
	kVtbl_TESWorldSpace = 0x103195C,
	kVtbl_TESObjectLAND = 0x102DCD4,
	kVtbl_NavMesh = 0x106A0B4,
	kVtbl_TESTopic = 0x104D19C,
	kVtbl_TESTopicInfo = 0x104D5B4,
	kVtbl_TESQuest = 0x104AC44,
	kVtbl_TESIdleForm = 0x1049D0C,
	kVtbl_TESPackage = 0x106847C,
	kVtbl_TESCombatStyle = 0x10266E4,
	kVtbl_TESLoadScreen = 0x10366CC,
	kVtbl_TESLevSpell = 0x1028C5C,
	kVtbl_TESObjectANIO = 0x102A0A4,
	kVtbl_TESWaterForm = 0x103140C,
	kVtbl_TESEffectShader = 0x102685C,
	kVtbl_BGSExplosion = 0x1024A94,
	kVtbl_BGSDebris = 0x1024834,
	kVtbl_TESImageSpace = 0x102D7F4,
	kVtbl_TESImageSpaceModifier = 0x102D97C,
	kVtbl_BGSListForm = 0x10334B4,
	kVtbl_BGSPerk = 0x1046EC4,
	kVtbl_BGSBodyPartData = 0x1045504,
	kVtbl_BGSAddonNode = 0x1024214,
	kVtbl_ActorValueInfo = 0x1067A2C,
	kVtbl_BGSRadiationStage = 0x1033B34,
	kVtbl_BGSCameraShot = 0x10327F4,
	kVtbl_BGSCameraPath = 0x103245C,
	kVtbl_BGSVoiceType = 0x104733C,
	kVtbl_BGSImpactData = 0x1032F6C,
	kVtbl_BGSImpactDataSet = 0x103323C,
	kVtbl_TESObjectARMA = 0x102A31C,
	kVtbl_BGSEncounterZone = 0x102CBBC,
	kVtbl_BGSMessage = 0x10337C4,
	kVtbl_BGSRagdoll = 0x10470EC,
	kVtbl_BGSLightingTemplate = 0x102CD94,
	kVtbl_BGSMusicType = 0x103397C,
	kVtbl_TESObjectIMOD = 0x102B5AC,
	kVtbl_TESReputation = 0x104BA24,
	kVtbl_ContinuousBeamProjectile = 0x108EA64,
	kVtbl_TESRecipe = 0x1036B2C,
	kVtbl_TESRecipeCategory = 0x10369DC,
	kVtbl_TESCasinoChips = 0x10263DC,
	kVtbl_TESCasino = 0x1026574,
	kVtbl_TESLoadScreenType = 0x1036854,
	kVtbl_MediaSet = 0x10342EC,
	kVtbl_MediaLocationController = 0x10340C4,
	kVtbl_TESChallenge = 0x104891C,
	kVtbl_TESAmmoEffect = 0x103449C,
	kVtbl_TESCaravanCard = 0x103478C,
	kVtbl_TESCaravanMoney = 0x10349B4,
	kVtbl_TESCaravanDeck = 0x1034B4C,
	kVtbl_BGSDehydrationStage = 0x101144C,
	kVtbl_BGSHungerStage = 0x10115B4,
	kVtbl_BGSSleepDeprevationStage = 0x10116FC,
	kVtbl_PlayerCharacter = 0x108AA3C,

	kVtbl_BGSQuestObjective = 0x1047088,
	kVtbl_TESModelTextureSwap = 0x101D124,
	kVtbl_BGSPrimitiveBox = 0x101E8C4,
	kVtbl_BGSPrimitiveSphere = 0x101EA64,
	kVtbl_BGSPrimitivePlane = 0x101E75C,
	kVtbl_MagicShaderHitEffect = 0x107B70C,

	kVtbl_BGSQuestPerkEntry = 0x1046B84,
	kVtbl_BGSAbilityPerkEntry = 0x1046C44,
	kVtbl_BGSEntryPointPerkEntry = 0x1046D0C,
	kVtbl_BGSEntryPointFunctionDataOneValue = 0x10462C0,
	kVtbl_BGSEntryPointFunctionDataTwoValue = 0x1046300,
	kVtbl_BGSEntryPointFunctionDataLeveledList = 0x1046320,
	kVtbl_BGSEntryPointFunctionDataActivateChoice = 0x1046340,

	kVtbl_ExtraSeenData = 0x1014294,
	kVtbl_ExtraSpecialRenderFlags = 0x1014458,
	kVtbl_ExtraPrimitive = 0x10151B4,
	kVtbl_ExtraLinkedRef = 0x1015CC0,
	kVtbl_ExtraRadius = 0x1015208,
	kVtbl_ExtraCellWaterType = 0x1014270,
	kVtbl_ExtraCellImageSpace = 0x1014258,
	kVtbl_ExtraCellMusicType = 0x1014234,
	kVtbl_ExtraCellClimate = 0x101424C,
	kVtbl_ExtraTerminalState = 0x1015190,
	kVtbl_ExtraCellAcousticSpace = 0x1014240,
	kVtbl_ExtraOriginalReference = 0x1015BC4,
	kVtbl_ExtraContainerChanges = 0x1015BB8,
	kVtbl_ExtraWorn = 0x1015BDC,
	kVtbl_ExtraHealth = 0x10158E4,
	kVtbl_ExtraLock = 0x101589C,
	kVtbl_ExtraCount = 0x10158D8,
	kVtbl_ExtraTeleport = 0x10158A8,
	kVtbl_ExtraWeaponModFlags = 0x10159A4,
	kVtbl_ExtraHotkey = 0x101592C,
	kVtbl_ExtraCannotWear = 0x1015BF4,
	kVtbl_ExtraOwnership = 0x10158B4,
	kVtbl_ExtraRank = 0x10158CC,
	kVtbl_ExtraAction = 0x1015BAC,
	kVtbl_ExtraFactionChanges = 0x1015F30,
	kVtbl_ExtraScript = 0x1015914,
	kVtbl_ExtraObjectHealth = 0x1015184,

	kVtbl_SeenData = 0x1083FC4,
	kVtbl_IntSeenData = 0x1083FE4,

	kVtbl_TileMenu = 0x106ED44,

	kVtbl_MessageMenu = 0x107566C,
	kVtbl_InventoryMenu = 0x10739B4,
	kVtbl_StatsMenu = 0x106FFD4,
	kVtbl_HUDMainMenu = 0x1072DF4,
	kVtbl_LoadingMenu = 0x1073EBC,
	kVtbl_ContainerMenu = 0x10721AC,
	kVtbl_DialogMenu = 0x107257C,
	kVtbl_SleepWaitMenu = 0x10763AC,
	kVtbl_StartMenu = 0x1076D1C,
	kVtbl_LockpickMenu = 0x107439C,
	kVtbl_QuantityMenu = 0x10701C4,
	kVtbl_MapMenu = 0x1074D44,
	kVtbl_LevelUpMenu = 0x1073CDC,
	kVtbl_RepairMenu = 0x1075C5C,
	kVtbl_RaceSexMenu = 0x1075974,
	kVtbl_CharGenMenu = 0x1071BB4,
	kVtbl_TextEditMenu = 0x1070034,
	kVtbl_BarterMenu = 0x10706EC,
	kVtbl_SurgeryMenu = 0x1070084,
	kVtbl_HackingMenu = 0x10728F4,
	kVtbl_VATSMenu = 0x10700D4,
	kVtbl_ComputersMenu = 0x1072004,
	kVtbl_RepairServicesMenu = 0x1075DB4,
	kVtbl_TutorialMenu = 0x106FF84,
	kVtbl_SpecialBookMenu = 0x1070124,
	kVtbl_ItemModMenu = 0x1073B7C,
	kVtbl_LoveTesterMenu = 0x1070174,
	kVtbl_CompanionWheelMenu = 0x1071D0C,
	kVtbl_TraitSelectMenu = 0x1077ABC,
	kVtbl_RecipeMenu = 0x107048C,
	kVtbl_SlotMachineMenu = 0x10764DC,
	kVtbl_BlackjackMenu = 0x10708FC,
	kVtbl_RouletteMenu = 0x1075F7C,
	kVtbl_CaravanMenu = 0x107108C,
	kVtbl_TraitMenu = 0x10779BC,

	kVtbl_NiNode = 0x109B5AC,
	kVtbl_BSFadeNode = 0x10A8F90,
	kVtbl_NiControllerManager = 0x109619C,
	kVtbl_BSScissorTriShape = 0x10C2E7C,
	kVtbl_NiPointLight = 0x109DD0C,
	kVtbl_NiAlphaProperty = 0x10162DC,
	kVtbl_NiMaterialProperty = 0x109D6C4,
	kVtbl_NiStencilProperty = 0x101E07C,
	kVtbl_TileShaderProperty = 0x10B9D28,
	kVtbl_WaterShaderProperty = 0x10AE438,

	kVtbl_ImageSpaceModifierInstanceForm = 0x102D12C,

	kVtbl_hkpAabbPhantom = 0x10CC004,
	kVtbl_hkpSimpleShapePhantom = 0x10CE15C,
	kVtbl_hkpCachingShapePhantom = 0x10D087C,
	kVtbl_hkpRigidBody = 0x10C7888,
	kVtbl_hkpSphereMotion = 0x10C6D54,
	kVtbl_hkpBoxMotion = 0x10C6DC4,
	kVtbl_hkpThinBoxMotion = 0x10C6E34,
	kVtbl_ahkpCharacterProxy = 0x10C83E8,
};

#define IS_TYPE(form, type) (*(uint32_t*)form == kVtbl_##type)
#define NOT_TYPE(form, type) (*(uint32_t*)form != kVtbl_##type)

class TESFile;
class TESFullName;
class EnchantmentItem;
class TESSound;
class BGSItemList;
class Character;
class EffectItem;
class EffectSetting;
class TESAmmo;
class TESAmmoEffect;
class BGSListForm;
class BoundObjectListHead;
class BGSVoiceType;
class TESFaction;
class SpellItem;
class TESLevSpell;
class BGSRagdoll;
class BGSBodyPartData;
class TESRace;
class TESQuest;
class BGSExplosion;
class BGSDebris;
class BGSProjectile;
class BGSImpactDataSet;
class FaceGenUndo;
class TESCombatStyle;
class TESWorldSpace;
class BGSLightingTemplate;
class TESImageSpace;
class TESWaterForm;
class Script;
class TESObjectREFR;
class TESChildCell;
class ScriptLocals;
class TESEffectShader;
class TESPackage;
class Actor;
class TESNPC;
class TESGlobal;
class BGSImpactData;
class BGSMusicType;
class BGSEncounterZone;
class BGSNote;
class TESLeveledList;
class TESImageSpaceModifier;
class QueuedFile;

// IngredientItem (A4)
class IngredientItem;

class NiPointLight;

// TESObjectTREE (94)
class TESObjectTREE;

// TESFlora (90)
class TESFlora;

// 388
class TESObjectWEAP : public TESBoundObject {
public:
	TESObjectWEAP();
	~TESObjectWEAP();

	enum EWeaponType {
		kWeapType_HandToHandMelee = 0,
		kWeapType_OneHandMelee,
		kWeapType_TwoHandMelee,
		kWeapType_OneHandPistol,
		kWeapType_OneHandPistolEnergy,
		kWeapType_TwoHandRifle,
		kWeapType_TwoHandAutomatic,
		kWeapType_TwoHandRifleEnergy,
		kWeapType_TwoHandHandle,
		kWeapType_TwoHandLauncher,
		kWeapType_OneHandGrenade,
		kWeapType_OneHandMine,
		kWeapType_OneHandLunchboxMine,
		kWeapType_OneHandThrown,
		kWeapType_Last	// During animation analysis, player weapon can be classified as 0x0C = last
	};

	enum EWeaponSounds {
		kWeapSound_Shoot3D = 0,
		kWeapSound_Shoot2D,
		kWeapSound_Shoot3DLooping,
		kWeapSound_NoAmmo,
		kWeapSound_Swing = kWeapSound_NoAmmo,
		kWeapSound_Block,
		kWeapSound_Idle,
		kWeapSound_Equip,
		kWeapSound_Unequip
	};

	enum EHandGrip {
		eHandGrip_Default = 0xFF,
		eHandGrip_1 = 0xE6,
		eHandGrip_2 = 0xE7,
		eHandGrip_3 = 0xE8,
		eHandGrip_4 = 0xE9,
		eHandGrip_5 = 0xEA,
		eHandGrip_6 = 0xEB,
		eHandGrip_Count = 7,
	};

	enum EAttackAnimations {
		eAttackAnim_Default = 255,
		eAttackAnim_Attack3 = 38,
		eAttackAnim_Attack4 = 44,
		eAttackAnim_Attack5 = 50,
		eAttackAnim_Attack6 = 56,
		eAttackAnim_Attack7 = 62,
		eAttackAnim_Attack8 = 68,
		eAttackAnim_Attack9 = 144,
		eAttackAnim_AttackLeft = 26,
		eAttackAnim_AttackLoop = 74,
		eAttackAnim_AttackRight = 32,
		eAttackAnim_AttackSpin = 80,
		eAttackAnim_AttackSpin2 = 86,
		eAttackAnim_AttackThrow = 114,
		eAttackAnim_AttackThrow2 = 120,
		eAttackAnim_AttackThrow3 = 126,
		eAttackAnim_AttackThrow4 = 132,
		eAttackAnim_AttackThrow5 = 138,
		eAttackAnim_AttackThrow6 = 150,
		eAttackAnim_AttackThrow7 = 156,
		eAttackAnim_AttackThrow8 = 162,
		eAttackAnim_PlaceMine = 102,
		eAttackAnim_PlaceMine2 = 108,
		eAttackAnim_Count = 23,
	};

	enum ReloadAnim {
		eReload_A = 0,
		eReload_B,
		eReload_C,
		eReload_D,
		eReload_E,
		eReload_F,
		eReload_G,
		eReload_H,
		eReload_I,
		eReload_J,
		eReload_K,
		eReload_L,
		eReload_M,
		eReload_N,
		eReload_O,
		eReload_P,
		eReload_Q,
		eReload_R,
		eReload_S,
		eReload_W,
		eReload_X,
		eReload_Y,
		eReload_Z,
		eReload_Count,
	};
	static_assert(eReload_Count == 23);

	enum EWeaponFlags1 {
		eFlag_IgnoresNormalWeapResist = 0x1,
		eFlag_IsAutomatic = 0x2,
		eFlag_HasScope = 0x4,
		eFlag_CantDrop = 0x8,
		eFlag_HideBackpack = 0x10,
		eFlag_EmbeddedWeapon = 0x20,
		eFlag_No1stPersonISAnims = 0x40,
		eflag_NonPlayable = 0x80
	};

	enum EWeaponFlags2 {
		eFlag_PlayerOnly = 0x1,
		eFlag_NPCsUseAmmo = 0x2,
		eFlag_NoJamAfterReload = 0x4,
		eFlag_ActionPointOverride = 0x8,
		eFlag_MinorCrime = 0x10,
		eFlag_FixedRange = 0x20,
		eFlag_NotUsedNormalCombat = 0x40,
		eFlag_DamageToWeaponOverride = 0x80,
		eFlag_No3rdPersonISAnims = 0x100,
		eFlag_BurstShot = 0x200,
		eFlag_RumbleAlternate = 0x400,
		eFlag_LongBurst = 0x800,
		eFlag_ScopeNightVision = 0x1000,
		eFlag_ScopeFromMod = 0x2000
	};

	enum EEmbedWeapAV {
		eEmbedAV_Perception = 0,
		eEmbedAV_Endurance,
		eEmbedAV_LeftAttack,
		eEmbedAV_RightAttack,
		eEmbedAV_LeftMobility,
		eEmbedAV_RightMobility,
		eEmbedAV_Brain,
	};

	enum EOnHit {
		eOnHit_Normal = 0,
		eOnHit_DismemberOnly,
		eOnHit_ExplodeOnly,
		eOnHit_NoDismemberOrExplode,
	};

	enum ERumblePattern {
		eRumblePattern_Constant = 0,
		eRumblePattern_Square,
		eRumblePattern_Triangle,
		eRumblePattern_Sawtooth
	};

	enum ECritDamageFlags {
		eCritDamage_OnDeath = 0x1
	};

	enum {
		kWeaponModEffect_None = 0,
		kWeaponModEffect_IncreaseDamage,
		kWeaponModEffect_IncreaseClipCapacity,
		kWeaponModEffect_DecreaseSpread,
		kWeaponModEffect_DecreaseWeight,
		kWeaponModEffect_RegenerateAmmo_Shots,
		kWeaponModEffect_RegenerateAmmo_Seconds,
		kWeaponModEffect_DecreaseEquipTime,
		kWeaponModEffect_IncreaseRateOfFire,		// 8
		kWeaponModEffect_IncreaseProjectileSpeed,
		kWeaponModEffect_IncreaseMaxCondition,
		kWeaponModEffect_Silence,
		kWeaponModEffect_SplitBeam,
		kWeaponModEffect_VATSBonus,
		kWeaponModEffect_IncreaseZoom,				// 14
	};

	// bases
	TESFullName					fullName;			// 030
	TESModelTextureSwap			textureSwap;		// 03C
	TESIcon						icon;				// 05C
	TESScriptableForm			scritpable;			// 068
	TESEnchantableForm			enchantable;		// 074
	TESValueForm				value;				// 084
	TESWeightForm				weight;				// 08C
	TESHealthForm				health;				// 094
	TESAttackDamageForm			attackDmg;			// 09C
	BGSAmmoForm					ammo;				// 0A4
	BGSClipRoundsForm			clipRounds;			// 0AC
	BGSDestructibleObjectForm	destructible;		// 0B4
	BGSRepairItemList			repairItemList;		// 0BC
	BGSEquipType				equipType;			// 0C4
	BGSPreloadable				preloadable;		// 0CC
	BGSMessageIcon				messageIcon;		// 0D0
	BGSBipedModelList			bipedModelList;		// 0E0
	BGSPickupPutdownSounds		pickupPutdownSounds;// 0E8

	uint8_t				eWeaponType;				// 0F4
	uint8_t				pad[3];
	float				animMult;					// 0F8
	float				reach;						// 0FC
	uint8_t				weaponFlags1;				// 100
	uint8_t				handGrip;					// 101
	uint8_t				ammoUse;					// 102
	uint8_t				reloadAnim;					// 103
	float				minSpread;					// 104
	float				spread;						// 108
	uint32_t				unk10C;						// 10C
	float				sightFOV;					// 110
	uint32_t				unk114;						// 114
	BGSProjectile*		projectile;					// 118
	uint8_t				baseVATSChance;				// 11C
	uint8_t				attackAnim;					// 11D
	uint8_t				numProjectiles;				// 11E
	uint8_t				embedWeaponAV;				// 11F
	float				minRange;					// 120
	float				maxRange;					// 124
	uint32_t				onHit;						// 128
	uint32_t				weaponFlags2;				// 12C
	float				animAttackMult;				// 130
	float				fireRate;					// 134
	float				AP;							// 138
	float				rumbleLeftMotor;			// 13C
	float				rumbleRightMotor;			// 140
	float				rumbleDuration;				// 144
	float				damageToWeaponMult;			// 148
	float				animShotsPerSec;			// 14C
	float				animReloadTime;				// 150
	float				animJamTime;				// 154
	float				aimArc;						// 158
	uint32_t				weaponSkill;				// 15C - actor value
	uint32_t				rumblePattern;				// 160 - reload anim?
	float				rumbleWavelength;			// 164
	float				limbDamageMult;				// 168
	int32_t				resistType;					// 16c - actor value
	float				sightUsage;					// 170
	float				semiAutoFireDelay[2];		// 174
	uint32_t				unk17C;						// 17C - 0-0x10: 0x8:str req 0x10: - skill req  - 0xb:kill impulse B158 - mod 1 val B15C - Mod 2 val Effects: 0x1: e(zoom) 0x2: a 0x3:0 0x4-6: Values c-e Mod Effects Val2:1-3
	uint32_t				effectMods[3];				// 180
	float				value1Mod[3];				// 18C
	uint32_t				powerAttackAnimOverride;	// 198
	uint32_t				strRequired;				// 19C
	uint8_t				pad1A0;						// 1A0
	uint8_t				modReloadAnim;				// 1A1
	uint8_t				pad1A2[2];					// 1A2
	float				regenRate;					// 1A4
	float				killImpulse;				// 1A8
	float				value2Mod[3];				// 1AC
	float				impulseDist;				// 1B8
	uint32_t				skillRequirement;			// 1BC
	uint16_t				criticalDamage;				// 1C0
	uint8_t				unk1C2[2];					// 1C2
	float				criticalPercent;			// 1C4
	uint8_t				critDamageFlags;			// 1C8
	uint8_t				pad1C9[3];					// 1C9
	SpellItem*			criticalEffect;				// 1CC
	TESModel			shellCasingModel;			// 1DO
	TESModel			kScope;					// 1E8 - target NIF
	TESModel			kWorldModel;					// 200 - could be a texture swap
	uint32_t				unk218;						// 218
	TESSound*			sounds[12];					// 21C
	BGSImpactDataSet*	impactDataSet;				// 24C
	TESObjectSTAT*		worldStatic;				// 250
	TESObjectSTAT*		modStatics[7];				// 254
	TESModelTextureSwap	modModels[7];				// 270
	TESObjectIMOD*		itemMod[3];					// 350
	BSString			embeddedNodeName;			// 35C
	uint32_t				soundLevel;					// 364
	uint32_t				unk368;						// 368
	uint32_t				unk36C;						// 36C
	SpellItem*			VATSEffect;					// 370
	float				vatsSkill;					// 374
	float				vatsDamMult;				// 378
	float				vatsAP;						// 37C
	byte				isSilent;					// 380
	byte				modRequired;				// 381
	byte				pad382[3];

	bool IsEmbeddedWeapon() const { return weaponFlags1 & eFlag_EmbeddedWeapon; }

	bool IsAutomatic() const { return (weaponFlags1 & eFlag_IsAutomatic) != 0; }
	void SetIsAutomatic(bool bAuto) {
		if (bAuto) weaponFlags1 |= eFlag_IsAutomatic;
		else weaponFlags1 &= ~eFlag_IsAutomatic;
	}
	bool HasScope() const { return (weaponFlags1 & eFlag_HasScope) != 0; }
	bool HasModScope() const { return (weaponFlags2 & eFlag_ScopeFromMod) != 0; }
	bool IsNonPlayable() { return (weaponFlags1 & eflag_NonPlayable) != 0; }
	bool IsPlayable() { return !IsNonPlayable(); }
	void SetPlayable(bool doset) {
		if (doset) weaponFlags1 &= ~eflag_NonPlayable;
		else weaponFlags1 |= eflag_NonPlayable;
	}
	bool IsMelee() const { return eWeaponType <= kWeapType_TwoHandMelee; }
	uint8_t HandGrip() const;
	void SetHandGrip(uint8_t handGrip);
	uint8_t AttackAnimation() const;
	void SetAttackAnimation(uint32_t attackAnim);
	TESObjectIMOD* GetItemMod(uint8_t which);
	TESAmmo* GetAmmo();
	float GetModBonuses(uint8_t modFlags, uint32_t effectID);
	uint32_t GetItemModEffect(uint8_t which) { which -= 1; return (which < 3) ? effectMods[which] : 0; }
	float GetItemModValue1(uint8_t which) { which -= 1; return (which < 3) ? value1Mod[which] : 0; }
	float GetItemModValue2(uint8_t which) { which -= 1; return (which < 3) ? value2Mod[which] : 0; }

	void EjectShellCasing(TESObjectREFR* apReference) {
		ThisCall(0x524DB0, this, apReference);
	}
	TESForm* GetAmmoInInventory();

	bool IsFixedRange() const {
		return ThisCall<bool>(0x647790, this);
	}

	bool IsRangedWeapon() const {
		return ThisCall<bool>(0x4C0C30, this);
	}
};
#ifdef GAME
static_assert(sizeof(TESObjectWEAP) == 0x388);
#else
static_assert(sizeof(TESObjectWEAP) == 0x470);
#endif

class BSFaceGenNiNode;

struct AreaPointEntry {
	float	x;
	float	y;
};
typedef tList<AreaPointEntry> AreaPointEntryList;

struct RegionAreaEntry {
	AreaPointEntryList	points;
	uint32_t				unk08[2];
	float				unk10[4];
	uint32_t				edgeFallOff;
	uint32_t				pointCount;
};
typedef tList<RegionAreaEntry> RegionAreaEntryList;

// NavMeshInfoMap (40)
class NavMeshInfoMap;

class NavMesh;
class NavMeshArray;

class CellMopp : public NiRefObject {
public:
	NiTObjectArray<NiPointer<bhkRigidBody>> kRigidBodies;

	void Kill() {
		ThisCall(0x621E60, this);
	}
};
// 3C	Init proc: 0x6FC490
class BGSTerrainManager {
public:
	// 60
	struct LODNode {
		BGSTerrainManager* parent;		// 00
		uint32_t			lodLevel;		// 04
		uint32_t		cellXY;			// 08
		uint8_t			byte0C;			// 0C
		uint8_t			byte0D;			// 0D
		uint8_t			byte0E;			// 0E
		uint8_t			byte0F;			// 0F
		uint32_t			ukn10;			// 10
		void* object;		// 14
		uint32_t			ukn18;			// 18
		uint32_t			ukn1C;			// 1C
		LODNode* linked[4];		// 20
		uint32_t			unk30;			// 30
		float			flt34;			// 34
		float			flt38;			// 38
		float			flt3C;			// 3C
		float			flt40;			// 40
		float			flt44;			// 44
		float			flt48;			// 48
		float			flt4C;			// 4C
		uint32_t			unk50;			// 50
		uint32_t			ukn54;			// 54
		uint32_t			ukn58;			// 58
		uint8_t			byte5C;			// 5C
		uint8_t			byte5D;			// 5D
		uint8_t			byte5E;			// 5E
		uint8_t			byte5F;			// 5F

		LODNode* GetNodeByCoord(uint32_t coord);
	};
	static_assert(sizeof(LODNode) == 0x60);

	TESWorldSpace* world;		// 00
	LODNode* lodNode;	// 04
	NiNode* node08;	// 08
	NiNode* node0C;	// 0C
	uint32_t						coordNW;	// 10
	uint32_t						coordSE;	// 14
	uint32_t							ukn18;		// 18
	uint32_t							ukn1C;		// 1C
	uint32_t							ukn20;		// 20
	uint32_t							lodLevel;	// 24
	uint8_t							byte28;		// 28
	uint8_t							byte29;		// 29
	uint8_t							byte2A;		// 2A
	uint8_t							byte2B;		// 2B
	BSSimpleArray<TESObjectREFR*>	array2C;	// 2C
};
static_assert(sizeof(BGSTerrainManager) == 0x3C);

class ScriptVariable {
public:
	uint32_t			idx;		// 00
	uint32_t			pad04;		// 04
	double			data;		// 08
	uint8_t			type;		// 10
	uint8_t			pad11[3];	// 11
	uint32_t			unk14;		// 14
	BSString		name;		// 18
};

#ifdef GAME
// 68
struct CombatTarget
{
	Actor* target;
	uint32_t unk04[25];
};

// 14
struct CombatAlly
{
	Actor* ally;
	uint32_t unk04[4];
};

// 28
struct CombatActors
{
	uint32_t unk00[2]; // 00
	BSSimpleArray<CombatTarget> targets; // 08
	BSSimpleArray<CombatAlly> allies; // 18
};
// 188
class CombatController : public TESPackage
{
public:
	CombatController();
	~CombatController();

	struct Unk09C
	{
		uint32_t unk000[4]; // 000
		TESObjectWEAP* weapon1; // 010
		TESObjectWEAP* weapon2; // 014
		TESObjectWEAP* weapon3; // 018
		TESObjectWEAP* weapon4; // 01C
		uint32_t unk020; // 020
		BSSimpleArray<TESObjectWEAP> arr024; // 024
		uint32_t unk034[36]; // 034
		void* ptr0C4; // 0C4
		uint32_t unk0C8[17]; // 0C8
		BSSimpleArray<PathingCoverLocation*> arr10C; // 10C
		uint32_t unk11C[11]; // 11C
		BSSimpleArray<PathingCoverLocation*> arr148; // 148
		uint32_t unk158[3]; // 158
		BSSimpleArray<UnreachableCoverLocation*> arr164; // 164
		BSSimpleArray<UnreachableLocation*> arr174; // 174
		uint32_t unk184[15]; // 184
		Actor* actor1C0; // 1C0
		CombatController* cmbtCtrl; // 1C4
		uint32_t unk1C8[22]; // 1C8
	};

	CombatActors* combatActors; // 080
	CombatProcedure* combatProcedure1; // 084
	CombatProcedure* combatProcedure2; // 088
	BSSimpleArray<CombatProcedure*> combatProcedures; // 08C
	Unk09C* struct09C; // 09C
	void* ptr0A0; // 0A0
	uint32_t unk0A4; // 0A4
	CombatAction* combatAction; // 0A8
	CombatGoal* combatGoal; // 0AC
	uint32_t unk0B0; // 0B0
	float flt0B4[2]; // 0B4
	Actor* packageOwner; // 0BC
	Actor* packageTarget; // 0C0
	uint32_t unk0C4[2]; // 0C4
	float flt0CC; // 0CC
	float flt0D0; // 0D0
	uint8_t byte0D4; // 0D4
	uint8_t byte0D5; // 0D5
	uint8_t pad0D6[2]; // 0D6
	float flt0D8; // 0D8
	float flt0DC; // 0DC
	float flt0E0; // 0E0
	uint32_t unk0E4[3]; // 0E4
	TESObjectWEAP* weapon; // 0F0
	TESCombatStyle* combatStyle; // 0F4
	uint32_t unk0F8[11]; // 0F8
	uint8_t byte124; // 124
	bool stopCombat; // 125
	uint8_t byte126; // 126
	uint8_t byte127; // 127
	uint32_t unk128[8]; // 128
	float flt148; // 148
	uint32_t unk14C[15]; // 14C
};
static_assert(sizeof(CombatController) == 0x188);
#endif

// TESLevSpell (44)
class TESLevSpell;

// 730
class TESImageSpaceModifier : public TESForm {
public:
	TESImageSpaceModifier();
	~TESImageSpaceModifier();

	TESSound* outroSound;		// 018
	TESSound* introSound;		// 01C
	uint8_t					animable;			// 020
	uint8_t					pad021[3];			// 021
	float					duration;			// 024
	uint32_t					unk028[49];			// 028
	float					radialBlurCentreX;	// 0EC
	float					radialBlurCentreY;	// 0F0
	uint32_t					unk0F4[3];			// 0F4
	uint8_t					useTarget;			// 100
	uint8_t					pad101[3];			// 101
	uint32_t					unk104[4];			// 104
	NiFloatInterpolator		fltIntrpl1[44];		// 114
	NiColorInterpolator		clrIntrpl[2];		// 534
	NiFloatInterpolator		fltIntrpl2[9];		// 57C
	FloatData* data654[44];		// 654
	// 00:	HDR: Eye Adapt Speed (Multiply)
	// 01:	HDR: Eye Adapt Speed (Add)
	// 02:	HDR: Blur Radius (Multiply)
	// 03:	HDR: Blur Radius (Add)
	// 04:	HDR: Skin Dimmer (Multiply)
	// 05:	HDR: Skin Dimmer (Add)
	// 06:	HDR: Emissive Mult (Multiply)
	// 07:	HDR: Emissive Mult (Add)
	// 08:	HDR: Target LUM (Multiply)
	// 09:	HDR: Target LUM (Add)
	// 10:	HDR: Upper LUM Clamp (Multiply)
	// 11:	HDR: Upper LUM Clamp (Add)
	// 12:	HDR: Bright Scale (Multiply)
	// 13:	HDR: Bright Scale (Add)
	// 14:	HDR: Bright Clamp (Multiply)
	// 15:	HDR: Bright Clamp (Add)
	// 16:	HDR: LUM Ramp No Tex (Multiply)
	// 17:	HDR: LUM Ramp No Tex (Add)
	// 18:	HDR: LUM Ramp Min (Multiply)
	// 19:	HDR: LUM Ramp Min (Add)
	// 20:	HDR: LUM Ramp Max (Multiply)
	// 21:	HDR: LUM Ramp Max (Add)
	// 22:	HDR: Sunlight Dimmer (Multiply)
	// 23:	HDR: Sunlight Dimmer (Add)
	// 24:	HDR: Grass Dimmer (Multiply)
	// 25:	HDR: Grass Dimmer (Add)
	// 26:	HDR: Tree Dimmer (Multiply)
	// 27:	HDR: Tree Dimmer (Add)
	// 28:	Bloom: Blur Radius (Multiply)
	// 29:	Bloom: Blur Radius (Add)
	// 30:	Bloom: Alpha Mult Interior (Multiply)
	// 31:	Bloom: Alpha Mult Interior (Add)
	// 32:	Bloom: Alpha Mult Exterior (Multiply)
	// 33:	Bloom: Alpha Mult Exterior (Add)
	// 34:	Cinematic: Saturation (Multiply)
	// 35:	Cinematic: Saturation (Add)
	// 36:	Cinematic: Contrast (Multiply)
	// 37:	Cinematic: Contrast (Add)
	// 38:	Cinematic: Contrast Avg Lum (Multiply)
	// 39:	Cinematic: Contrast Avg Lum (Add)
	// 40:	Cinematic: Brightness (Multiply)
	// 41:	Cinematic: Brightness (Add)
	// 42:	Blur: Blur Radius
	// 43:	Double Vision: Strength
	ColorData* data704[2];		// 704
	FloatData* data70C[9];		// 70C
	// 00:	Radial Blur: Strength
	// 01:	Radial Blur: Rampup
	// 02:	Radial Blur: Up Start
	// 03:	Radial Blur: Rampdown
	// 04:	Radial Blur: Down Start
	// 05:	Depth of Field: Strength
	// 06:	Depth of Field: Distance
	// 07:	Depth of Field: Range
	// 08:	Full-Screen Motion Blur: Strength
#ifdef EDITOR
	float fUnk744;
	float fUnk748;
#endif
};
#ifdef GAME
static_assert(sizeof(TESImageSpaceModifier) == 0x730);
#else
static_assert(sizeof(TESImageSpaceModifier) == 0x74C);
#endif

extern TESForm* __fastcall GetTESForm(const TESForm* apForm);