#pragma once

#include "Utilities.h"
#include "GameTypes.h"
#include "GameBSExtraData.h"
#include "internal/netimmerse.h"
#include "internal/havok.h"

#include "Bethesda/ActorValueInfo.hpp"
#include "Bethesda/ActorValueOwner.hpp"
#include "Bethesda/BGSAcousticSpace.hpp"
#include "Bethesda/BGSAddonNode.hpp"
#include "Bethesda/BGSAmmoForm.hpp"
#include "Bethesda/BGSBipedModelList.hpp"
#include "Bethesda/BGSCameraShot.hpp"
#include "Bethesda/BGSClipRoundsForm.hpp"
#include "Bethesda/BGSDebris.hpp"
#include "Bethesda/BGSDefaultObjectManager.hpp"
#include "Bethesda/BGSDestructibleObjectForm.hpp"
#include "Bethesda/BGSEncounterZone.hpp"
#include "Bethesda/BGSEntryPointPerkEntry.hpp"
#include "Bethesda/BGSEquipType.hpp"
#include "Bethesda/BGSHeadPart.hpp"
#include "Bethesda/BGSImpactData.hpp"
#include "Bethesda/BGSImpactDataSet.hpp"
#include "Bethesda/BGSListForm.hpp"
#include "Bethesda/BGSMenuIcon.hpp"
#include "Bethesda/BGSMessage.hpp"
#include "Bethesda/BGSMessageIcon.hpp"
#include "Bethesda/BGSMusicType.hpp"
#include "Bethesda/BGSOpenCloseForm.hpp"
#include "Bethesda/BGSPerk.hpp"
#include "Bethesda/BGSPerkEntry.hpp"
#include "Bethesda/BGSPickupPutdownSounds.hpp"
#include "Bethesda/BGSPlaceableWater.hpp"
#include "Bethesda/BGSPreloadable.hpp"
#include "Bethesda/BGSRadiationStage.hpp"
#include "Bethesda/BGSRagdoll.hpp"
#include "Bethesda/BGSRepairItemList.hpp"
#include "Bethesda/BGSTextureModel.hpp"
#include "Bethesda/BGSTextureSet.hpp"
#include "Bethesda/BGSTouchSpellForm.hpp"
#include "Bethesda/BipedAnim.hpp"
#include "Bethesda/CachedValuesOwner.hpp"
#include "Bethesda/TESActorBase.hpp"
#include "Bethesda/TESActorBaseData.hpp"
#include "Bethesda/TESAIForm.hpp"
#include "Bethesda/TESAmmo.hpp"
#include "Bethesda/TESAnimation.hpp"
#include "Bethesda/TESAttackDamageForm.hpp"
#include "Bethesda/TESAttributes.hpp"
#include "Bethesda/TESBipedModelForm.hpp"
#include "Bethesda/TESBoundAnimObject.hpp"
#include "Bethesda/TESClass.hpp"
#include "Bethesda/TESClimate.hpp"
#include "Bethesda/TESCombatStyle.hpp"
#include "Bethesda/TESCondition.hpp"
#include "Bethesda/TESContainer.hpp"
#include "Bethesda/TESDescription.hpp"
#include "Bethesda/TESEnchantableForm.hpp"
#include "Bethesda/TESEyes.hpp"
#include "Bethesda/TESFaction.hpp"
#include "Bethesda/TESFullName.hpp"
#include "Bethesda/TESGlobal.hpp"
#include "Bethesda/TESGrass.hpp"
#include "Bethesda/TESHair.hpp"
#include "Bethesda/TESHealthForm.hpp"
#include "Bethesda/TESIcon.hpp"
#include "Bethesda/TESImageSpaceModifiableForm.hpp"
#include "Bethesda/TESKey.hpp"
#include "Bethesda/TESLandTexture.hpp"
#include "Bethesda/TESLevCharacter.hpp"
#include "Bethesda/TESLevCreature.hpp"
#include "Bethesda/TESLeveledList.hpp"
#include "Bethesda/TESLevItem.hpp"
#include "Bethesda/TESLoadScreen.hpp"
#include "Bethesda/TESModelAnim.hpp"
#include "Bethesda/TESModelList.hpp"
#include "Bethesda/TESModelRDT.hpp"
#include "Bethesda/TESModelTextureSwap.hpp"
#include "Bethesda/TESObjectACTI.hpp"
#include "Bethesda/TESObjectANIO.hpp"
#include "Bethesda/TESObjectARMA.hpp"
#include "Bethesda/TESObjectARMO.hpp"
#include "Bethesda/TESObjectBOOK.hpp"
#include "Bethesda/TESObjectCLOT.hpp"
#include "Bethesda/TESObjectLAND.hpp"
#include "Bethesda/TESObjectMISC.hpp"
#include "Bethesda/TESObjectSTAT.hpp"
#include "Bethesda/TESPackageData.hpp"
#include "Bethesda/TESRaceForm.hpp"
#include "Bethesda/TESReactionForm.hpp"
#include "Bethesda/TESScriptableForm.hpp"
#include "Bethesda/TESSkill.hpp"
#include "Bethesda/TESTexture1024.hpp"
#include "Bethesda/TESValueForm.hpp"
#include "Bethesda/TESWeightForm.hpp"

#include "Obsidian/BGSDehydrationStage.hpp"
#include "Obsidian/BGSHungerStage.hpp"
#include "Obsidian/BGSSleepDeprevationStage.hpp"
#include "Obsidian/TESAmmoEffect.hpp"
#include "Obsidian/TESCaravanCard.hpp"
#include "Obsidian/TESCaravanDeck.hpp"
#include "Obsidian/TESCaravanMoney.hpp"
#include "Obsidian/TESCasino.hpp"
#include "Obsidian/TESChallenge.hpp"
#include "Obsidian/TESLoadScreenType.hpp"
#include "Obsidian/TESReputation.hpp"
#include "Obsidian/TESObjectIMOD.hpp"
#include "Obsidian/TESCasinoChips.hpp"
#include "Obsidian/TESRecipe.hpp"
#include "Obsidian/MediaSet.hpp"
#include "Obsidian/MediaLocationController.hpp"

class PathingLocation;
class PathingCoverLocation;
struct UnreachableLocation;
struct UnreachableCoverLocation;
class CombatProcedure;
class CombatAction;
class CombatGoal;
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

#define IS_ID(form, type) (form->GetFormType() == FORM_TYPE::##type)
#define NOT_ID(form, type) (form->GetFormType() != FORM_TYPE::##type)

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
class TESObjectLAND;
class TESWorldSpace;
class BGSLightingTemplate;
class TESImageSpace;
class TESWaterForm;
class Script;
class TESObjectREFR;
class TESChildCell;
class ScriptLocals;
class TESObjectLIGH;
class TESEffectShader;
class TESObjectIMOD;
class TESObjectMISC;
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

struct PermanentClonedForm {
	uint32_t orgRefID;
	uint32_t cloneRefID;
};

class TESImageSpaceModifier;

// 24
class EffectItem {
public:
	EffectItem();
	~EffectItem();

	enum {
		kRange_Self = 0,
		kRange_Touch,
		kRange_Target,
	};

	struct ScriptEffectInfo {
		uint32_t		scriptRefID;
		uint32_t		school;
		BSString	effectName;
		uint32_t		visualEffectCode;
		uint32_t		isHostile;

		void SetName(const char* name);
		void SetSchool(uint32_t school);
		void SetVisualEffectCode(uint32_t code);
		void SetIsHostile(bool bIsHostile);
		bool IsHostile() const;
		void SetScriptRefID(uint32_t refID);

		ScriptEffectInfo* Clone() const;
		void CopyFrom(const ScriptEffectInfo* from);
		static ScriptEffectInfo* Create();
	};

	// mising flags
	uint32_t				magnitude;			// 00	used as a float
	uint32_t				area;				// 04
	uint32_t				duration;			// 08
	uint32_t				range;				// 0C
	uint32_t				actorValueOrOther;	// 10
	EffectSetting*		setting;			// 14
	float				cost;				// 18 on autocalc items this seems to be the cost
	TESCondition		conditions;			// 1C

	//bool HasActorValue() const;
	//uint32_t GetActorValue() const;
	//bool IsValidActorValue(uint32_t actorValue) const;
	//void SetActorValue(uint32_t actorValue);

	//bool IsScriptedEffect() const;
	//uint32_t ScriptEffectRefId() const;
	//uint32_t ScriptEffectSchool() const;
	//uint32_t ScriptEffectVisualEffectCode() const;
	//bool IsScriptEffectHostile() const;

	//EffectItem* Clone() const;
	//void CopyFrom(const EffectItem* from);
	//static EffectItem* Create();
	//static EffectItem* ProxyEffectItemFor(uint32_t effectCode);
	//
	//bool operator<(EffectItem*rhs) const;
	//// return the magicka cost of this effect item
	//// adjust for skill level if actorCasting is used
	//float MagickaCost(TESForm* actorCasting = NULL) const;

	//void SetMagnitude(uint32_t magnitude);
	//void ModMagnitude(float modBy);
	//void SetArea(uint32_t area);
	//void ModArea(float modBy);
	//void SetDuration(uint32_t duration);
	//void ModDuration(float modBy);
	//void SetRange(uint32_t range);
	//bool IsHostile() const;
};

// 10
class EffectItemList : public BSSimpleList<EffectItem*> {
public:
	EffectItemList();
	~EffectItemList();

	virtual bool		IsMedicine() const;
	virtual bool		IsFood() const;
	virtual float		GetCost(Actor* apActor) const;
	virtual uint32_t	GetMaxEffectCount() const;
	virtual uint32_t	GetLevel() const;

	uint32_t uiHostileCount;

	bool RemoveNthEffect(uint32_t index);

	void GetEffectsString(char* apBuffer, uint32_t auiBufferSize) const {
		ThisCall(0x406620, this, apBuffer, auiBufferSize);
	}
};

static_assert(sizeof(EffectItemList) == 0x10);

// 1C
class MagicItem : public TESFullName {
public:
	MagicItem();
	~MagicItem();

	virtual void	Unk_04(void); // pure virtual
	virtual void	Unk_05(void); // pure virtual
	virtual uint32_t	GetType();
	virtual bool	Unk_07(void);
	virtual bool	Unk_08(void);
	virtual void	Unk_09(void); // pure virtual
	virtual void	Unk_0A(void); // pure virtual
	virtual void	Unk_0B(void); // pure virtual
	virtual void	Unk_0C(void); // pure virtual
	virtual void	Unk_0D(void); // pure virtual
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void); // pure virtual

	EffectItemList	list;	// 00C
