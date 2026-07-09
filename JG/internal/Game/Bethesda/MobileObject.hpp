#pragma once

#include "TESObjectREFR.hpp"
#include "BaseProcess.hpp"

class CFilter;
struct PackageLocation;
class TESTopic;
class DialogueResponse;

class MobileObject : public TESObjectREFR {
public:
	MobileObject();
	~MobileObject();

	virtual bool						MoveToHigh();
	virtual bool						MoveToLow();
	virtual bool						MoveToMiddleLow();
	virtual bool						MoveToMiddleHigh();
	virtual bhkCharacterController*		Move(float afTimeDelta, NiPoint3& arDeltaMove, uint8_t abDefer);
	virtual bhkCharacterController*		Jump();
	virtual void						SetAvoidanceDisabled(bool abVal);
	virtual void						Process(float afTimeDelta);
	virtual void						ChangeProcessLevel();
	virtual void						UpdateInDialogue(float afTime, DialogueResponse* apResponse, bool);
	virtual void						UpdateAnimationAlt(float = 0.f);
	virtual bool						GetBufferedPackageEvaluation() const;
	virtual void						EvaluatePackage();
	virtual bool						IsInCombat(bool abSearching) const;
	virtual void						SetDialoguewithPlayer(bool abInDialog);
	virtual void						InitiateDialogueFromPackage(TESPackage* apPackage);
	virtual bool						InitiateDialogue(Actor* apTarget, PackageLocation* apSubjectLocation, PackageLocation* apTargetLocation, bool abHeadTrack, bool abMove, bool abInterateIndexFlag, TESTopic* apTopic, bool abTargetContinueMoving, bool abTargetMoveTowardStarter);
	virtual float						SpeakSoundFunction(const char* apSoundFile, BSSoundHandle* apSoundHandle, uint32_t aeEmotionType, uint32_t auiEmotionValue, uint32_t auiResponseLength, TESIdleForm* apSpeakerAnimation, TESIdleForm* apListenerAnimation, Actor* apListener, bool abSetEmotion, bool ab2D, bool abQueue, bool abLip, bool abForceSpeakerAnim);
	virtual void						EndDialogue();
	virtual void						SetRunOnceExtraPackage(TESPackage* apPackage, uint8_t aucDay);
	virtual bool						HasEditorLocation() const;
	virtual TESWorldSpace*				GetEditorLocationWorld() const;
	virtual TESObjectCELL*				GetEditorLocationInteriorCell() const;
	virtual NiPoint3					GetEditorLocationCoord() const;
	virtual bool						DetachCharController();
	virtual bool						RemoveCharController();
	virtual void						SetPosition(const NiPoint3& arPosition);
	virtual void						GetLinearVelocity(NiPoint3& arVelocity) const;
	virtual void						EvaluateDetection(float afDelta);
	virtual float						GetDetectionTimer() const;
	virtual void						ReduceDetectionTimer();
	virtual float						GetHeading(bool abIgnoreImmobile) const;
	virtual void						SetHeadingToRef(TESObjectREFR* apRef);
	virtual void						SetHeading(float afValue);
	virtual TESObjectREFR*				GetCurrentTarget() const;
	virtual bool						IsAtPoint(NiPoint3& arPoint, float afRadius, bool abExpandRadius, bool abAlwaysTestHeight);
	virtual int32_t						GetSpeakingEmotion() const;
	virtual void						SetSpeakingEmotion(int32_t aiEmotion);
	virtual int32_t						GetSpeakingEmotionValue() const;
	virtual void						SetSpeakingEmotionValue(int32_t aiValue);
	virtual void						SetSize(float afSize);
	virtual float						GetAcrobatics() const;
	virtual bool						IsDying() const;
	virtual bool						IsTransient() const;
	virtual void						SetDisplayGeometry(bool abShow);
	virtual void						PutCreatedPackage(TESPackage* apPackage, bool abTempPackage, bool abIsaCreatedPackage);
	virtual void						Update(float afDelta);
	virtual void						CleanUpPointersOnDisable();
	virtual MobileObject*				SetUpTalkingActivatorActor(MobileObject* apTarget, MobileObject*& apTalkingActivator);

	BaseProcess*	pCurrentProcess;
	TESObjectREFR*	pTalkingActivator;
	MobileObject*	pDialogueItemTarget;
	float			fUpdateTargetTimer;
	float			fSayToFailVoiceTimer;
	bool			bSpeakingDone;
	bool			bTalkingToPlayer;
	bool			bIgnoreChangeAnimationCall;
	bool			bSoundFileDone;
	bool			bVoiceFileDone;
	bool			bTalkingActivator;
	bool			bChangingProcess;
	bool			bDoNotRunSayToCallBack;
	int8_t			cSoundCallbackSet;
	bool			bSoundCallbackSuccess;
	bool			bUseEmotion;
	bool			bRunsInLow;

	BaseProcess* GetCurrentAIProcess() const;
	void SetCurrentAIProcess(BaseProcess* apProcess);

	TESPackage* GetCurrentPackage() const;

	PROCESS_TYPE GetCurrentProcessType() const;

	PROCESS_TYPE GetDesiredProcessLevel() const;

	float GetLastTimeProcessed() const;

	MobileObject* GetDialogueItemTarget() const;
	void SetDialogueItemTarget(MobileObject* apTarget);

	bool IsTalkingActivator() const;
	void SetTalkingActivator(bool abVal);
	
	TESObjectREFR* GetTalkingActivator() const;
	void SetTalkingActivatorRef(TESObjectREFR* apRef);

	void SetSoundCallBack(int8_t acCallback);

	void SetSoundCallBackSuccess(bool abSuccess);

	bool GetShouldUseEmotionAnimation() const;
	void SetShouldUseEmotionAnimation(bool abVal);

	bool GetRunsInLow() const;

	void UpdateTopicInfoSayOnce();

	CFilter GetCollisionFilter() const;

	bhkCharacterController* GetCharController() const;

	void SetRotation(const NiPoint3& arRotation);

	void SetChaseBip(bool abVal);

	float GetActualHeading() const;
	void ModHeading(float afModAngle);

	float GetLooking() const;
	void SetLooking(float afAngle);
	void ModLooking(float afModAngle);

	bool IsInAir() const;

	bool IsTalking() const;

	bool IsinDialogue() const;

	bool IsInDialogueWithPlayer() const;

	void SetPackageStartLocationFromCurrentLocation();
};

ASSERT_SIZE(MobileObject, 0x88);