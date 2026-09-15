#include "TESPackage.hpp"
#include "Gamebryo/NiPoint3.hpp"

#ifdef GAME
const PROCEDURE* const* const pProcedures = reinterpret_cast<PROCEDURE**>(0x11A3FF0);
const char* const* const pProcedureNames = reinterpret_cast<const char**>(0x11A3CC0);
#endif

#ifdef GAME
PACKAGE_PROCEDURE_TYPE TESPackage::GetProcedureType() const {
	return static_cast<PACKAGE_PROCEDURE_TYPE>(eProcedureType);
}

// GAME - 0x984F60
void TESPackage::SetProcedureType(PACKAGE_PROCEDURE_TYPE aeProcedure) {
	eProcedureType = aeProcedure;
}

// GAME - 0x6777B0
void TESPackage::CalculateProcedureType(TESObjectREFR* apLinkedRef) {
	ThisCall(0x6777B0, this, apLinkedRef);
}

const char* TESPackage::GetCurrentActionName(int32_t aiIndex) const {
	if (GetProcedureType() == PACKAGE_PROCEDURE_TYPE::NONE || aiIndex == -1)
		return "None";
	return GetProcedureName(GetProcedureAction(GetProcedureType(), aiIndex));
}

PROCEDURE TESPackage::GetProcedureAction(PACKAGE_PROCEDURE_TYPE aeProcedure, int32_t aiIndex) {
	return pProcedures[aeProcedure][aiIndex];
}

const char* TESPackage::GetProcedureName(PROCEDURE auiProcedure) {
	return pProcedureNames[auiProcedure];
}

// GAME - 0x67A1B0
void TESPackage::CopyAllFlags(const TESPackage* apSource) {
	ThisCall(0x67A1B0, this, apSource);
}
#endif

// GAME - 0x41CA90
PACKAGE_TYPE TESPackage::GetPackType() const {
	return static_cast<PACKAGE_TYPE>(kData.eType);
}

#pragma region Flags

const TESPackage::_PackageFlags& TESPackage::GetPackageFlags() const {
	return kData.uiPackageFlags;
}

TESPackage::_PackageFlags& TESPackage::GetPackageFlags() {
	return kData.uiPackageFlags;
}

// GAME - 0x8840D0
bool TESPackage::GetServicesEnabled() const {
	return GetPackageFlags().bOffersServices;
}

void TESPackage::SetServicesEnabled(bool abVal) {
	GetPackageFlags().bOffersServices = abVal;
}

// GAME - 0x8B1FF0
bool TESPackage::GetMustReachLocation() const {
	return GetPackageFlags().bMustReachLocation;
}

// GAME - 0x826B40
void TESPackage::SetMustReachLocation(bool abVal) {
	GetPackageFlags().bMustReachLocation = abVal;
}

// GAME - 0x67EFD0
bool TESPackage::GetMustComplete() const {
	return GetPackageFlags().bMustComplete;
}

// GAME - 0x826B90
void TESPackage::SetMustComplete(bool abVal) {
	GetPackageFlags().bMustComplete = abVal;
}

// GAME - 0x5394A0
bool TESPackage::GetLockDoorsAtStart() const {
	return GetPackageFlags().bLockDoorsAtStart;
}

void TESPackage::SetLockDoorsAtStart(bool abVal) {
	GetPackageFlags().bLockDoorsAtStart = abVal;
}

// GAME - 0x670EF0
bool TESPackage::GetLockDoorsAtEnd() const {
	return GetPackageFlags().bLockDoorsAtEnd;
}

void TESPackage::SetLockDoorsAtEnd(bool abVal) {
	GetPackageFlags().bLockDoorsAtEnd = abVal;
}

// GAME - 0x670F40
bool TESPackage::GetLockDoorsAtLocation() const {
	return GetPackageFlags().bLockDoorsAtLocation;
}

void TESPackage::SetLockDoorsAtLocation(bool abVal) {
	GetPackageFlags().bLockDoorsAtLocation = abVal;
}

// GAME - 0x670ED0
bool TESPackage::GetUnlockDoorsAtStart() const {
	return GetPackageFlags().bUnlockDoorsAtStart;
}