//	uint32_t	unk018;			// 018
	// perhaps types are no longer correct!
	enum EType {
		kType_None = 0,
		kType_Spell = 1,
		kType_Enchantment = 2,
		kType_Alchemy = 3,
		kType_Ingredient = 4,
	};
	EType Type() const;
};

static_assert(sizeof(MagicItem) == 0x1C);

// 034
class MagicItemForm : public TESForm {
public:
	MagicItemForm();
	~MagicItemForm();

	virtual void	ByteSwap(void); // pure virtual

	// base
	MagicItem	magicItem;	// 018
};

static_assert(sizeof(MagicItemForm) == 0x34);

// 0C
struct LvlListExtra {
	union						// 00
	{
		TESFaction* ownerFaction;
		TESNPC*		ownerNPC;
	};
	union						// 04
	{
		uint32_t		requiredRank;
		TESGlobal*	globalVar;
	};
	float			health;		// 08
};

class FactionRank;

// 24
class BGSQuestObjective {
public:
	BGSQuestObjective();
	virtual ~BGSQuestObjective();

	enum {
		eQObjStatus_displayed = 1,
		eQObjStatus_completed = 2,
	};

	struct TargetData {
		TESObjectREFR* target;
		uint8_t			flags;
		uint8_t			filler[3];
	};

	struct ParentSpaceNode {};

	struct TeleportLink {
		TESObjectREFR* door;
		uint32_t			unk04[3];
	};

	struct Target {
		struct Data {
			BSSimpleArray<ParentSpaceNode>	parentSpaceNodes;	// 00
			BSSimpleArray<TeleportLink>		teleportLinks;		// 10
			uint32_t							unk20[6];			// 20
		};

		uint8_t			byte00;			// 00
		uint8_t			pad01[3];		// 01
		TESCondition	conditions;		// 04
		TESObjectREFR*	target;			// 0C
		Data			data;			// 10
	};

	uint32_t			objectiveId;	// 004 Objective Index in the GECK
	BSString		displayText;	// 008
	TESQuest*		quest;			// 010
	tList<Target>	targets;		// 014
	uint32_t			unk01C;			// 01C
	uint32_t			status;			// 020	bit0 = displayed, bit 1 = completed. 1 and 3 significant. If setting it to 3, quest flags bit1 will be set also.

	int32_t GetTargetIndex(TESObjectREFR* refr);
};

/**** forms ****/

class TESTopic;
// 54
class TESIdleForm : public TESForm {
public:
	TESIdleForm();
	~TESIdleForm();

	enum {
		eIFgf_groupIdle = 0,
		eIFgf_groupMovement = 1,
		eIFgf_groupLeftArm = 2,
		eIFgf_groupLeftHand = 3,
		eIFgf_groupLeftWeapon = 4,
		eIFgf_groupLeftWeaponUp = 5,
		eIFgf_groupLeftWeaponDown = 6,
		eIFgf_groupSpecialIdle = 7,
		eIFgf_groupWholeBody = 20,
		eIFgf_groupUpperBody = 20,

		eIFgf_flagOptionallyReturnsAFile = 128,
		eIFgf_flagUnknown = 64,
	};

	struct Data {
		uint8_t			groupFlags;		// 000	animation group and other flags
		uint8_t			loopMin;		// 001
		uint8_t			loopMax;		// 002
		uint8_t			fil03B;			// 003
		uint16_t			replayDelay;	// 004
		uint8_t			flags;			// 006	bit0 is No attacking
		uint8_t			fil03F;			// 007
	};

	TESModelAnim					anim;			// 018
	TESCondition					conditions;		// 030
	Data							data;			// 038
	BSSimpleArray<TESIdleForm*>*	children;		// 040	NiFormArray, contains all idle anims in path if eIFgf_flagUnknown is set
	TESIdleForm*					parent;			// 044
	TESIdleForm*					previous;		// 048
	BSString						editorID;		// 04C

	TESIdleForm* FindIdle(Actor* animActor);
};

struct TESTopicInfoResponse {
	struct Data {
		uint32_t	emotionType;	//	00
		uint32_t	emotionValue;	//	04	Init'd to 0x32
		uint32_t	unused;			//	08
		uint8_t	responseNumber;	//	0C
		uint8_t	pad00D[3];
		uint32_t	sound;			//	10
		uint8_t	flags;			//	14	Init'd to 1
		uint8_t	pad015[3];
	};

	Data					data;					//	000
	BSString				responseText;			//	018
	TESIdleForm*			spkeakerAnimation;		//	020
	TESIdleForm*			listenerAnimation;		//	024
	TESTopicInfoResponse*	next;					//	028
};

// 50
class TESTopicInfo : public TESForm {
public:
	TESTopicInfo();
	~TESTopicInfo();

	struct RelatedTopics {
		tList<TESTopic>		linkFrom;
		tList<TESTopic>		choices;
		tList<TESTopic>		followUps;
	};

	TESCondition		conditions;			// 18
	uint16_t				unk20;				// 20
	bool				saidOnce;			// 22
	uint8_t				type;				// 23
	uint8_t				nextSpeaker;		// 24
	uint8_t				flags1;				// 25
	uint8_t				flags2;				// 26
	uint8_t				pad27;				// 27
	BSString			prompt;				// 28
	tList<TESTopic>		addTopics;			// 30
	RelatedTopics*		relatedTopics;		// 38
	uint32_t				speaker;			// 3C
	uint32_t				actorValueOrPerk;	// 40
	uint32_t				speechChallenge;	// 44
	TESQuest*			quest;				// 48
	uint32_t				modInfoFileOffset;	// 4C	during LoadForm
#if USE_MODDED_CHANGES
	TESTopic*				pParentTopic;
#endif

	void RunResultScript(bool onEnd, Actor* actor);

	void SetSaidOnce() {
		ThisCall(0x61F220, this);
	}

	void ResetSaidOnceFlags() {
		ThisCall(0x61F280, this);
	}
};

class TopicInfoArray : public NiTLargePrimitiveArray<TESTopicInfo*> {
public:
};
typedef void* INFO_LINK_ELEMENT;

// 48
class TESTopic : public TESForm {
public:
	TESTopic();
	~TESTopic();

	struct Info	//	34
	{
		TESQuest* quest;		//	00
		TopicInfoArray	infoArray;	//	04
		BSSimpleArray<INFO_LINK_ELEMENT>		unk01C;
		TESQuest* quest2;	//	2C
		uint8_t			unk030;
		uint8_t			pad031[3];
	};

	TESFullName		fullName;		// 18

	uint8_t			unk24;			// 24
	uint8_t			unk25;			// 25	used as bool or flag, connected to INFOGENERAL
	uint8_t			pad26[2];		// 26
	float			unk28;			// 28
	tList<Info>		infos;			// 2C
	uint32_t			unk34;			// 34	string TDUM
	uint32_t			unk38;			// 38
	uint16_t			unk3C;			// 3C
	uint16_t			unk3E;			// 3E
	BSString		editorIDstr;	// 40

	TopicInfoArray* GetTopicInfosForQuest(TESQuest* apQuest) {
		return ThisCall<TopicInfoArray*>(0x619F70, this, apQuest);
	}
};

// 4E4 - incomplete
class TESRace : public TESForm {
public:
	// 18
	struct FaceGenData {
		uint32_t	unk00;
		uint32_t	unk04;
		uint32_t	unk08;
		uint32_t	unk0C;
		uint32_t	unk10;
		uint32_t	unk14;
	};

	// 2
	struct SkillMod {
		uint8_t	actorValue;
		char	mod;
	};

	enum {
		kFlag_Playable = 0x00000001,
		kFlag_Child = 0x00000004,
	};

	TESRace();
	~TESRace();

	TESFullName		fullName;				// 018
	TESDescription	desc;					// 024
	TESSpellList	spells;					// 02C
	TESReactionForm	reaction;				// 040

	SkillMod		skillMods[7];			// 050
	uint8_t			pad05E[2];				// 05E
	float			height[2];				// 060 male/female
	float			weight[2];				// 068 male/female
	uint32_t			raceFlags;				// 070

	TESAttributes	baseAttributes[2];		// 074 male/female
	tList<TESHair>	hairs;					// 08C
	TESHair* defaultHair[2];			// 094 male/female
	uint8_t			defaultHairColor[2];	// 09C male/female
	uint8_t			fill09E[2];				// 09E

	uint32_t			unk0A0[(0xA8 - 0xA0) >> 2];	// 0A0

	tList<TESEyes>	eyes;					// 0A8

	TESModel		faceModels[2][8];			// 0B0	male/female Head, Ears, Mouth, TeethLower, TeethUpper, Tongue, LeftEye, RightEye
	TESTexture		faceTextures[2][8];			// 230	male/female Head, Ears, Mouth, TeethLower, TeethUpper, Tongue, LeftEye, RightEye
	TESTexture		bodyPartsTextures[2][3];	// 2F0	male/female	UpperBody, LeftHand, RightHand
	TESModel		bodyModels[2][3];			// 338	male/female	UpperBody, LeftHand, RightHand
	BGSTextureModel	bodyTextures[2];			// 3C8	male/female	EGT file, not DDS.
	FaceGenData		unk3F8[2][4];				// 3F8  male/female

	uint32_t			unk4B8[(0x4CC - 0x4B8) >> 2]; // 4B8

	BSString			name;				// 4CC
	NiTPrimitiveArray <void*>	faceGenUndo;		// 4D4 - NiTPrimitiveArray<FaceGenUndo *>
	uint32_t				unk4E4[6];			// 4E4
	BGSVoiceType*		voiceTypes[2];		// 4FC // VTCK male/female
	TESRace*			ageRace[2];			// 504 // ONAM/YNAM

	bool IsPlayable() const { return (raceFlags & kFlag_Playable) == kFlag_Playable; }
	void SetPlayable(bool doset) { if (doset) raceFlags |= kFlag_Playable; else raceFlags &= ~kFlag_Playable; }
};

// 68
class TESSound : public TESBoundAnimObject {
public:
	TESSound();
	~TESSound();

	enum {
		kFlag_RandomFrequencyShift = 1,
		kFlag_PlayAtRandom = 2,
		kFlag_EnvironmentIgnored = 4,
		kFlag_RandomLocation = 8,
		kFlag_Loop = 16,
		kFlag_MenuSound = 32,
		kFlag_2D = 64,
		kFlag_360LFE = 128,
		kFlag_DialogueSound = 256,
		kFlag_EnvelopeFast = 512,
		kFlag_EnvelopeSlow = 1024,
		kFlag_2DRadius = 2048,
		kFlag_MuteWhenSubmerged = 4096,
		kFlag_StartAtRandomPosition = 8192,
	};

