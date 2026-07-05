#include "TESObjectLAND.hpp"

// GAME - 0x534140
// GECK - 0x614690
bool TESObjectLAND::GetLandRemapped() const {
#ifdef GAME
    return kData.uiFlags.bLandRemapped;
#else
    const TESObjectCELL* pCell = GetParentCell();
    if (!pCell)
        return false;

	const TESWorldSpace* pWorldSpace = pCell->GetWorldSpace();
    if (!pWorldSpace)
        return false;
	
    return pWorldSpace->GetParentWorld(TESWorldSpace::ParentUseBit::LAND); 
#endif
}

// GAME - 0x5394A0
bool TESObjectLAND::IsLoaded() const {
    return kData.uiFlags.bLoaded;
}

// GAME - 0x7AF430
TESObjectCELL* TESObjectLAND::GetParentCell() const {
    return pParentCell;
}

// GAME - 0x535AF0
// GECK - 0x616CB0
NiNode* TESObjectLAND::GetLandNode(uint32_t auiNode) const {
#ifdef GAME
	return ThisCall<NiNode*>(0x535AF0, this, auiNode);
#else
	return ThisCall<NiNode*>(0x616CB0, this, auiNode);
#endif
}

// GAME - 0x53F440
// GECK - 0x618B10
NiPoint2 TESObjectLAND::GetMinMaxLandHeight() const {
#ifdef GAME
    return ThisCall<NiPoint2>(0x53F440, this);
#else
    return ThisCall<NiPoint2>(0x618B10, this);
#endif
}

// GAME - 0x53F390
// GECK - 0x618A90
NiPoint2 TESObjectLAND::GetMinMaxBlockHeight(uint32_t auiBlock) const {
#ifdef GAME
	return ThisCall<NiPoint2>(0x53F390, this, auiBlock);
#else
	return ThisCall<NiPoint2>(0x618A90, this, auiBlock);
#endif
}

// GAME - 0x53B550
// GECK - 0x617440
bool TESObjectLAND::GetCoordData(COORD_DATA& arCoordData, const NiPoint3& arCoord, bool abForceToVertex) const {
#ifdef GAME
    return ThisCall<bool>(0x53B550, this, &arCoordData, &arCoord, abForceToVertex);
#else
	return ThisCall<bool>(0x617440, this, &arCoordData, &arCoord, abForceToVertex);
#endif
}

// GAME - 0x53F180
// GECK - 0x61A810
bool TESObjectLAND::GetLandHeight(const NiPoint3& arPoint, float& arfHeight) const {
#ifdef GAME
    return ThisCall<bool>(0x53F180, this, &arPoint, &arfHeight);
#else
	return ThisCall<bool>(0x61A810, this, &arPoint, &arfHeight);
#endif
}

// GAME - 0x53D2E0
// GECK - 0x618030
bool TESObjectLAND::GetLandNormal(const NiPoint3& arPoint, NiPoint3& arNormal, NiPoint3& arFaceNormal) const {
#ifdef GAME
    return ThisCall<bool>(0x53D2E0, this, &arPoint, &arNormal, &arFaceNormal);
#else
	return ThisCall<bool>(0x618030, this, &arPoint, &arNormal, &arFaceNormal);
#endif
}

// GAME - 0x53CAF0
// GECK - 0x617960
bool TESObjectLAND::GetLandNormal(const COORD_DATA& arCoordData, NiPoint3& arNormal, NiPoint3& arFaceNormal) const {
#ifdef GAME
    return ThisCall<bool>(0x53CAF0, this, &arCoordData, &arNormal, &arFaceNormal);
#else
	return ThisCall<bool>(0x617960, this, &arCoordData, &arNormal, &arFaceNormal);
#endif
}

#ifdef GAME
// GAME - 0x53FA10
bool TESObjectLAND::GetLandColor(const COORD_DATA& arCoordData, NiColorA& arColor) const {
	return ThisCall<bool>(0x53FA10, this, &arCoordData, &arColor);
}
#endif

