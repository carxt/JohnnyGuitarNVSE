#include "TESObjectCELL.hpp"
#include "TESDataHandler.hpp"
#include "TESWorldSpace.hpp"
#include "BGSLightingTemplate.hpp"
#ifdef EDITOR
#include "TESObjectLAND.hpp"
#endif

// GAME - 0x5516C0
bool TESObjectCELL::GetPersistentCell() const {
    return uiFormFlags.Get<FormFlags::PERSISTENT_CELL>();
}

// GAME - 0x5516F0
// GECK - SetPersistent
void TESObjectCELL::SetPersistentCell(bool abPersist) {
    uiFormFlags.Set<FormFlags::PERSISTENT_CELL>(abPersist);
}

// GAME - 0x425FD0
bool TESObjectCELL::GetInterior() const {
    return ucCellFlags.bInterior;
}

// GAME - 0x544300
// GECK - 0x6258D0
void TESObjectCELL::SetInterior(bool abInterior) {
#ifdef GAME
    ThisCall(0x544300, this, abInterior);
#else
    ThisCall(0x6258D0, this, abInterior);
#endif
}

// GAME - 0x4518E0
bool TESObjectCELL::GetHasWater() const {
    return ucCellFlags.bHasWater;
}

// GAME - 0x451250
// GECK - 0x609070
void TESObjectCELL::SetHasWater(bool abHasWater) {
#ifdef GAME
    ThisCall(0x451250, this, abHasWater);
#else
    ThisCall(0x609070, this, abHasWater);
#endif
}

// GAME - 0x544520
bool TESObjectCELL::GetCantTravelFrom() const {
#ifdef GAME
    return ThisCall<bool>(0x544520, this);
#else
    bool bNoTravel = ucCellFlags.bCantFastTravel;
    if (GetInterior())
        bNoTravel = !bNoTravel;

    if (bNoTravel)
        return true;

    const TESWorldSpace* pWorld = GetWorldSpace();
    return pWorld && pWorld->GetCantTravelFrom();
#endif
}

#ifdef GAME
// GAME - 0x551420
bool TESObjectCELL::GetHasTempData() const {
    return ucCellFlags.bHasTempData;
}
#endif

// GAME - 0x502180
bool TESObjectCELL::GetPublic() const {
#ifdef GAME
    return ThisCall<bool>(0x502180, this);
#else
    return ucCellFlags.bPublic;
#endif
}

// GAME - 0x544340
void TESObjectCELL::SetPublic(bool abPublic) {
#ifdef GAME
    ThisCall(0x544340, this, abPublic);
#else
    ucCellFlags.bPublic = abPublic;
#endif
}

// GAME - 0x544420
bool TESObjectCELL::GetTempPublic() const {
#ifdef GAME
    return ThisCall<bool>(0x544420, this);
#else
    return ucCellFlags.bTempPublic;
#endif
}

// GAME - 0x544390
void TESObjectCELL::SetTempPublic(bool abPublic) {
#ifdef GAME
    ThisCall(0x544390, this, abPublic);
#else
    ucCellFlags.bTempPublic = abPublic;
#endif
}

// GAME - 0x454B10
bool TESObjectCELL::GetFakeExterior() const {
#ifdef GAME
    return ThisCall<bool>(0x454B10, this);
#else
    return ucCellFlags.bFakeExterior;
#endif
}

// GECK - 0x626B30
void TESObjectCELL::SetFakeExterior(bool abExterior) {
#ifdef GAME
    if (!GetInterior())
        return;

    if (abExterior) {
        ucCellFlags.bFakeExterior = true;
    }
    else {
        if (ucCellFlags.GetAndClear<CellFlags::FAKE_EXTERIOR>())
            SetClimate(nullptr);
    }
#else
    ThisCall(0x626B30, this, abExterior);
#endif
}

// GAME - 0x5443E0
bool TESObjectCELL::GetPublicState() const {
#ifdef GAME
    return ThisCall<bool>(0x5443E0, this);
#else
    return GetPublic() || GetTempPublic();
#endif
}