	TESSoundFile	soundFile;				// 30

	uint32_t			unk3C;					// 3C
	uint16_t			unk40;					// 40
	uint16_t			unk42;					// 42
	uint8_t			minAttenuationDist;		// 44
	uint8_t			maxAttenuationDist;		// 45
	int16_t			frequencyAdj;			// 46
	uint32_t			soundFlags;				// 48
	uint16_t			staticAttenuation;		// 4C
	uint8_t			endsAt;					// 4E
	uint8_t			startsAt;				// 4F
	uint16_t			attenuationCurve[5];	// 50
	uint16_t			reverbAttenuation;		// 5A
	uint32_t			priority;				// 5C
	uint32_t			unk60;					// 60
	uint32_t			unk64;					// 64

	void SetFlag(uint32_t pFlag, bool bEnable) {
		if (bEnable) soundFlags |= pFlag;
		else soundFlags &= ~pFlag;
	}
};
static_assert(sizeof(TESSound) == 0x68);

// B0
class EffectSetting : public TESForm {
public:
	EffectSetting();
	~EffectSetting();

	enum {
		kArchType_ValueModifier = 0,
		kArchType_Script,
		kArchType_Dispel,
		kArchType_CureDisease,
		kArchType_Absorb,
		kArchType_Shield,
		kArchType_Calm,
		kArchType_Demoralize,
		kArchType_Frenzy,
		kArchType_CommandCreature,
		kArchType_CommandHumanoid,
		kArchType_Invisibility,
		kArchType_Chameleon,
		kArchType_Light,
		kArchType_Darkness,
		kArchType_NightEye,
		kArchType_Lock,
		kArchType_Open,
		kArchType_BoundItem,
		kArchType_SummonCreature,
		kArchType_DetectLife,
		kArchType_Telekinesis,
		kArchType_DisintigrateArmor,
		kArchType_DisinitgrateWeapon,
		kArchType_Paralysis,
		kArchType_Reanimate,
		kArchType_SoulTrap,
		kArchType_TurnUndead,
		kArchType_SunDamage,
		kArchType_Vampirism,
		kArchType_CureParalysis,
		kArchType_CureAddiction,
		kArchType_CurePoison,
		kArchType_Concussion,
		kArchType_ValueAndParts,
		kArchType_LimbCondition,
		kArchType_Turbo,
	};

	enum EffectFlags {
		kEffectFlag_HOSTILE = 0x1,
		kEffectFlag_RECOVER = 0x2,
		kEffectFlag_DETRIMENTAL = 0x4,
		kEffectFlag_UNK_8 = 0x8, 
		kEffectFlag_SELF = 0x10,
		kEffectFlag_TOUCH = 0x20,
		kEffectFlag_TARGET = 0x40, 
		kEffectFlag_NO_DURATION = 0x80,
		kEffectFlag_NO_MAGNITUDE = 0x100,
		kEffectFlag_NO_AREA = 0x200,
		kEffectFlag_PERSIST = 0x400,
		kEffectFlag_CREATE_SPELLMAKING = 0x800,
		kEffectFlag_GORY_VISUALS = 0x1000,
		kEffectFlag_kDisplayNameOnly = 0x2000,
		kEffectFlag_kRadioBroadcastSomething = 0x8000,
		kEffectFlag_kUseSkill = 0x80000,
		kEffectFlag_kUseAttribute = 0x100000,
		kEffectFlag_PAINLESS = 0x1000000,
		kEffectFlag_kSprayProjectileType = 0x2000000,
		kEffectFlag_kBoltProjectileType = 0x4000000,
		kEffectFlag_NO_HIT_EFFECT = 0x8000000,
		kEffectFlag_NO_DEATH_DISPEL = 0x10000000,
	};

	TESModel		model;			// 18
	TESDescription	description;	// 30
	TESFullName		fullName;		// 38
	TESIcon			icon;			// 44
	uint32_t			unk50;			// 50
	uint32_t			unk54;			// 54
	uint32_t			effectFlags;	// 58
	float			unk5C;			// 5C
	TESForm* associatedItem;// 60	// Script* for ScriptEffects
	uint32_t			unk64;			// 64
	uint32_t			resistVal;		// 68 - actor value for resistance
	uint16_t			unk6C;			// 6C
	uint8_t			pad6E[2];		// 6E
	TESObjectLIGH* light;			// 70
	float			projectileSpeed;// 74
	TESEffectShader* effectShader;	// 78 - effect shader
	uint32_t			unk7C;			// 7C
	uint32_t			unk80;			// 80
	uint32_t			unk84;			// 84
	uint32_t			hitSound;		// 88
	uint32_t			unk8C;			// 8C
	float			unk90;			// 90 - fMagicDefaultCEEnchantFactor
	float			unk94;			// 94 - fMagicDefaultCEBarterFactor
	uint8_t			archtype;		// 98
	uint8_t			pad99[3];		// 99
	uint8_t			actorVal;		// 9C - actor value
	uint8_t			pad9D[3];		// 9D
	uint32_t			unkA0;			// A0
	uint32_t			unkA4;			// A4
	uint32_t			unkA8;			// A8
	uint32_t			unkAC;			// AC
};

static_assert(sizeof(EffectSetting) == 0xB0);

// 44
class EnchantmentItem : public MagicItemForm {
public:
	EnchantmentItem();
	~EnchantmentItem();

	virtual void	ByteSwap(void);

	enum {
		kType_Weapon = 2,
		kType_Apparel,
	};

	uint32_t		type;		// 34
	uint32_t		unk38;		// 38
	uint32_t		unk3C;		// 3C
	uint8_t		enchFlags;	// 40
	uint8_t		pad41[3];	// 41
};

static_assert(sizeof(EnchantmentItem) == 0x44);

// 44
class SpellItem : public MagicItemForm {
public:
	SpellItem();
	~SpellItem();

	virtual void	ByteSwap(void);

	enum {
		kType_ActorEffect = 0,
		kType_Disease,
		kType_Power,
		kType_LesserPower,
		kType_Ability,
		kType_Poison,
		kType_Addiction = 10,
	};

	uint32_t		type;		// 34
	uint32_t		unk38;		// 38
	uint32_t		unk3C;		// 3C
	uint8_t		spellFlags;	// 40
	uint8_t		pad41[3];	// 41
};

static_assert(sizeof(SpellItem) == 0x44);

class BGSTalkingActivator;

// 98
class BGSTalkingActivator : public TESObjectACTI {
public:
	BGSTalkingActivator();
	~BGSTalkingActivator();

	Actor* talkingActor;		// 90
	BGSVoiceType* voiceType;	// 94
};
static_assert(sizeof(BGSTalkingActivator) == 0x98);

// BGSTerminal (9C)
class BGSTerminal : public TESObjectACTI {
public:
	BGSTerminal();
	~BGSTerminal();

	enum {
		kTerminalFlagLeveled = 1 << 0,
		kTerminalFlagUnlocked = 1 << 1,
		kTerminalFlagAltColors = 1 << 2,
		kTerminalFlagHideWelcome = 1 << 3,
	};

	enum {
		kEntryFlagAddNote = 1 << 0,
		kEntryFlagForceRedraw = 1 << 1,
	};

	struct TermData {
		uint8_t difficulty;       // 0: very easy, 1: easy, 2: average, 3: hard, 4: very hard, 5: requires key
		uint8_t terminalFlags;
		uint8_t type;             // 0-9, corresponds to GECK types 1-10
	};

	struct MenuEntry {
		BSString			entryText;
		BSString			resultText;
		Script*				resultScript;
		uint8_t				pad[78];
		TESCondition		conditions;
		BGSNote*			displayNote;
		BGSTerminal*		subMenu;
		uint8_t				entryFlags;
	};

	BSString			desc;			// 090	DESC
	tList<MenuEntry>	menuEntries;	// 098
	BGSNote*			password;		// 0A0	PNAM
	TermData			data;			// 0A4	DNAM
};

// 9C
class TESObjectCONT : public TESBoundAnimObject {
public:
	TESObjectCONT();
	~TESObjectCONT();

	TESContainer                container;				// 30
	TESFullName					name;					// 3C
	TESModelTextureSwap			model;					// 48
	TESScriptableForm			scriptForm;				// 68
	TESWeightForm				weightForm;				// 74
	BGSDestructibleObjectForm	destructForm;			// 7C
	BGSOpenCloseForm			openCloseForm;			// 84

	uint32_t						unk88;					// 88
	TESSound* openSound;				// 8C
	TESSound* closeSound;			// 90
	TESSound* randomLoopingSound;	// 94
	uint8_t						flags;					// 98
	uint8_t						pad99[3];				// 99
};

// 90
class TESObjectDOOR : public TESBoundAnimObject {
public:
	TESObjectDOOR();
	~TESObjectDOOR();

	TESFullName					name;					// 30
	TESModelTextureSwap			model;					// 3C
	TESScriptableForm			scriptForm;				// 5C
	BGSDestructibleObjectForm	destructForm;			// 68
	BGSOpenCloseForm			openCloseForm;			// 70

	uint32_t						unk74;					// 74
	TESSound* openSound;				// 78
	TESSound* closeSound;			// 7C
	TESSound* randomLoopingSound;	// 80
	uint32_t						unk84;					// 84
	tList<void>					list88;					// 88
};

// IngredientItem (A4)
class IngredientItem;

class NiPointLight;

// TESObjectLIGH (C8)
class TESObjectLIGH : public TESBoundAnimObject {
public:
	TESObjectLIGH();
	~TESObjectLIGH();

	enum {
		kFlag_Dynamic = 1,
		kFlag_CanBeCarried = 2,
		kFlag_Negative = 4,
		kFlag_Flicker = 8,
		kFlag_Unused = 16,
		kFlag_OffByDefault = 32,
		kFlag_FlickerSlow = 64,
		kFlag_Pulse = 128,
		kFlag_PulseSlow = 256,
		kFlag_SpotLight = 512,
		kFlag_SpotShadow = 1024,
	};

	TESFullName					fullName;		// 030
	TESModelTextureSwap			modelSwap;		// 03C
	TESIcon						icon;			// 05C
	BGSMessageIcon				messageIcon;	// 068
	TESScriptableForm			scriptable;		// 078
	TESWeightForm				weight;			// 084
	TESValueForm				value;			// 08C
	BGSDestructibleObjectForm	destructible;	// 094

