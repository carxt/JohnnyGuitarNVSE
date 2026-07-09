#pragma once

#include "Gamebryo/NiRefObject.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "PathingLocation.hpp"
#include "PathingAvoidNodeArray.hpp"
#include "ActorLockData.hpp"

class TESForm;
class BGSSaveFormBuffer;
class BGSLoadFormBuffer;
class PathingAvoidNodeArray;
class DebugText;
class Actor;

NiSmartPointer(PathingRequest);

struct _PathingRequestType {
	enum Type {
		STANDARD		 = 0,
		COVER			 = 1,
		CLOSE_POINT		 = 2,
		FLEE			 = 3,
		HIDE			 = 4,
		LOS				 = 5,
		STRAIGHT_LINE	 = 6,
		OPTIMAL_LOCATION = 7,
		COVERED_MOVE	 = 8,
		COUNT			 = 9,
	};
};
using PATHING_REQUEST_TYPE = _PathingRequestType::Type;

class PathingRequest : public NiRefObject {
public:
	virtual ~PathingRequest();

	virtual void					CopyTo(PathingRequest* apTarget);			// 02
	virtual void					CheckValid();								// 03
	virtual PATHING_REQUEST_TYPE	GetType() const;							// 04
	virtual void					PrintDebugText(DebugText* apText);			// 05
	virtual void					SaveGame(BGSSaveFormBuffer* apBuffer);		// 06
	virtual void					LoadGame(BGSLoadFormBuffer* apBuffer);		// 07
	virtual void					InitLoadGame(BGSLoadFormBuffer* apBuffer);	// 08

	Actor*						pActor;
	PathingLocation				kStart;
	PathingLocation				kDest;
	ActorLockData				kActorLockData;
	float						fActorRadius;
	float						fActorHeight;
	float						fGoalZDelta;
	float						fTargetRadius;
	float						fCenterRadius;
	NiPoint3					kTargetPt;
	float						fSmoothingRandomness;
	float						fGoalAngle;
	float						fInitialPathHeading;
	PathingAvoidNodeArrayPtr	spAvoidNodeArray;
	bool						bCantOpenDoors;
	bool						bFaceTargetAtGoal;
	bool						bDrawDebugGeometry;
	bool						bAllowIncompletePath;
	bool						bSoftGoalRadius;
	bool						bCanSwim;
	bool						bCanFly;
	bool						bWaitIfPlayerWaits;
	bool						bFirstTangentUsesHeading;
	bool						bGoDirectIfPathingFails;
	bool						bTryToUseCurvedPath;
	bool						bIgnoreSmoothingIfFails;
	bool						bIgnoreLocks;
	uint32_t					iRetryCount;
	bool						bFailIfGoalOccupied;

	static constexpr AddressPtr<float, 0x119E4BC> fDefaultRadius;
};

ASSERT_SIZE(PathingRequest, 0xB0);