void TESPackage::SetUnlockDoorsAtStart(bool abVal) {
	GetPackageFlags().bUnlockDoorsAtStart = abVal;
}

// GAME - 0x670F10
bool TESPackage::GetUnlockDoorsAtEnd() const {
	return GetPackageFlags().bUnlockDoorsAtEnd;
}

void TESPackage::SetUnlockDoorsAtEnd(bool abVal) {
	GetPackageFlags().bUnlockDoorsAtEnd = abVal;
}

// GAME - 0x670F60
bool TESPackage::GetUnlockDoorsAtLocation() const {
	return GetPackageFlags().bUnlockDoorsAtLocation;
}

void TESPackage::SetUnlockDoorsAtLocation(bool abVal) {
	GetPackageFlags().bUnlockDoorsAtLocation = abVal;
}

// GAME - 0x8840F0
bool TESPackage::GetPCContinue() const {
	return GetPackageFlags().bContinueIfPCNear;
}

void TESPackage::SetPCContinue(bool abVal) {
	GetPackageFlags().bContinueIfPCNear = abVal;
}

// GAME - 0x670F90
bool TESPackage::GetOncePerDay() const {
	return GetPackageFlags().bOncePerDay;
}

void TESPackage::SetOncePerDay(bool abVal) {
	GetPackageFlags().bOncePerDay = abVal;
}

#ifdef GAME
// GAME - 0x674D40
bool TESPackage::GetIsCreated() const {
	return ThisCall<bool>(0x674D40, this);
}

// GAME - 0x674D70
void TESPackage::SetIsCreated(bool abVal) {
	ThisCall(0x674D70, this, abVal);
}
#endif

// GAME - 0x67A380
bool TESPackage::GetSelectiveFalloutBehavior() const {
	return GetPackageFlags().bSkipFalloutBehavior;
}

// GAME - 0x67A3A0
void TESPackage::SetSelectiveFalloutBehavior(bool abVal) {
	GetPackageFlags().bSkipFalloutBehavior = abVal;
}

// GAME - 0x67A480
bool TESPackage::GetAlwaysRun() const {
	return GetPackageFlags().bAlwaysRun;
}

// GAME - 0x67A4A0
void TESPackage::SetAlwaysRun(bool abVal) {
	GetPackageFlags().bAlwaysRun = abVal;
}

// GAME - 0x674DD0
bool TESPackage::GetIsScriptPackage() const {
	return GetPackageFlags().bScriptPackage;
}

// GAME - 0x674E00
void TESPackage::SetIsScriptPackage(bool abVal) {
	GetPackageFlags().bScriptPackage = abVal;
}

// GAME - 0x674E40
bool TESPackage::GetNeverRun() const {
	return GetPackageFlags().bNeverRun;
}

// GAME - 0x674E70
void TESPackage::SetNeverRun(TESObjectREFR* apRef, bool abVal) {
#ifdef GAME
	ThisCall(0x674E70, this, apRef, abVal);
#else
	GetPackageFlags().bScriptPackage = abVal;
#endif
}

// GAME - 0x8A6290
bool TESPackage::GetWaiting() const {
	return GetPackageFlags().bWaiting;
}

// GAME - 0x674F30
void TESPackage::SetWaiting(bool abVal) {
#ifdef GAME
	ThisCall(0x674F30, this, abVal);
#else
	GetPackageFlags().bWaiting = abVal;
#endif
}

// GAME - 0x67A4F0
bool TESPackage::GetAlwaysSneak() const {
	return GetPackageFlags().bAlwaysSneak;
}

// GAME - 0x67A510
void TESPackage::SetAlwaysSneak(bool abVal) {
	GetPackageFlags().bAlwaysSneak = abVal;
}

// GAME - 0x67A560
bool TESPackage::GetAllowsSwim() const {
	return GetPackageFlags().bAllowSwimming;
}

// GAME - 0x67A580
void TESPackage::SetAllowsSwim(bool abVal) {
	GetPackageFlags().bAllowSwimming = abVal;
}

// GAME - 0x67A5D0
bool TESPackage::GetAllowFalls() const {
	return GetPackageFlags().bAllowFalls;
}

