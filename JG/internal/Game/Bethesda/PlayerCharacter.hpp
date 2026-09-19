#pragma once

#include "Character.hpp"
#include "BSSimpleList.hpp"
#include "TESRegion.hpp"
#include "TESSound.hpp"
#include "TeleportPath.hpp"
#include "BSSoundHandle.hpp"
#include "TESRegionList.hpp"
#include "CharacterProgression.hpp"

class AlchemyItem;
class BGSNote;
class BGSQuestObjective;
class BGSMusicType;
class bhkMouseSpringAction;
class CameraCaster;
class CombatGroup;
class DialoguePackage;
class ImageSpaceModifierInstanceDOF;
class ImageSpaceModifierInstanceDRB;
class MagicItem;
class MagicShaderHitEffect;
class MagicTarget;
class AudioMarkerInfo;
class TESCaravanCard;
class TESClass;
class TESEnchantableForm;
class TESObjectCELL;
class TESObjectREFR;
class TESObjectWEAP;
class TESQuest;
class TESReputation;
class TESTopic;
class Animation;
class BipedAnim;
class NiLight;
class TESQuestStageItem;
class TESQuestTarget;
class MapMarkerData;
class BGSPerkEntry;
class PerkRankData;
class HitCaster;
class TESRegionSound;
NiSmartPointer(NiNode);

struct MapMarkerInstance {
	MapMarkerData* pData;
	TESObjectREFR* pRef;
};

struct AchievementInstance {
	bool	bUnlocked;
	int32_t	iCurrentValue;
	bool	bTracking;
};

struct CasinoData {
	FormID	uiCasinoFormID;
	int32_t iEarnings;
	int16_t sEarningsLevel;
};

struct PlayerActionObject;

class PlayerCharacter : public Character {
public:
	PlayerCharacter();
	~PlayerCharacter();

	struct PerceivedActor {
		Actor*	pActor;
		bool	bIsHostile;
		bool	bIsUndetected; // Has LOS!
	};

	struct PositionRequest {
		TESWorldSpace*	pWorld;
		TESObjectCELL*	pInterior;
		NiPoint3		kPos;
		NiPoint3		kRot;
		bool			bResetWeather;
		void(__cdecl*	pfnArrivalFunc)(void*);
		void*			pArrivalFuncData;
		TESObjectREFR*	pFurnitureRef;
		TESObjectREFR*	pFastTravelMarker;
	};

	struct _ModifierGroup {
		enum Group {
			TEMPORARY	= 0,
			SCRIPTS		= 1,
			DAMAGE		= 2,
		};
	};
	using ModifierGroup = _ModifierGroup::Group;

	struct _GrabbingType {
		enum Type {
			NONE			= 0,
			NORMAL			= 1,
			INVENTORY_DROP	= 2,
			TELEKINESIS		= 3,
		};
	};
	using GrabbingType = _GrabbingType::Type;

	struct ALIGN1 _ControlDisablementFlags {
		enum Flags {
			NONE		= 0,
			MOVEMENT	= 1u << 0,
			LOOKING		= 1u << 1,
			PIPBOY		= 1u << 2,
			FIGHTING	= 1u << 3,
			POV_SWITCH	= 1u << 4,
			ROLL_OVER	= 1u << 5,
			SNEAKING	= 1u << 6,
			ALL			= 0xFF,
			COUNT		= 7,
		};

		bool bMovement	: 1;
		bool bLooking	: 1;
		bool bPipBoy	: 1;
		bool bFighting	: 1;
		bool bPOVSwitch : 1;
		bool bRollOver	: 1;
		bool bSneaking	: 1;
	};
	using ControlDisablementFlags = _ControlDisablementFlags::Flags;

	virtual bool							InitiateDialogue(MobileObject* apTarget, PackageLocation* apPackLocation, PackageLocation* apPackSecondLocation, bool abHeadTrack, bool abMove, bool abFlag, TESTopic* apTopic);
	virtual BSSimpleList<PerkRankData*>*	GetPerkList(bool abTeammate);