	int32_t						time;			// 09C
	uint32_t						radius;			// 0A0
	uint8_t						red;			// 0A4
	uint8_t						green;			// 0A5
	uint8_t						blue;			// 0A6
	uint8_t						padA7;			// 0A7
	uint32_t						lightFlags;		// 0A8
	float						falloffExp;		// 0AC
	float						FOV;			// 0B0
	float						fadeValue;		// 0B4
	TESSound* sound;			// 0B8
	uint32_t						padBC[3];		// 0BC

	void SetFlag(uint32_t pFlag, bool bEnable) {
		if (bEnable) lightFlags |= pFlag;
		else lightFlags &= ~pFlag;
	}

	NiPointLight* CreatePointLight(TESObjectREFR* targetRef, NiNode* targetNode, bool arg3);
};
static_assert(sizeof(TESObjectLIGH) == 0x0C8);

// BGSStaticCollection (50)
class BGSStaticCollection;

// BGSMovableStatic (6C)
class BGSMovableStatic;

// TESObjectTREE (94)
class TESObjectTREE;

// TESFlora (90)
class TESFlora;

// TESFurniture (88)
class TESFurniture;

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

	bool IsAutomatic() const { return (weaponFlags1 & eFlag_IsAutomatic) != 0; }
	void SetIsAutomatic(bool bAuto) {
		if (bAuto) weaponFlags1 |= eFlag_IsAutomatic;
		else weaponFlags1 &= ~eFlag_IsAutomatic;
	}
	bool HasScope() const { return (weaponFlags1 & eFlag_HasScope) != 0; }
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
	TESAmmo* GetAmmo(Actor* apActor = nullptr);
	float GetModBonuses(uint8_t modFlags, uint32_t effectID);
	uint32_t GetItemModEffect(uint8_t which) { which -= 1; return (which < 3) ? effectMods[which] : 0; }
	float GetItemModValue1(uint8_t which) { which -= 1; return (which < 3) ? value1Mod[which] : 0; }
	float GetItemModValue2(uint8_t which) { which -= 1; return (which < 3) ? value2Mod[which] : 0; }

	void EjectShellCasing(TESObjectREFR* apReference) {
		ThisCall(0x524DB0, this, apReference);
	}
	TESForm* GetAmmoInInventory();
};
static_assert(sizeof(TESObjectWEAP) == 0x388);

enum AmmoEffectID {
	kAmmoEffect_DamageMod = 0,
	kAmmoEffect_DRMod = 1,
	kAmmoEffect_DTMod = 2,
	kAmmoEffect_SpreadMod = 3,
	kAmmoEffect_ConditionMod = 4,
	kAmmoEffect_FatigueMod = 5,
};

class BSFaceGenNiNode;

// 20
struct FaceGenData {
	enum FGGeoSymmetry {
		kBrow_HighLow,
		kBrowInner_HighLow,
		kBrowOuter_HighLow,
		kCheekbone_LowHigh,
		kCheekbone_ShallowPronounced,
		kCheekbone_ThinWide,
		kCheek_ConcaveConvex,
		kCheek_RoundGaunt,
		kChin_ForwardBackward,
		kChin_PronouncedRecessed,
		kChin_RetractedJutting,
		kChin_ShallowDeep,
		kChin_SmallLarge,
		kChin_TallShort,
		kChin_WideThin,
		kEyes_DownUp,
		kEyes_SmallLarge,
		kEyes_TiltInwardOutward,
		kEyes_TogetherApart,
		kFace_BrowNoseChinRatio,
		kFace_ForeheadSellionNoseRatio,
		kFace_HeavyLight,
		kFace_RoundGaunt,
		kFace_ThinWide,
		kForehead_SmallLarge,
		kForehead_TallShort,
		kForehead_TiltForwardBackward,
		kJaw_RetractedJutting,
		kJaw_WideThin,
		kJawNeck_SlopeHighLow,
		kJawline_ConcaveConvex,
		kMouth_DrawnPursed,
		kMouth_HappySad,
		kMouth_HighLow,
		kMouth_Lips_DeflatedInflated,
		kMouth_Lips_LargeSmall,
		kMouth_Lips_PuckeredRetracted,
		kMouth_ProtrudingRetracted,
		kMouth_TiltUpDown,
		kMouth_UnderbiteOverbite,
		kMouthChin_DistanceShortLong,
		kNose_BridgeShallowDeep,
		kNose_BridgeShortLong,
		kNose_DownUp,
		kNose_FlatPointed,
		kNose_NostrilTiltUpDown,
		kNose_NostrilSmallLarge,
		kNose_NostrilWideThin,
		kNose_RegionConcaveConvex,
		kNose_SellionDownUp,
		kNose_SellionShallowDeep,
		kNose_SellionShallowDeep2, //This one also seems to control the brow ridge
		kNose_SellionThinWide,
		kNose_ShortLong,
		kNose_TiltDownUp,
		kMaxSize //This is actually a valid property but it's not exposed normally. Seems to control upper cranial width.
	};
	enum FGGeoAsym {
		kBrowRidge_ForwardAxisTwist,
		kCheekbone_ProtrusionAsymmetry,
		kChin_ChinAxisTwist,
		kChin_ForwardAxisTwist,
		kChin_TransverseShift,
		kEyes_HeightDisparity,
		kEyes_TransverseShift,
		kFace_CoronalBend,
		kFace_CoronalShear,
		kFace_VerticalAxisTwist,
		kForehead_ForwardAxisTwist,
		kMouth_CornersTransverseShift,
		kMouth_ForwardAxisTwist,
		kMouth_TransverseShift,
		kMouth_TwistAndShift,
		kMouthNose_CoronalShear,
		kMouthNose_TransverseShift,
		kNose_BridgeTransverseShift,
		kNose_FrontalAxisTwist,
		kNose_SellionTransverseShift,
		kNose_TipTransverseShift,
		kNose_TransverseShift,
		kNose_VerticalAxisTwist,
		kNoseRegion_FrontalAxisTwist,
		kNostrils_FrontalAxisTwist,
		kMax, ////Seems to control face assymetry, but it's not exposed to GECK, either.
	};

	uint32_t		unk00;		// 00
	void* unk04;		// 04
	uint32_t		unk08;		// 08
	float** values;	// 0C
	uint32_t		useOffset;	// 10
	uint32_t		maxOffset;	// 14
	uint32_t		count;		// 18
	uint32_t		size;		// 1C
};

// 1EC
class TESNPC : public TESActorBase {
public:
	TESNPC();
	~TESNPC();

	TESRaceForm				race;				// 10C
	uint8_t					skillValues[14];	// 114
	uint8_t					skillOffsets[14];	// 122
	TESClass* classID;			// 130
	FaceGenData				faceGenData[3];		// 134
	uint32_t					unk194[8];			// 194
	FaceGenData* faceGenDataPtr;	// 1B4
	TESHair* hair;				// 1B8
	float					hairLength;			// 1BC
	TESEyes* eyes;				// 1C0
	BSFaceGenNiNode* unk1C4;			// 1C4
	BSFaceGenNiNode* unk1C8;			// 1C8
	uint32_t					unk1CC;				// 1CC
	uint16_t					unk1D0;				// 1D0
	uint16_t					unk1D2;				// 1D2
	TESCombatStyle* combatStyle;		// 1D4
	uint32_t					hairColor;			// 1D8
	tList<BGSHeadPart>		headPart;			// 1DC
	uint32_t					impactMaterialType;	// 1E4
	uint32_t					unk01E8;			// 1E8
	TESRace* race1EC;			// 1EC
	TESNPC* copyFrom;			// 1F0	Not set once PlayerRef exists and the target is the Player
	float					height;				// 1F4
	float					weight;				// 1F8	Aparently, getWeight purposly returns height except for the player.
	NiTPrimitiveArray<FaceGenUndo*>	faceGenUndo;		// 1FC

	void SetSex(uint32_t flags);
	void SetRace(TESRace* pRace);
	void CopyAppearance(TESNPC* srcNPC);
};

static_assert(sizeof(TESNPC) == 0x20C);

// 160
class TESCreature : public TESActorBase {
public:
	TESCreature();
	~TESCreature();

	TESAttackDamageForm			attackDmg;			// 10C
	TESModelList				modelList;			// 114

	TESCreature* audioTemplate;		// 128
	uint8_t						type;				// 12C
	uint8_t						combatSkill;		// 12D
	uint8_t						magicSkill;			// 12E
	uint8_t						stealthSkill;		// 12F
	uint8_t						attackReach;		// 130
	uint8_t						pad0131[3];			// 131
	float						turningSpeed;		// 134
	float						footWeight;			// 138
	float						baseScale;			// 13C
	TESCombatStyle* combatStyle;		// 140
	BGSBodyPartData* bodyPartData;		// 144
	uint32_t						materialType;		// 148
	BGSImpactDataSet* impactDataSet;		// 14C
	uint32_t						unk0150;			// 150
	uint32_t						soundLevel;			// 154
	BGSListForm* weaponList;		// 158
	uint8_t						byt015C;			// 15C
	uint8_t						pad015D[3];			// 15D
};

// D8
class AlchemyItem : public TESBoundObject {
public:
	AlchemyItem();
	~AlchemyItem();

	MagicItem					magicItem;				// 30
	TESModelTextureSwap			model;					// 4C
	TESIcon						icon;					// 6C
	BGSMessageIcon				messageIcon;			// 78
	TESScriptableForm			scriptable;				// 88
	TESWeightForm				weight;					// 94
	BGSEquipType				equipType;				// 9C
	BGSDestructibleObjectForm	destructible;			// A4
	BGSPickupPutdownSounds		pickupPutdownsounds;	// AC
	uint32_t						value;					// B8
	uint8_t						alchFlags;				// BC
	uint8_t						padBD[3];				// BD
	SpellItem* withdrawalEffect;		// C0
	float						addictionChance;		// C4
	TESSound* consumeSound;			// C8
	TESIcon						iconCC;					// CC

	bool IsPoison();
};

static_assert(sizeof(AlchemyItem) == 0xD8);

class BGSIdleCollection : public BaseFormComponent {
public:
	BGSIdleCollection();
	~BGSIdleCollection();

	uint8_t flags;
	uint8_t animCount;
	TESIdleForm** idleList;
	float idleTimer;
};

static_assert(sizeof(BGSIdleCollection) == 0x10);

class BGSIdleMarker : public TESBoundObject {
public:
	BGSIdleMarker();
	~BGSIdleMarker();
	BGSIdleCollection idleCollection;
};

static_assert(sizeof(BGSIdleMarker) == 0x40);

// BGSNote (80)
class BGSNote : public TESBoundObject {
public:
	BGSNote();
	~BGSNote();