// GAME - 0x544490
bool TESObjectCELL::GetOffLimits() const {
#ifdef GAME
    return ThisCall<bool>(0x544490, this);
#else
    return uiFormFlags.Get<FormFlags::OFF_LIMITS>();
#endif
}

void TESObjectCELL::SetOffLimits(bool abOffLimits) {}

// GAME - 0x5444C0
bool TESObjectCELL::GetCantWaitHere() const {
#ifdef GAME
    return ThisCall<bool>(0x5444C0, this);
#else
    if (GetInterior()) {
        return uiFormFlags.Get<FormFlags::CANT_WAIT>();
    }
    else {
        const TESWorldSpace* pWorld = GetWorldSpace();
        if (pWorld)
            return pWorld->GetCantWaitHere();
    }
    return false;
#endif
}

#ifdef GAME
// GAME - 0x556850
bool TESObjectCELL::GetFullySeen() const {
    return ThisCall<bool>(0x556850, this);
}
#endif

// GAME - 0x450FD0
TESObjectCELL::State TESObjectCELL::GetState() const {
    return static_cast<TESObjectCELL::State>(eCellState);
}

// GAME - 0x450FF0
bool TESObjectCELL::IsAttached() const {
#ifdef GAME
    return ThisCall<bool>(0x450FF0, this);
#else
    return GetState() == State::ATTACHING;
#endif
}

// GAME - 0x4523C0
bool TESObjectCELL::IsAttaching() const {
#ifdef GAME
    return ThisCall<bool>(0x4523C0, this);
#else
    return GetState() == State::ATTACHING;
#endif
}

// GAME - 0x450FB0
bool TESObjectCELL::IsLoaded() const {
#ifdef GAME
    return ThisCall<bool>(0x450FB0, this);
#else
    return GetState() == State::LOADED;
#endif
}

