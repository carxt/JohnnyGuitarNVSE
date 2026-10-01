#include "TESWorldSpace.hpp"

// GECK - 0x6666D0
uint32_t TESWorldSpace::GetCellCount() const {
    return pCellMap->GetCount();
}

// GAME - 0x587670
// GECK - 0x666380
bool TESWorldSpace::AddCell(TESObjectCELL* apCell) {
#ifdef GAME
    return ThisCall<bool>(0x587670, this, apCell);
#else
    return ThisCall<bool>(0x666380, this, apCell);
#endif
}

// GAME - 0x587760
// GECK - 0x666550
void TESWorldSpace::ReleaseCell(TESObjectCELL* apCell) {
#ifdef GAME
    ThisCall(0x587760, this, apCell);
#else
    ThisCall(0x666550, this, apCell);
#endif
}

#ifdef GAME
// GAME - 0x585B30
TESObjectCELL* TESWorldSpace::LoadCell(int32_t aiX, int32_t aiY) {
    return ThisCall<TESObjectCELL*>(0x585B30, this, aiX, aiY);
}

// GAME - 0x585E00
void TESWorldSpace::UnloadCell(TESObjectCELL* apCell) {
    ThisCall(0x585E00, this, apCell);
}
#endif

// GAME - 0x587550
// GECK - 0x6699B0
TESObjectCELL* TESWorldSpace::GetCellFromWorldCoord(const NiPoint3& arPos) const {
#ifdef GAME
    return ThisCall<TESObjectCELL*>(0x587550, this, &arPos);
#else
    return ThisCall<TESObjectCELL*>(0x6699B0, this, &arPos);
#endif
}

// GAME - 0x5875A0
// GECK - 0x6662D0
TESObjectCELL* TESWorldSpace::GetCellFromCellCoord(int32_t aiX, int32_t aiY) const {
#ifdef GAME
    return ThisCall<TESObjectCELL*>(0x5875A0, this, aiX, aiY);
#else
    return ThisCall<TESObjectCELL*>(0x6662D0, this, aiX, aiY);
#endif
}

// GAME - 0x587630
// GECK - 0x666350
TESObjectCELL* TESWorldSpace::GetCellFromKey(int32_t aiKey) const {
#ifdef GAME
    return ThisCall<TESObjectCELL*>(0x587630, this, aiKey);
#else
    return ThisCall<TESObjectCELL*>(0x666350, this, aiKey);
#endif
}

#ifdef GAME
// GAME - 0x588560
TESObjectCELL* TESWorldSpace::GetCellByEditorID(const char* apEDID) const {
    return ThisCall<TESObjectCELL*>(0x588560, this, apEDID);
}
#endif

// GAME - 0x5877E0
// GECK - 0x6665B0
void TESWorldSpace::ClearCellMap() {
#ifdef GAME
    ThisCall(0x5877E0, this);
#else
    ThisCall(0x6665B0, this);
#endif
}

// GECK - 0x665620
TESObjectCELL* TESWorldSpace::GetPersistentCell() const {
    return pPersistentCell;
}

// GAME - 0x588070
// GECK - 0x665630
TESObjectCELL* TESWorldSpace::CreatePersistentCell() {
#ifdef GAME
    return ThisCall<TESObjectCELL*>(0x588070, this);
#else
    return ThisCall<TESObjectCELL*>(0x665630, this);
#endif
}

// GAME - 0x586170
// GECK - 0x6662A0
BGSTerrainManager* TESWorldSpace::GetTerrainManager() const {
#ifdef GAME
    return ThisCall<BGSTerrainManager*>(0x586170, this);
#else
    return ThisCall<BGSTerrainManager*>(0x6662A0, this);
#endif
}

// GAME - 0x585FE0
// GECK - 0x6661B0
TESClimate* TESWorldSpace::GetClimate() const {
#ifdef GAME
    return ThisCall<TESClimate*>(0x585FE0, this);
#else
    return ThisCall<TESClimate*>(0x6661B0, this);
#endif
}

// GAME - 0x87CE80
void TESWorldSpace::SetClimate(TESClimate* apClimate) {
    pClimate = apClimate;
}

// GAME - 0x586020
// GECK - 0x6661E0
TESImageSpace* TESWorldSpace::GetImageSpace() const {
#ifdef GAME
    return ThisCall<TESImageSpace*>(0x586020, this);
#else
    return ThisCall<TESImageSpace*>(0x6661E0, this);
#endif
}

// GAME - 0x8D8040
void TESWorldSpace::SetImageSpace(TESImageSpace* apImageSpace) {
    pImageSpace = apImageSpace;
}

// GAME - 0x6733E0
ImpactSwap* TESWorldSpace::GetImpactSwap() const {
    return pImpactSwap;
}

