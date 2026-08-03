#include "TESObjectREFR.hpp"
#include "TESActorBase.hpp"
#include "TESDataHandler.hpp"
#include "TESObjectSTAT.hpp"

// GAME - 0x7AF430
TESBoundObject* TESObjectREFR::GetObjectReference() const {
	return kData.pObjectReference;
}

// GAME - 0x575690
// GECK - 0x6415D0
void TESObjectREFR::SetObjectReference(TESBoundObject* apObject) {
#ifdef GAME
	ThisCall(0x575690, this, apObject);
#else
	ThisCall(0x6415D0, this, apObject);
#endif
}

TESBoundObject* TESObjectREFR::GetOriginalObjectReference() const {
	TESBoundObject* pOrgBase = GetExtra()->GetLevCreaOriginalBase();
	if (pOrgBase)
		return pOrgBase;
	else
		return GetObjectReference();
}

// GAME - 0x55D3B0
bool TESObjectREFR::GetIsOfType(const TESBoundObject* apObject) const {
	return ThisCall<bool>(0x55D3B0, this, apObject);
}

// Non virtual call to TESObjectREFR::GetLocationOnReference
// GAME - 0x436AA0
const NiPoint3& TESObjectREFR::GetLocationOnReferenceSimple() const {
	return kData.kPosition;
}

// GAME - 0x575830
void TESObjectREFR::SetLocationOnReference(const NiPoint3& arPos) {
#ifdef GAME
	ThisCall(0x575830, this, &arPos);
#else
	kData.kPosition = arPos;
#endif
}

// GAME - 0x430830
const NiPoint3& TESObjectREFR::GetAngleOnReference() const {
	return kData.kRotation;
}

// GAME - 0x575700
// GECK - 0x6416B0
void TESObjectREFR::SetAngleOnReference(NiPoint3 akRot) {
#ifdef GAME
	ThisCall(0x575700, this, akRot);
#else
	ThisCall(0x6416B0, this, akRot);
#endif
}

// GAME - 0x56FA00
// GECK - 0x63E960
NiMatrix3 TESObjectREFR::GetOrientation() const {
#ifdef GAME
	return ThisCall<NiMatrix3>(0x56FA00, this);
#else
	return ThisCall<NiMatrix3>(0x63E960, this);
#endif
}

// GAME - 0x56FA90
bool TESObjectREFR::SetOrientation(const NiMatrix3& arRot) {
#ifdef GAME
	return ThisCall<bool>(0x56FA90, this, &arRot);
#else
	return arRot.ToEulerAnglesXYZ(kData.kRotation.x, kData.kRotation.y, kData.kRotation.z);
#endif
}

// GAME - 0x598040
float TESObjectREFR::GetRawScale() const {
	return fRefScale;
}

// GAME - 0x567400
// GECK - 0x63DD40
float TESObjectREFR::GetScale() const {
#ifdef GAME
	return ThisCall<float>(0x567400, this);
#else
	return ThisCall<float>(0x63DD40, this);
#endif
}

// GAME - 0x567490
// GECK - 0x642910
void TESObjectREFR::SetScale(float afScale) {
#ifdef GAME
	ThisCall(0x567490, this, afScale);
#else
	ThisCall(0x642910, this, afScale);
#endif
}

// GAME - 0x8D6F30
TESObjectCELL* TESObjectREFR::GetParentCell() const {
	return pParentCell;
}

// GAME - 0x575D10
// GECK - 0x641890
TESObjectCELL* TESObjectREFR::GetInterior() const {
#ifdef GAME
	return ThisCall<TESObjectCELL*>(0x575D10, this);
#else
	return ThisCall<TESObjectCELL*>(0x641890, this);
#endif
}

// GAME - 0x575D70
// GECK - 0x6418D0
TESWorldSpace* TESObjectREFR::GetWorldSpace() const {
#ifdef GAME
	return ThisCall<TESWorldSpace*>(0x575D70, this);
#else
	return ThisCall<TESWorldSpace*>(0x6418D0, this);
#endif
}

// GAME - 0x575CA0
// GECK - 0x641860
TESForm* TESObjectREFR::GetSpace() const {
#ifdef GAME
	return ThisCall<TESForm*>(0x575CA0, this);
#else
	return ThisCall<TESForm*>(0x641860, this);
#endif
}