// GAME - 0x67A5F0
void TESPackage::SetAllowFalls(bool abVal) {
	GetPackageFlags().bAllowFalls = abVal;
}

// GAME - 0x67A690
bool TESPackage::GetNoHeadTrack() const {
	return GetPackageFlags().bNoHeadTrack;
}

// GAME - 0x67A6B0
void TESPackage::SetNoHeadTrack(bool abVal) {
	GetPackageFlags().bNoHeadTrack = abVal;
}

// GAME - 0x441B00
bool TESPackage::GetForceUnequipWeapon() const {
	return GetPackageFlags().bForceUnequipWeapon;
}

// GAME - 0x67A640
void TESPackage::SetForceUnequipWeapon(bool abVal) {
	GetPackageFlags().bForceUnequipWeapon = abVal;
}

// GAME - 0x67A3F0
bool TESPackage::GetDefensive() const {
	return GetPackageFlags().bDefensiveCombat;
}

// GAME - 0x67A410
void TESPackage::SetDefensive(bool abVal) {
	GetPackageFlags().bDefensiveCombat = abVal;
}

// GAME - 0x67A460
bool TESPackage::GetForceDrawWeapon() const {
	return GetPackageFlags().bForceDrawWeapon;
}

// GAME - 0x671A20
void TESPackage::SetForceDrawWeapon(bool abVal) {
	GetPackageFlags().bForceDrawWeapon = abVal;
}

// GAME - 0x8DADE0
bool TESPackage::GetNoIdles() const {
	return GetPackageFlags().bNoIdleAnims;
}

void TESPackage::SetNoIdles(bool abVal) {
	GetPackageFlags().bNoIdleAnims = abVal;
}

// GAME - 0x981300
bool TESPackage::GetPretendInCombat() const {
	return GetPackageFlags().bPretendInCombat;
}

// GAME - 0x898200
void TESPackage::SetPretendInCombat(bool abVal) {
	GetPackageFlags().bPretendInCombat = abVal;
}

// GAME - 0x67A700
bool TESPackage::GetContinueDuringCombat() const {
	return GetPackageFlags().bContinueDuringCombat;
}

// GAME - 0x67A720
void TESPackage::SetContinueDuringCombat(bool abVal) {
	GetPackageFlags().bContinueDuringCombat = abVal;
}

// GAME - 0x67A770
bool TESPackage::GetCombatAlert() const {
	return !GetPackageFlags().bNoCombatAlert;
}

void TESPackage::SetCombatAlert(bool abVal) {
	GetPackageFlags().bNoCombatAlert = !abVal;
}

// GAME - 0x67A7E0
bool TESPackage::GetGuardWarnBehavior() const {
	return !GetPackageFlags().bNoWarnAttackBehavior;
}

// GAME - 0x67A800
void TESPackage::SetGuardWarnBehavior(bool abVal) {
	GetPackageFlags().bNoWarnAttackBehavior = !abVal;
}

const TESPackage::_FOBehaviorFlags& TESPackage::GetFOBehaviorFlags() const {
	return kData.usFOBehaviorFlags;
}

TESPackage::_FOBehaviorFlags& TESPackage::GetFOBehaviorFlags() {
	return kData.usFOBehaviorFlags;
}

// GAME - 0x67A850
bool TESPackage::GetFOEnableHellosToPlayer() const {
	return GetFOBehaviorFlags().bHellosToPlayer;
}

// GAME - 0x67A870
void TESPackage::SetFOEnableHellosToPlayer(bool abVal) {
	GetFOBehaviorFlags().bHellosToPlayer = abVal;
}

// GAME - 0x67A8D0
bool TESPackage::GetFOEnableRandomConversations() const {
	return GetFOBehaviorFlags().bRandomConversations;
}

// GAME - 0x67A8F0
void TESPackage::SetFOEnableRandomConversations(bool abVal) {
	GetFOBehaviorFlags().bRandomConversations = abVal;
}

// GAME - 0x67A950
bool TESPackage::GetFOEnableObserveCombatBehavior() const {
	return GetFOBehaviorFlags().bObserveCombatBehavior;
}

// GAME - 0x67A970
void TESPackage::SetFOEnableObserveCombatBehavior(bool abVal) {
	GetFOBehaviorFlags().bObserveCombatBehavior = abVal;
}

