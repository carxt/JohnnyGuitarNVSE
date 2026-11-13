#pragma once

#include "BaseProcess.hpp"
#include "ModifierList.hpp"
#include "CombatTimer.hpp"

class BGSListForm;
class TESBoundObject;
class TESFaction;
class GuardActorPackageData;

class LowProcess : public BaseProcess {
public:
	LowProcess();
	~LowProcess();

	virtual void			ProcessEscort(Actor* apActor);
	virtual void			ProcessSleep(Actor* apActor);
	virtual void			ProcessEat(Actor* apActor, TESObjectREFR* apLocRef);
	virtual void			ProcessCombat(Actor* apActor);
	virtual void			ProcessAlarm(Actor* apActor);
	virtual bool			ProcessActivate(Actor* apActor, bool abIterateIndex);
	virtual void			ProcessAccompany(Actor* apActor);
	virtual void			ProcessAcquire(Actor* apActor);
	virtual void			ProcessAmbushWait(Actor* apActor);
	virtual void			ProcessUseItemAt(Actor* apActor);
	virtual void			ProcessUseWeapon(Actor* apActor);
	virtual void			ProcessChooseCast(Actor* apActor);
	virtual void			ProcessFleeNonCombat(Actor* apActor);
	virtual void			ProcessAvoidArea(Actor* apActor);
	virtual void			ProcessSandbox(Actor* apActor);
	virtual void			ProcessMovementBlocked(Actor* apActor);
	virtual void			ProcessGuard(Actor* apActor);
	virtual void			ProcessGuardStartTravelToLocation(Actor* apActor, GuardActorPackageData* apPackageData);
	virtual void			ProcessPatrol(Actor* apActor);
	virtual void			ProcessSummonCreatureDefend(Actor* apActor);
	virtual void			ProcessClearMountPosition(Actor* apActor);
	virtual void			ProcessNotify(Actor* apActor);
	virtual bool			CheckIfHasObject(Actor* apActor, uint32_t auiCount) const;
	virtual TESObjectREFR*	GetTargetForPackage(MobileObject* apOject, TESPackage* apPackage);
	virtual TESObjectREFR*	GetLocationForPackage(MobileObject* apOject, TESPackage* apPackage, bool abSecondaryLocation);
	virtual void			EvaluateOrderAcquireList(Actor* apActor);

	struct ALIGN1 _LowFlags {
		enum Flags : uint8_t {
			PACKAGE_TARGET_ACTIVATED	= 1u << 0,
			CURRENT_ACTION_COMPLETE		= 1u << 1,
			IS_AGGRESSOR				= 1u << 2,
			ALERTED						= 1u << 3,
			IS_FOLLOWER					= 1u << 4,
			PACKAGE_DONE_ONCE			= 1u << 5,
			PACKAGE_IDLE_DONE			= 1u << 6,
			LOCKED_LOCATION				= 1u << 7,
		};

		bool bPackageTargetActivated	: 1;
		bool bCurrentActionComplete		: 1;
		bool bIsAggressor				: 1;
		bool bAlerted					: 1;
		bool bIsFollower				: 1;
		bool bPackageDoneOnce			: 1;
		bool bPackageIdleDone			: 1;
		bool bLockedLocation			: 1;
	};
	using LowFlags = _LowFlags::Flags;

	Bitfield<_LowFlags>				ucLowProcessFlags;
	TESBoundObject*					pItemBeingUsed;
	CombatTimer						kCombatDelayTimer;
	const TESObjectREFR*			pTarget;
	TESObjectREFR*					pGenericLocation;
	TESObjectREFR*					pSecondLocation;
	BGSListForm*					pTargetFormList;
	int16_t							sFormListNumber;
	TESObjectREFR*					pPatrolLocation;
	int32_t							iNumberItemsActivate;
	BSSimpleList<ObjectToAcquire*>	kObjectList;
	ObjectToAcquire*				pAcquireObject;
	ObjectToAcquire*				pSavedAcquireObject;
	BSSimpleList<TESObjectREFR*>	kGenericLocations;
	BSSimpleList<ObjectToAcquire*>	kTempObjects;
	BSSimpleList<TESObjectREFR*>	kTempLocations;
	TESBoundObject*					pObjectToAcquire;
	TESBoundObject*					pObjectForLocation;
	PACKAGE_OBJECT_TYPE				ePackageObjectType;
	TESFaction*						pFactionToAcquire;
	ModifierList					kDamageModifiers;
	float							fEssentialDownTimer;
	float							fDeathTime;
	float							fTrackedDamage;
	bool							bSkippedTimeStampForPathing;

	bool FindSpecialIdletoPlay(Actor* apActor, TESBoundObject* apObject, TESObjectREFR* apRef);
};

ASSERT_SIZE(LowProcess, 0xB4);