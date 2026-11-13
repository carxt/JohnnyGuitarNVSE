#pragma once

#include "MiddleHighProcess.hpp"
#include "BSSoundHandle.hpp"
#include "DetectionState.hpp"

class NiBSBoneLODController;
class MuzzleFlash;
class DetectionEvent;
class Actor;
class bhkSimpleShapePhantom;
class DialogueItem;
class LipSynchAnim;
class MoveToMarker;
class NiBillboardNode;
class StartCombatStates;
class ActorValueCache;
class AnimIdle;
class CombatGroup;

NiSmartPointer(PathingRequest);
NiSmartPointer(ActorPathingMessageQueue);

class HighProcess : public MiddleHighProcess {
public:
	HighProcess();
	~HighProcess();

	virtual BSSimpleList<Actor*>* GetAvoidActorLists() const;

	struct HeadTracking {
		union {
			TESObjectREFR* pHeadTrackingTargets[HeadTrackType::COUNT];
			struct {
				TESObjectREFR* pTargetDefault;
				TESObjectREFR* pTargetAction;
				TESObjectREFR* pTargetCombat;
				TESObjectREFR* pTargetDialog;
				TESObjectREFR* pTargetScript;
				TESObjectREFR* pTargetProcedure;
			};
		};
		uint8_t ucHeadTrackingTargetFlags[HeadTrackType::COUNT];
	};

	struct _ActorSoundHandle {
		enum Handle {
			VOICE = 0,
			TORCH = 1,
			COUNT = 2,
		};
	};
	using ActorSoundHandle = _ActorSoundHandle::Handle;

	BSSimpleList<DetectionState*>*			pDetectedActors;
	BSSimpleList<DetectionState*>*			pDetectingActors;
	BSSimpleList<Actor*>*					pLastSpokenToActors;
	BSSimpleList<DetectionState*>*			pTheadDetectedActors;
	BSSimpleList<DetectionState*>*			pTempDetectingActors;
	bool									bEvaluateDetection;
	BSSimpleList<StartCombatStates*>		kAggroList;
	BSSimpleList<StartCombatStates*>		kGroupsToHelp;
	BSSimpleList<StartCombatStates*>		kTargetsToAdd;
	BSSimpleList<StartCombatStates*>		kSpectators;
	float									fDetectListTimer;
	float									fIdleChatterTimer;
	bool									bSayGoodByePlayer;
	bool									bProcessGreetSayTo;
	float									fAITalkToSameNPCTimer;
	TESObjectREFR*							pLastDetected;
	float									fTalkTimer;
	TESObjectREFR*							pPathLookAtTarget;
	float									fMaxAlpha;
	float									fPackageEvalTimer;
	float									fUseItemTimer;
	float									fHoldAttackTimer;
	int16_t									sShotsFired;
	int16_t									sShotsToFire;
	int16_t									sBurstsFired;
	bool									bCheckDeadTalk;
	bool									bSkippedUpdate;
	float									fCheckToTalkTimer;
	NiNode*									pUnkNode22C;
	float									fDelayTimer;
	float									fDistanceMoved;
	float									fTurnTime;
	uint32_t								cLastTurnDir;
	float									fEvaluateAcquireTimer;
	NiBSBoneLODController*					pBoneLOD;
	int32_t									iLastBoneLOD;
	int16_t									sAnimAction;
	BSAnimGroupSequence*					pAnimSequence;
	bool									bAutomaticFireAtLeastOne;
	float									fDetectionTimer;
	int16_t									sLastDetection;
	NiPoint3								kLastWeaponPos;
	TESObjectREFR*							pGreetActor;
	float									fSoundDelay;
	BSSoundHandle							kSounds[ActorSoundHandle::COUNT];
	bool									bGreetingFlag;
	float									fGreetingTimer;
	float									fIdleTimer;
	float									fDetectGreetTimer;
	float									fBreathTimer;
	bool									bHeadTrack;
	float									fVoiceTimer;
	bool									bLipQueued;
	bool									bWeaponAlertDrawn;
	float									fAwarePlayerTimer;
	TESIdleForm*							pIdleToPlay;
	NiPointer<AnimIdle>						spAnimIdleToPlay[2];
	NiPointer<KFModel>						spAnimIdleKF[2];
	bool									bDialoguewithPlayer;
	DialogueItem*							pGreetTopic;
	uint32_t								eLastSpeakingEmotion;
	Actor*									pDialogTarget;
	bool									bContinuingPackageforPC;
	bool 									bActivateAnim;
	float									fScriptPackageEndTime;
	float									fHealthBarAlphaValue;
	NiPointer<NiBillboardNode>				spHealthBarNode;
	float									fActorHealthPercentage;
	float									fHealthBarEmittanceValue;
	BSSimpleList<Actor*>					kActorsInAggroRadius;
	BSSimpleList<Actor*>					kActorsToFleeFrom;
	uint32_t								iNumberGuardsPursuing;
	bool									bStop;
	float									fReequipArmorTimer;
	bool									bUnequippedArmorToSwim;
	int32_t									iHasHealingSpell;
	int32_t									iHasHealingPotion;
	BSSimpleList<SpellItem*>*				pLeveledSpells;
	int8_t									cLastTurn;
	bool									bCurrentlyReanimating;
	float									fDetectionModifier;
	float									fDetectionModifierTimer;
	float									fLightAmount;
	float									fLightUpdateTimer;
	LipSynchAnim*							pLipSyncAnim;
	bool									bIsLoadingLipFile;
	bool									bLipFileFailed;
	MuzzleFlash*							pMuzzleFlash;
	uint32_t								uiDetectionCounter;
	DetectionEvent*							pActorsGeneratedDetectionEvent;
	bool									bFinishingCombatPackage;
	DialogueItem*							pSayToDialogueTopic;
	FadeState								eFadeState;
	float									fFadeAlpha;
	TESObjectREFR*							pTeleportFadeRef;
	MoveToMarker*							pMoveToMarker;
	HeadTracking							kHeadTracking;
	float									fHeadTrackTargetTimer;
	TESObjectREFR*							pLastTarget;
	bool									bForceRotate;
	uint32_t								ePostAnimActon;
	ActorValueCache*						pActorValueCache;
	float									fCachedActorHeight;
	uint32_t								eSpecialIdleType;
	NiPointer<bhkSimpleShapePhantom>		spShapePhantom;
	float									fDetectDoorForPathingTimer;
	float									fRadiationTimer;
	float									fHighestRadiation;
	bool									bPlantedExplosive;
	bool									bNeedTalkPlayer;
	float									fTakeBackTimer;
	BSSimpleList<PathingAvoidNodeArray*>*	pAvoidAreas;
	float									fAvoidWaitTimer;
	DialogueItem*							pSubtitleVoice;
	bool									bHiding;
	bool									bIsDoingSayTo;
	PathingRequestPtr						spMeToGoalRequest;
	PathingRequestPtr						spEscortedToGoalRequest;
	ActorPathingMessageQueuePtr				spMeToGoalMessageQueue;
	ActorPathingMessageQueuePtr				spEscortedToGoalMessageQueue;
};

class StartCombatStates {
public:
	Actor*			pTarget;
	CombatGroup*	pGroup;
	bool			bMustEntercombat;
	bool			bSendAlarm;
	bool			bForceFlee;
	bool			bFleeing;
	bool			bIgnoreDefensivePackage;
	bool			bSpectatorOfCombat;
	int32_t			iPriority;
};

class ActorValueCache {
public:
	struct Value {
		bool	bIsDirty;
		float	fValue;
	};

	Value kAVs[77];
};

ASSERT_SIZE(HighProcess, 0x46C);