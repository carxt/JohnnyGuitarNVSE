#include "TESObjectCELL.hpp"

// GAME - 0x558B80
bool TESObjectCELL::GetInheritFlag(CellInheritFlags aeFlag) const {
    return uiInheritFlags.IsSet(aeFlag);
}

// GAME - 0x425FD0
bool TESObjectCELL::IsInterior() const {
    return ucCellFlags.bInterior;
}

// GAME - 0x4518E0
bool TESObjectCELL::HasWater() const {
    return ucCellFlags.bHasWater;
}

// GAME - 0x451250
void TESObjectCELL::SetHasWater(bool abHasWater) {
    ucCellFlags.bHasWater = abHasWater;
}

// GAME - 0x544520
bool TESObjectCELL::CantTravelFrom() const {
    return ThisCall<bool>(0x544520, this);
}

#ifdef GAME
// GAME - 0x551420
bool TESObjectCELL::GetHasTempData() const {
    return ucCellFlags.bHasTempData;
}
#endif

// GAME - 0x502180
bool TESObjectCELL::GetPublic() const {
    return ucCellFlags.bPublic;
}

// GAME - 0x544420
bool TESObjectCELL::GetTempPublic() const {
    return ucCellFlags.bTempPublic;
}

// GAME - 0x454B10
bool TESObjectCELL::GetFakeExterior() const {
    return ucCellFlags.bFakeExterior;
}

// GAME - 0x5443E0
bool TESObjectCELL::GetPublicState() const {
    return ThisCall<bool>(0x5443E0, this);
}

// GAME - 0x544490
bool TESObjectCELL::GetOffLimits() const {
    return ThisCall<bool>(0x544490, this);
}

// GAME - 0x5444C0
bool TESObjectCELL::GetCantWaitHere() const {
    return ThisCall<bool>(0x5444C0, this);
}

// GAME - 0x556850
bool TESObjectCELL::GetFullySeen() const {
    return ThisCall<bool>(0x556850, this);
}

// GAME - 0x450FD0
TESObjectCELL::State TESObjectCELL::GetState() const {
    return static_cast<TESObjectCELL::State>(eCellState);
}

// GAME - 0x450FF0
bool TESObjectCELL::IsAttached() const {
    return ThisCall<bool>(0x450FF0, this);
}

// GAME - 0x4523C0
bool TESObjectCELL::IsAttaching() const {
    return ThisCall<bool>(0x4523C0, this);
}

// GAME - 0x450FB0
bool TESObjectCELL::IsLoaded() const {
    return ThisCall<bool>(0x450FB0, this);
}

// GAME - 0x548720
bool TESObjectCELL::IsLoading() const {
    return ThisCall<bool>(0x548720, this);
}

// GAME - 0x4610D0
ExtraDataList* TESObjectCELL::GetExtra() {
    return &kExtraList;
}

// GAME - 0x4610D0
const ExtraDataList* TESObjectCELL::GetExtra() const {
    return &kExtraList;
}

BSExtraData* TESObjectCELL::GetExtraData(uint8_t aucType) const {
    return GetExtra()->GetExtraData(aucType);
}

bool TESObjectCELL::HasExtra(uint8_t aucType) const {
    return GetExtra()->HasExtra(aucType);
}

// GAME - 0x546FB0
// GECK - 0x627140
TESObjectLAND* TESObjectCELL::GetLand() {
#ifdef GAME
    return ThisCall<TESObjectLAND*>(0x546FB0, this);
#else
    return ThisCall<TESObjectLAND*>(0x627140, this);
#endif
}

// GAME - 0x5471E0
float TESObjectCELL::GetWaterHeight() const {
    return ThisCall<float>(0x5471E0, this);
}

// GAME - 0x547250
// GECK - 0x62D460
bool TESObjectCELL::GetWaterHeight(const NiPoint3& arPos, float& arHeight) const {
#ifdef GAME
    return ThisCall<bool>(0x547250, this, &arPos, &arHeight);
#else
    return ThisCall<bool>(0x62D460, this, &arPos, &arHeight);
#endif
}

// GAME - 0x547440
// GECK - 0x62D610
void TESObjectCELL::SetWaterHeight(float afHeight) {
#ifdef GAME
    ThisCall(0x547440, this, afHeight);
#else
    ThisCall(0x62D610, this, afHeight);
#endif
}

// GAME - 0x451CD0
bool TESObjectCELL::GetAutoWaterLoaded() const {
    return bAutoWaterLoaded;
}

// GAME - 0x4543A0
const char* TESObjectCELL::GetWaterNoiseTextureName() const {
    return ThisCall<const char*>(0x4543A0, this);
}

// GAME - 0x557090
bool TESObjectCELL::IsRefListLocked() const {
    return ThisCall<bool>(0x557090, this);
}