// GAME - 0x5D43C0
ExtraDataList* TESObjectREFR::GetExtra() {
	return &kExtraList;
}

// GAME - 0x5D43C0
const ExtraDataList* TESObjectREFR::GetExtra() const {
	return &kExtraList;
}

// GAME - 0x527080
BSExtraData* TESObjectREFR::GetExtraData(uint8_t aucType) const {
#ifdef GAME
	return ThisCall<BSExtraData*>(0x527080, this, aucType);
#else
	return GetExtra()->GetExtraData(aucType);
#endif
}

bool TESObjectREFR::HasExtra(uint8_t aucType) const {
	return kExtraList.HasExtra(aucType);
}

// GAME - 0x57B0A0
float TESObjectREFR::GetRelevantWaterHeight() const {
	return ThisCall<float>(0x57B0A0, this);
}

// GAME - 0x558C30
TESObjectREFR* TESObjectREFR::GetCurrentWaterObject() const {
	return ThisCall<TESObjectREFR*>(0x558C30, this);
}

// Non virtual call to Get3D. Game uses it quite often
// GAME - 0x43FCD0
// GECK - 0x645930
NiAVObject* TESObjectREFR::Get3DSimple() const {
#ifdef GAME
	return ThisCall<NiAVObject*>(0x43FCD0, this);
#else
	return ThisCall<NiAVObject*>(0x645930, this);
#endif
}

#ifdef GAME
NiAVObject* TESObjectREFR::Get3DVerySimple() const {
	return pLoadedData ? pLoadedData->spSceneRoot : nullptr;
}
#endif

// GAME - 0x570F70
// GECK - 0x64C030
void TESObjectREFR::Set3DSimple(NiAVObject* apScene) {
#ifdef GAME
	ThisCall(0x570F70, this, apScene);
#else
	ThisCall(0x64C030, this, apScene);
#endif
}

// GAME - 0x571080
// GECK - 0x645B80
void TESObjectREFR::Set3DVerySimple(NiAVObject* apScene) {
#ifdef GAME
	ThisCall(0x571080, this, apScene);
#else
	ThisCall(0x645B80, this, apScene);
#endif
}

// GAME - 0x565450
bool TESObjectREFR::GetPersistFlagValue() const {
	return uiFormFlags.Get(FormFlags::PERSISTENT);
}

// GAME - 0x565260
// GECK - 0x642660
bool TESObjectREFR::MustRefPersist() const {
#ifdef GAME
	return ThisCall<bool>(0x565260, this);
#else
	return ThisCall<bool>(0x642660, this);
#endif
}

// GAME - 0x5653D0
// GECK - 0x4052F0
bool TESObjectREFR::GetRefPersists() const {
#ifdef GAME
	return ThisCall<bool>(0x5653D0, this);
#else
	return ThisCall<bool>(0x4052F0, this);
#endif
}

// GAME - 0x565480
// GECK - 0x63DC10
void TESObjectREFR::SetRefPersists(bool abPersists) {
#ifdef GAME
	ThisCall(0x565480, this, abPersists);
#else
	ThisCall(0x63DC10, this, abPersists);
#endif
}

// GAME - 0x55D520
const char* TESObjectREFR::GetFullName() const {
#ifdef GAME
	return ThisCall<const char*>(0x55D520, this); // Hooked by JIP to allow alt names
#else
	return TESFullName::GetFullName(GetObjectReference());
#endif
}

#ifdef GAME
// GAME - 0x562020
void TESObjectREFR::Update3DPosition() {
	ThisCall(0x562020, this);
}
#endif

// GAME - 0x5710C0
// GECK - 0x650F00
void TESObjectREFR::ReplaceModel() {
#ifdef GAME
	ThisCall(0x5710C0, this);
#else
	ThisCall(0x650F00, this);
#endif
}

// GAME - 0x564E60
// GECK - 0x63D970
bool TESObjectREFR::GetVisibleDistant() const {
#ifdef GAME
	return ThisCall<bool>(0x564E60, this);
#else
	return ThisCall<bool>(0x63D970, this);
#endif
}