	enum Type : uint8_t
	{
		kSound = 0,
		kText = 1,
		kImage = 2,
		kVoice = 3,
	};
	// bases
	TESModel					model;					// 30
	TESFullName					fullName;				// 48
	TESIcon						icon;					// 54
	BGSPickupPutdownSounds		pickupPutdownSounds;	// 60
	union												// 6C
	{
		TESDescription* noteText;
		TESTexture* picture;
		TESTopic* voice;
		TESSound* sound;
	};
	TESNPC*						speaker;
	tList<TESQuest>				questList;
	Type						type;
	bool						read;
};
static_assert(sizeof(BGSNote) == 0x80);

// BGSConstructibleObject (B0)
class BGSConstructibleObject;

// C0
class BGSProjectile : public TESBoundObject {
public:
	BGSProjectile();
	~BGSProjectile();

	enum {
		kFlags_Hitscan = 0x1,
		kFlags_Explosion = 0x2,
		kFlags_AltTrigger = 0x4,
		kFlags_MuzzleFlash = 0x8,
		//								0x10,
		kFlags_CanBeDisabled = 0x20,
		kFlags_CanBePicked = 0x40,
		kFlags_Supersonic = 0x80,
		kFlags_PinsLimbs = 0x100,
		kFlags_PassSmallTransparent = 0x200,
		kFlags_Detonates = 0x400,
		kFlags_Rotation = 0x800,
	};

	TESFullName						fullName;			// 30
	TESModel						model;				// 3C
	BGSPreloadable					preloadable;		// 54
	BGSDestructibleObjectForm		destructible;		// 58

	uint16_t							projFlags;			// 60
	uint16_t							type;				// 62
	float							gravity;			// 64
	float							speed;				// 68
	float							range;				// 6C
	TESObjectLIGH* lightProjectile;	// 70
	TESObjectLIGH* lightMuzzleFlash;	// 74
	float							tracerChance;		// 78
	float							altProximity;		// 7C
	float							altTimer;			// 80
	BGSExplosion* explosion;			// 84
	TESSound* soundProjectile;	// 88
	float							flashDuration;		// 8C
	float							fadeDuration;		// 90
	float							impactForce;		// 94
	TESSound* soundCountDown;	// 98
	TESSound* soundDisable;		// 9C
	TESObjectWEAP* defaultWeapSrc;	// A0
	float							rotationX;			// A4
	float							rotationY;			// A8
	float							rotationZ;			// AC
	float							bouncyMult;			// B0
	TESModel						muzzleFlash;		// B4
	uint8_t							soundLevel;			// CC

	void SetFlag(uint32_t pFlag, bool bEnable) {
		if (bEnable) projFlags |= pFlag;
		else projFlags &= ~pFlag;
	}
};

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

// E0
class TESObjectCELL : public TESForm {
public:
	TESObjectCELL();
	~TESObjectCELL();

	typedef BSSimpleList<TESObjectREFR*> RefList;

	struct ExteriorCoords {
		int32_t		x;			// 00
		int32_t		y;			// 04
		uint8_t		byte08;		// 08
		uint8_t		pad09[3];	// 09
	};
	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t alpha;
	};
	struct LightingData {
		Color		ambientRGB;		// 00
		Color		directionalRGB;		// 04
		Color		fogRGB;		// 08
		float		fogNear;		// 0C
		float		fogFar;		// 10
		int			directionalRotXY;		// 14
		int			directionalRotZ;		// 18
		float		directionalFade;		// 1C
		float		fogClipDist;		// 20
		float		fogPower;		// 24
		uint32_t* getValuesFrom;		// 28
	};

	union CellCoordinates {
		ExteriorCoords* exterior;
		LightingData* interior;
	};

	// 64
	struct LoadedData {
		NiPointer<NiNode>									spCell3D;
		BSSimpleList<TESObjectREFR*>						kLargeAnimatedRefs;
		NiTMap<TESObjectREFR*, NiNode*>						kAnimatedRefs;
		NiTMap<TESForm*, TESObjectREFR*>					kEmittanceSourceRefMap; // Form can be either TESRegion or TESObjectLIGH
		NiTMap<TESObjectREFR*, NiNode*>						kEmittanceLightRefMap;
		NiTMap<TESObjectREFR*, NiPointer<BSMultiBoundNode>> kMultiboundRefMap;
		BSSimpleList<TESObjectREFR*>						kScriptedRefs;
		BSSimpleList<TESObjectREFR*>						kActivatingRefs;
		BSSimpleList<TESObjectREFR*>						kWaterRefs;
	};

	enum {
		kCellFlag_IsInterior = 1 << 0,
		kCellFlag_HasWater = 1 << 1,
		kCellFlag_InvertFastTravelBehavior = 1 << 2,
		kCellFlag_ForceHideLand = 1 << 3,
		kCellFlag_PublicPlace = 1 << 5,
		kCellFlag_HandChanged = 1 << 6,
		kCellFlag_BehaveLikeExterior = 1 << 7,
	};

	struct ALIGN1 _CellFlags {
		enum Flags : uint8_t {
			INTERIOR			= 1u << 0,
			HAS_WATER			= 1u << 1,
			CANT_FAST_TRAVEL	= 1u << 2,
			NO_LOD_WATER		= 1u << 3,
			HAS_TEMP_DATA		= 1u << 4,
			PUBLIC				= 1u << 5,
			TEMP_PUBLIC			= 1u << 6,
			FAKE_EXTERIOR		= 1u << 7,
		};

		bool bInterior				: 1;
		bool bHasWater				: 1;
		bool bCantFastTravel		: 1;
		bool bNoLODWater			: 1;
		bool bHasTempData			: 1;
		bool bPublic				: 1;
		bool bTempPublic			: 1;
		bool bBehaveLikeExterior	: 1;
	};
	using CellFlags = _CellFlags::Flags;

	TESFullName				fullName;				// 18
	Bitfield<_CellFlags>	cellFlags;				// 24
	uint8_t					byte25;					// 25
	uint8_t					byte26;					// 26	5 or 6 would mean cell is loaded
	uint8_t					byte27;					// 27
	ExtraDataList			extraDataList;			// 28
	CellCoordinates			coords;					// 48
	TESObjectLAND* land;					// 4C
	float					waterHeight;			// 50
	uint32_t					unk54;					// 54
	TESTexture				noiseTexture;			// 58
	NavMeshArray*			pNavMeshes;
	uint32_t					unk68[6];				// 68
	void* refLockSemaphore;		// 80
	uint32_t					unk84[8];				// 84
	uint32_t					actorCount;				// A4
	uint16_t					countVisibleDistant;	// A8
	uint16_t					unkAA;					// AA
	RefList					objectList;				// AC
	NiNode* niNodeB4;				// B4
	NiNode* niNodeB8;				// B8
	uint32_t					unkBC;					// BC
	TESWorldSpace* worldSpace;			// C0
	LoadedData* renderData;			// C4
	float					fltC8;					// C8
	uint8_t					byteCC;					// CC
	uint8_t					byteCD;					// CD
	uint8_t					byteCE;					// CE
	uint8_t					byteCF;					// CF
	uint8_t					byteD0;					// D0
	uint8_t					byteD1;					// D1
	uint8_t					byteD2;					// D2
	uint8_t					byteD3;					// D3
	BSPortalGraph* portalGraph;			// D4
	BGSLightingTemplate* lightingTemplate;		// D8
	uint32_t					inheritFlags;			// DC

	bool IsInterior() const { return cellFlags.bInterior; }
	NiNode* Get3DNode(uint32_t index);
	void ToggleNodes(uint32_t nodeBits, uint8_t doHide);
	void GenerateRenderedTexture(NiCamera* camera, NiRenderedTexture** outTexture);
	TESWorldSpace* GetWorldSpace() const { return IsInterior() ? nullptr : worldSpace; }

	void CellRefLockEnter();
	void CellRefLockLeave();

	static uint32_t GetCoord(int16_t x, int16_t y) {
		return (int32_t(x) << 16) | uint16_t(y);
	};

	CellMopp* GetCellMopp() const {
		return ThisCall<CellMopp*>(0x537B30, this);
	}

	void SetupMopp() {
		ThisCall(0x5535F0, this);
	}
};
static_assert(sizeof(TESObjectCELL) == 0xE0);

// 3C	Init proc: 0x6FC490
struct BGSTerrainManager {
	// 60
	struct LODNode {
		BGSTerrainManager* parent;		// 00
		uint32_t			lodLevel;		// 04
		Coordinate		cellXY;			// 08
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
	Coordinate						coordNW;	// 10
	Coordinate						coordSE;	// 14
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

typedef NiTPointerMap<int32_t, TESObjectCELL*> CellPointerMap;

// EC
class NiPoint3;
class TESWorldSpace : public TESForm, public TESFullName, public TESTexture {
public:
	TESWorldSpace();
	~TESWorldSpace();

	// Returns true if name has changed
	virtual bool	GetMapNameForLocation(BSString& name, float x, float y, float z);
	virtual void	Unk_4F(uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint32_t arg6);

	struct DCoordXY {
		int32_t	X;
		int32_t	Y;
	};

	struct WCoordXY {
		int16_t	X;
		int16_t	Y;
	};

	struct OFFSET_DATA {
		uint32_t*	pCellFileOffsets;
		NiPoint2	kOffsetMinCoords;
		NiPoint2	kOffsetMaxCoords;
		uint32_t	uiFileOffset;
	};	// 014

	struct MapData {
		DCoordXY	usableDimensions;	// 00
		WCoordXY	cellNWCoordinates;	// 08
		WCoordXY	cellSECoordinates;	// 0C
	};	// 010

	struct ImpactSwap {
		typedef NiTMap<BGSImpactData*, BGSImpactData*> ImpactImpactMap;
		enum MaterialType {
			eMT_Stone,
			eMT_Dirt,
			eMT_Grass,
			eMT_Glass,
			eMT_Metal,
			eMT_Wood,
			eMT_Organic,
			eMT_Cloth,
			eMT_Water,
			eMT_HollowMetal,
			eMT_OrganicBug,
			eMT_OrganicGlow,
			eMT_Max
		};

		ImpactImpactMap* impactImpactMap[eMT_Max];	// 000
		char				footstepMaterials[0x12C];	// 030
	};

	typedef NiTPointerMap<uint32_t, BSSimpleList<TESObjectREFR*>*>	RefListPointerMap;
	typedef NiTMap<TESFile*, TESWorldSpace::OFFSET_DATA*>			OffsetDataMap;
	enum {
		kWorldFlag_SmallWorld = 1 << 0,
		kWorldFlag_NoFastTravel = 1 << 1,
		kWorldFlag_NoLODWater = 1 << 4,
		kWorldFlag_NoLODNoise = 1 << 5,
		kWorldFlag_NoFallDamage = 1 << 6,
		kWorldFlag_WaterAdjustment = 1 << 7,