// GAME - 0x67A9D0
bool TESPackage::GetFOEnableGreetCorpseBehavior() const {
	return GetFOBehaviorFlags().bGreetCorpsesBehavior;
}

// GAME - 0x67A9F0
void TESPackage::SetFOEnableGreetCorpseBehavior(bool abVal) {
	GetFOBehaviorFlags().bGreetCorpsesBehavior = abVal;
}

// GAME - 0x67AA50
bool TESPackage::GetFOEnableReactionToPlayerActions() const {
	return GetFOBehaviorFlags().bReactionToPlayerActions;
}

// GAME - 0x67AA70
void TESPackage::SetFOEnableReactionToPlayerActions(bool abVal) {
	GetFOBehaviorFlags().bReactionToPlayerActions = abVal;
}

// GAME - 0x67AAD0
bool TESPackage::GetFOEnableFriendlyFireComments() const {
	return GetFOBehaviorFlags().bFriendlyFireComments;
}

// GAME - 0x67AAF0
void TESPackage::SetFOEnableFriendlyFireComments(bool abVal) {
	GetFOBehaviorFlags().bFriendlyFireComments = abVal;
}

// GAME - 0x67AB50
bool TESPackage::GetFOEnableAggroRadiusBehavior() const {
	return GetFOBehaviorFlags().bAggroRadiusBehavior;
}

// GAME - 0x67AB70
void TESPackage::SetFOEnableAggroRadiusBehavior(bool abVal) {
	GetFOBehaviorFlags().bAggroRadiusBehavior = abVal;
}

// GAME - 0x67ABD0
bool TESPackage::GetFOEnableIdleChatterBehavior() const {
	return GetFOBehaviorFlags().bIdleChatterBehavior;
}

// GAME - 0x67ABF0
void TESPackage::SetFOEnableIdleChatterBehavior(bool abVal) {
	GetFOBehaviorFlags().bIdleChatterBehavior = abVal;
}

// GAME - 0x67AC50
bool TESPackage::GetFOEnableAvoidRadiationBehavior() const {
	return GetFOBehaviorFlags().bAvoidRadiation;
}

// GAME - 0x67AC70
void TESPackage::SetFOEnableAvoidRadiationBehavior(bool abVal) {
	GetFOBehaviorFlags().bAvoidRadiation = abVal;
}

const TESPackage::_PackageSpecificFlags& TESPackage::GetPackageSpecificFlags() const {
	return kData.usSpecificFlags;
}

TESPackage::_PackageSpecificFlags& TESPackage::GetPackageSpecificFlags() {
	return kData.usSpecificFlags;
}

const TESPackage::_GuardPackageFlags& TESPackage::GetGuardFlags() const {
	return kData.usSpecificFlags.usGuard;
}

TESPackage::_GuardPackageFlags& TESPackage::GetGuardFlags() {
	return kData.usSpecificFlags.usGuard;
}

// GAME - 0x981320
bool TESPackage::GuardGetContinueInCombatAtTarget() const {
	return GetGuardFlags().bRemainNearTarget;
}

// GAME - 0x901C50
bool TESPackage::GuardGetContinueInCombatAtLocation() const {
	return !GetGuardFlags().bRemainNearTarget;
}

// GECK - 0x493490
void TESPackage::GuardSetContinueInCombatAtTarget(bool abVal) {
	GetGuardFlags().bRemainNearTarget = abVal;
}

// GAME - 0x674D20
bool TESPackage::GuardGetTargetIsLinkedRef() const {
	return GetGuardFlags().bTargetIsLinkedRef;
}

// GECK - 0x493470
void TESPackage::GuardSetTargetIsLinkedRef(bool abVal) {
	GetGuardFlags().bTargetIsLinkedRef = abVal;
}

const TESPackage::_SandboxPackageFlags& TESPackage::GetSandboxFlags() const {
	return kData.usSpecificFlags.usSandbox;
}

TESPackage::_SandboxPackageFlags& TESPackage::GetSandboxFlags() {
	return kData.usSpecificFlags.usSandbox;
}

// GAME - 0x9F45E0
bool TESPackage::SandboxGetAllowEating() const {
	return !GetSandboxFlags().bNoEating;
}