// GAME - 0x564EB0
void TESObjectREFR::SetVisibleDistant(bool abVal) {
	uiFormFlags.Set(FormFlags::VISIBLE_DISTANT, abVal);
}


// GAME - 0x5651E0
bool TESObjectREFR::HasTemp3D() const {
	return uiFormFlags.IsSet(FormFlags::HAS_TEMP_3D);
}

// GAME - 0x565210
void TESObjectREFR::SetHasTemp3D(bool abVal) {
	uiFormFlags.Set(FormFlags::HAS_TEMP_3D, abVal);
}

// GAME - 0x572350
// GECK - 0x63ED90
bool TESObjectREFR::Is3DCritical() const {
#ifdef GAME
	return ThisCall<bool>(0x572350, this);
#else
	return ThisCall<bool>(0x63ED90, this);
#endif
}

// GAME - 0x56B250
bool TESObjectREFR::Is3DHighPriority() const {
	return ThisCall<bool>(0x56B250, this);
}

// GAME - 0x444ED0
// GECK - 0x40E380
bool TESObjectREFR::IsMarker() const {
#ifdef GAME
	return ThisCall<bool>(0x444ED0, this);
#else
	return ThisCall<bool>(0x40E380, this);
#endif
}

// GAME - 0x439F90
// GECK - 0x4BA240
bool TESObjectREFR::IsMultiBoundRef() const {
#ifdef GAME
	return ThisCall<bool>(0x439F90, this);
#else
	return ThisCall<bool>(0x4BA240, this);
#endif
}

// GAME - 0x54A0CC - inlined
bool TESObjectREFR::IsPortalOrRoomMarker() const {
	return GetObjectReference() == pPortalMarker || GetObjectReference() == pRoomMarker;
}

// GAME - 0x557204 - inlined
bool TESObjectREFR::IsBoundOrRoomMarker() const {
	return GetObjectReference() == pPortalMarker || GetObjectReference() == pBoundMarker;
}

bool TESObjectREFR::IsPlane() const {
	return GetObjectReference() == pPlaneMarker;
}

bool TESObjectREFR::IsMapMarker() const {
	return GetObjectReference() == pMapMarker;
}

// GAME - 0x568680
// GECK - 0x63DEE0
bool TESObjectREFR::IsFurniture() const {
#ifdef GAME
	return ThisCall<bool>(0x568680, this);
#else
	return ThisCall<bool>(0x63DEE0, this);
#endif
}

// GAME - 0x56AF40
bool TESObjectREFR::IsLeveledCreature() const {
	return ThisCall<bool>(0x56AF40, this);
}

// GAME - 0x57B500
bool TESObjectREFR::GetIgnoredBySandbox() const {
	return ThisCall<bool>(0x57B500, this);
}

void TESObjectREFR::SetIgnoredBySandbox(bool abVal) {
	GetExtra()->SetIgnoredBySandbox(abVal);
}

// GAME - 0x564F00
// GECK - 0x63DA90
bool TESObjectREFR::GetIsImposter() const {
#ifdef GAME
	return ThisCall<bool>(0x564F00, this);
#else
	return ThisCall<bool>(0x63DA90, this);
#endif
}

// GAME - 0x564F40
// GECK - 0x63DAB0
void TESObjectREFR::SetIsImposter(bool abVal) {
#ifdef GAME
	ThisCall(0x564F40, this, abVal);
#else
	ThisCall(0x63DAB0, this, abVal);
#endif
}

// GAME - 0x579690
bool TESObjectREFR::IsCrimeToActivate() const {
	return ThisCall<bool>(0x579690, this);
}

// GAME - 0x5678A0
bool TESObjectREFR::IsPartofEvilFaction() const {
	return ThisCall<bool>(0x5678A0, this);
}

// GAME - 0x57B790
bool TESObjectREFR::IsCellLoaded() const {
	return ThisCall<bool>(0x57B790, this);
}

#ifdef GAME
// GAME - 0x572C80
bool TESObjectREFR::CanBeMoved() const {
	return ThisCall<bool>(0x572C80, this);
}
#endif

