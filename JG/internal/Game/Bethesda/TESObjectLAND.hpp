#pragma once

#include "BSSimpleArray.hpp"
#include "Gamebryo/NiColor.hpp"
#include "Gamebryo/NiColorA.hpp"
#include "Gamebryo/NiPoint2.hpp"
#include "Gamebryo/NiPoint3.hpp"
#include "Gamebryo/NiTPointerMap.hpp"
#include "QueuedFile.hpp"
#include "TESChildCell.hpp"
#include "TESForm.hpp"

class TESObjectCELL;
class NiNode;
class NiObject;
class TESLandTexture;
class bhkRigidBody;
class hkpMoppCode;
class NiLines;
class TESGrassAreaParam;

struct COORD_DATA {
	NiPoint2	kCellPoint;
	NiPoint2	kBlockPoint;
	tagPOINT	kBlock;
	int32_t		iBlock;
	NiPoint2	kTilePoint;
	tagPOINT	kTile;
	int32_t		iShape;
	NiPoint3	kVertCoord;
	int32_t		iVertIdx;
	int32_t		iTriVertIdx[3];
	bool		bTriRight;
	bool		bTriUpper;
};

class TESObjectLAND : public TESForm, public TESChildCell {
public:
	TESObjectLAND();
	~TESObjectLAND();

	struct LoadedLandData {
		struct Geometry {
			NiPoint3 kVertices[289];
		};

		struct Normals {
			NiPoint3 kNormals[289];
		};

		struct NormalSets {
			bool bNormalSets[289];
		};

		struct Colors {
			NiColorA kColors[289];
		};

		struct Textures {
			TESLandTexture* pLandTexture[6];
		};

		NiNode**										ppMesh;
		Geometry**										ppVertices;
		Normals**										ppNormals;
		Colors**										ppColors;
		NormalSets**									ppNormalSets;
		NiPointer<NiLines>								spBorder;
		NiPoint2										kHeights; // min, max
		TESLandTexture*									pDefQuadTexture[4];
		Textures*										pQuadTextureArray[4];
		float**											ppPercentArrays[4]; // 4 * 289 * 8
		hkpMoppCode*									pMoppCode;
		NiTPointerMap<uint32_t, TESGrassAreaParam**>	kGrassParams[4];
		NiPointer<bhkRigidBody>							spRigidBody;
		int32_t											iCellX;
		int32_t											iCellY;
		float											fBaseHeight;
	};

	struct ALIGN4 _LandscapeFlags {
		enum Flags : uint32_t {
			HAS_VTX_NORMALS		= 1u << 0,
			HAS_VTX_COLOR		= 1u << 1,
			HAS_LAYERS			= 1u << 2,
			LOADED				= 1u << 3,
			AUTO_CALC_NORMALS	= 1u << 4,
			HIGH_RES			= 1u << 5,
			UNK_6				= 1u << 6,
			UNK_7				= 1u << 7,
			UNK_8				= 1u << 8,
			UNK_9				= 1u << 9,
			LAND_REMAPPED		= 1u << 10,
			GOOD_MOPP			= 1u << 11,
		};

		bool bHasVertexNormals	: 1;
		bool bHasVertexColors	: 1;
		bool bHasLayers			: 1;
		bool bLoaded			: 1;
		bool bAutoCalcNormals	: 1;
		bool bHighRes			: 1;
		bool 					: 1;
		bool 					: 1;
		bool 					: 1;
		bool 					: 1;
		bool bLandRemapped		: 1;
		bool bGoodMopp			: 1;
	};
	using LandscapeFlags = _LandscapeFlags::Flags;

	struct Data {
		Bitfield<_LandscapeFlags>	uiFlags;
	};

	Data				kData;
	TESObjectCELL*		pParentCell;
	QueuedFilePtr		spQueuedTextures;
	LoadedLandData*		pLoadedData;

	TESFORM_TYPE(TESObjectLAND);

	bool GetLandRemapped() const;

	bool IsLoaded() const;

	TESObjectCELL* GetParentCell() const;

	NiNode* GetLandNode(uint32_t auiNode) const;

	NiPoint2 GetMinMaxLandHeight() const;

	NiPoint2 GetMinMaxBlockHeight(uint32_t auiBlock) const;

	bool GetCoordData(COORD_DATA& arCoordData, const NiPoint3& arCoord, bool abForceToVertex) const;

	bool GetLandHeight(const NiPoint3& arPoint, float& arfHeight) const;

	bool GetLandNormal(const NiPoint3& arPoint, NiPoint3& arNormal, NiPoint3& arFaceNormal) const;
	bool GetLandNormal(const COORD_DATA& arCoordData, NiPoint3& arNormal, NiPoint3& arFaceNormal) const;

	bool GetLandColor(const COORD_DATA& arCoordData, NiColorA& arColor) const;

	void GetVertex(uint32_t auiBlock, uint32_t auiVertex, NiPoint3& arOut) const;

	TESLandTexture* GetMainTexture(const NiPoint3& arPosition) const;

	NiPoint3 GetWorldOffsetForBlock(uint32_t auiBlock) const;


	int32_t GetDataX() const;
	int32_t GetDataY() const;

	float GetWorldCellX() const;
	float GetWorldCellY() const;

	float GetDefaultWorldHeight() const;

	bool CalculateGrassParams();

	void SetupTextures();

	bool InitLandscape();
	bool CreateLandscape(TESObjectLAND* apCopyFrom);

	bool LoadVertices(bool abLoad3D);
	bool UnloadVertices();

	bool LoadVerticesIntoArrays();

	void Attach3D();
	void Detach3D();
};

ASSERT_SIZE(TESObjectLAND, 0x2C);
ASSERT_SIZE(TESObjectLAND::LoadedLandData, 0xA4);