		kParentFlag_UseLandData = 1 << 0,
		kParentFlag_UseLODData = 1 << 1,
		kParentFlag_UseMapData = 1 << 2,
		kParentFlag_UseWaterData = 1 << 3,
		kParentFlag_UseClimateData = 1 << 4,
		kParentFlag_UseISData = 1 << 5,
	};

	CellPointerMap*						pCellMap;
	TESObjectCELL*						pPersistentCell;
	uint32_t							kTerrainLODManager; // Unused
	BGSTerrainManager*					pTerrainManager;
	TESClimate*							pClimate;
	TESImageSpace*						pImageSpace;
	ImpactSwap*							pImpactSwap;
	Bitfield8							ucWorldFlags;
	Bitfield16							usParentUseFlags;
	RefListPointerMap					kFixedPersistentRefMap;			// 50
	BSSimpleList<TESObjectREFR*>		kMobilePersistentRefs;
	NiTMap<uint32_t, TESObjectREFR*>*	pOverlappedMultiBoundMap;
	NiPointer<NiRefObject>				spPortalGraph;
	TESWorldSpace*						pParentWorld;			// 70
	TESWaterForm*						pWorldWater;
	TESWaterForm*						pLODWater;
	float								fWaterLODHeight;
	MapData								kMapData;			// 80
	float								worldMapScale;		// 90
	float								worldMapCellX;		// 94
	float								worldMapCellY;		// 98
	BGSMusicType*						pMusic;
	NiPoint2							kMinCoords;
	NiPoint2							kMaxCoords;
	OffsetDataMap						kOffsetMap;
	BSString							strEditorID;
	float								fDefaultLandHeight;
	float								fDefaultWaterHeight;
	BGSEncounterZone*					pEncounterZone;
	TESTexture							kCanopyShadowTexture;
	TESTexture							kWaterNoiseTexture;

	TESWorldSpace* GetRootMapWorld();
};
static_assert(sizeof(TESWorldSpace) == 0xEC);


struct VariableInfo {
	uint32_t			idx;		// 00
	uint32_t			pad04;		// 04
	double			data;		// 08
	uint8_t			type;		// 10
	uint8_t			pad11[3];	// 11
	uint32_t			unk14;		// 14
	BSString		name;		// 18
};

// TESQuest (6C)
class TESQuest : public TESForm {
public:
	TESQuest();
	~TESQuest();

	virtual char* GetEditorName() const;

	TESScriptableForm		scriptable;			// 18
	TESIcon					icon;				// 24
	TESFullName				fullName;			// 30

	struct StageInfo {
		uint8_t			stage;		// 00 stageID
		uint8_t			unk001;		// 01 status ?
		uint8_t			pad[2];		// 02
		tList<void>		unk004;		// 04 log entries
	};

	uint8_t					flags;				// 3C	bit0 is startGameEnabled/isRunning
	uint8_t					priority;			// 3D
	uint8_t					pad3E[2];			// 3E
	float					questDelayTime;		// 40
	tList<StageInfo>		stages;				// 44
	tList<void>				lVarOrObjectives;	// 4C
		// So: this list would contain both Objectives and LocalVariables !
		// That seems very strange but still, looking at Get/SetObjective... and ShowQuestVars there's no doubt.
	TESCondition			conditions;			// 54
	ScriptLocals*		scriptEventList;	// 5C
	uint8_t					currentStage;		// 60
	uint8_t					pad61[3];			// 61
	BSString				editorName;			// 64

	bool SetStage(uint8_t stageID);
	BGSQuestObjective* GetObjective(uint32_t objectiveID);
};

static_assert(sizeof(TESQuest) == 0x6C);

// TESIdleForm (54)
class TESIdleForm;

class TESPatrolPackageData : public TESPackageData {
public:
	TESPatrolPackageData();
	~TESPatrolPackageData();

	uint8_t	patrolFlags;
};

enum {
	kPackageFlag_OffersServices = 1 << 0,
	kPackageFlag_MustReachLocation = 1 << 1,
	kPackageFlag_MustComplete = 1 << 2,
	kPackageFlag_LockDoorsAtStart = 1 << 3,
	kPackageFlag_LockDoorsAtEnd = 1 << 4,
	kPackageFlag_LockDoorsAtLocation = 1 << 5,
	kPackageFlag_UnlockDoorsAtStart = 1 << 6,
	kPackageFlag_UnlockDoorsAtEnd = 1 << 7,
	kPackageFlag_UnlockDoorsAtLocation = 1 << 8,
	kPackageFlag_ContinueIfPCNear = 1 << 9,
	kPackageFlag_OncePerDay = 1 << 10,
	kPackageFlag_Unk11 = 1 << 11,
	kPackageFlag_SkipFalloutBehavior = 1 << 12,
	kPackageFlag_AlwaysRun = 1 << 13,
	kPackageFlag_Unk14 = 1 << 14,
	kPackageFlag_NeverRun = 1 << 15,
	kPackageFlag_Unk16 = 1 << 16,
	kPackageFlag_AlwaysSneak = 1 << 17,
	kPackageFlag_AllowSwimming = 1 << 18,
	kPackageFlag_AllowFalls = 1 << 19,
	kPackageFlag_ArmorUnequipped = 1 << 20,
	kPackageFlag_WeaponsUnequipped = 1 << 21,
	kPackageFlag_DefensiveCombat = 1 << 22,
	kPackageFlag_WeaponsDrawn = 1 << 23,
	kPackageFlag_NoIdleAnims = 1 << 24,
	kPackageFlag_PretendInCombat = 1 << 25,
	kPackageFlag_ContinueDuringCombat = 1 << 26,
	kPackageFlag_NoCombatAlert = 1 << 27,
	kPackageFlag_NoWarnAttackBehavior = 1 << 28,
	kPackageFlag_AlwaysWalk = 1 << 29,	//	JIP LN
	kPackageFlag_Unk30 = 1 << 30,
	kPackageFlag_Unk31 = 1 << 31
};

// TESPackage (80) class definition duplicated from Oblivion. Enum not updated
class TESPackage : public TESForm {
public:
	TESPackage();
	~TESPackage();

	virtual void	Unk_4E();
	virtual void	Unk_4F();
	virtual void	Unk_50();
	virtual void	Unk_51();
	virtual void	Unk_52();
	virtual void	Unk_53();
	virtual void	Unk_54();
	virtual void	Unk_55();
	virtual void	Unk_56();
	virtual void	Unk_57();

	enum	// From OBSE and FNVEdit. Runtimes has 0x24 types!
	{
		kPackageType_Find = 0,		// 00
		kPackageType_Follow,
		kPackageType_Escort,
		kPackageType_Eat,
		kPackageType_Sleep,
		kPackageType_Wander,
		kPackageType_Travel,
		kPackageType_Accompany,
		kPackageType_UseItemAt,
		kPackageType_Ambush,
		kPackageType_FleeNotCombat,
		kPackageType_Unk11,
		kPackageType_Sandbox,
		kPackageType_Patrol,
		kPackageType_Guard,
		kPackageType_Dialogue,
		kPackageType_UseWeapon,			// 10

		// unless shown otherwise kPackageType_CombatController,	// Actor::GetCombatController returns package only if type matches this
		// unless shown otherwise kPackType_Unk0D,				// also related to dynamic combat packages?

		kPackType_MAX
	};

	// 8
	struct PackageTime {
		enum {
			kDay_Any = 0,
			kTime_Any = 0xFF,
		};

		enum {
			kMonth_January = 0,
			kMonth_February,
			kMonth_March,
			kMonth_April,
			kMonth_May,
			kMonth_June,
			kMonth_July,
			kMonth_August,
			kMonth_September,
			kMonth_October,
			kMonth_November,
			kMonth_December,
			kMonth_Spring,	// march, april, may
			kMonth_Summer,	// june, july, august
			kMonth_Autumn,	// september, august, november (in Geck)
			kMonth_Winter,	// december, january, february

			kMonth_Any = 0xFF,
		};

		enum {
			kWeekday_Sundays = 0,
			kWeekday_Morndays,
			kWeekday_Tuesdays,
			kWeekday_Wednesdays,
			kWeekday_Thursdays,
			kWeekday_Frydays,
			kWeekday_Saturdays,
			kWeekday_Weekdays,
			kWeekday_Weekends,
			kWeekday_MWF,
			kWeekday_TT,

			kWeekday_Any = 0xFF
		};

		uint8_t	month;
		uint8_t	weekDay;
		uint8_t	date;
		uint8_t	time;
		uint32_t	duration;
	};

	union ObjectType {
		TESForm* form;
		TESObjectREFR* refr;
		uint32_t			objectCode;
	};

	// order only somewhat related to kFormType_XXX (values off by 17, 20, or 21)
	enum	// From OBSE and FNVEdit
	{
		kObjectType_None = 0,
		kObjectType_Activators,
		kObjectType_Armor,
		kObjectType_Books,
		kObjectType_Clothing,
		kObjectType_Containers,
		kObjectType_Doors,
		kObjectType_Ingredients,
		kObjectType_Lights,
		kObjectType_Misc,
		kObjectType_Flora,
		kObjectType_Furniture,
		kObjectType_WeaponsAny,
		kObjectType_Ammo,
		kObjectType_NPCs,
		kObjectType_Creatures,
		kObjectType_Keys,				//	10
		kObjectType_Alchemy,
		kObjectType_Food,
		kObjectType_AllCombatWearable,
		kObjectType_AllWearable,
		kObjectType_WeaponsRanged,
		kObjectType_WeaponsMelee,
		kObjectType_WeaponsNone,
		kObjectType_ActorEffectAny,
		kObjectType_ActorEffectRangeTarget,
		kObjectType_ActorEffectRangeTouch,
		kObjectType_ActorEffectRangeSelf,
		kObjectType_ActorsAny,

		kObjectType_Max,						//	1E
	};

	struct LocationData {
		enum {
			kPackLocation_NearReference = 0,
			kPackLocation_InCell = 1,
			kPackLocation_CurrentLocation = 2,
			kPackLocation_EditorLocation = 3,
			kPackLocation_ObjectID = 4,
			kPackLocation_ObjectType = 5,
			kPackLocation_LinkedReference = 6,

			kPackLocation_Max,
		};

		uint8_t		locationType;
		uint8_t		pad[3];
		uint32_t		radius;
		ObjectType  object;
	};

	enum {
		kTargetType_Refr = 0,
		kTargetType_BaseObject = 1,
		kTargetType_TypeCode = 2,

		kTargetType_Max = 3,
	};

