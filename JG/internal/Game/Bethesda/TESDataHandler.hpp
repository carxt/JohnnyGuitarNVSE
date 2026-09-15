#pragma once

#include "BSSimpleArray.hpp"
#include "BSSimpleList.hpp"
#include "TESFile.hpp"
#include "Gamebryo/NiTPrimitiveArray.hpp"
#include "Gamebryo/NiTPointerList.hpp"

using FormID = uint32_t;
class BGSAcousticSpace;
class BGSAddonNode;
class BGSBodyPartData;
class BGSCameraShot;
class BGSDebris;
class BGSDehydrationStage;
class BGSEncounterZone;
class BGSExplosion;
class BGSHeadPart;
class BGSHungerStage;
class BGSImpactData;
class BGSImpactDataSet;
class BGSLightingTemplate;
class BGSListForm;
class BGSMenuIcon;
class BGSMessage;
class BGSMusicType;
class BGSNote;
class BGSPerk;
class BGSProjectile;
class BGSRadiationStage;
class BGSRagdoll;
class BGSSleepDeprevationStage;
class BGSVoiceType;
class EnchantmentItem;
class InventoryChanges;
class MediaLocationController;
class MediaSet;
class Script;
class SpellItem;
class TESAmmoEffect;
class TESBoundObject;
class TESCaravanDeck;
class TESCasino;
class TESChallenge;
class TESClass;
class TESClimate;
class TESCombatStyle;
class TESEffectShader;
class TESEyes;
class TESFaction;
class TESFile;
class TESForm;
class TESGlobal;
class TESHair;
class TESImageSpace;
class TESImageSpaceModifier;
class TESLandTexture;
class TESLoadScreen;
class TESLoadScreenType;
class TESObjectACTI;
class TESObjectANIO;
class TESObjectCELL;
class TESObjectDOOR;
class TESObjectList;
class TESObjectMISC;
class TESObjectSTAT;
class TESObjectWEAP;
class TESPackage;
class TESQuest;
class TESRace;
class TESRecipe;
class TESRecipeCategory;
class TESRegionDataManager;
class TESRegionList;
class TESRegions;
class TESReputation;
class TESSound;
class TESTopic;
class TESTopicInfo;
class TESWaterForm;
class TESWeather;
class TESWorldSpace;

inline constexpr uint32_t HAS_SMALL_PLUGINS_FLAG	= 0x40;
inline constexpr uint32_t HAS_OVERLAY_PLUGINS_FLAG	= 0x80;

#pragma warning(disable:4624)
class CompiledFiles {
public:
	union {
		struct {
			BSSimpleArray<TESFile*> kNormalFiles;
			BSSimpleArray<TESFile*> kSmallFiles;
			BSSimpleArray<TESFile*> kOverlayFiles;
			uint32_t				padding[0xF4];
		};

		struct {
			uint32_t	uiCompiledFileCount;
			TESFile*	pFileArray[0xFF];
		};
	};

protected:
	friend class TESDataHandler;
	uint32_t __fastcall GetFileCount() const;

	TESFile* __fastcall GetFile(uint32_t auiIndex) const;

#if ESL_SUPPORT
	uint32_t __fastcall GetSmallFileCount() const;

	TESFile* __fastcall GetSmallFile(uint32_t auiIndex) const;
#endif

#if OVERLAY_SUPPORT
	uint32_t __fastcall GetOverlayFileCount() const;

	TESFile* __fastcall GetOverlayFile(uint32_t auiIndex) const;
#endif

public:
#if ESL_SUPPORT || OVERLAY_SUPPORT
	void Initialize();
#endif
};
#pragma warning(default:4624)

class TESDataHandler {
public:
	TESDataHandler();
	~TESDataHandler();