// GAME - 0x548720
bool TESObjectCELL::IsLoading() const {
#ifdef GAME
    return ThisCall<bool>(0x548720, this);
#else
    return GetState() == State::LOADING;
#endif
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

// GAME - 0x70EC90
// GECK - 0x951CD0
NavMeshArray* TESObjectCELL::GetNavMeshArray() const {
    return pNavMeshes;
}

// GAME - 0x557760
// GECK - 0x63B730
void TESObjectCELL::SetNavMeshArray(NavMeshArray* apArray) {
#ifdef GAME
    ThisCall(0x557760, this, apArray);
#else
    ThisCall(0x63B730, this, apArray);
#endif
}

// GAME - 0x5471E0
// GECK - 0x62D420
float TESObjectCELL::GetWaterHeight() const {
#ifdef GAME
    return ThisCall<float>(0x5471E0, this);
#else
    return ThisCall<float>(0x62D420, this);
#endif
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
#ifdef GAME
    return ThisCall<const char*>(0x4543A0, this);
#else
    return kWaterNoiseTexture.GetTextureName();
#endif
}

// GAME - 0x4FD400
int32_t TESObjectCELL::GetCriticalQueuedRefCount() const {
    return iCriticalQueuedRefCount;
}

// GAME - 0x5E3FC0
int32_t TESObjectCELL::GetQueuedRefCount() const {
    return iQueuedRefCount;
}

// GAME - 0x557090
// GECK - 0x626170
bool TESObjectCELL::IsRefListLocked() const {
#ifdef GAME
    return ThisCall<bool>(0x557090, this);
#else
    return ThisCall<bool>(0x626170, this);
#endif
}

// GAME - 0x541AC0
// GECK - 0x625850
void TESObjectCELL::CellRefLockEnter() {
#ifdef GAME
    ThisCall(0x541AC0, this);
#else
    ThisCall(0x625850, this);
#endif
}

// GAME - 0x541AE0
// GECK - 0x625870
void TESObjectCELL::CellRefLockLeave() {
#ifdef GAME
    ThisCall(0x541AE0, this);
#else
    ThisCall(0x625870, this);
#endif
}

// GAME - 0x537B50
bool TESObjectCELL::HasReferences() const {
    return !kReferences.IsEmpty();
}

// GAME - 0x454400
uint32_t TESObjectCELL::GetReferenceCount() const {
    return kReferences.ItemsInList();
}

// GAME - 0x9604F0
BSSimpleList<TESObjectREFR*>* TESObjectCELL::GetRefList() {
    return &kReferences;
}

// GAME - 0x9604F0
const BSSimpleList<TESObjectREFR*>* TESObjectCELL::GetRefList() const {
    return &kReferences;
}

// GAME - 0x548230
// GECK - 0x63B1E0
void TESObjectCELL::AddReference(TESObjectREFR* apReference, bool abOnTop) {
#ifdef GAME
    ThisCall(0x548230, this, apReference, abOnTop);
#else
    ThisCall(0x63B1E0, this, apReference, abOnTop);
#endif
}

#ifdef GAME
// GAME - 0x548740
void TESObjectCELL::AddReferenceSimple(TESObjectREFR* apReference) {
    ThisCall(0x548740, this, apReference);
}
#endif

// GAME - 0x54CA90
// GECK - 0x6323E0
void TESObjectCELL::RemoveReference(TESObjectREFR* apReference) {
#ifdef GAME
    ThisCall(0x54CA90, this, apReference);
#else
    ThisCall(0x6323E0, this, apReference);
#endif
}

// GAME - 0x5452C0
// GECK - 0x62CE50
void TESObjectCELL::AddAnimatedRef(TESObjectREFR* apReference) {
#ifdef GAME
    ThisCall(0x5452C0, this, apReference);
#else
    ThisCall(0x62CE50, this, apReference);
#endif
}

// GAME - 0x545360
// GECK - 0x631A10
void TESObjectCELL::RemoveAnimatedRef(TESObjectREFR* apReference) {
#ifdef GAME
    ThisCall(0x545360, this, apReference);
#else
    ThisCall(0x631A10, this, apReference);
#endif
}

// GAME - 0x5453B0
// GECK - 0x626F80
void TESObjectCELL::AddEmittanceRef(TESObjectREFR* apReference) {
#ifdef GAME
    ThisCall(0x5453B0, this, apReference);
#else
    ThisCall(0x626F80, this, apReference);
#endif
}

// GAME - 0x5454F0
// GECK - 0x6270D0
void TESObjectCELL::RemoveEmittanceRef(TESObjectREFR* apReference) {
#ifdef GAME
    ThisCall(0x5454F0, this, apReference);
#else
    ThisCall(0x6270D0, this, apReference);
#endif
}

// GAME - 0x54DDD0
// GECK - 0x627820
TESWorldSpace* TESObjectCELL::GetWorldSpace() const {
#ifdef GAME
    return GetInterior() ? nullptr : pWorldSpace;
#else
	return ThisCall<TESWorldSpace*>(0x627820, this);
#endif
}

// GAME - 0x545CB0
// GECK - 0x627130
NiNode* TESObjectCELL::Get3D() const {
	return pLoadedData ? pLoadedData->spCell3D.m_pObject : nullptr;
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
#ifdef GAME
    return ThisCall<NiNode*>(0x45C9A0, this, auiIndex);
#else
    const NiNode* pLand = GetChildNode(CellNodeType::LAND);
	if (pLand)
		return static_cast<NiNode*>(pLand->GetAt(auiIndex));
	return nullptr;
#endif
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
    return spPortalGraph.m_pObject;
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
	const ExteriorCellData* pData = GetExteriorData();
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
	const ExteriorCellData* pData = GetExteriorData();
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
#ifdef GAME
    return CdeclCall<bhkWorld*>(0x451010);
#else
    return (*reinterpret_cast<NiPointer<bhkWorld>**>(0xEDD880))->m_pObject;
#endif
}

// GAME - 0x544600
// GECK - 0x625900
InteriorCellData* TESObjectCELL::GetInteriorData() const {
#ifdef GAME
    return ThisCall<InteriorCellData*>(0x544600, this);
#else
    return ThisCall<InteriorCellData*>(0x625900, this);
#endif
}

// GAME - 0x5445D0
// GECK - 0x6258F0
ExteriorCellData* TESObjectCELL::GetExteriorData() const {
#ifdef GAME
    return ThisCall<ExteriorCellData*>(0x5445D0, this);
#else
    return ThisCall<ExteriorCellData*>(0x6258F0, this);
#endif
}

// GAME - 0x544750
// GECK - 0x626B90
uint32_t TESObjectCELL::GetDataAmbientColor() const {
#ifdef GAME
    return ThisCall<uint32_t>(0x544750, this);
#else
    return ThisCall<uint32_t>(0x626B90, this);
#endif
}

// GAME - 0x5447B0
// GECK - 0x626BC0
void TESObjectCELL::GetDataAmbientColor(NiColor& arColor) const {
#ifdef GAME
    ThisCall<void>(0x5447B0, this, &arColor);
#else
    ThisCall<void>(0x626BC0, this, &arColor);
#endif
}

void TESObjectCELL::SetDataAmbientColor(uint32_t auiColor) {
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior())
        pData->uiAmbientColor = auiColor;
}

