#include "Actor.hpp"
#include "TESActorBase.hpp"

// GAME - 0x4181E0
TESActorBase* Actor::GetActorBase() const {
	return static_cast<TESActorBase*>(GetObjectReference());
}

#ifdef GAME
// GAME - 0x87F9F0
uint16_t Actor::GetLevel() const {
	return ThisCall<uint16_t>(0x87F9F0, this);
}

// GAME - 0x4F8960
ACTOR_LIFE_STATE Actor::GetLifeState() const {
	return eLifeState;
}

// GAME - 0x8A1800
void Actor::SetLifeState(ACTOR_LIFE_STATE aeLifeState) {
	ThisCall(0x8A1800, this, aeLifeState);
}

// GAME - 0x8A7F80
TESCombatStyle* Actor::GetCombatStyle() const {
	return ThisCall<TESCombatStyle*>(0x8A7F80, this);
}

// GAME - 0x88C650
void Actor::QueueEquipObject(TESForm* apItem, int32_t aiCount, ExtraDataList* apList, bool abShouldApplyEnchantment, bool abNoUnequip, bool abNoMessage) {
	ThisCall(0x88C650, this, apItem, aiCount, apList, abShouldApplyEnchantment, abNoUnequip, abNoMessage);
}

// GAME - 0x88C790
void Actor::QueueUnequipObject(TESForm* apItem, int32_t aiCount, ExtraDataList* apList, bool abShouldApplyEnchantment, bool abNoUnequip, bool abNoMessage) {
	ThisCall(0x88C790, this, apItem, aiCount, apList, abShouldApplyEnchantment, abNoUnequip, abNoMessage);
}

// GAME - 0x8A7570
ANIMATION_ACTION Actor::GetAnimAction() const {
	return ThisCall<ANIMATION_ACTION>(0x8A7570, this);
}

// GAME - 0x8A73E0
void Actor::SetAnimAction(ANIMATION_ACTION aeAction, BSAnimGroupSequence* apSequence) {
	ThisCall(0x8A73E0, this, aeAction, apSequence);
}

// GAME - 0x87F4A0
bool Actor::GetRespawn() const {
	return ThisCall<bool>(0x87F4A0, this);
}

// GAME - 0x493BB0
bool Actor::IsInCombat() const {
	return bIsInCombat;
}

// GAME - 0x8A61B0
bool Actor::IsAlarmed() const {
	return ThisCall<bool>(0x8A61B0, this);
}

// GAME - 0x566950
bool Actor::IsPlayerTeammate() const {
	return bPlayerTeammate;
}

// GAME - 0x8A8870
bool Actor::IsReloading() const {
	return ThisCall<bool>(0x8A8870, this);
}

// GAME - 0x8A8840
void Actor::QueueReload() const {
	ThisCall(0x8A8840, this);
}

// GAME - 0x8A16D0
bool Actor::IsWeaponDrawn() const {
	return ThisCall<bool>(0x8A16D0, this);
}

// GAME - 0x8A6840
void Actor::SetWantWeaponDrawn(bool abDraw) {
	ThisCall(0x8A6840, this, abDraw);
}

// GAME - 0x4938E0
bool Actor::IsMoving() const {
	return (GetMoveMode() & 0xF) != 0;
}

// GAME - 0x8BBC10
bool Actor::GetIronSights() const {
	return ThisCall<bool>(0x8BBC10, this);
}

// GAME - 0x8BB650
void Actor::SetIronSights(bool abIronSights, bool abPostAnim, bool abCheckAnimBlendOut) {
	ThisCall(0x8BB650, this, abIronSights, abPostAnim, abCheckAnimBlendOut);
}

bool Actor::IsBlocking() const {
	return GetAnimAction() == 7;
}

// GAME - 0x894CC0
void Actor::SetBlock(bool abBlock) {
	ThisCall(0x894CC0, this, abBlock);
}