// GAME - 0x4FD400
int32_t TESObjectCELL::GetCriticalQueuedRefCount() const {
    return iCriticalQueuedRefCount;
}

// GAME - 0x5E3FC0
int32_t TESObjectCELL::GetQueuedRefCount() const {
    return iQueuedRefCount;
}

// GAME - 0x541AC0
void TESObjectCELL::CellRefLockEnter() {
    ThisCall(0x541AC0, this);
}

// GAME - 0x541AE0
void TESObjectCELL::CellRefLockLeave() {
    ThisCall(0x541AE0, this);
}

// GAME - 0x537B50
bool TESObjectCELL::HasReferences() const {
    return !kReferences.IsEmpty();
}

// GAME - 0x9604F0
BSSimpleList<TESObjectREFR*>* TESObjectCELL::GetRefList() {
    return &kReferences;
}

// GAME - 0x9604F0
const BSSimpleList<TESObjectREFR*>* TESObjectCELL::GetRefList() const {
    return &kReferences;
}

// GAME - 0x54DDD0
// GECK - 0x627820
TESWorldSpace* TESObjectCELL::GetWorldSpace() const {
#ifdef GAME
    return IsInterior() ? nullptr : pWorldSpace;
#else
	return ThisCall<TESWorldSpace*>(0x627820, this);
#endif
}

// GAME - 0x545CB0
// GECK - 0x627130
NiNode* TESObjectCELL::Get3D() const {
	return pLoadedData ? pLoadedData->spCell3D : nullptr;
}

// GAME - 0x456FC0
// GECK - 0x44FE40
NiNode* TESObjectCELL::GetChildNode(CellNodeType aeNode) const {
#ifdef GAME
    return ThisCall<NiNode*>(0x456FC0, this, aeNode);
#else
    return ThisCall<NiNode*>(0x44FE40, this, aeNode);
#endif
}

// GAME - 0x524CF0
// GECK - 0x4C8940
NiNode* TESObjectCELL::GetMarkerNode() const {
#ifdef GAME
    return ThisCall<NiNode*>(0x524CF0, this);
#else
    return ThisCall<NiNode*>(0x4C8940, this);
#endif
}

// GAME - 0x45C9A0
NiNode* TESObjectCELL::GetLandNode(uint32_t auiIndex) const {
	const NiNode* pLand = GetChildNode(CellNodeType::LAND);
	if (pLand)
		return static_cast<NiNode*>(pLand->GetAt(auiIndex));
	return nullptr;
}

// GAME - 0x5497A0
// GECK - 0x62C7B0
NiNode* TESObjectCELL::GetDynamicNode() const {
#ifdef GAME
    return ThisCall<NiNode*>(0x5497A0, this);
#else
    return ThisCall<NiNode*>(0x62C7B0, this);
#endif
}

// GAME - 0x9D9F20
// GECK - 0x627120
BSPortalGraph* TESObjectCELL::GetPortalGraph() const {
    return spPortalGraph;
}

// GAME - 0x587410
// GECK - 0x665510
uint32_t TESObjectCELL::GetCoord(int16_t x, int16_t y) {
    return (int32_t(x) << 16) | uint16_t(y);
}

// GAME - 0x544C30
// GECK - 0x625A70
int32_t TESObjectCELL::GetDataX() const {
#ifdef GAME
    return ThisCall<int32_t>(0x544C30, this);
#else
    return ThisCall<int32_t>(0x625A70, this);
#endif
}

// GAME - 0x544C60
// GECK - 0x625A90
int32_t TESObjectCELL::GetDataY() const {
#ifdef GAME
    return ThisCall<int32_t>(0x544C60, this);
#else
    return ThisCall<int32_t>(0x625A90, this);
#endif
}

void TESObjectCELL::GetDataXandY(int32_t& aiX, int32_t& aiY) const {
	const ExteriorData* pData = GetExteriorData();
	if (pData) {
		aiX = pData->iCellX;
		aiY = pData->iCellY;
	}
    else {
		aiX = 0;
		aiY = 0;
    }
}

void TESObjectCELL::GetWorldXandY(float& afX, float& afY) const {
	const ExteriorData* pData = GetExteriorData();
    if (pData) {
        afX = float(pData->iCellX << 12);
        afY = float(pData->iCellY << 12);
    }
    else {
        afX = 0.f;
        afY = 0.f;
    }
}

// GAME - 0x5547C0
// GECK - 0x628FF0
bool TESObjectCELL::GetHeightAtPos(const NiPoint3& arPos, float& afHeight) const {
#ifdef GAME
    return ThisCall<bool>(0x5547C0, this, &arPos, &afHeight);
#else
    return ThisCall<bool>(0x628FF0, this, &arPos, &afHeight);
#endif
}

void TESObjectCELL::GetWorldPosition(NiPoint3& arPos) const {
    int32_t iX, iY;
    GetDataXandY(iX, iY);
    arPos.x = iX << 12;
    arPos.y = iY << 12;
    arPos.z = 0.f;
}