// GAME - 0x544830
// GECK - 0x626C40
uint32_t TESObjectCELL::GetDataDirectionalColor() const {
#ifdef GAME
    return ThisCall<uint32_t>(0x544830, this);
#else
    return ThisCall<uint32_t>(0x626C40, this);
#endif
}

// GAME - 0x544890
// GECK - 0x626C70
void TESObjectCELL::GetDataDirectionalColor(NiColor& arColor) const {
#ifdef GAME
    ThisCall<void>(0x544890, this, &arColor);
#else
    ThisCall<void>(0x626C70, this, &arColor);
#endif
}

void TESObjectCELL::SetDataDirectionalColor(uint32_t auiColor) {
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior())
        pData->uiDirectionalColor = auiColor;
}

// GAME - 0x5449D0
// GECK - 0x626D70
uint32_t TESObjectCELL::GetDataFogColor() const {
#ifdef GAME
    return ThisCall<uint32_t>(0x5449D0, this);
#else
    return ThisCall<uint32_t>(0x626D70, this);
#endif
}

// GAME - 0x544A30
// GECK - 0x626DB0
void TESObjectCELL::GetDataFogColor(NiColor& arColor) const {
#ifdef GAME
    ThisCall<void>(0x544A30, this, &arColor);
#else
    ThisCall<void>(0x626DB0, this, &arColor);
#endif
}

void TESObjectCELL::SetDataFogColor(uint32_t auiColor) {
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior())
        pData->uiFogColor = auiColor;
}

// GAME - 0x544AB0
// GECK - 0x626E30
float TESObjectCELL::GetDataFogNearPlane() const {
#ifdef GAME
    return ThisCall<float>(0x544AB0, this);
#else
    return ThisCall<float>(0x626E30, this);
#endif
}

// GECK - 0x625A10
void TESObjectCELL::SetDataFogNearPlane(float afVal) {
#ifdef GAME
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior())
        pData->fFogNear = afVal;
#else
    ThisCall(0x625A10, this, afVal);
#endif
}

// GECK - 0x544B10
// GECK - 0x626E70
float TESObjectCELL::GetDataFogFarPlane() const {
#ifdef GAME
    return ThisCall<float>(0x544B10, this);
#else
    return ThisCall<float>(0x626E70, this);
#endif
}

// GECK - 0x625A30
void TESObjectCELL::SetDataFogFarPlane(float afVal) {
#ifdef GAME
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior())
        pData->fFogFar = afVal;
#else
    ThisCall(0x625A30, this, afVal);
#endif
}

// GAME - 0x544910
// GECK - 0x626CF0
int32_t TESObjectCELL::GetDataDirectionalXY() const {
#ifdef GAME
    return ThisCall<int32_t>(0x544910, this);
#else
    return ThisCall<int32_t>(0x626CF0, this);
#endif
}