// GAME - 0x534240
// GECK - 0x6168B0
void TESObjectLAND::GetVertex(uint32_t auiBlock, uint32_t auiVertex, NiPoint3& arOut) const {
#ifdef GAME
    ThisCall(0x534240, this, auiBlock, auiVertex, &arOut);
#else
    ThisCall(0x6168B0, this, auiBlock, auiVertex, &arOut);
#endif
}

// GAME - 0x53A5E0
TESLandTexture* TESObjectLAND::GetMainTexture(const NiPoint3& arPosition) const {
    return ThisCall<TESLandTexture*>(0x53A5E0, this, &arPosition);
}

// GAME - 0x535B30
NiPoint3 TESObjectLAND::GetWorldOffsetForBlock(uint32_t auiBlock) const {
    return ThisCall<NiPoint3>(0x535B30, this, auiBlock);
}

// GAME - 0x533FD0
// GECK - 0x6145C0
int32_t TESObjectLAND::GetDataX() const {
#ifdef GAME
	return ThisCall<int32_t>(0x533FD0, this);
#else
	return ThisCall<int32_t>(0x6145C0, this);
#endif
}

// GAME - 0x534010
// GECK - 0x6145E0
int32_t TESObjectLAND::GetDataY() const {
#ifdef GAME
	return ThisCall<int32_t>(0x534010, this);
#else
	return ThisCall<int32_t>(0x6145E0, this);
#endif
}

// GAME - 0x534050
// GECK - 0x614600
float TESObjectLAND::GetWorldCellX() const {
    return float(GetDataX() << 12);
}

// GAME - 0x534080
// GECK - 0x614640
float TESObjectLAND::GetWorldCellY() const {
    return float(GetDataY() << 12);
}

// GAME - 0x53A550
float TESObjectLAND::GetDefaultWorldHeight() const {
    return ThisCall<float>(0x53A550, this);
}

#ifdef GAME
// GAME - 0x53BC10
bool TESObjectLAND::CalculateGrassParams() {
    return ThisCall<bool>(0x53BC10, this);
}
#endif

// GAME - 0x53AEB0
// GECK - 0x615640
void TESObjectLAND::SetupTextures() {
#ifdef GAME
    ThisCall(0x53AEB0, this);
#else
    ThisCall(0x615640, this);
#endif
}

// GAME - 0x539960
// GECK - 0x61A9C0
bool TESObjectLAND::InitLandscape() {
#ifdef GAME
    return ThisCall<bool>(0x539960, this);
#else
    return ThisCall<bool>(0x61A9C0, this);
#endif
}

// GAME - 0x539500
bool TESObjectLAND::CreateLandscape(TESObjectLAND* apCopyFrom) {
    return ThisCall<bool>(0x539500, this, apCopyFrom);
}

// GAME - 0x535B90
// GECK - 0x61E3C0
bool TESObjectLAND::LoadVertices(bool abLoad3D) {
#ifdef GAME
	return ThisCall<bool>(0x535B90, this, abLoad3D);
#else
	return ThisCall<bool>(0x61E3C0, this, abLoad3D);
#endif
}

// GAME - 0x536D80
bool TESObjectLAND::UnloadVertices() {
    return ThisCall<bool>(0x536D80, this);
}

// GAME - 0x535D00
// GECK - 0x61BC70
bool TESObjectLAND::LoadVerticesIntoArrays() {
#ifdef GAME
	return ThisCall<bool>(0x535D00, this);
#else
	return ThisCall<bool>(0x61BC70, this);
#endif
}

// GAME - 0x5374F0
// GECK - 0x61B710
void TESObjectLAND::Attach3D() {
#ifdef GAME
    ThisCall(0x5374F0, this);
#else
    ThisCall(0x61B710, this);
#endif
}

// GAME - 0x537EB0
void TESObjectLAND::Detach3D() {
    ThisCall(0x537EB0, this);
}