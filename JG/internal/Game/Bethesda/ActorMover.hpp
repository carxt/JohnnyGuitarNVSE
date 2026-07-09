#pragma once

#include "ActorPathingMessageQueue.hpp"
#include "PathingLocation.hpp"
#include "PathingRequest.hpp"
#include "PathingSolution.hpp"

class BGSLoadFormBuffer;
class ActorPathHandler;
class TESObjectREFR;
class Actor;

class ActorMover {
public:
	ActorMover();
	
	virtual				~ActorMover();
	virtual void		SetMoveModePreference(uint32_t auiFlags);
	virtual void		ClearMoveModePreference(uint32_t auiFlag);
	virtual void		ForceMoveMode(uint32_t auiFlags);
	virtual void		ClearForcedMoveMode();
	virtual void		Update(float afDelta);
	virtual void		UpdateTurnTimer(float afDelta);
	virtual uint32_t	GetPreferredMoveMode() const;
	virtual uint32_t	GetMoveMode() const;
	virtual bool		GetMoveDelta(NiPoint3& arDelta);
	virtual void		SaveGame(BGSSaveFormBuffer* apBuffer);
	virtual void		LoadGame(BGSLoadFormBuffer* apBuffer);
	virtual void		InitLoadGame(BGSLoadFormBuffer* apBuffer);
	virtual void		FinishLoadGame(BGSLoadFormBuffer* apBuffer);
	virtual void		Revert(BGSLoadFormBuffer* apBuffer);

	struct ALIGN4 _MovementFlags {
		enum Flags : uint32_t {
			// Input states
			FORWARD			= 1u << 0,
			BACKWARD		= 1u << 1,
			LEFT			= 1u << 2,
			RIGHT			= 1u << 3,
			TURN_LEFT		= 1u << 4,
			TURN_RIGHT		= 1u << 5,

			NON_CONTROLLER	= 1u << 6,

			// Movement states
			WALKING			= 1u << 8,
			RUNNING			= 1u << 9,
			SNEAKING		= 1u << 10,
			SWIMMING		= 1u << 11,
			JUMP			= 1u << 12,
			FLYING			= 1u << 13,
			FALL			= 1u << 14,
			SLIDE			= 1u << 15,

			INPUT_MASK		= 0x003F,
			MOVEMENT_MASK	= 0xFF00,
		};

		bool bForward		: 1;
		bool bBackward		: 1;
		bool bLeft			: 1;
		bool bRight			: 1;
		bool bTurnLeft		: 1;
		bool bTurnRight		: 1;

		bool bNonController : 1;

		bool 				: 1;

		bool bWalking		: 1;
		bool bRunning		: 1;
		bool bSneaking		: 1;
		bool bSwimming		: 1;
		bool bJump			: 1;
		bool bFlying		: 1;
		bool bFall			: 1;
		bool bSlide			: 1;
	};
	using MovementFlags = _MovementFlags::Flags;

	enum State {
		INVALID					= 0,
		INIT					= 1,
		WAITING					= 2,
		MOVING					= 3,
		ROTATING				= 4,
		LAST_UPDATE				= 5,
		FINISHED				= 6,
		FAILED					= 7,
		FAILED_PROCESS_UPDATE	= 8,
	};

	NiPoint3						kLookAtPoint;
	NiPoint3						kCachedMoveDelta;
	PathingRequestPtr				spCurrentRequest;			
	PathingSolutionPtr				spCurrentPath;
	ActorPathHandler*				pCurrentPathHandler;
	Actor*							pActor;							
	uint32_t						uiDetectionDoorID;				
	ActorPathingMessageQueuePtr		spMessageQueue;
	Bitfield<_MovementFlags>		uiPreferredMoveMode;
	Bitfield<_MovementFlags>		uiForcedMoveMode;
	Bitfield<_MovementFlags>		uiCachedLastValidMoveMode;
	int16_t							sPreviousNode;
	int16_t							sNextNode;
	PathingLocation					kFailedPathDestination;		
	uint32_t						eState;							
	bool							bPathingFailed;
	bool							bForceMoveMode;
	bool							bStopMovementNextUpdate;
	bool							bFaceTargetPoint;
	bool							bWaitingForPath;
	bool							bActorChangedProcessLevel;
	bool							bInDialog;							
	bool							bHaveValidDeltaThisFrame;				
	bool							bStopCurrentMoveAnim;							
	uint32_t						uiLastFailureTimeStamp;							
	uint32_t						uiFirstFailureTimeStamp;							
	uint32_t						uiContinuedFailureCount;		

	void StopMoving();
	void ForceStopMoving();
	void ResumeMoving();

	bool RequestRotateActor(NiPoint3 akTargetPos, bool abForceTurn);
	bool RequestRotateActor(float afRotation, bool abForceTurn);

	bool SetGoalAndAngle(const NiPoint3& arGoalLocation, TESObjectCELL* apCell, TESWorldSpace* apWorldSpace, float afAngleToFace, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes);
	bool SetGoalAndAngle(TESObjectREFR* apReference, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes);

	uint32_t GetPreferredMoveModeType() const;

	bool DidPathingFail() const;

	float GetDistanceRemaining() const;
	float GetDistanceTraveled() const;
	float GetCurrentPercent() const;

	NiPoint3 ComputeApproximateLocation(float afTimeDelta) const;

	bool ComputePathPassesThroughPlayersArea() const;

	void ClearCurrentData();

	void SetLookAtTarget(NiPoint3 akTarget);
	void ClearLookAtTarget();
};

using ACTOR_MOVE_MODE = ActorMover::MovementFlags;

ASSERT_SIZE(ActorMover, 0x88);