	AchievementInstance					kPlayerAchievements[3];
	PositionRequest*					pQueuedTargetLoc;
	TESObjectWEAP*						pQueuedWeaponAttach;
	float								fTimeSinceLastAmmoRegenTick;
	int8_t								cShotsSinceLastAmmoRegen;
	int32_t								iSandmanDetection;
	int32_t								iCombatPursue;
	bool								bTravelUseDoor;
	bool								bOnElevator;
	bool								bForceQuestTargetUpdate;
	DialoguePackage*					pClosestConversation;
	bool								bTransporting;
	BSSimpleList<ActiveEffect*>*		pActiveEffects;
	MagicItem*							pCurrentSpell;
	MagicTarget*						pDesiredTarget;
	CameraCaster*						pCameraCaster;
	HitCaster*							pHitCaster;
	DialoguePackage*					pAIConversationRunning;
	int32_t								iNumberofStealWarnings;
	float								fStealWarningTimer;
	int32_t								iNumberofPickpocketWarnings;
	float								fPickPocketWarningTimer;
	BSSimpleList<MagicItem*>*			pEatDrinkItems;
	BSSimpleList<TESBoundObject*>*		pQueuedWornEnchantments;
	bool								bShowQuestItemsInInventory;
	float								fTemporaryActorValueModifiers[ActorValue::Index::COUNT];
	float								fScriptActorValueModifiers[ActorValue::Index::COUNT];
	float								fHealthModifier; // C-c-c-combo breaker!
	float								fDamageActorValueModifiers[ActorValue::Index::COUNT];
	BSSimpleList<BGSNote*>				kNotes;
	ImageSpaceModifierInstanceDOF*		pIronSightsDOFInstance;
	ImageSpaceModifierInstanceDOF*		pVATSDOFInstance;
	ImageSpaceModifierInstanceDRB*		pVATSDRBInstance;
	bool								bHostileDetection;
	bool								bIsAcousticSpaceTransition;
	BSSimpleList<Actor*>				kTeammates;
	TESObjectREFR*						pLastExtDoorActivated;
	bool								bSpeaking;
	BSSimpleList<PlayerActionObject*>*	pPlayerActions;
	BSSimpleList<CasinoData*>*			pCasinoData;
	BSSimpleList<TESCaravanCard*>*		pInactiveCaravanCards;
	BSSimpleList<TESCaravanCard*>*		pActiveCaravanCards;
	uint32_t							uiCaravanCapWinnings;
	uint32_t							uiCaravanCapLosses;
	uint32_t							uiCaravanWinnings;
	uint32_t							uiCaravanLosses;
	uint32_t							uiCaravanLargestWinning;
	int32_t								iCasinoCheatLevel;
	NiPointer<bhkMouseSpringAction>		spGrabSpring;
	TESObjectREFR*						pGrabbedObject;
	GrabbingType						eGrabType;
	float								fGrabObjectWeight;
	float								fGrabDistance;
	bool								bSave3rdPerson;
	bool								b3rdPersonSaved;
	bool								b3rdPerson;
	bool								bActually3rdPerson; // Bethesda, if you are not okay, just say
	bool								bWant3rdPerson;
	bool								bTemp3rdPerson;
	bool								bTemp3rdPersonSwitchBack;
	bool								bTemp1stPerson;
	bool								bTemp1stPersonSwitchBack;
	bool								bAlwaysRun;
	bool								bAutoMove;
	int32_t								iSleepHours;
	bool								bIsSleeping;
	float								fFOV;
	float								fSecondsRunning;
	float								fSecondsSwimming;
	float								fSecondsSneaking;
	bool								bActorinSneakRange;
	bool								bCanFastTravel;
	bool								bCanWait;
	float								fWorldFOV;
	float								f1stPersonFOV;
	float								f3rdPersonFOV;
	int32_t								iNumberTraining;
	Bitfield<_ControlDisablementFlags>	ucControlsDisabled;
	bool								bBlockActivate;
	float								fBlockActivateTimer;
	TESObjectREFR*						pForceActivateRef;
	BipedAnim*							p1stPersonBipedAnim;
	Animation*							p1stPersonAnimation;
	NiAVObjectPtr						sp1stPerson3D;
	float								fEyeHeight;
	NiNodePtr							spInventoryPC;
	Animation*							pInventoryAnimation;
	MagicShaderHitEffect*				pInventoryWeaponEffect;
	BSSimpleList<TESTopic*>				kTopics;
	BSSimpleList<TESQuestStageItem*>	kQuestLog;
	TESQuest*							pActiveQuest;
	BSSimpleList<BGSQuestObjective*>	kQuestObjectives;
	BSSimpleList<TESQuestTarget*>		kQuestTargets;
	bool								bGreetingPlayer;
	float								fGreetTimer;
	int32_t								iHoursToSleep;
	int8_t								cMurder;
	int32_t								iAmountStolenSold;
	float								fSortActorDistanceTimer;
	float								fSitHeadingDelta;
	bool								bBeenAttacked;
	MagicItem*							pSelectedSpell;
	TESObjectBOOK*						pSelectedScroll;
	TESObjectREFR*						pPlayerMapMarker;
	TeleportPath						kPlayerMarkerPath;
	float								fProjectileReleaseTimer;
	int32_t								iNumAdvance;
	uint32_t							eSkillAdvance;
	TESClass*							pDefaultClass;
	TESClass*							pClassBasedOn;
	uint32_t							uiCrimeCounts[5];
	AlchemyItem*						pPendingPoison;
	bool								bChargen;
	bool								bAllowEGMCacheClear;
	bool								bTelekinesisSelected;
	TESRegion*							pOccupiedRegion;
	TESRegionList						kAllOccupiedRegions;
	BSSimpleList<TESRegionSound*>		kCurrentRegionSounds;
	BSSoundHandle						kHeartBeatSound;
	void*								pInitialStateBuffer;
	uint32_t							uiLastPlayingTimeUpdate;
	uint32_t							uiTotalPlayingTime;
	uint32_t							uiCharacterSeed;
	bool								bAiControlledToPos;
	bool								bAiControlledFromPos;
	bool								bAiControlledActivate;
	bool								bAiControlledPackage;
	bool								bInBorderContainedCell;
	bool								bReturnToLastKnownGoodPosition;
	NiPoint3							kLastKnownGoodPosition;
	TESForm*							pLastKnownGoodLocation;
	NiTPrimitiveArray<TESRegion>*		pBorderRegions;
	BGSMusicType*						pLastKnownMusicType;
	uint32_t							eDifficultyLevel;
	uint32_t							eHardcoreSetting;
	uint32_t							eKillCameraSetting;
	bool								bBeingChased;
	bool								bIsYoung;
	bool								bIsToddler;
	bool								bCanUsePowerArmor;
	BSSimpleList<MapMarkerInstance*>	kMapMarkers;
	TESWorldSpace*						pMapWorld;
	BSSimpleList<AudioMarkerInfo*>		kMusicMarkers;
	AudioMarkerInfo*					pCurrMusicMarker;
	float								fFlyCameraHeading;
	float								fFlyCameraPitch;
	NiPoint3							kFlyCameraPos;
	uint32_t							uiSelectedSpellCastSoundID;
	BSSoundHandle						kSelectedSpellCastSound;
	BSSoundHandle						kMagicFailureSounds[6];
	BSSimpleList<TESObjectREFR*>		kDroppedRefs;
	NiTMap<uint32_t, uint8_t>			kRandomDoorSpaces;
	NiPointer<NiLight>					spThirdPersonLight;
	NiPointer<NiLight>					spFirstPersonLight;
	bool								bInsufficientChargeMessageShown;
	float								fDropAngleMod;
	float								fLastDropAngleMod;
	CharacterProgression				kCharacterProgressionInfo;
	BSSimpleList<PerkRankData*>			kPerks;
	BSSimpleList<BGSPerkEntry*>			kPerkEntries[74];
	BSSimpleList<PerkRankData*>			kCompanionPerks;
	BSSimpleList<BGSPerkEntry*>			kCompanionPerkEntries[74];
	Actor*								pAutoAimActor;
	NiPoint3							kBulletAutoAim;
	NiNodePtr							spTargeted3D;
	bool								bTarget3DDistant;
	Actor*								pPlayersTargetActor;
	BSSimpleList<PerceivedActor*>*		pPerceivedActors;
	float								fMenuModeButtonTimer;
	float								fAmmoSwapButtonTimer;
	bool								bMenuModeButtonClicked;
	NiPoint3							kCamera3rdPersonShoulderOffset;
	CombatGroup*						pCombatGroup;
	uint32_t							uiTeammateCount;
	float								fCombatTimer;
	float								fYieldTimer;
	NiAVObject*							pWobbleNodes[2][12];
	NiPoint3							kCached1stPersonCameraPos;
	NiPoint3							kCachedWorldCameraPos;
	NiPointer<bhkRigidBody>				spCameraRigidBody;
	bool								bPlayerInCombat;
	bool								bAllCombatTargetsSearching;
	bool								bMegatonDestroyed;
	BSSimpleArray<ItemChange*>			kRockItLauncherAmmo;
	float								fRockItLauncherAmmoWeight;
	bool								bNightVisionOn;
	TESReputation*						pReputationUpdate;
	uint8_t								ucSloMoCameraHits;
	float								fTimeSinceLastAttack;
	float								fTimeInSlowMoCam;
	float								fKillCamCooldown;
	char								bIgnoresGTM;
	char								bTurboISM;
	float								fLastHelloTime;
	float								fCounterAttackTimer;
	bool								bCounterAttackCamera;
	bool								bHasCateyeActive;
	bool								bHasSpotterActive;
	float								fItemDetectionTimer;
	NiNode*								pIronSightNode;
	bool								bAlwaysHardcore;
	bool								bResetHardcoreTimers;
	BSSimpleArray<TESAmmo*>				kHotkeyedWeaponAmmos;
	TESQuest*							pPatch04DebugQuest;