// GAME - 0x571600
// GECK - N/A
float TESObjectREFR::GetModelBoundSize() const {
#ifdef GAME
	return ThisCall<float>(0x571600, this);
#else
	if (!GetObjectReference())
		return 0.f;

	return GetObjectReference()->GetBoundSize();
#endif
}

// GAME - 0x568CB0
// GECK - 0x63E080
float TESObjectREFR::GetRadius() {
#ifdef GAME
	return ThisCall<float>(0x568CB0, this);
#else
	return ThisCall<float>(0x63E080, this);
#endif
}

// GAME - 0x5715D0
// GECK - 0x64C0C0
const char* TESObjectREFR::GetModel() const {
#ifdef GAME
	return ThisCall<const char*>(0x5715D0, this);
#else
	return ThisCall<const char*>(0x64C0C0, this);
#endif
}

// GAME - 0x571630
// GECK - 0x645C90
TESModel* TESObjectREFR::GetTESModel() const {
#ifdef GAME
	return ThisCall<TESModel*>(0x571630, this);
#else
	return ThisCall<TESModel*>(0x645C90, this);
#endif
}

#ifdef GAME
// GAME - 0x5723B0
float TESObjectREFR::GetDistanceFromReference(TESObjectREFR* apTarget, bool abDisabled, bool abSharedSpace) const {
	return ThisCall<float>(0x5723B0, this, apTarget, abDisabled, abSharedSpace);
}
#endif

// GAME - 0x572380
float TESObjectREFR::GetDistanceFromPoint(const NiPoint3& arPoint) const {
	return (arPoint - kData.kPosition).Length();
}

// GAME - 0x57B4B0
// GECK - 0x641B50
bool TESObjectREFR::GetIsHiddenDoor() const {
#ifdef GAME
	return ThisCall<bool>(0x57B4B0, this);
#else
	return ThisCall<bool>(0x641B50, this);
#endif
}

void TESObjectREFR::SetIsHiddenDoor(bool abVal) {
	if (GetObjectReference() && GetObjectReference()->GetFormType() == FORM_TYPE::TESObjectDOOR) {
		uiFormFlags.Set(FormFlags::HIDDEN_DOOR, abVal);
	}
}

// GAME - 0x564D80
bool TESObjectREFR::GetTargeted() const {
	return uiFormFlags.Get(FormFlags::TARGETED);
}

// GAME - 0x564DB0
void TESObjectREFR::SetTargeted(bool abVal) {
	uiFormFlags.Set(FormFlags::TARGETED, abVal);
}

// GAME - 0x573090
bool TESObjectREFR::GetDismembered(BODY_PART_TYPE aeLimb) {
	return ThisCall<bool>(0x573090, this, aeLimb);
}

// GAME - 0x55D310
// GECK - 0x63D740
TESContainer* TESObjectREFR::HasContainer() const {
#ifdef GAME
	return ThisCall<TESContainer*>(0x55D310, this);
#else
	return ThisCall<TESContainer*>(0x63D740, this);
#endif
}

// GAME - 0x569B80
// GECK - 0x63E6D0
TESObjectREFR* TESObjectREFR::GetLinkedRef() const {
#ifdef GAME
	return ThisCall<TESObjectREFR*>(0x569B80, this);
#else
	return ThisCall<TESObjectREFR*>(0x63E6D0, this);
#endif
}

// GAME - 0x56A250
bool TESObjectREFR::HasActivateRefChildren() const {
	return ThisCall<bool>(0x56A250, this);
}

// GAME - 0x56B020
void TESObjectREFR::SetLeveledCreature(TESActorBase* apOriginalBase, TESActorBase* apTemplate) {
	ThisCall(0x56B020, this, apOriginalBase, apTemplate);
}

// GAME - 0x56AFC0
// GECK - 0x63E720
bool TESObjectREFR::HasLeveledCreatureCalced() const {
#ifdef GAME
	return ThisCall<bool>(0x56AFC0, this);
#else
	return ThisCall<bool>(0x63E720, this);
#endif
}

// GAME - 0x567E10
uint32_t TESObjectREFR::GetCalcLevel(bool abAllowShift) const {
	return ThisCall<uint32_t>(0x567E10, this, abAllowShift);
}