// GECK - 0x625990
void TESObjectCELL::SetDataDirectionalXY(int32_t aiVal) {
#ifdef GAME
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior()) {
        if (aiVal > 360)
            aiVal = 360;

        pData->iDirectionalXY = aiVal;
    }
#else
    ThisCall(0x625990, this, aiVal);
#endif
}

// GAME - 0x544970
// GECK - 0x626D30
int32_t TESObjectCELL::GetDataDirectionalZ() const {
#ifdef GAME
    return ThisCall<int32_t>(0x544970, this);
#else
    return ThisCall<int32_t>(0x626D30, this);
#endif
}

// GECK - 0x6259C0
void TESObjectCELL::SetDataDirectionalZ(int32_t aiVal) {
#ifdef GAME
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior()) {
        if (aiVal > 360)
            aiVal = 360;

        pData->iDirectionalZ = aiVal;
    }
#else
    ThisCall(0x6259C0, this, aiVal);
#endif
}

float TESObjectCELL::GetDataDirectionalFade() const {
    InteriorCellData* pData = GetInteriorData();
    if (!pData)
        return 0.f;

    if (!GetLightingTemplateInheritFlag(TemplateInheritFlags::DIRECTIONAL_FADE) || !GetLightingTemplate())
        return pData->fDirectionalFade;

    return GetLightingTemplate()->GetDataDirectionalFade();
}

// GECK - 0x6259F0
void TESObjectCELL::SetDataDirectionalFade(float afVal) {
#ifdef GAME
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior()) {
        pData->fDirectionalFade = afVal;
    }
#else
    ThisCall(0x6259F0, this, afVal);
#endif
}


// GAME - 0x544BD0
// GECK - 0x626EF0
float TESObjectCELL::GetDataClipDist() const {
#ifdef GAME
    return ThisCall<float>(0x544BD0, this);
#else
    return ThisCall<float>(0x626EF0, this);
#endif
}

// GECK - 0x625A50
void TESObjectCELL::SetDataClipDist(float afVal) {
#ifdef GAME
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior())
        pData->fClipDist = afVal;
#else
    ThisCall(0x625A50, this, afVal);
#endif
}

// GAME - 0x544B70
// GECK - 0x626EB0
float TESObjectCELL::GetDataFogPower() const {
#ifdef GAME
    return ThisCall<float>(0x544B70, this);
#else
    return ThisCall<float>(0x626EB0, this);
#endif
}

void TESObjectCELL::SetDataFogPower(float afVal) {
    InteriorCellData* pData = GetInteriorData();
    if (pData && !GetFakeExterior())
        pData->fFogPower = afVal;
}