	struct TargetData {
		uint8_t		targetType;	// 00
		uint8_t		pad[3];		// 01
		ObjectType	target;		// 04
		uint32_t		count;		// 08 can be distance too
		float		unk0C;		// 0C
	};

	enum eProcedure {			// uint32_t	// Checked the Geck Wiki. Not consistent with s_procNames (which has a diffferent order and 0x37 procedures)
		kProcedure_TRAVEL = 0,
		kProcedure_ACTIVATE,
		kProcedure_ACQUIRE,
		kProcedure_WAIT,
		kProcedure_DIALOGUE,
		kProcedure_GREET,
		kProcedure_GREET_DEAD,
		kProcedure_WANDER,
		kProcedure_SLEEP,
		kProcedure_OBSERVE_COMBAT,
		kProcedure_EAT,
		kProcedure_FOLLOW,
		kProcedure_ESCORT,
		kProcedure_COMBAT,
		kProcedure_ALARM,
		kProcedure_PURSUE,
		kProcedure_FLEE,					// 0x10
		kProcedure_DONE,
		kProcedure_YELD,
		kProcedure_TRAVEL_TARGET,
		kProcedure_CREATE_FOLLOW,
		kProcedure_GET_UP,
		kProcedure_MOUNT_HORSE,
		kProcedure_DISMOUNT_HORSE,
		kProcedure_DO_NOTHING,
		kProcedure_UNK019,
		kProcedure_UNK01A,
		kProcedure_ACCOMPANY,
		kProcedure_USE_ITEM_AT,
		kProcedure_SANDMAN,
		kProcedure_WAIT_AMBUSH,
		kProcedure_SURFACE,					// 0x20
		kProcedure_WAIT_FOR_SPELL,
		kProcedure_CHOOSE_CAST,
		kProcedure_FLEE_NON_COMBAT,
		kProcedure_REMOVE_WORN_ITEMS,
		kProcedure_SEARCH,
		kProcedure_CLEAR_MOUNT_POSITION,
		kProcedure_SUMMON_CREATURE_DEFEND,
		kProcedure_AVOID_AREA,
		kProcedure_UNEQUIP_ARMOR,
		kProcedure_PATROL,
		kProcedure_USE_WEAPON,
		kProcedure_DIALOGUE_ACTIVATE,
		kProcedure_GUARD,
		kProcedure_SANDBOX,
		kProcedure_USE_IDLE_MARKER,
		kProcedure_TAKE_BACK_ITEM,
		kProcedure_SITTING,					// 0x30
		kProcedure_MOVEMENT_BLOCKED,
		kProcedure_CANIBAL_FEED,			// 0x32

		kProcedure_MAX						// 0x33
	};

	// In DialoguePackage, there are 0x58 virtual functions (including 0x4E from TESForm)

	uint32_t			procedureArrayIndex;	// 018 index into array of array of eProcedure terminated by 0x2C.
											//	   -1 if no procedure array exists for package type.
	uint32_t				packageFlags;		// 01C
	char				type;				// 020
	uint8_t				pad021[1];			// 021
	uint16_t				behaviorFlags;		// O22
	uint32_t				specificFlags;		// 024
	TESPackageData* packageData;		// 028
	LocationData* location;			// 02C
	TargetData* target;				// 030	target ?
	uint32_t				unk034;				// 034	idles
	PackageTime			time;				// 038
	uint32_t unk040[(0x80 - 0x40) >> 2];		// 040	040 is a tList of Condition, 7C is an Interlocked counter
		//	048 is a DWord CombatStyle,
		//	04C, 05C and 06C are the same 4 DWord struct onBegin onEnd onChange, { TESIdle* idle; EmbeddedScript* script; Topic* topic; uint32_t unk0C; }
		//	07C is a DWord

	void SetTarget(TESObjectREFR* refr);
	void SetTarget(TESForm* baseForm, uint32_t count);
	void SetTarget(uint8_t typeCode, uint32_t count);
	void SetCount(uint32_t aCount);
	void SetDistance(uint32_t aDistance) { SetCount(aDistance); }
	TargetData* GetTargetData();
	LocationData* GetLocationData();

	bool IsFlagSet(uint32_t flag);
	void SetFlag(uint32_t flag, bool bSet);

	static const char* StringForPackageType(uint32_t pkgType);
	static const char* StringForObjectCode(uint8_t objCode);
	static uint8_t ObjectCodeForString(const char* objString);
	static bool IsValidObjectCode(uint8_t o) { return o < kObjectType_Max; }
	static const char* StringForProcedureCode(eProcedure proc);
};

static_assert(sizeof(TESPackage) == 0x80);

// DialoguePackage : Only package tested and verified effectivly
class DialoguePackage : public TESPackage {
public:
	DialoguePackage();
	~DialoguePackage();

	uint32_t unk080[(0x8C - 0x80) >> 2];	// 080
	TESTopic* topic;		// 08C
	uint32_t		unk090;			// 090
	Character* speaker;		// 094
	uint8_t		unk098;			// 098
	uint8_t		unk099;			// 098
	uint8_t		unk09A;			// 098
	uint8_t		unk09B;			// 098
	TESForm* unk09C;		// 09C
	uint32_t		unk0A0;			// 0A0
	void* unk0A4;			// 0A4	list of Dialogue Item and Dialogue Response, plus current item and current response
	uint32_t		unk0A8;			// 0A8
	uint32_t		unk0AC;			// 0AC
	Character* subject;		// 0B0
	Character* target;		// 0B4
	TESForm* unk0B8;		// 0B8
	uint8_t		unk0BC;			// 0BC
	uint8_t		unk0BD;			// 0BD
	uint8_t		unk0BE;			// 0BE
	uint8_t		unk0BF;			// 0BF
	uint8_t		unk0C0;			// 0C0
	uint8_t		unk0C1;			// 0C1
	uint8_t		unk0C2;			// 0C2
	uint8_t		unk0C3;			// 0C3
	uint32_t		unk0C4;			// 0C4
	uint32_t		unk0C8;			// 0C8
	uint8_t		unk0CC;			// OCC
	uint8_t		unk0CD[3];		// OCD
};	// 0D0

typedef struct {
	float vector[3];
} ThreeFloatArray;

class FleePackage : public TESPackage {
public:
	FleePackage();
	~FleePackage();

	uint8_t			unk080;		// 080
	uint8_t			unk081;		// 081
	uint8_t			pad082[2];	// 082
	ThreeFloatArray	unk084;		// 084	is array of 3 floats, should be Pos
	float			unk090;		// 090
	uint8_t			unk094;		// 094
	uint8_t			pad095[3];	// 095
	tList<TESForm*>	list098;	// 098
	TESForm* unk0A0;	// 0A0
	TESForm* unk0A4;	// 0A4
	uint8_t			unk0A8;		// 0A8
	uint8_t			unk0A9;		// 0A9
	uint8_t			pad0AA[2];	// 0AA
};	// 0AC

class TressPassPackage : public TESPackage {
public:
	TressPassPackage();
	~TressPassPackage();

	float		warningTimer;		// 080
	uint32_t		warningLevel;		// 084
	TESForm* unk088;	// 088
	TESForm* unk08C;	// 08C
	uint32_t		crimeNumber;		// 090
	uint32_t		warning;		// 094
	uint32_t		unk098;		// 098
};	// 09C

struct SpectatorThreatInfo {
	TESForm* unk000;	// 000
	TESForm* unk004;	// 004
	uint32_t			unk008;		// 008
	uint32_t			unk00C;		// 00C	elapsed tick count
	uint32_t			unk010;		// 010
	ThreeFloatArray	unk014;		// 014	is array of 3 floats, should be Pos
	ThreeFloatArray	unk020;		// 020	is array of 3 floats, should be Rot
	uint8_t			unk02C;		// 02C
	uint8_t			unk02D;		// 02D
	uint8_t			pad[2];		// 02E
};	// 030

class SpectatorPackage : public TESPackage {
public:
	SpectatorPackage();
	~SpectatorPackage();

	uint32_t			unk080;		// 080
	uint32_t			unk084;		// 084
	uint32_t			unk088;		// 088
	uint32_t			unk08C;		// 08C
	uint8_t			unk090;		// 090
	uint8_t			pad091[3];	// 091
	ThreeFloatArray	unk094;		// 094	is array of 3 floats, should be Pos
	BSSimpleArray<SpectatorThreatInfo>	arr0A0;	// 0A0
	// There is an object containing a semaphore at B0/B4
};	// 0B4

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


class TESFollowPackageData : public TESPackageData {
public:
	TESFollowPackageData();
	~TESFollowPackageData();
	TESPackage::LocationData* endLocation;
	float	flt008;
};

// TESLevSpell (44)
class TESLevSpell;

// 194
class TESWaterForm : public TESForm {
public:
	TESWaterForm();
	~TESWaterForm();

	TESFullName				fullName;		// 018
	TESAttackDamageForm		attackDamage;	// 024
	uint32_t					unk02C[14];		// 02C
	TESTexture				noiseMap;		// 064
	uint8_t					opacity;		// 070 ANAM
	uint8_t					flags;			// 071 FNAM (0x01: causes damage, 0x02: reflective)
	uint8_t					unk072[2];		// 072
	uint32_t					unk074[2];		// 074
	TESSound* sound;			// 07C
	TESWaterForm* waterForm;		// 080
	float					visData[49];	// 084
	uint32_t					unk148[12];		// 148
	SpellItem* drinkEffect;	// 178
	uint32_t					unk17C[3];		// 17C
	uint8_t					radiation;		// 188
	uint8_t					pad189[3];		// 189
	uint32_t					unk18C[2];		// 18C
};

// A8
class BGSExplosion : public TESBoundObject {
public:
	BGSExplosion();
	~BGSExplosion();

	enum {
		kFlags_Unknown = 1,
		kFlags_AlwaysUseWorldOrientation = 2,
		kFlags_KnockDownAlways = 4,
		kFlags_KnockDownByFormula = 8,
		kFlags_IgnoreLOSCheck = 16,
		kFlags_PushSourceRefOnly = 32,
		kFlags_IgnoreImageSpaceSwap = 64,
	};

	TESFullName					fullName;			// 30
	TESModel					model;				// 3C
	TESEnchantableForm			enchantable;		// 54
	BGSPreloadable				preloadable;		// 64
	TESImageSpaceModifiableForm	imageSpaceModForm;	// 68

