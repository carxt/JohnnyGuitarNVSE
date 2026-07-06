#include "GameObjects.h"
#include "GameRTTI.h"
#include "GameExtraData.h"
#include "GameTasks.h"
#include "GameUI.h"
#include "GameProcess.h"
#include "CommandTable.h"

#include "Bethesda/BSUtilities.hpp"
#if 0
TESForm* TESObjectREFR::GetBaseForm()
{
	TESBoundObject* baseform = nullptr;
	if (this->baseForm) {
		baseform = this->baseForm;
		if (baseform->GetCompileIndex() == 0xFF) {
			if (IS_TYPE(baseform, BGSPlaceableWater))
				return baseform->GetWaterType();

			ExtraLeveledCreature* pLevCrea = extraDataList.GetExtraData<ExtraLeveledCreature>();
			if (pLevCrea && pLevCrea->pOriginalBase)
				return pLevCrea->pOriginalBase;
		}
	}
	return baseform;
}
#endif

PlayerCharacter* PlayerCharacter::GetSingleton() {
	return *(PlayerCharacter**)0x11DEA3C;
}

NiAVObject* PlayerCharacter::Get3D(bool abFirstPerson) const {
	if (abFirstPerson)
		return playerNode;
	else if (pLoadedData)
		return pLoadedData->spSceneRoot;
	else
		return nullptr;
}

// GAME - 0x950B00
BipedAnim* PlayerCharacter::GetBiped(bool abFirstPerson) const {
	return abFirstPerson ? p1stPersonBipedAnim : pBipedAnim;
}

// GAME - 0x950A60
Animation* PlayerCharacter::GetAnimation(bool abFirstPerson) const {
	if (abFirstPerson)
		return p1stPersonAnimation;
	else if (baseProcess)
		return baseProcess->GetAnimation();
	else
		return nullptr;
}

extern bool (*Cmd_Update3D)(COMMAND_ARGS);
void __fastcall UpdateReference3D(TESObjectREFR* apReference) {
	Cmd_Update3D(nullptr, nullptr, apReference, nullptr, nullptr, nullptr, nullptr, nullptr);
}

TESCombatStyle* Actor::GetCombatStyle() 
{
	ExtraCombatStyle* xCmbStyle = GetExtraData<ExtraCombatStyle>();
	if (xCmbStyle && xCmbStyle->pCombatStyle) return xCmbStyle->pCombatStyle;
	return ((TESActorBase*)GetObjectReference())->GetCombatStyle();
}

TESActorBase* Actor::GetActorBase() {
	return (TESActorBase*)GetObjectReference();
}

TESObjectWEAP* Actor::GetEquippedWeapon() {
	return ThisCall<TESObjectWEAP*>(0x8A1710, this);
}

// GAME - 0x8B36F0
bool Actor::SetPathfindingGoal(TESObjectREFR* apTargetRef, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x8B36F0, this, apTargetRef, afTargetRadius, apAvoidNodes);
}

// GAME - 0x8B3690
bool Actor::SetPathfindingGoal(const NiPoint3& arGoalLocation, TESObjectCELL* apCell, TESWorldSpace* apWorldSpace, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x8B3690, this, &arGoalLocation, apCell, apWorldSpace, afTargetRadius, apAvoidNodes);
}

// GAME - 0x8B37C0
bool Actor::SetPathfindingGoalAndAngle(TESObjectREFR* apTargetRef, float afTargetRadius, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x8B37C0, this, apTargetRef, afTargetRadius, apAvoidNodes);
}

// GAME - 0x8B3750
bool Actor::SetPathfindingGoalAndAngle(const NiPoint3& arGoalLocation, TESObjectCELL* apCell, TESWorldSpace* apWorldSpace, float afTargetRadius, float afTargetAngle, PathingAvoidNodeArray* apAvoidNodes) {
	return ThisCall<bool>(0x8B3750, this, &arGoalLocation, apCell, apWorldSpace, afTargetRadius, afTargetAngle, apAvoidNodes);
}

void Actor::StopMoving() {
	ThisCall(0x8B3AB0, this);
}

bool Actor::IsInDialogueWithPlayer() const {
	return ThisCall<bool>(0x933840, this);
}

bool Actor::GetRespawn() const {
	return ThisCall<bool>(0x87F4A0, this);
}