	Bitfield8								ucDLCFlags;				// 000
	TESObjectList*							pObjects;				// 004
	BSSimpleList<TESPackage*>				kPackages;				// 008
	BSSimpleList<TESWorldSpace*>			kWorldSpaces;			// 010
	BSSimpleList<TESClimate*>				kClimates;				// 019
	BSSimpleList<TESImageSpace*>			kImageSpaces;			// 020
	BSSimpleList<TESImageSpaceModifier*>	kImageSpaceMods;		// 028
	BSSimpleList<TESWeather*>				kWeathers;				// 030
	BSSimpleList<EnchantmentItem*>			kEnchantmentItems;		// 038
	BSSimpleList<SpellItem*>				kSpellItems;			// 040
	BSSimpleList<BGSHeadPart*>				kHeadParts;				// 048
	BSSimpleList<TESHair*>					kHairs;					// 050
	BSSimpleList<TESEyes*>					kEyes;					// 058
	BSSimpleList<TESRace*>					kRaces;					// 060
	BSSimpleList<BGSEncounterZone*>			kEncounterZones;		// 068
	BSSimpleList<TESLandTexture*>			kLandTextures;			// 070
	BSSimpleList<BGSCameraShot*>			kCameraShots;			// 078
	BSSimpleList<TESClass*>					kClasses;				// 080
	BSSimpleList<TESFaction*>				kFactions;				// 088
	BSSimpleList<TESReputation*>			kReputations;			// 090
	BSSimpleList<TESChallenge*>				kChallenges;			// 098
	BSSimpleList<TESRecipe*>				kRecipes;				// 0A0
	BSSimpleList<TESRecipeCategory*>		kRecipeCategories;		// 0A8
	BSSimpleList<TESAmmoEffect*>			kAmmoEffects;			// 0B0
	BSSimpleList<TESCasino*>				kCasinos;				// 0B8
	BSSimpleList<TESCaravanDeck*>			kCaravanDecks;			// 0C0
	BSSimpleList<Script*>					kScripts;				// 0C8
	BSSimpleList<TESSound*>					kSounds;				// 0D0
	BSSimpleList<BGSAcousticSpace*>			kAcousticSpaces;		// 0D8
	BSSimpleList<BGSRagdoll*>				kRagdolls;				// 0E0
	BSSimpleList<TESGlobal*>				kGlobals;				// 0E8
	BSSimpleList<BGSVoiceType*>				kVoiceTypes;			// 0F0
	BSSimpleList<BGSImpactData*>			kImpactData;			// 0F8
	BSSimpleList<BGSImpactDataSet*>			kImpactDataSets;		// 100
	BSSimpleList<TESTopic*>					kTopics;				// 108
	BSSimpleList<TESTopicInfo*>				kTopicInfos;			// 110
	BSSimpleList<TESQuest*>					kQuests;				// 118
	BSSimpleList<TESCombatStyle*>			kCombatStyles;			// 120
	BSSimpleList<TESLoadScreen*>			kLoadScreens;			// 128
	BSSimpleList<TESWaterForm*>				kWaterForms;			// 130
	BSSimpleList<TESEffectShader*>			kEffectShaders;			// 138
	BSSimpleList<BGSProjectile*>			kProjectiles;			// 140
	BSSimpleList<BGSExplosion*>				kExplosions;			// 148
	BSSimpleList<BGSRadiationStage*>		kRadiationStages;		// 150
	BSSimpleList<BGSDehydrationStage*>		kDehydrationStages;		// 158
	BSSimpleList<BGSHungerStage*>			kHungerStages;			// 160
	BSSimpleList<BGSSleepDeprevationStage*>	kSleepDepriveStages;	// 168
	BSSimpleList<BGSDebris*>				kDebris;				// 170
	BSSimpleList<BGSPerk*>					kPerks;					// 178
	BSSimpleList<BGSBodyPartData*>			kBodyPartData;			// 180
	BSSimpleList<BGSNote*>					kNotes;					// 188
	BSSimpleList<BGSListForm*>				kListForms;				// 190
	BSSimpleList<BGSMenuIcon*>				kMenuIcons;				// 198
	BSSimpleList<TESObjectANIO*>			kAnimatedObjects;		// 1A0
	BSSimpleList<BGSMessage*>				kMessages;				// 1A8
	BSSimpleList<BGSLightingTemplate*>		kLightningTemplates;	// 1B0
	BSSimpleList<BGSMusicType*>				kMusicTypes;			// 1B8
	BSSimpleList<TESLoadScreenType*>		kLoadScreenTypes;		// 1C0
	BSSimpleList<MediaSet*>					kMediaSets;				// 1C8
	BSSimpleList<MediaLocationController*>	kMediaLocControllers;	// 1D0
	TESRegionList*							pRegions;				// 1D8
	NiTPrimitiveArray<TESObjectCELL*>		kCellArray;				// 1DC
	NiTPrimitiveArray<BGSAddonNode*>		kAddonArray;			// 1EC
	NiTPointerList<TESForm*>				kBadForms;				// 1FC
	FormID									uiNextCreatedRefID;		// 208
	TESFile*								pActiveFile;			// 20C
	BSSimpleList<TESFile*>					kFiles;					// 210
	CompiledFiles							kCompiledFiles;			// 218
	bool									bMasterSave;			// 618
	bool									bSaveLoadGame;			// 619
	bool									bSaveLoad;				// 61A
	bool									bAutoSaving;			// 61B
	bool									bExportingPlugin;		// 61C
	bool									bClearingData;			// 61D
	bool									bHasDesiredFiles;		// 61E
	bool									bCheckingModels;		// 61F
	bool									bLoadingFiles;			// 620
	bool									bIsLoading;				// 621
	uint8_t									ucGameSettingsLoadState;// 622
	TESRegionDataManager*					pRegionDataManager;		// 624
	InventoryChanges*						pBarterContainer;		// 628
	InventoryChanges*						pRecipeContainer;		// 62C
	TESForm*								pSpotterEffect;			// 630
	TESForm*								pItemDetectedEffect;	// 634
	TESForm*								pCatEyeMobileEffect;	// 638
#ifdef EDITOR
	const char*								pBetaCommentPath;
#endif