	TESForm* placedObj;			// 70
	float						force;				// 74
	float						damage;				// 78
	float						radius;				// 7C
	TESObjectLIGH* light;				// 80
	TESSound* sound1;			// 84
	uint32_t						explFlags;			// 88
	float						ISradius;			// 8C
	BGSImpactDataSet* impactDataSet;		// 90
	TESSound* sound2;			// 94
	float						RADlevel;			// 98
	float						dissipationTime;	// 9C
	float						RADradius;			// A0
	uint8_t						soundLevel;			// A4	0 - Loud, 1 - Normal, 2 - Silent
	uint8_t						padA5[3];			// A5

	void SetFlag(uint32_t pFlag, bool bEnable) {
		if (bEnable) explFlags |= pFlag;
		else explFlags &= ~pFlag;
	}
};

static_assert(sizeof(BGSExplosion) == 0xA8);

// B0
class TESImageSpace : public TESForm {
public:
	TESImageSpace();
	~TESImageSpace();

	float		traitValues[33];	// 18
	// 00:	HDR: Eye Adapt Speed
	// 01:	HDR: Blur Radius
	// 02:	HDR: Blur Passes
	// 03:	HDR: Emissive Mult
	// 04:	HDR: Target LUM
	// 05:	HDR: Upper LUM Clamp
	// 06:	HDR: Bright Scale
	// 07:	HDR: Bright Clamp
	// 08:	HDR: LUM Ramp No Tex
	// 09:	HDR: LUM Ramp Min
	// 10:	HDR: LUM Ramp Max
	// 11:	HDR: Sunlight Dimmer
	// 12:	HDR: Grass Dimmer
	// 13:	HDR: Tree Dimmer
	// 14:	HDR: Skin Dimmer
	// 15:	Bloom: Blur Radius
	// 16:	Bloom: Alpha Mult Interior
	// 17:	Bloom: Alpha Mult Exterior
	// 18:	Get Hit: Blur Radius
	// 19:	Get Hit: Blur Damping Contrast
	// 20:	Get Hit: Damping Contrast
	// 21:	Night Eye: Tint: Red
	// 22:	Night Eye: Tint: Green
	// 23:	Night Eye: Tint: Blue
	// 24:	Night Eye: Brightness
	// 25:	Cinematic: Saturation: Value
	// 26:	Cinematic: Contrast: Avg Lum Value
	// 27:	Cinematic: Contrast: Value
	// 28:	Cinematic: Brightness: Value
	// 29:	Cinematic: Tint: Red
	// 30:	Cinematic: Tint: Green
	// 31:	Cinematic: Tint: Blue
	// 32:	Cinematic: Tint: Value
	uint32_t		unk9C[5];			// 9C
};
static_assert(sizeof(TESImageSpace) == 0xB0);

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
};
static_assert(sizeof(TESImageSpaceModifier) == 0x730);

struct EntryPointConditions {
	TESCondition		tab1;
	TESCondition		tab2;
	TESCondition		tab3;
};

// B0
class BGSBodyPart : public BaseFormComponent {
public:
	BGSBodyPart();
	~BGSBodyPart();

	enum {
		kFlags_Severable = 1,
		kFlags_IKData = 2,
		kFlags_BipedData = 4,
		kFlags_Explodable = 8,
		kFlags_IsHead = 16,
		kFlags_Headtracking = 32,
		kFlags_Absolute = 64,
	};

	BSString			partNode;				// 04
	BSString			VATSTarget;				// 0C
	BSString			startNode;				// 14
	BSString			partName;				// 1C
	BSString			targetBone;				// 24
	TESModel			limbReplacement;		// 2C
	uint32_t				unk44[6];				// 44
	float				damageMult;				// 5C
	uint8_t				flags;					// 60
	uint8_t				pad61;					// 61
	uint8_t				healthPercent;			// 62
	uint8_t				actorValue;				// 63
	uint8_t				toHitChance;			// 64
	uint8_t				explChance;				// 65
	uint8_t				explDebrisCount;		// 66
	uint8_t				pad67;					// 67
	BGSDebris*			explDebris;			// 68
	BGSExplosion*		explExplosion;			// 6C
	float				trackingMaxAngle;		// 70
	float				explDebrisScale;		// 74
	uint8_t				sevrDebrisCount;		// 78
	uint8_t				pad79[3];				// 79
	BGSDebris*			sevrDebris;			// 7C
	BGSExplosion*		sevrExplosion;			// 80
	float				sevrDebrisScale;		// 84
	float				goreEffTranslate[3];	// 88
	float				goreEffRotation[3];		// 94
	BGSImpactDataSet*	sevrImpactDS;			// A0
	BGSImpactDataSet*	explImpactDS;			// A4
	uint8_t				sevrDecalCount;			// A8
	uint8_t				explDecalCount;			// A9
	uint8_t				padAA[2];				// AA
	float				limbRepScale;			// AC

	void SetFlag(uint32_t pFlag, bool bEnable) {
		if (bEnable) flags |= pFlag;
		else flags &= ~pFlag;
	}
};

static_assert(sizeof(BGSBodyPart) == 0xB0);

// 74
class BGSBodyPartData : public TESForm {
public:
	BGSBodyPartData();
	~BGSBodyPartData();

	enum {
		eBodyPart_Torso = 0,
		eBodyPart_Head1,
		eBodyPart_Head2,
		eBodyPart_LeftArm1,
		eBodyPart_LeftArm2,
		eBodyPart_RightArm1,
		eBodyPart_RightArm2,
		eBodyPart_LeftLeg1,
		eBodyPart_LeftLeg2,
		eBodyPart_LeftLeg3,
		eBodyPart_RightLeg1,
		eBodyPart_RightLeg2,
		eBodyPart_RightLeg3,
		eBodyPart_Brain,
		eBodyPart_Weapon,
	};

	TESModel		model;				// 018
	BGSPreloadable	preloadable;		// 030
	BGSBodyPart* bodyParts[15];		// 034
	BGSRagdoll* ragDoll;			// 070
};
static_assert(sizeof(BGSBodyPartData) == 0x74);

// BGSCameraPath (38)
class BGSCameraPath;

// 44
class BGSLightingTemplate : public TESForm {
public:
	BGSLightingTemplate();
	~BGSLightingTemplate();

	uint8_t			ambientRGB[4];			// 18
	uint8_t			directionalRGB[4];		// 1C
	uint8_t			fogRGB[4];				// 20
	float			fogNear;			// 24
	float			fogFar;				// 28
	uint32_t			directionalXY;		// 2C
	uint32_t			directionalZ;		// 30
	float			directionalFade;	// 34
	float			fogClipDist;		// 38
	float			fogPower;			// 3C
	TESObjectCELL* getValuesFrom;		// 40
};

static_assert(sizeof(BGSLightingTemplate) == 0x44);

enum EActionListForm {
	eActionListForm_AddAt = 00,
	eActionListForm_DelAt,
	eActionListForm_ChgAt,
	eActionListForm_GetAt,
	eActionListForm_Max,
};

enum EWhichListForm {
	eWhichListForm_RaceHair = 00,
	eWhichListForm_RaceEyes,
	eWhichListForm_RaceHeadPart,			// ? //
	eWhichListForm_BaseFaction,
	eWhichListForm_BaseRank,
	eWhichListForm_BasePackage,
	eWhichListForm_BaseSpellListSpell,
	eWhichListForm_BaseSpellListLevSpell,
	eWhichListForm_FactionRankName,
	eWhichListForm_FactionRankFemaleName,
	eWhichListForm_HeadParts,
	eWhichListForm_LevCreatureRef,
	eWhichListForm_LevCharacterRef,
	eWhichListForm_FormList,
	eWhichListForm_Max,
};

struct CasinoStats
{
	uint32_t casinoRefID;
	int32_t earnings;
	uint16_t earningStage;
	uint8_t gap0A[2];
};

// 170
class TESEffectShader : public TESForm {
public:
	TESEffectShader();
	~TESEffectShader();

	struct EffectShaderData {
		uint8_t flags;
		uint32_t membraneSourceBlendMode;
		uint32_t membraneBlendOp;
		uint32_t membraneZTestFunc;
		uint32_t fillTextureRGB;
		float fillTextureAlphaFadeInTime;
		float fillTextureFullAlphaTime;
		float fillTextureAlphaFadeOutTime;
		float fillTexturePersistentAlphaRatio;
		float fillTextureAlphaPulseAmpl;
		float fillTextureAlphaPulseFreq;
		float fillTextureAnimSpeedU;
		float fillTextureAnimSpeedV;
		float edgeFallOff;
		uint32_t edgeColor;
		float edgeAlphaFadeInTime;
		float edgeFullAlphaTime;
		float edgeAlphaFadeOutTime;
		float edgePersistentAlphaRatio;
		float edgeAlphaPulseAmpl;
		float edgeAlphaPulseFreq;
		float fillTextureFullAlphaRatio;
		float edgeFullAlphaRatio;
		uint32_t membraneDestBlendMode;
		uint32_t particleSourceBlendMode;
		uint32_t particleBlendOp;
		uint32_t particleZTestFunc;
		uint32_t particleDestBlendMode;
		float particleBirthRampUpTime;
		float particleBirthFullTime;
		float particleBirthRampDownTime;
		float particleBirthFullRatio;
		float particleBirthPersistRatio;
		float particleLifetime;
		float particleLifetimeVar;
		float particleInitSpeedAlongNormal;
		float particleAccelAlongNormal;
		NiPoint3 initialVelocity;
		NiPoint3 acceleration;
		float scaleKey1;
		float scaleKey2;
		float scaleKey1Time;
		float scaleKey2Time;
		uint32_t colorKey1RGB;
		uint32_t colorKey2RGB;
		uint32_t colorKey3RGB;
		float colorKey1Alpha;
		float colorKey2Alpha;
		float colorKey3Alpha;
		float colorKey1Time;
		float colorKey2Time;
		float colorKey3Time;
		float particleInitSpeedAlongNormalVar;
		float particleInitRotDeg;
		float particleInitRotDegVar;
		float particleRotSpeedDegPerSec;
		float particleRotSpeedDegPerSecVar;
		BGSDebris* addonModels;
		float holesStartTime;
		float holesEndTime;
		float holesStartVal;
		float holesEndVal;
		float edgeWidthAlphaUnits;
		uint32_t edgeColorRGB;
		float explosionWindSpeed;
		uint32_t textureCountU;
		uint32_t textureCountV;
		float addonFadeInTime;
		float addonFadeOutTime;
		float addonScaleStart;
		float addonScaleEnd;
		float addonScaleInTime;
		float addonScaleOutTime;
	} shaderData;
	TESTexture fillTexture;
	TESTexture particleShaderTexture;
	TESTexture holesTexture;
};
static_assert(sizeof(TESEffectShader) == 0x170);

extern TESForm* __fastcall GetTESForm(const TESForm* apForm);