// GAME - 0x5861B0
// GECK - 0x665480
bool TESWorldSpace::GetSmallWorld() const {
#ifdef GAME
    return ThisCall<bool>(0x5861B0, this);
#else
    return ThisCall<bool>(0x665480, this);
#endif
}

// GAME - 0x5861D0
void TESWorldSpace::SetSmallWorld(bool abVal) {
#ifdef GAME
    ThisCall(0x5861D0, this, abVal);
#else
    ucWorldFlags.bSmallWorld = abVal;
#endif
}

// GAME - 0x586210
bool TESWorldSpace::GetCantTravelFrom() const {
#ifdef GAME
    return ThisCall<bool>(0x586210, this);
#else
    return ucWorldFlags.bNoFastTravel;
#endif
}

void TESWorldSpace::SetCantTravelFrom(bool abVal) {
    ucWorldFlags.bNoFastTravel = abVal;
}

// GAME - 0x586230
bool TESWorldSpace::GetCantWaitHere() const {
#ifdef GAME
    return ThisCall<bool>(0x586230, this);
#else
    return uiFormFlags.Get<FormFlags::CANT_WAIT>();
#endif
}

void TESWorldSpace::SetCantWaitHere(bool abVal) {
    uiFormFlags.Set<FormFlags::CANT_WAIT>(abVal);
}

// GAME - 0x586260
bool TESWorldSpace::GetHasBorderRegion() const {
#ifdef GAME
    return ThisCall<bool>(0x586260, this);
#else
    return ucWorldFlags.bHasBorderRegion;
#endif
}

// GAME - 0x586280
void TESWorldSpace::SetHasBorderRegion(bool abVal) {
#ifdef GAME
    ThisCall(0x586280, this, abVal);
#else
    ucWorldFlags.bHasBorderRegion = abVal;
#endif
}

// GAME - 0x5862C0
bool TESWorldSpace::GetNoLODWater() const {
#ifdef GAME
    return ThisCall<bool>(0x5862C0, this);
#else
    return ucWorldFlags.bNoLODWater;
#endif
}

void TESWorldSpace::SetNoLODWater(bool abVal) {
    ucWorldFlags.bNoLODWater = abVal;
}

// GAME - 0x5862E0
// GECK - 0x6654A0
bool TESWorldSpace::GetNoLODNoise() const {
#ifdef GAME
    return ThisCall<bool>(0x5862E0, this);
#else
    return ThisCall<bool>(0x6654A0, this);
#endif
}

void TESWorldSpace::SetNoLODNoise(bool abVal) {
    ucWorldFlags.bNoLODNoise = abVal;
}

// GAME - 0x586320
bool TESWorldSpace::GetAllowsNPCFallDamage() const {
#ifdef GAME
    return ThisCall<bool>(0x586320, this);
#else
    return !ucWorldFlags.bNoNPCFallDamage;
#endif
}

void TESWorldSpace::SetAllowsNPCFallDamage(bool abVal) {
    ucWorldFlags.bNoNPCFallDamage = !abVal;
}

// GAME - 0x586300
bool TESWorldSpace::GetNeedsWaterAdjustment() const {
#ifdef GAME
    return ThisCall<bool>(0x586300, this);
#else
    return ucWorldFlags.bNeedsWaterAdjustment;
#endif
}

void TESWorldSpace::SetNeedsWaterAdjustment(bool abVal) {
    ucWorldFlags.bNeedsWaterAdjustment = abVal;
}

// GAME - 0x586340
bool TESWorldSpace::GetParentUseFlag(ParentUseBit auiBit) const {
#ifdef GAME
    return ThisCall<bool>(0x586340, this, auiBit);
#else
    return auiBit >= ParentUseBit::COUNT || usParentUseFlags.GetBit(auiBit);
#endif
}

void TESWorldSpace::SetParentUseFlag(ParentUseBit auiBit, bool abVal) {
    usParentUseFlags.SetBit(auiBit, abVal);
}

// GAME - 0x587FF0
// GECK - 0x666640
void TESWorldSpace::AddPersistentRef(TESObjectREFR* apRef) {
#ifdef GAME
    ThisCall(0x587FF0, this, apRef);
#else
    ThisCall(0x666640, this, apRef);
#endif
}

// GAME - 0x588030
// GECK - 0x666670
void TESWorldSpace::RemovePersistentRef(TESObjectREFR* apRef) {
#ifdef GAME
    ThisCall(0x588030, this, apRef);
#else
    ThisCall(0x666670, this, apRef);
#endif
}

#ifdef GAME
// GAME - 0x587D10
void TESWorldSpace::AddToPersistentRefData(TESObjectREFR* apRef) {
    ThisCall(0x587D10, this, apRef);
}

// GAME - 0x587E40
void TESWorldSpace::RemoveFromPersistentRefData(TESObjectREFR* apRef) {
    ThisCall(0x587E40, this, apRef);
}

