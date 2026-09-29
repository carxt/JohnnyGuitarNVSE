#pragma once

#include "ProcessArray.hpp"
#include "BSSimpleList.hpp"
#include "BSSpinLock.hpp"
#include "BSTempEffect.hpp"
#include "AITaskManager.hpp"
#include "LipSyncBackgroundManager.hpp"
#include "BSSemaphore.hpp"

class Actor;
class Crime;
class MuzzleFlash;
class DialoguePackage;

class ProcessLists {
public:
	float											fSecondsPassedNoProcess;
	ProcessArray									kAllProcessArrays;
	BSSimpleList<Crime*>*							pCrimes[CRIME_TYPE::COUNT];
	BSSimpleList<NiPointer<BSTempEffect>>			kTempEffects;
	BSSimpleList<NiPointer<BSTempEffect>>			kMagicEffects;
	BSSimpleList<MuzzleFlash*>						kMuzzleFlashesToPostProcess;
	BSSimpleList<MobileObject*>						kProjectilesToPostProcess;
	BSSimpleList<MobileObject*>						kTempChangeList;
	BSSimpleList<Actor*>							kAliveActors;
	Actor*											pNearbyActors[50];
	uint32_t										uiNearbyActorCount;
	float											fPlayerActionCommentTimer;
	float											fPlayerKnockObjectCommentTimer;
	bool											bPlayerInRadiatedWater;
	bool											bPlayerInRadiationArea;
	AITaskManager									kAITaskManager;
	BSSimpleList<DialoguePackage*>					kDialogPackages;
	BSSpinLock										kNearbyActorLock;
	BSSpinLock										kUpdateLock;
	BSSimpleList<MobileObject*>*					pPrevMobileObjects;
	BSSimpleList<MobileObject*>*					pMobileObjects;
	LipSyncBackgroundManager						kLipBackgroundManager;
	bool											bRunSchedules;
	bool											bRunDetection;
	bool											bShowDetectionStats;
	Actor*											pStatDetect;
	bool											bProcessHighProcess;
	bool											bProcessLowProcess;
	bool											bProcessMidHighProcess;
	bool											bProcessMidLowProcess;
	bool											bProcessAISchedules;
	bool											bShowSubtitle;
	bool											bUpdatingLowList;
	int32_t											iNumberHighActors;
	float											fCrimeUpdateTimer;
	int32_t											iCrimeNumber;
	float											fRemoveExcessDeadTimer;
	BSSemaphore										kMovementSyncSema;

	static ProcessLists* GetSingleton();

	const ProcessArray* GetProcessArray() const;
	ProcessArray* GetProcessArray();

	bool AreHostileActorsNear(bool abInterior);

	static constexpr AddressPtr<int32_t, 0x11E0360> iGameDay;
	static constexpr AddressPtr<int32_t, 0x11A39C4> iGameMonth;
	static constexpr AddressPtr<int32_t, 0x11E035C> iGameYear;
	static constexpr AddressPtr<float, 0x11E0358> fGameHour;
};

ASSERT_SIZE(ProcessLists, 0x103E0);