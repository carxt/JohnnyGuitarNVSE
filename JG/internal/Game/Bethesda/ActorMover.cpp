#include "ActorMover.hpp"

// GAME - 0x9DD0A0
void ActorMover::StopMoving() {
	ThisCall(0x9DD0A0, this);
}

// GAME - 0x9DD0C0
void ActorMover::ForceStopMoving() {
	ThisCall(0x9DD0C0, this);
}

// GAME - 0x8B3B10
void ActorMover::ResumeMoving() {
	ThisCall(0x8B3B10, this);
}

// GAME - 0x9DCE20
bool ActorMover::RequestRotateActor(NiPoint3 akTargetPos, bool abForceTurn) {
	return ThisCall<bool>(0x9DCE20, this, akTargetPos, abForceTurn);
}

// GAME - 0x9DCE80
bool ActorMover::RequestRotateActor(float afRotation, bool abForceTurn) {
	return ThisCall<bool>(0x9DCE80, this, afRotation, abForceTurn);
}

// GAME - 0x9DBB60
bool ActorMover::SetGoalAndAngle(const NiPoint3& arGoalLocation, TESObjectCELL* apCell, TESWorldSpace* apWorldSpace, float afAngleToFace, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x9DBB60, this, &arGoalLocation, apCell, apWorldSpace, afAngleToFace, afTargetRadius, apAvoidNodes);
}

// GAME - 0x9DBC30
bool ActorMover::SetGoalAndAngle(TESObjectREFR* apReference, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x9DBC30, this, apReference, afTargetRadius, apAvoidNodes);
}

// GAME - 0x9DD130
uint32_t ActorMover::GetPreferredMoveModeType() const {
	return ThisCall<uint32_t>(0x9DD130, this);
}

// GAME - 0x97F2F0
bool ActorMover::DidPathingFail() const {
	return bPathingFailed;
}

// GAME - 0x9DCC50
float ActorMover::GetDistanceRemaining() const {
	return ThisCall<float>(0x9DCC50, this);
}

// GAME - 0x9DCC20
float ActorMover::GetDistanceTraveled() const {
	return ThisCall<float>(0x9DCC20, this);
}

// GAME - 0x9DCBF0
float ActorMover::GetCurrentPercent() const {
	return ThisCall<float>(0x9DCBF0, this);
}

// GAME - 0x9DCC80
NiPoint3 ActorMover::ComputeApproximateLocation(float afTimeDelta) const {
	return ThisCall<NiPoint3>(0x9DCC80, this, afTimeDelta);
}

// GAME - 0x9DCCF0
bool ActorMover::ComputePathPassesThroughPlayersArea() const {
	return ThisCall<bool>(0x9DCCF0, this);
}

// GAME - 0x9DAF80
void ActorMover::ClearCurrentData() {
	ThisCall(0x9DAF80, this);
}

// GAME - 0x9DE160
void ActorMover::SetLookAtTarget(NiPoint3 akTarget) {
	ThisCall(0x9DE160, this, akTarget);
}

// GAME - 0x9DE230
void ActorMover::ClearLookAtTarget() {
	ThisCall(0x9DE230, this);
}