// GAME - 0x587F40
void TESWorldSpace::ClearPersistentRefData() const {
    ThisCall(0x587F40, this);
}

// GAME - 0x588150
void TESWorldSpace::AssignPersistentRefsToCell(TESObjectCELL* apCell) {
    ThisCall(0x588150, this, apCell);
}

// GAME - 0x587870
BSSimpleList<TESObjectREFR*>* TESWorldSpace::GetOverlappedMultiBoundRefs(TESObjectCELL* apCell) const {
    return ThisCall<BSSimpleList<TESObjectREFR*>*>(0x587870, this, apCell);
}

// GAME - 0x5878D0
void TESWorldSpace::AddMultiBoundRef(TESObjectREFR* apRef) {
    ThisCall(0x5878D0, this, apRef);
}

// GAME - 0x587BB0
void TESWorldSpace::ClearMultiBoundRefs() {
    ThisCall(0x587BB0, this);
}
#endif

BSPortalGraph* TESWorldSpace::GetPortalGraph() const {
    return spPortalGraph.m_pObject;
}

// GAME - 0x5831D0
// GECK - 0x6659B0
BSPortalGraph* TESWorldSpace::CreatePortalGraph() {
#ifdef GAME
    return ThisCall<BSPortalGraph*>(0x5831D0, this);
#else
    return ThisCall<BSPortalGraph*>(0x6659B0, this);
#endif
}

// GAME - 0x586390
// GECK - 0x6654B0
TESWorldSpace* TESWorldSpace::GetParentWorld(ParentUseBit auiBit) const {
#ifdef GAME
    return ThisCall<TESWorldSpace*>(0x586390, this, auiBit);
#else
    return ThisCall<TESWorldSpace*>(0x6654B0, this, auiBit);
#endif
}

TESWorldSpace* TESWorldSpace::GetParentWorldSimple() const {
    return pParentWorld;
}

// GAME - 0x5863D0
void TESWorldSpace::SetParentWorld(TESWorldSpace* apWorld) {
#ifdef GAME
    ThisCall(0x5863D0, this, apWorld);
#else
    pParentWorld = apWorld;
    if (!apWorld)
        usParentUseFlags.Clear();
#endif
}

// GAME - 0x586070
// GECK - 0x666210
TESWaterForm* TESWorldSpace::GetWaterType() const {
#ifdef GAME
    return ThisCall<TESWaterForm*>(0x586070, this);
#else
    return ThisCall<TESWaterForm*>(0x666210, this);
#endif
}

// GAME - 0x4FEBB0
void TESWorldSpace::SetWaterType(TESWaterForm* apWater) {
    pWorldWater = apWater;
}

// GAME - 0x5860C0
// GECK - 0x666240
TESWaterForm* TESWorldSpace::GetLODWaterType() const {
#ifdef GAME
    return ThisCall<TESWaterForm*>(0x5860C0, this);
#else
    return ThisCall<TESWaterForm*>(0x666240, this);
#endif
}

// GAME - 0x442A80
void TESWorldSpace::SetLODWaterType(TESWaterForm* apWater) {
    pLODWater = apWater;
}

// GAME - 0x45CD80
float TESWorldSpace::GetWaterLODHeight() const {
    return fWaterLODHeight;
}

// GAME - 0x584150
void TESWorldSpace::SetWaterLODHeight(float afHeight) {
    fWaterLODHeight = afHeight;
}

// GAME - 0x586400
// GECK - 0x6654E0
TESWorldSpace::MapData* TESWorldSpace::GetWorldMapData() const {
#ifdef GAME
    return ThisCall<MapData*>(0x586400, this);
#else
    return ThisCall<MapData*>(0x6654E0, this);
#endif
}

// GAME - 0x586440
const char* TESWorldSpace::GetWorldMapTextureName() const {
#ifdef GAME
    return ThisCall<const char*>(0x586440, this);
#else
    TESWorldSpace* pParentWorld = GetParentWorld(ParentUseBit::MAP);
    if (!pParentWorld)
        return GetTextureName();
    return pParentWorld->GetTextureName();
#endif
}

void TESWorldSpace::SetWorldMapTextureName(const char* apName) {
    SetTextureName(apName);
}

float TESWorldSpace::GetWorldMapScale() const {
    return kMapOffsetData.fMapScale;
}

void TESWorldSpace::SetWorldMapScale(float afScale) {
    kMapOffsetData.fMapScale = afScale;
}

float TESWorldSpace::GetWorldMapOffsetX() const {
    return kMapOffsetData.fMapOffsetX;
}

void TESWorldSpace::SetWorldMapOffsetX(float afOffset) {
    kMapOffsetData.fMapOffsetX = afOffset;
}