	static TESDataHandler* GetSingleton();

	BSSimpleList<TESFile*>* GetFileList();
	const BSSimpleList<TESFile*>* GetFileList() const;

	TESFile* GetListFile(uint32_t auiIndex) const;
	TESFile* GetListFile(const char* apFileName) const;

	uint32_t GetCompiledFileCount() const;
	TESFile* GetCompiledFile(uint32_t auiIndex) const;
	TESFile* GetCompiledFileForFormID(uint32_t auiFormID) const;


#if ESL_SUPPORT || OVERLAY_SUPPORT
	bool SupportsSmallPugins() const { return ucDLCFlags.Get(HAS_SMALL_PLUGINS_FLAG); }
	bool SupportsOverlayPugins() const { return ucDLCFlags.Get(HAS_OVERLAY_PLUGINS_FLAG); }
	bool SupportsAllPlugins() const { return ucDLCFlags.Get(HAS_SMALL_PLUGINS_FLAG | HAS_OVERLAY_PLUGINS_FLAG) == (HAS_SMALL_PLUGINS_FLAG | HAS_OVERLAY_PLUGINS_FLAG); }
	static bool HasSmallPluginSupport() { return TESDataHandler::GetSingleton()->SupportsSmallPugins(); }
	static bool HasOverlayPluginSupport() { return TESDataHandler::GetSingleton()->SupportsOverlayPugins(); }
	static bool HasExtendedPlugins() { return TESDataHandler::GetSingleton()->ucDLCFlags.Get(HAS_SMALL_PLUGINS_FLAG | HAS_OVERLAY_PLUGINS_FLAG); }
#endif

#if ESL_SUPPORT
	uint32_t GetSmallCompiledFileCount() const;
	TESFile* GetSmallFile(uint32_t auiIndex) const;
#endif

#if OVERLAY_SUPPORT
	uint32_t GetOverlayFileCount() const;
	TESFile* GetOverlayFile(uint32_t auiIndex) const;
#endif

