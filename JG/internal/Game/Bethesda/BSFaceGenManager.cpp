#include "BSFaceGenManager.hpp"

// GAME - 0x6521F0
// GECK - 0x68E8F0
void BSFaceGenManager::InitFaceGenCoord(FaceGenCoords* apCoords) {
#ifdef GAME
    CdeclCall(0x6521F0, apCoords);
#else
    CdeclCall(0x68E8F0, apCoords);
#endif
}

// GAME - 0x6529A0
// GECK - 0x68E960
void BSFaceGenManager::CopyFaceGenCoord(const FaceGenCoords* apSource, FaceGenCoords* apTarget, bool abGeometryOnly, bool abTextureOnly) {
#ifdef GAME
    CdeclCall(0x6529A0, apSource, apTarget, abGeometryOnly, abTextureOnly);
#else
    CdeclCall(0x68E960, apSource, apTarget, abGeometryOnly, abTextureOnly);
#endif
}

// GAME - 0x652FC0
// GECK - 0x690590
void BSFaceGenManager::RandomizeFaceGenetic(float afVariation, const FaceGenCoords* apSource, FaceGenCoords* apTarget) {
#ifdef GAME
    CdeclCall(0x652FC0, afVariation, apSource, apTarget);
#else
    CdeclCall(0x690590, afVariation, apSource, apTarget);
#endif
}

// GAME - 0x652E00
// GECK - 0x68ED20
void BSFaceGenManager::OffsetFaceGenCoord(const FaceGenCoords* apSourceOld, const FaceGenCoords* apSourceNew, FaceGenCoords* apTarget, bool abNoTextureOffset) {
#ifdef GAME
    CdeclCall(0x652E00, apSourceOld, apSourceNew, apTarget, abNoTextureOffset);
#else
    CdeclCall(0x68ED20, apSourceOld, apSourceNew, apTarget, abNoTextureOffset);
#endif
}

// GAME - 0x652900
// GECK - 0x68CE20
bool BSFaceGenManager::CompareFaceGenCoord(const FaceGenCoords* apA, const FaceGenCoords* apB) {
#ifdef GAME
    return CdeclCall<bool>(0x652900, apA, apB);
#else
    return CdeclCall<bool>(0x68CE20, apA, apB);
#endif
}

// GAME - 0x652440
// GECK - 0x690470
float BSFaceGenManager::GetFaceCoordAttribute(const FaceGenCoords* apCoords, FaceGenAttributeType aeAttribute, FaceGenDataType aeType) {
#ifdef GAME
    return CdeclCall<float>(0x652440, apCoords, aeAttribute, aeType);
#else
    return CdeclCall<float>(0x690470, apCoords, aeAttribute, aeType);
#endif
}

// GAME - 0x652470
// GECK - 0x692C20
void BSFaceGenManager::SetFaceCoordAttribute(FaceGenCoords* apCoords, FaceGenAttributeType aeAttribute, FaceGenDataType aeType, float afValue) {
#ifdef GAME
    CdeclCall(0x652470, apCoords, aeAttribute, aeType, afValue);
#else
    CdeclCall(0x692C20, apCoords, aeAttribute, aeType, afValue);
#endif
}

// GAME - 0x652230
// GECK - 0x690260
float BSFaceGenManager::GetFaceCoordValue(const FaceGenCoords* apCoords, FaceGenDataType aeType, FaceGenSymmetryType aeSymmetry, uint32_t auiCtrlID) {
#ifdef GAME
    return CdeclCall<float>(0x652230, apCoords, aeType, aeSymmetry, auiCtrlID);
#else
    return CdeclCall<float>(0x690260, apCoords, aeType, aeSymmetry, auiCtrlID);
#endif
}

// GAME - 0x652320
// GECK - 0x690330
void BSFaceGenManager::SetFaceCoordValue(FaceGenCoords* apCoords, FaceGenDataType aeType, FaceGenSymmetryType aeSymmetry, uint32_t auiCtrlID, float afValue) {
#ifdef GAME
    CdeclCall(0x652320, apCoords, aeType, aeSymmetry, auiCtrlID, afValue);
#else
    CdeclCall(0x690330, apCoords, aeType, aeSymmetry, auiCtrlID, afValue);
#endif
}