// GAME - 0x544590
// GECK - 0x626B60
bool TESObjectCELL::GetHideLand(uint8_t aucBlock) const {
#ifdef GAME
    return ThisCall<bool>(0x544590, this, aucBlock);
#else
    return ThisCall<bool>(0x626B60, this, aucBlock);
#endif
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
// GECK - 0x6304B0
void TESObjectCELL::SetupMopp() {
#ifdef GAME
    ThisCall(0x5535F0, this);
#else
    ThisCall(0x6304B0, this);
#endif
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
// GECK - 0x6261D0
void TESObjectCELL::SetLightingTemplate(BGSLightingTemplate* apTemplate) {
#ifdef GAME
    ThisCall(0x558B60, this, apTemplate);
#else
    ThisCall(0x6261D0, this, apTemplate);
#endif
}

// GAME - 0x558B80
bool TESObjectCELL::GetLightingTemplateInheritFlag(TemplateInheritFlags aeFlag) const {
    return uiLightingTemplateInheritFlags.IsSet(aeFlag);
}

// GECK - 0x626210
void TESObjectCELL::SetLightingTemplateInheritFlag(TemplateInheritFlags aeFlag, bool abVal) {
    uiLightingTemplateInheritFlags.Set(aeFlag, abVal);
}

// GAME - 0x546C20
// GECK - 0x62D3E0
BGSEncounterZone* TESObjectCELL::GetEncounterZone() const {
#ifdef GAME
    return ThisCall<BGSEncounterZone*>(0x546C20, this);
#else
    return ThisCall<BGSEncounterZone*>(0x62D3E0, this);
#endif
}

void TESObjectCELL::SetEncounterZone(BGSEncounterZone* apZone) {
    GetExtra()->SetEncounterZone(apZone);
}

// GAME - 0x547590
BGSAcousticSpace* TESObjectCELL::GetAcousticSpace() const {
#ifdef GAME
    return ThisCall<BGSAcousticSpace*>(0x547590, this);
#else
    return GetExtra()->GetAcousticSpace();
#endif
}

void TESObjectCELL::SetAcousticSpace(BGSAcousticSpace* apSpace) {
    GetExtra()->SetAcousticSpace(apSpace);
}

// GAME - 0x5475B0
// GECK - 0x62D680
TESClimate* TESObjectCELL::GetClimate() const {
#ifdef GAME
    return ThisCall<TESClimate*>(0x5475B0, this);
#else
    return ThisCall<TESClimate*>(0x62D680, this);
#endif
}

// GECK - 0x62FFB4 - Inlined
void TESObjectCELL::SetClimate(TESClimate* apClimate) {
    if (!GetInterior() || GetFakeExterior())
        GetExtra()->SetClimate(apClimate);
}

// GAME - 0x547650
TESImageSpace* TESObjectCELL::GetImageSpace() const {
#ifdef GAME
    return ThisCall<TESImageSpace*>(0x547650, this);
#else
    return GetExtra()->GetImageSpace();
#endif
}

// GAME - 0x547680
// GECK - 0x62D6B0
TESImageSpace* TESObjectCELL::GetUsableImageSpace() const {
#ifdef GAME
    return ThisCall<TESImageSpace*>(0x547680, this);
#else
    return ThisCall<TESImageSpace*>(0x62D6B0, this);
#endif
}

// GAME - 0x547750
void TESObjectCELL::SetImageSpace(TESImageSpace* apImageSpace) {
#ifdef GAME
    ThisCall(0x547750, this, apImageSpace);
#else
    GetExtra()->SetImageSpace(apImageSpace);
#endif
}

// GAME - 0x547770
// GECK - 0x62D740
TESWaterForm* TESObjectCELL::GetWaterType() const {
#ifdef GAME
    return ThisCall<TESWaterForm*>(0x547770, this);
#else
    return ThisCall<TESWaterForm*>(0x62D740, this);
#endif
}

// GECK - 0x62D790
void TESObjectCELL::SetWaterType(TESWaterForm* apWater) {
#ifdef GAME
    TESWaterForm* pExistingWater = pDefaultWater.ReadAs<TESWaterForm*>();
    TESWorldSpace* pWorld = GetWorldSpace();
    if (pWorld)
        pExistingWater = pWorld->GetWaterType();

    ExtraDataList* pExtra = GetExtra();
    if (apWater == pExistingWater)
        pExtra->SetWaterType(nullptr);
    else
        pExtra->SetWaterType(apWater);
#else
    ThisCall(0x62D790, this, apWater);
#endif
}

// GAME - 0x547610
// GECK - 0x625BC0
ImpactSwap* TESObjectCELL::GetImpactSwap() const {
#ifdef GAME
    return ThisCall<ImpactSwap*>(0x547610, this);
#else
    return ThisCall<ImpactSwap*>(0x625BC0, this);
#endif
}

void TESObjectCELL::SetImpactSwap(ImpactSwap* apSwap) {
    if (GetInterior())
        GetExtra()->SetImpactSwap(apSwap);
}

// GAME - 0x5474B0
BGSMusicType* TESObjectCELL::GetMusicType(NiPoint3* apPos) const {
#ifdef GAME
    return ThisCall<BGSMusicType*>(0x5474B0, this, apPos);
#else
    return GetExtra()->GetMusicType();
#endif
}

// GECK - 0x6302D5 - Inlined
void TESObjectCELL::SetMusicType(BGSMusicType* apType) {
    GetExtra()->SetMusicType(apType);
}

TESRegionList* TESObjectCELL::GetRegionList() const {
    return const_cast<TESObjectCELL*>(this)->GetRegionList(false);
}

// GAME - 0x547110
// GECK - 0x625B20
TESRegionList* TESObjectCELL::GetRegionList(bool abCreate) {
#ifdef GAME
    return ThisCall<TESRegionList*>(0x547110, this, abCreate);
#else
    return ThisCall<TESRegionList*>(0x625B20, this, abCreate);
#endif
}

// GAME - 0x546A40
// GECK - 0x631A90
TESForm* TESObjectCELL::GetOwner() const {
#ifdef GAME
    return ThisCall<TESForm*>(0x546A40, this);
#else
    return ThisCall<TESForm*>(0x631A90, this);
#endif
}

// GAME - 0x546AA0
TESGlobal* TESObjectCELL::GetOwnershipGlobal() const {
#ifdef GAME
    return ThisCall<TESGlobal*>(0x546AA0, this);
#else
    return GetExtra()->GetGlobal();
#endif
}

// GAME - 0x546AC0
int32_t TESObjectCELL::GetOwnershipRank() const {
#ifdef GAME
    return ThisCall<int32_t>(0x546AC0, this);
#else
    int32_t iRank = GetExtra()->GetRank();
    if (iRank == -1)
        return 0;
    return iRank;
#endif
}

// GAME - 0x546BF0
void TESObjectCELL::SetOwnership(TESForm* apOwner) {
#ifdef GAME
    ThisCall(0x546BF0, this, apOwner);
#else
    GetExtra()->SetOwnership(apOwner);
#endif
}

#ifdef GAME
// GAME - 0x546CA0
bool TESObjectCELL::IsActorCellOwner(Actor* apActor) const {
    return ThisCall<bool>(0x546CA0, this, apActor);
}

// GAME - 0x546DA0
bool TESObjectCELL::IsActorTrespassing(Actor* apActor) const {
    return ThisCall<bool>(0x546DA0, this, apActor);
}
#endif

// GAME - 0x546EE0
// GECK - 0x631AF0
bool TESObjectCELL::IsActorBaseCellOwner(TESActorBase* apActorBase) const {
#ifdef GAME
    return ThisCall<bool>(0x546EE0, this, apActorBase);
#else
    return ThisCall<bool>(0x631AF0, this, apActorBase);
#endif
}

#ifdef GAME
// GAME - 0x555AD0
float TESObjectCELL::GetNorthRotation() const {
    return ThisCall<float>(0x555AD0, this);
}

// GAME - 0x555BC0
SeenData* TESObjectCELL::GetSeenData() const {
    return ThisCall<SeenData*>(0x555BC0, this);
}

// GAME - 0x555BE0
void TESObjectCELL::ClearSeenData() {
    ThisCall(0x555BE0, this);
}

// GAME - 0x555C20
void TESObjectCELL::UpdateSeenDataForPlayer() {
    ThisCall(0x555C20, this);
}

// GAME - 0x555F60
void TESObjectCELL::UpdateSeenData(const NiPoint3& arPos) {
    ThisCall(0x555F60, this, &arPos);
}

IntSeenData* TESObjectCELL::GetIntSeenSection(int32_t aiSectionX, int32_t aiSectionY) const {
    return const_cast<TESObjectCELL*>(this)->GetIntSeenSection(aiSectionX, aiSectionY, false);
}

// GAME - 0x556EF0
IntSeenData* TESObjectCELL::GetIntSeenSection(int32_t aiSectionX, int32_t aiSectionY, bool abCreate) {
    return ThisCall<IntSeenData*>(0x556EF0, this, aiSectionX, aiSectionY, abCreate);
}

// GAME - 0x556870
int32_t TESObjectCELL::GetSeenValue(const NiPoint3& arPos) const {
    return ThisCall<int32_t>(0x556870, this, &arPos);
}

// GAME - 0x879BB0
float TESObjectCELL::GetSeenDataUpdateRadius() {
    return CdeclCall<float>(0x879BB0);
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
#endif