// GAME - 0x5728C0
// GECK - 0x6473D0
void TESObjectREFR::AddLight(bool abMagic) {
#ifdef GAME
	ThisCall(0x5728C0, this, abMagic);
#else
	ThisCall(0x6473D0, this, abMagic);
#endif
}

// GAME - 0x5729E0
// GECK - 0x647480
void TESObjectREFR::RemoveLight(bool abMagic) {
#ifdef GAME
	ThisCall(0x5729E0, this, abMagic);
#else
	ThisCall(0x647480, this, abMagic);
#endif
}

// GAME - 0x568AD0
// GECK - 0x63E000
float TESObjectREFR::GetHealth() const {
#ifdef GAME
	return ThisCall<float>(0x568AD0, this);
#else
	return ThisCall<float>(0x63E000, this);
#endif
}

// GAME - 0x553BB0
bool TESObjectREFR::HasRandomSound() const {
	return ThisCall<bool>(0x553BB0, this);
}

// GAME - 0x57A2F0
bool TESObjectREFR::CanHaveSound() const {
	return ThisCall<bool>(0x57A2F0, this);
}

// GAME - 0x577DE0
bool TESObjectREFR::HasQuestObject() const {
	return ThisCall<bool>(0x577DE0, this);
}

// GAME - 0x568260
bool TESObjectREFR::HasFreeMarker(bool abIgnoreReservations) const {
	return ThisCall<bool>(0x568260, this, abIgnoreReservations);
}

// GAME - 0x5785E0
bool TESObjectREFR::IsAnOwner(Actor* apActor, bool abCheckFaction) const {
	return ThisCall<bool>(0x5785E0, this, apActor, abCheckFaction);
}

// GAME - 0x578790
bool TESObjectREFR::IsOwnerEvil(TESForm* apOwner) const {
	return ThisCall<bool>(0x578790, this, apOwner);
}

// GAME - 0x567770
TESForm* TESObjectREFR::GetMyOwner() const {
	return ThisCall<TESForm*>(0x567770, this);
}

// GAME - 0x567790
// GECK - 0x642BC0
TESForm* TESObjectREFR::GetOwner() const {
#ifdef GAME
	return ThisCall<TESForm*>(0x567790, this);
#else
	return ThisCall<TESForm*>(0x642BC0, this);
#endif
}

// GAME - 0x56AE60
bool TESObjectREFR::GetRespawn() const {
	return ThisCall<bool>(0x56AE60, this);
}

// GAME - 0x569580
// GECK - 0x63E630
TESForm* TESObjectREFR::GetEmittanceSource() const {
#ifdef GAME
	return ThisCall<TESForm*>(0x569580, this);
#else
	return ThisCall<TESForm*>(0x63E630, this);
#endif
}

#ifdef GAME
// GAME - 0x568E50
// GECK - 0x63E3A0
DoorTeleportData* TESObjectREFR::GetTeleport() const {
#ifdef GAME
	return ThisCall<DoorTeleportData*>(0x568E50, this);
#else
	return ThisCall<DoorTeleportData*>(0x63E3A0, this);
#endif
}

// GAME - 0x569140
LockData* TESObjectREFR::GetMyLock() const {
	return ThisCall<LockData*>(0x569140, this);
}

// GAME - 0x569160
// GECK - 0x63E460
LockData* TESObjectREFR::GetLock() const {
#ifdef GAME
	return ThisCall<LockData*>(0x569160, this);
#else
	return ThisCall<LockData*>(0x63E460, this);
#endif
}

// GAME - 0x5673E0
ScriptLocals* TESObjectREFR::GetScriptLocals() const {
	return ThisCall<ScriptLocals*>(0x5673E0, this);
}

// GAME - 0x565870
bool TESObjectREFR::RunScript() {
	return ThisCall<bool>(0x565870, this);
}

// GAME - 0x5656D0
// GECK - 0x63DCC0
bool TESObjectREFR::HasScript() const {
#ifdef GAME
	return ThisCall<bool>(0x5656D0, this);
#else
	return ThisCall<bool>(0x63DCC0, this);
#endif
}

// GAME - 0x935A40
bool TESObjectREFR::HasSaidTopicInfo(TESTopicInfo* apTopicInfo) const {
	return ThisCall<bool>(0x935A40, this, apTopicInfo);
}