	TESRegionDataManager* GetRegionDataManager() const;

	bool AddFormToDataHandler(TESForm* apForm);
};

#ifdef GAME
ASSERT_SIZE(TESDataHandler, 0x63C);
#else
ASSERT_SIZE(TESDataHandler, 0x640);
#endif

#ifdef GAME
static constexpr inline AddressPtr<const BGSVoiceType*,  0x11CB298> pMaleVoice;
static constexpr inline AddressPtr<const BGSVoiceType*,  0x11CB29C> pFemaleVoice;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA220> pDoorMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA224> pMapMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA228> pAudioMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA22C> pAudioBuoyMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA230> pBoundMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA234> pPlaneMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA238> pRoomMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA23C> pPortalMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA240> pCollisionMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA244> pXMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA248> pXMarkerHeading;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA24C> pCOCMarkerHeading;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA250> pTravelMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA254> pNorthMarker;
static constexpr inline AddressPtr<const TESObjectDOOR*, 0x11CA258> pDefaultDoor;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA25C> pTempleMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA260> pHolyMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA264> pRadiationMarker;
static constexpr inline AddressPtr<const TESObjectMISC*, 0x11CA268> pLockpick;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0x11CA26C> pHorseMarker;
static constexpr inline AddressPtr<const TESWaterForm*,  0x11CA53C> pDefaultWater;
static constexpr inline AddressPtr<const TESObjectWEAP*, 0x11CA278> pDefaultUnarmedWeapon;
static constexpr inline AddressPtr<const TESObjectACTI*, 0x11CA27C> pAshPile1;
static constexpr inline AddressPtr<const TESObjectACTI*, 0x11CA280> pAshPile2;
static constexpr inline AddressPtr<const BGSExplosion*,  0x11CA284> pWaterExplosion;
static constexpr inline AddressPtr<const TESObjectWEAP*, 0x11CA288> pGasTrapDummyWeap;
#else
static constexpr inline AddressPtr<const BGSVoiceType*,  0xED7C9C> pMaleVoice;
static constexpr inline AddressPtr<const BGSVoiceType*,  0xED7CA0> pFemaleVoice;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA30> pDoorMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA34> pMapMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA38> pAudioMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA3C> pAudioBuoyMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA40> pBoundMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA44> pPlaneMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA48> pRoomMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA4C> pPortalMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA50> pCollisionMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA54> pXMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA58> pXMarkerHeading;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA5C> pCOCMarkerHeading;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA60> pTravelMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA64> pNorthMarker;
static constexpr inline AddressPtr<const TESObjectDOOR*, 0xEDDA68> pDefaultDoor;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA6C> pTempleMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA70> pHolyMarker;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA74> pRadiationMarker;
static constexpr inline AddressPtr<const TESObjectMISC*, 0xEDDA78> pLockpick;
static constexpr inline AddressPtr<const TESObjectSTAT*, 0xEDDA7C> pHorseMarker;
static constexpr inline AddressPtr<const TESWaterForm*,  0xEDDD7C> pDefaultWater;
static constexpr inline AddressPtr<const TESObjectWEAP*, 0xEDDA88> pDefaultUnarmedWeapon;
static constexpr inline AddressPtr<const TESObjectACTI*, 0xEDDA8C> pAshPile1;
static constexpr inline AddressPtr<const TESObjectACTI*, 0xEDDA90> pAshPile2;
static constexpr inline AddressPtr<const BGSExplosion*,  0xEDDA94> pWaterExplosion;
static constexpr inline AddressPtr<const TESObjectWEAP*, 0xEDDA98> pGasTrapDummyWeap;
#endif