float TESWorldSpace::GetWorldMapOffsetY() const {
    return kMapOffsetData.fMapOffsetY;
}

void TESWorldSpace::SetWorldMapOffsetY(float afOffset) {
    kMapOffsetData.fMapOffsetY = afOffset;
}

// GAME - 0x586150
BGSMusicType* TESWorldSpace::GetMusicType() const {
    return pMusicType;
}

// GAME - 0x810570
void TESWorldSpace::SetMusicType(BGSMusicType* apType) {
    pMusicType = apType;
}

// GAME - 0x4565F0
float TESWorldSpace::GetMinimumXCoord() const {
    return kMinCoords.x;
}

// GAME - 0x812870
float TESWorldSpace::GetMinimumYCoord() const {
    return kMinCoords.y;
}

// GAME - 0x9B88A0
float TESWorldSpace::GetMaximumXCoord() const {
    return kMaxCoords.x;
}

// GAME - 0x9B88C0
float TESWorldSpace::GetMaximumYCoord() const {
    return kMaxCoords.y;
}

// GAME - 0x9A1260
// GECK - 0x5FD3D0
float TESWorldSpace::GetDefaultLandHeight() const {
    return fDefaultLandHeight;
}

// GAME - 0x586110
void TESWorldSpace::SetDefaultLandHeight(float afHeight) {
    fDefaultLandHeight = afHeight;
}

// GAME - 0x4536E0
// GECK - 0x5FD3F0
float TESWorldSpace::GetDefaultWaterHeight() const {
    return fDefaultWaterHeight;
}

// GAME - 0x586130
void TESWorldSpace::SetDefaultWaterHeight(float afHeight) {
    fDefaultWaterHeight = afHeight;
}

// GAME - 0x458400
BGSEncounterZone* TESWorldSpace::GetEncounterZone() const {
    return pEncounterZone;
}

// GAME - 0x584BC0
void TESWorldSpace::SetEncouterZone(BGSEncounterZone* apZone) {
    pEncounterZone = apZone;
}

// GAME - 0x548210
const char* TESWorldSpace::GetCanopyShadowTextureName() const {
#ifdef GAME
    return ThisCall<const char*>(0x548210, this);
#else
    return kCanopyShadowTexture.GetTextureName();
#endif
}

void TESWorldSpace::SetCanopyShadowTextureName(const char* apName) {
    kCanopyShadowTexture.SetTextureName(apName);
}

// GAME - 0x454B50
const char* TESWorldSpace::GetWaterNoiseTextureName() const {
#ifdef GAME
    return ThisCall<const char*>(0x454B50, this);
#else
    return kWaterNoiseTexture.GetTextureName();
#endif
}

void TESWorldSpace::SetWaterNoiseTextureName(const char* apName) {
    kWaterNoiseTexture.SetTextureName(apName);
}

// GAME - 0x5854F0
// GECK - 0x6652B0
bool TESWorldSpace::FindCellInFile(TESFile* apFile, int32_t aiX, int32_t aiY) const {
#ifdef GAME
    return ThisCall<bool>(0x5854F0, this, apFile, aiX, aiY);
#else
	return ThisCall<bool>(0x6652B0, this, apFile, aiX, aiY);
#endif
}

#ifdef GAME
// GAME - 0x588B00
TESWorldSpace::OFFSET_DATA* TESWorldSpace::CreateOffsetData(const TESFile* apFile) {
    return ThisCall<OFFSET_DATA*>(0x588B00, this, apFile);
}

// GAME - 0x588A90
TESWorldSpace::OFFSET_DATA* TESWorldSpace::GetOffsetData(const TESFile* apFile) const {
    return ThisCall<OFFSET_DATA*>(0x588A90, this, apFile);
}

// GAME - 0x584530
uint32_t TESWorldSpace::GetIndexForCellCoord(const TESFile* apFile, int32_t aiX, int32_t aiY) const {
    return ThisCall<uint32_t>(0x584530, this, apFile, aiX, aiY);
}

// GAME - 0x585940
bool TESWorldSpace::GetExtCellDataFromFileByEditorID(const char* apCellID, int32_t& aiOutX, int32_t& aiOutY) {
    return ThisCall<bool>(0x585940, this, apCellID, &aiOutX, &aiOutY);
}

// GAME - 0x587C80
bool TESWorldSpace::IsFixedRef(const TESObjectREFR* apRef) {
    return CdeclCall<bool>(0x587C80, apRef);
}
#endif

// GAME - 0x587440
// GECK - 0x665520
uint32_t TESWorldSpace::GetKeyForWorldCoord(NiPoint3& arPoint) {
#ifdef GAME
    return CdeclCall<uint32_t>(0x587440, &arPoint);
#else
    return CdeclCall<uint32_t>(0x665520, &arPoint);
#endif
}