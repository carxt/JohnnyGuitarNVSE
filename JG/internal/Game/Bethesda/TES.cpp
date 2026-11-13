#include "TES.hpp"
#ifdef GAME
#include "TESLandTexture.hpp"
#endif

TES* TES::GetSingleton() {
#ifdef GAME
	return *reinterpret_cast<TES**>(0x11DEA10);
#else
	return *reinterpret_cast<TES**>(0xECF93C);
#endif
}

// GAME - 0x8D8520
Sky* TES::GetSky() const {
	return pSky;
}

// GAME - 0x84E3A0
NiNode* TES::GetRoot() const {
    return pObjRoot;
}

// GAME - 0x70EC90
TESWaterSystem* TES::GetWaterSystem() const {
    return pWaterSystem;
}

// GAME - 0x4FD3E0
TESWorldSpace* TES::GetWorldSpace() const {
	return pWorldSpace;
}

// GAME - 0x5F36F0
TESObjectCELL* TES::GetInterior() const {
	return pInteriorCell;
}

// GAME - 0x457070
// GECK - 0x4C98B0
TESObjectCELL* TES::GetCurrentCell() const {
#ifdef GAME
    return ThisCall<TESObjectCELL*>(0x457070, this);
#else
    return ThisCall<TESObjectCELL*>(0x4C98B0, this);
#endif
}

// GAME - 0x451900
// GECK - 0x4C8EE0
TESObjectCELL* TES::GetGridCellCell(int32_t aiX, int32_t aiY) const {
#ifdef GAME
    return ThisCall<TESObjectCELL*>(0x451900, this, aiX, aiY);
#else
    return ThisCall<TESObjectCELL*>(0x4C8EE0, this, aiX, aiY);
#endif
}

// GAME - 0x4519D0
TESObjectCELL* TES::GetCellForPoint(NiPoint3 akPoint) const {
#ifdef GAME
	return ThisCall<TESObjectCELL*>(0x4519D0, this, akPoint);
#else
    if (GetInterior())
        return GetInterior();

    TESObjectCELL* pCell = GetGridCellCell(int32_t(akPoint.x) >> 12, int32_t(akPoint.y) >> 12);
    if (pCell && IsCellLoaded(pCell, true))
        return pCell;

    return nullptr;
#endif
}

// GAME - 0x45AF00
// GECK - 0x4C84E0
NavMeshInfoMap* TES::GetNavMeshInfoMap() {
#ifdef GAME
	return ThisCall<NavMeshInfoMap*>(0x45AF00, this);
#else
	return ThisCall<NavMeshInfoMap*>(0x4C84E0, this);
#endif
}

// GAME - 0x43B5D0
BSSimpleList<NiPointer<ImageSpaceModifierInstance>>* TES::GetActiveImageSpaceModifiers() {
	return &kActiveImageSpaceModifiers;
}

// GAME - 0x55AC00
BSSimpleList<TESObjectREFR*>* TES::GetBedsAndChairs() {
    return &kBedsAndChairs;
}

// GAME - 0x451530
// GECK - 0x43DA10
bool TES::IsRunningCellTests() const {
#ifdef GAME
    return ThisCall<bool>(0x451530, this);
#else
    return ThisCall<bool>(0x43DA10, this);
#endif
}

// GAME - 0x458E20
// GECK - 0x4C8430
void TES::AddTempDebugObject(NiAVObject* apObject, float afTime) {
#ifdef GAME
    ThisCall(0x458E20, this, apObject, afTime);
#else
	ThisCall(0x4C8430, this, apObject, afTime);
#endif
}

// GAME - 0x4511E0
// GECK - 0x4C7C30
bool TES::IsCellLoaded(const TESObjectCELL* apCell, bool abIgnoreBuffered) const {
#ifdef GAME
    return ThisCall<bool>(0x4511E0, this, apCell, abIgnoreBuffered);
#else
    return ThisCall<bool>(0x4C7C30, this, apCell, abIgnoreBuffered);
#endif
}

// GAME - 0x458BE0
// GECK - 0x4C8250
IO_TASK_PRIORITY TES::GetCellPriority(TESObjectCELL* apCell, NiPoint3* apPos) const {
#ifdef GAME
    return ThisCall<IO_TASK_PRIORITY>(0x458BE0, this, apCell, apPos);
#else
	return ThisCall<IO_TASK_PRIORITY>(0x4C8250, this, apCell, apPos);
#endif
}