	static constexpr AddressPtr<NiAVObject*, 0x11E07D0> p1stPersonCamera;
	static constexpr AddressPtr<NiAVObject*, 0x11E07D4> p3rdPersonCamera;
	static constexpr AddressPtr<NiAVObject*, 0x11E07D8> p1stPersonBip;

	static constexpr AddressPtr<bool, 0x11E07B8> bIsVanityMode;
	static constexpr AddressPtr<bool, 0x11E07B9> bIsAutoVanityMode;
	static constexpr AddressPtr<NiPoint3, 0x11E0B58> kVanityModePos;

	static constexpr AddressPtr<float, 0x11E0D48> fDialogZoomPercent;

	static PlayerCharacter* GetSingleton();

	NiAVObject* Get3D(bool abFirstPerson) const;

	BipedAnim* GetBiped(bool abFirstPerson) const;

	Animation* GetAnimation(bool abFirstPerson) const;

	float Get1stPersonFOV() const;

	float GetWorldFOV() const;

	bool IsPipboyActive() const;

	bool Is3rdPerson() const;
	bool IsActually3rdPerson() const;
	void ForceTemp3rdPerson(bool abResetVanity);

	bool IsVanityMode() const;

	bool IsSleepingOrResting() const;

	bool GetUnderAIControl() const;

	PerceivedActor* IsActorPerceived(Actor* apActor) const;
	void InsertPerceivedActor(Actor* apActor, bool abIsHostile, bool abIsUndetected);
	void RemovePerceivedActor(Actor* apActor);

	AudioMarkerInfo* GetCurrentMusicMarker();

	bool IsPlayerFollower(Actor* apActor);

	void SetPlayerMapMarker(NiPoint3 akLocation, TESForm* apSpace);
	void RemovePlayerMapMarker();
};

ASSERT_SIZE(PlayerCharacter, 0xE50);