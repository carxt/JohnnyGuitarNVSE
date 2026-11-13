#pragma once

#include "BSEnums.hpp"
#include "FaceGen/FR2MatrixVTC.hpp"

class BSFaceGenManager {
public:
	static void InitFaceGenCoord(FaceGenCoords* apCoords);
	static void CopyFaceGenCoord(const FaceGenCoords* apSource, FaceGenCoords* apTarget, bool abGeometryOnly, bool abTextureOnly);

	static void RandomizeFaceGenetic(float afVariation, const FaceGenCoords* apSource, FaceGenCoords* apTarget);
	static void OffsetFaceGenCoord(const FaceGenCoords* apSourceOld, const FaceGenCoords* apSourceNew, FaceGenCoords* apTarget, bool abNoTextureOffset);

	static bool CompareFaceGenCoord(const FaceGenCoords* apA, const FaceGenCoords* apB);

	static float GetFaceCoordAttribute(const FaceGenCoords* apCoords, FaceGenAttributeType aeAttribute, FaceGenDataType aeType);
	static void SetFaceCoordAttribute(FaceGenCoords* apCoords, FaceGenAttributeType aeAttribute, FaceGenDataType aeType, float afValue);

	static float GetFaceCoordValue(const FaceGenCoords* apCoords, FaceGenDataType aeType, FaceGenSymmetryType aeSymmetry, uint32_t auiCtrlID);
	static void SetFaceCoordValue(FaceGenCoords* apCoords, FaceGenDataType aeType, FaceGenSymmetryType aeSymmetry, uint32_t auiCtrlID, float afValue);
};

//ASSERT_SIZE(BSFaceGenManager, 0x11A4);