// GAME - 0x8B3BB0
bool Actor::IsPathingComplete() const {
	return ThisCall<bool>(0x8B3BB0, this);
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

// GAME - 0x8BB520
bool Actor::RequestRotate(NiPoint3 akPosition, bool abForceTurn) {
	return ThisCall<bool>(0x8BB520, this, akPosition, abForceTurn);
}

// GAME - 0x884EB0
float Actor::GetRunSpeed() {
	return ThisCall<float>(0x884EB0, this);
}

// GAME - 0x8C51C0
bool Actor::IsRefractive() {
	return ThisCall<bool>(0x8C51C0, this);
}

// GAME - 0x8ACE90
bool Actor::GetGhost() const {
	return ThisCall<bool>(0x8ACE90, this);
}

// GAME - 0x87F200
bool Actor::HasShadow() const {
	return ThisCall<bool>(0x87F200, this);
}

// GAME - 0x437BD0
bool Actor::GetIsUnconscious() const {
	return ThisCall<bool>(0x437BD0, this);
}

// GAME - 0x5678A0
bool Actor::IsEvil() const {
	return ThisCall<bool>(0x5678A0, this);
}

// GAME - 0x881C90
bool Actor::ShouldReset(uint32_t auiCurrentTime) const {
	return ThisCall<bool>(0x881C90, this, auiCurrentTime);
}

// GAME - 0x8846E0
uint32_t Actor::GetMoveMode() const {
	return ThisCall<uint32_t>(0x8846E0, this);
}

// GAME - 0x8A78F0
bool Actor::ShouldSkipFalloutBehavior(uint32_t auiFlag) const {
	return ThisCall<bool>(0x8A78F0, this, auiFlag);
}

// GAME - 0x8A1710
TESObjectWEAP* Actor::GetCurrentWeapon() const {
	return ThisCall<TESObjectWEAP*>(0x8A1710, this);
}

// GAME - 0x881650;
TESObjectREFR* Actor::GetPackageTarget() const {
	return ThisCall<TESObjectREFR*>(0x881650, this);
}

// GAME - 0x881680
void Actor::EndInterruptPackage(bool abNotRunOnceDialogue) {
	ThisCall(0x881680, this, abNotRunOnceDialogue);
}

// 0x893590
float Actor::GetHealthPercentage() {
	return ThisCall<float>(0x893590, this);
}

// GAME - 0x8A0D10
int32_t Actor::GetDetectionLevelAgainstActor(bool abRunFormula, Actor* apTarget, bool& arbInLOS, bool abInCombat, bool abAttacked, bool abCombat, bool* ap360LineOfSight) {
	return ThisCall<int32_t>(0x8A0D10, this, abRunFormula, apTarget, &arbInLOS, abInCombat, abAttacked, abCombat, ap360LineOfSight);
}

// GAME - 0x8BE940
float Actor::GetEyeLevel() const {
	return ThisCall<float>(0x8BE940, this);
}

// GAME - 0x8B06D0
bool Actor::GetShouldAttack(Actor* apTarget, bool a3, int32_t& a4, bool a5) {
	return ThisCall<bool>(0x8B06D0, this, apTarget, a3, &a4, a5);
}

// GAME - 0x8BC700
bool Actor::GetIsActorCombatTarget(Actor* apTarget) const {
	return ThisCall<bool>(0x8BC700, this, apTarget);
}

// GAME - 0x8BC9D0
bool Actor::CanUseWeapon(TESObjectWEAP* apWeapon, bool abAllowNonPlayable) const {
	return ThisCall<bool>(0x8BC9D0, this, apWeapon, abAllowNonPlayable);
}

// GAME - 0x8B3AB0
void Actor::StopMoving() {
	ThisCall(0x8B3AB0, this);
}


// GAME - 0x8B3AD0
void Actor::ForceStopMoving() {
	ThisCall(0x8B3AD0, this);
}

// GAME - 0x894900
bool Actor::IsDoingAttackAnimation() const {
	return ThisCall<bool>(0x894900, this);
}

// GAME - 0x8B39F0
void Actor::SetMoveMode(uint16_t ausMovementFlags) {
	ThisCall(0x8B39F0, this, ausMovementFlags);
}

// GAME - 0x8A0B10
float Actor::GetMovementSpeed() const {
	return ThisCall<float>(0x8A0B10, this);
}

// GAME - 0x8A7760
void Actor::BackUp() {
	ThisCall(0x8A7760, this);
}

// GAME - 0x8C1F80
bool Actor::DrinkPotion(AlchemyItem* apItem, ExtraDataList* apList, bool abNotPlayer) {
	return ThisCall<bool>(0x8C1F80, this, apItem, apList, abNotPlayer);
}

// GAME - 0x87EEF0
void Actor::AddDeathItems() {
	ThisCall(0x87EEF0, this);
}

// GAME - 0x891190
void Actor::UpdateWeaponHealth(bool abForce) {
	ThisCall(0x891190, this, abForce);
}

// GAME - 0x88C570
bool Actor::IsPointInCone(const NiPoint3& arPoint, float afConeSize) const {
	return ThisCall<bool>(0x88C570, this, &arPoint, afConeSize);
}

// GAME - 0x8B87A0
FIGHT_REACTION Actor::GetFactionFightReaction(Actor* apTarget, bool& abFromCrime) const {
	return ThisCall<FIGHT_REACTION>(0x8B87A0, this, apTarget, &abFromCrime);
}

// GAME - 0x8B8CA0
uint32_t Actor::IntegrateFactionLists(TESFaction** apArray, uint32_t auiArraySize, const BSSimpleList<FactionRank*>* apFactionList, const BSSimpleList<FactionRank*>* apExtraFactionList) const {
	return ThisCall<uint32_t>(0x8B8CA0, this, apArray, auiArraySize, apFactionList, apExtraFactionList);
}

// GAME - 0x88C240
bool Actor::CalculateLOS(const NiPoint3& arTargetPos, bool abUseEyeLevel, bool abSkipConeTest) {
	return ThisCall<bool>(0x88C240, this, &arTargetPos, abUseEyeLevel, abSkipConeTest);
}

// GAME - 0x88B880
bool Actor::LineOfSight(bool abRunFormula, Actor* apTarget, bool abUseEyeLevel, ACTOR_SEGMENT_IN_VIEW& aeInView, bool abFull360) {
	return ThisCall<bool>(0x88B880, this, abRunFormula, apTarget, abUseEyeLevel, &aeInView, abFull360);
}

// GAME - 0x8885E0
void Actor::UpdateAnimationMovement(Animation* apAnimation, float afDelta) {
	ThisCall(0x8885E0, this, apAnimation, afDelta);
}

// GAME - 0x897910
uint16_t Actor::GetAnimGroup(ANIM_GROUP aeGroup, ItemChange* apWeaponItem, bool abCheckHandToHand, Animation* apAnimation) {
	return ThisCall<uint16_t>(0x897910, this, aeGroup, apWeaponItem, abCheckHandToHand, apAnimation);
}

// GAME - 0x895110
void Actor::PickAnimations(float afWalkSpeed, float afTurnSpeed) {
	ThisCall(0x895110, this, afWalkSpeed, afTurnSpeed);
}

// GAME - 0x8A0C20
float Actor::GetMaxCarryWeight() const {
	return ThisCall<float>(0x8A0C20, this);
}

// GAME - 0x8AFF80
void Actor::GetViewData(NiPoint3& arViewPosition, NiPoint3& arViewDirection, bool abThirdPerson) const {
	ThisCall(0x8AFF80, this, &arViewPosition, &arViewDirection, abThirdPerson);
}

// GAME - 0x881D10
void Actor::SetLastSeenTime() {
	ThisCall(0x881D10, this);
}
#endif