// GAME - 0x561EF0
bool TESObjectREFR::MoveToEditorLocation(TESForm* apLocationForm) {
	return ThisCall<bool>(0x561EF0, this, apLocationForm);
}
#endif

// GAME - 0x93BBA0
TESObjectCELL* TESObjectREFR::GetNearbyWaterContainingCell(float afRadius) const {
	return ThisCall<TESObjectCELL*>(0x93BBA0, this, afRadius);
}

// GAME - 0x574FA0
// GECK - 0x641340
void TESObjectREFR::AddBoundObjectItem(TESBoundObject* apObject, ExtraDataList* apExtra, int32_t aiCount) {
#ifdef GAME
	ThisCall(0x574FA0, this, apObject, apExtra, aiCount);
#else
	ThisCall(0x641340, this, apObject, apExtra, aiCount);
#endif
}

// GAME - 0x575590
int32_t TESObjectREFR::GetInventoryCount(bool abBarter, bool abIncludeNonPlayable) const {
	return ThisCall<int32_t>(0x575590, this, abBarter, abIncludeNonPlayable);
}

// GAME - 0x575610
int32_t TESObjectREFR::GetInventoryObjectCount(TESBoundObject* apObject) const {
	return ThisCall<int32_t>(0x575610, this, apObject);
}

// GAME - 0x5754A0
ItemChange* TESObjectREFR::GetInventoryItem(uint32_t auiIndex, bool abBarter) const {
	return ThisCall<ItemChange*>(0x5754A0, this, auiIndex, abBarter);
}

// GAME - 0x576260
ItemChange* TESObjectREFR::GetInventoryItem(TESBoundObject* apObject, FormID auiFormID) const {
	return ThisCall<ItemChange*>(0x576260, this, apObject, auiFormID);
}

// GAME - 0x56F930
// GECK - 0x63E900
TESObjectREFR* TESObjectREFR::FindReferenceFor3D(NiAVObject* apObject) {
#ifdef GAME
	return CdeclCall<TESObjectREFR*>(0x56F930, apObject);
#else
	return CdeclCall<TESObjectREFR*>(0x63E900, apObject);
#endif
}

// GAME - 0x578400
bool TESObjectREFR::HasAddonNodes(NiNode* apNode) {
	return CdeclCall<bool>(0x578400, apNode);
}

// GAME - 0x5784B0
// GECK - 0x641A90
bool TESObjectREFR::HasAddonFlags(NiNode* apNode) {
#ifdef GAME
	return CdeclCall<bool>(0x5784B0, apNode);
#else
	return CdeclCall<bool>(0x641A90, apNode);
#endif
}

// GAME - 0x577E20
// GECK - 0x64D9C0
bool TESObjectREFR::AddAddonNodes(NiNode* apNode) {
#ifdef GAME
	return CdeclCall<bool>(0x577E20, apNode);
#else
	return CdeclCall<bool>(0x64D9C0, apNode);
#endif
}

// GAME - 0x578300
// GECK - 0x64A2E0
bool TESObjectREFR::RemoveAddonNodes(NiNode* apNode) {
#ifdef GAME
	return CdeclCall<bool>(0x578300, apNode);
#else
	return CdeclCall<bool>(0x64A2E0, apNode);
#endif
}

// GAME - 0x578060
// GECK - 0x64A1C0
bool TESObjectREFR::AddMasterParticleAddonNodes(NiNode* apNode) {
#ifdef GAME
	return CdeclCall<bool>(0x578060, apNode);
#else
	return CdeclCall<bool>(0x64A1C0, apNode);
#endif
}

// GAME - 0x578170
bool TESObjectREFR::RemoveMasterParticleAddonNodes(NiNode* apNode) {
	return CdeclCall<bool>(0x578170, apNode);
}

// GAME - 0x564900
bool TESObjectREFR::IsReferenceFormType(FORM_TYPE aeFormType) {
	return aeFormType >= FORM_TYPE::TESObjectREFR && (aeFormType <= FORM_TYPE::FlameProjectile || aeFormType == FORM_TYPE::ContinuousBeamProjectile);
}