// GAME - 0x451E40
// GECK - 0x4C7D50
bool TES::CanAttach3D(TESObjectREFR* apRef) {
#ifdef GAME
    return ThisCall<bool>(0x451E40, this, apRef);
#else
    return ThisCall<bool>(0x4C7D50, this, apRef);
#endif
}

// GAME - 0x457050
GridCell* TES::GetGridCell(int32_t aX, int32_t aY) {
    return pGridCellArray->GetCell(aX, aY);
}

// GAME - 0x4572E0
// GECK - 0x4C9A00
bool TES::GetLandHeight(const NiPoint3& arPosition, float& arfHeight) const {
#ifdef GAME
    return ThisCall<bool>(0x4572E0, this, &arPosition, &arfHeight);
#else
	return ThisCall<bool>(0x4C9A00, this, &arPosition, &arfHeight);
#endif
}

#ifdef GAME
// GAME - 0x4573F0
bool TES::GetLandNormal(const NiPoint3& arPosition, NiPoint3& arNormal, NiPoint3& arFaceNormal) const {
	return ThisCall<bool>(0x4573F0, this, &arPosition, &arNormal, &arFaceNormal);
}

// GAME - 0x457520
bool TES::GetLandColor(const NiPoint3& arPosition, NiColorA& arColor) const {
	return ThisCall<bool>(0x457520, this, &arPosition, &arColor);
}

// GAME - 0x457720
TESLandTexture* TES::GetLandTexture(const NiPoint3& arPosition) const {
    return ThisCall<TESLandTexture*>(0x457720, this, &arPosition);
}

float TES::GetLandFrictionValue(const NiPoint3& arPosition) const {
    const TESLandTexture* const pTexture = GetLandTexture(arPosition);
    return pTexture ? pTexture->GetHavokFrictionValue() : 0.3f;
}

float TES::GetLandRestitutionValue(const NiPoint3& arPosition) const {
    const TESLandTexture* const pTexture = GetLandTexture(arPosition);
    return pTexture ? pTexture->GetHavokRestitutionValue() : 0.3f;
}
#endif

// GAME - 0x457620
// GECK - 0x4C9BC0
NiGeometry* TES::GetLandGeometry(const NiPoint2& arPosition) const {
#ifdef GAME
    return ThisCall<NiGeometry*>(0x457620, this, &arPosition);
#else
	return ThisCall<NiGeometry*>(0x4C9BC0, this, &arPosition);
#endif
}

#ifdef GAME
// GAME - 0x458440
NiAVObject* TES::Pick(bhkPickData& arPickData, bool abHavok) const {
	return ThisCall<NiAVObject*>(0x458440, this, &arPickData, abHavok);
}

// GAME - 0x458420
NiAVObject* TES::HavokPick(bhkPickData& arPickData) const {
    return ThisCall<NiAVObject*>(0x458420, this, &arPickData);
}
#endif

// GAME - 0x4568C0
// GECK - 0x4C9510
void TES::CreateTextureImage(const char* apPath, NiTexturePtr& aspTexture, bool abNoFileOK, bool abArchiveOnly) {
#ifdef GAME
    ThisCall(0x4568C0, this, apPath, &aspTexture, abNoFileOK, abArchiveOnly);
#else
    ThisCall(0x4C9510, this, apPath, &aspTexture, abNoFileOK, abArchiveOnly);
#endif
}

// GAME - 0x457BA0
// GECK - 0x4C9DD0
NiObject* TES::CreateDeepCopySameTextures(NiObject* apObject, NiCloningProcess& arCloneProc) {
#ifdef GAME
    return ThisCall<NiObject*>(0x457BA0, apObject, &arCloneProc);
#else
    return ThisCall<NiObject*>(0x4C9DD0, apObject, &arCloneProc);
#endif
}

// GAME - 0x457A00
// GECK - 0x4C9C90
void TES::CloneModelData(NiObject* apObject) {
#ifdef GAME
    CdeclCall(0x457A00, apObject);
#else
    CdeclCall(0x4C9C90, apObject);
#endif
}

// GAME - 0x45CBC0
// GECK - 0x4C87B0
float TES::GetWaterHeight(const NiPoint3& arPos, const TESObjectCELL* apCell) const {
#ifdef GAME
    return ThisCall<float>(0x45CBC0, this, &arPos, apCell);
#else
    return ThisCall<float>(0x4C87B0, this, &arPos, apCell);
#endif
}