// GAME - 0x671AD0
// GECK - 0x4934B0
void TESPackage::SandboxSetAllowEating(bool abVal) {
	GetSandboxFlags().bNoEating = !abVal;
}

// GAME - 0x9F4600
bool TESPackage::SandboxGetAllowSleeping() const {
	return !GetSandboxFlags().bNoSleeping;
}

// GAME - 0x671B30
// GECK - 0x4934D0
void TESPackage::SandboxSetAllowSleeping(bool abVal) {
	GetSandboxFlags().bNoSleeping = !abVal;
}

// GAME - 0x901C50
bool TESPackage::SandboxGetAllowConversation() const {
	return !GetSandboxFlags().bNoConversation;
}

// GAME - 0x671B90
// GECK - 0x4934F0
void TESPackage::SandboxSetAllowConversation(bool abVal) {
	GetSandboxFlags().bNoConversation = !abVal;
}

// GAME - 0x9F54B0
bool TESPackage::SandboxGetAllowIdleMarkers() const {
	return !GetSandboxFlags().bNoIdleMarkers;
}

// GAME - 0x671BF0
// GECK - 0x493510
void TESPackage::SandboxSetAllowIdleMarkers(bool abVal) {
	GetSandboxFlags().bNoConversation = !abVal;
}

// GAME - 0x9F4620
bool TESPackage::SandboxGetAllowFurniture() const {
	return !GetSandboxFlags().bNoFurniture;
}

// GAME - 0x671C50
// GECK - 0x493530
void TESPackage::SandboxSetAllowFurniture(bool abVal) {
	GetSandboxFlags().bNoFurniture = !abVal;
}

// GAME - 0x9F5690
bool TESPackage::SandboxGetAllowWandering() const {
	return !GetSandboxFlags().bNoWandering;
}

// GAME - 0x671CB0
// GECK - 0x493550
void TESPackage::SandboxSetAllowWandering(bool abVal) {
	GetSandboxFlags().bNoWandering = !abVal;
}

// GAME - 0x673890
bool TESPackage::SandboxGetLocationIsLinkedRef() const {
	return GetSandboxFlags().bLocationIsLinkedRef;
}

// GAME - 0x671A70
void TESPackage::SandboxSetLocationIsLinkedRef(bool abVal) {
	GetSandboxFlags().bLocationIsLinkedRef = abVal;
}

const TESPackage::_UseItemPackageFlags& TESPackage::GetUseItemFlags() const {
	return kData.usSpecificFlags.usUseItem;
}

TESPackage::_UseItemPackageFlags& TESPackage::GetUseItemFlags() {
	return kData.usSpecificFlags.usUseItem;
}

// GAME - 0x674D20
bool TESPackage::UseItemGetSitDown() const {
	return GetUseItemFlags().bSitDown;
}

// GECK - 0x493470
void TESPackage::UseItemSetSitDown(bool abVal) {
	GetUseItemFlags().bSitDown = abVal;
}

const TESPackage::_AmbushPackageFlags& TESPackage::GetAmbushFlags() const {
	return kData.usSpecificFlags.usAmbush;
}

TESPackage::_AmbushPackageFlags& TESPackage::GetAmbushFlags() {
	return kData.usSpecificFlags.usAmbush;
}

// GAME - 0x8EEA80
bool TESPackage::AmbushGetHideWhileAmbushing() const {
	return GetAmbushFlags().bHide;
}

// GECK - 0x493570
void TESPackage::AmbushSetHideWhileAmbushing(bool abVal) {
	GetAmbushFlags().bHide = abVal;
}

// GAME - 0x674D20
bool TESPackage::AmbushGetLocationAtLinkedRef() const {
	return GetAmbushFlags().bLocationIsAtLinkedRef;
}

void TESPackage::AmbushSetLocationAtLinkedRef(bool abVal) {
	GetAmbushFlags().bLocationIsAtLinkedRef = abVal;
}

const TESPackage::_SearchPackageFlags& TESPackage::GetSearchFlags() const {
	return kData.usSpecificFlags.usSearch;
}

TESPackage::_SearchPackageFlags& TESPackage::GetSearchFlags() {
	return kData.usSpecificFlags.usSearch;
}