// GAME - 0x4543C0
// GECK - 0x43F400
bhkWorld* TESObjectCELL::GetbhkWorld() const {
#ifdef GAME
    return ThisCall<bhkWorld*>(0x4543C0, this);
#else
    return ThisCall<bhkWorld*>(0x43F400, this);
#endif
}

// GAME - 0x451010
bhkWorld* TESObjectCELL::GetExteriorbhkWorld() {
    return CdeclCall<bhkWorld*>(0x451010);
}

// GAME - 0x544600
// GECK - 0x625900
TESObjectCELL::InteriorData* TESObjectCELL::GetInteriorData() const {
#ifdef GAME
    return ThisCall<InteriorData*>(0x544600, this);
#else
    return ThisCall<InteriorData*>(0x625900, this);
#endif
}

// GAME - 0x5445D0
// GECK - 0x6258F0
TESObjectCELL::ExteriorData* TESObjectCELL::GetExteriorData() const {
#ifdef GAME
    return ThisCall<ExteriorData*>(0x5445D0, this);
#else
    return ThisCall<ExteriorData*>(0x6258F0, this);
#endif
}

// GAME - 0x544BD0
// GECK - N/A
float TESObjectCELL::GetDataClipDist() const {
#ifdef GAME
    return ThisCall<float>(0x544BD0, this);
#endif
}

// GAME - 0x544910
// GECK - 0x626CF0
int32_t TESObjectCELL::GetDirectionalXY() const {
#ifdef GAME
    return ThisCall<int32_t>(0x544910, this);
#else
    return ThisCall<int32_t>(0x626CF0, this);
#endif
}

// GAME - 0x544970
// GECK - 0x626D30
int32_t TESObjectCELL::GetDirectionalZ() const {
#ifdef GAME
    return ThisCall<int32_t>(0x544970, this);
#else
    return ThisCall<int32_t>(0x626D30, this);
#endif
}

// GAME - 0x555AD0
float TESObjectCELL::GetNorthRotation() const {
    return ThisCall<float>(0x555AD0, this);
}

// GAME - 0x544590
bool TESObjectCELL::GetHideLand(uint8_t aucBlock) const {
    auto pData = GetExteriorData();
    return pData && pData->ucLandHideFlags.Get(1 << aucBlock);
}

// GAME - 0x537B30
// GAME - 0x43F400
CellMopp* TESObjectCELL::GetCellMopp() const {
#ifdef GAME
    return ThisCall<CellMopp*>(0x537B30, this);
#else
    return ThisCall<CellMopp*>(0x43F400, this);
#endif
}

// GAME - 0x5535F0
void TESObjectCELL::SetupMopp() {
    ThisCall(0x5535F0, this);
}

// GAME - 0x54FB70
float TESObjectCELL::GetDistanceFromPoint(const NiPoint3& arPoint) {
	return ThisCall<float>(0x54FB70, this, &arPoint);
}

// GAME - 0x558B40
BGSLightingTemplate* TESObjectCELL::GetLightingTemplate() const {
    return pLightingTemplate;
}

// GAME - 0x558B60
void TESObjectCELL::SetLightingTemplate(BGSLightingTemplate* apTemplate) {
    ThisCall(0x558B60, this, apTemplate);
}

// GAME - 0x546C20
BGSEncounterZone* TESObjectCELL::GetEncounterZone() const {
    return ThisCall<BGSEncounterZone*>(0x546C20, this);
}

void TESObjectCELL::SetEncounterZone(BGSEncounterZone* apZone) {
    GetExtra()->SetEncounterZone(apZone);
}

// GAME - 0x547590
BGSAcousticSpace* TESObjectCELL::GetAcousticSpace() const {
    return ThisCall<BGSAcousticSpace*>(0x547590, this);
}

void TESObjectCELL::SetAcousticSpace(BGSAcousticSpace* apSpace) {
    GetExtra()->SetAcousticSpace(apSpace);
}

// GAME - 0x555BC0
SeenData* TESObjectCELL::GetSeenData() const {
    return ThisCall<SeenData*>(0x555BC0, this);
}

// GAME - 0x546AF0
uint32_t TESObjectCELL::GetDetachTime() const {
    return ThisCall<uint32_t>(0x546AF0, this);
}

// GAME - 0x546C70
void TESObjectCELL::SetDetachTime() {
    ThisCall(0x546C70, this);
}

// GAME - 0x546B10
void TESObjectCELL::SetDetachTime(uint32_t auiTime, bool abForce) {
    ThisCall(0x546B10, this, auiTime, abForce);
}

// GAME - 0x526100
uint32_t TESObjectCELL::GetHoursToClearCorpses() {
    return CdeclCall<uint32_t>(0x526100);
}
