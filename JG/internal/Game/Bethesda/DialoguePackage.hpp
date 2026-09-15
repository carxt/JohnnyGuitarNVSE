#pragma once

#include "TESPackage.hpp"
#include "DialogueItem.hpp"
#include "BSSoundHandle.hpp"

class MobileObject;
class Conversation;
class Character;

class DialoguePackage : public TESPackage {
public:
	DialoguePackage();
	~DialoguePackage();

	BSSoundHandle		kSound;
	TESTopic*			pTopic;
	float				fListenTimer;
	Actor*				pTalkingActor;
	bool				bWaitingforLipFile;
	TESForm*			pTargetLocation;
	bool				bUseIdleManager;
	Conversation*		pConversation;
	DialogueItem*		pCurrentItem;
	DialogueResponse*	pCurrentResponse;
	MobileObject*		pActor;
	MobileObject*		pTargetActor;
	MobileObject*		pTalkingActivator;
	bool				bActorHeadTrack;
	bool				bCreatedPack;
	bool				bContinueMoving;
	bool				bTargetContinueMoving;
	bool				bTargetMoveTowardStarter;
	bool				bDoNotControlTargetMovement;
	bool				bReachedAmbushLocation;
	int32_t				iEmotion;
	int32_t				iEmotionValue;
	bool				bSoundFile;

	MobileObject* GetActorStartedConversation() const;

	MobileObject* GetTargetOfConversation() const;

	MobileObject* GetTalkingActivator() const;
};

ASSERT_SIZE(DialoguePackage, 0xD0);