// GAME - 0x8E30E0
bool TESPackage::SearchGetAllowBuying() const {
	return GetSearchFlags().bAllowBuying;
}

void TESPackage::SearchSetAllowBuying(bool abVal) {
	GetSearchFlags().bAllowBuying = abVal;
}

// GAME - 0x8E3100
bool TESPackage::SearchGetAllowKilling() const {
	return GetSearchFlags().bAllowKilling;
}

void TESPackage::SearchSetAllowKilling(bool abVal) {
	GetSearchFlags().bAllowKilling = abVal;
}

// GAME - 0x8E3120
bool TESPackage::SearchGetAllowStealing() const {
	return GetSearchFlags().bAllowStealing;
}

void TESPackage::SearchSetAllowStealing(bool abVal) {
	GetSearchFlags().bAllowStealing = abVal;
}

#pragma endregion

// GAME - 0x55B980
PackageLocation* TESPackage::GetPackageLocation() const {
	return pPackageLocation;
}

// GAME - 0x671D30
// GECK - 0x4936B0
void TESPackage::SetPackageLocation(const PackageLocation* apLocation) {
#ifdef GAME
	ThisCall(0x671D30, this, apLocation);
#else
	ThisCall(0x4936B0, this, apLocation);
#endif
}

// GAME - 0x672DD0
// GECK - 0x493BA0
PackageLocation* TESPackage::GetPackageSecondLocation() const {
#ifdef GAME
	return ThisCall<PackageLocation*>(0x672DD0, this);
#else
	return ThisCall<PackageLocation*>(0x493BA0, this);
#endif
}

// GAME - 0x672F20
// GECK - 0x493C00
PackageLocation* TESPackage::GetPackageSearchLocation() const {
#ifdef GAME
	return ThisCall<PackageLocation*>(0x672F20, this);
#else
	return ThisCall<PackageLocation*>(0x493C00, this);
#endif
}

// GAME - 0x671D10
PackageTarget* TESPackage::GetPackageTarget() const {
	return pPackageTarget;
}

// GAME - 0x672FC0
// GECK - 0x493C50
void TESPackage::SetPackageTarget(const PackageTarget* apTarget) {
#ifdef GAME
	ThisCall(0x672FC0, this, apTarget);
#else
	ThisCall(0x493C50, this, apTarget);
#endif
}

// GAME - 0x5F36F0
BGSIdleCollection* TESPackage::GetPackageIdles() const {
	return pIdleCollection;
}

// GAME - 0x6730A0
// GECK - 0x493D10
void TESPackage::SetPackageIdles(const BGSIdleCollection* apCollection) {
#ifdef GAME
	ThisCall(0x6730A0, this, apCollection);
#else
	ThisCall(0x493D10, this, apCollection);
#endif
}

// GAME - 0x41D8A0
const PackageSchedule* TESPackage::GetPackageSchedule() const {
	return &kPackSched;
}

// GAME - 0x41D8A0
PackageSchedule* TESPackage::GetPackageSchedule() {
	return &kPackSched;
}

// GAME - 0x87EAA0
const TESCondition* TESPackage::GetPackageConditions() const {
	return &kConditions;
}

// GAME - 0x87EAA0
TESCondition* TESPackage::GetPackageConditions() {
	return &kConditions;
}

// GAME - 0x6733E0
TESCombatStyle* TESPackage::GetCombatStyle() const {
	return pCombatStyle;
}

// GAME - 0x673400
void TESPackage::SetCombatStyle(TESCombatStyle* apStyle) {
	pCombatStyle = apStyle;
}

#ifdef GAME
// GAME - 0x672760
TESTopic* TESPackage::GetDialogueTopic() const {
	return ThisCall<TESTopic*>(0x672760, this);
}

// GAME - 0x675DE0
NiPoint3 TESPackage::GetLocationCoord(Actor* apActor) const {
	return ThisCall<NiPoint3>(0x675DE0, this, apActor);
}

// GAME - 0x670B90
TESPackage* TESPackage::CreatePackage(PACKAGE_TYPE aeType) {
	return CdeclCall<TESPackage*>(0x670B90, aeType);
}
#endif