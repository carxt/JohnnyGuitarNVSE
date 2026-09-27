#pragma once

#include "EdgeExtraInfo.hpp"
#include "FindTriangleForLocationFilter.hpp"
#include "NavMeshGrid.hpp"
#include "NavMeshStaticAvoidNode.hpp"
#include "NavMeshTriangle.hpp"
#include "NavMeshTriangleDoorPortal.hpp"
#include "NavMeshClosedDoorInfo.hpp"
#include "ObstacleUndoData.hpp"
#include "TESChildCell.hpp"
#include "TESForm.hpp"
#include "Gamebryo/NiRefObject.hpp"

class NavMeshInfo;
class NavMeshPOVData;

class NavMesh : public TESForm, public TESChildCell, public NiRefObject {
public:
	NavMesh();
	~NavMesh();

	TESObjectCELL*								pParentCell;
#ifdef EDITOR
	BOOL										bCulled;
#endif
	BSSimpleArray<NiPoint3>						kVertices;
	BSSimpleArray<NavMeshTriangle>				kTriangles;
	BSSimpleArray<EdgeExtraInfo>				kEdgeInfos;
	BSSimpleArray<NavMeshTriangleDoorPortal>	kDoorPortals;
	BSSimpleArray<NavMeshClosedDoorInfo>		kClosedDoors;
	BSSimpleArray<uint16_t>						kCovers;
	NiTMap<uint16_t, NavMeshPOVData*>			kPOVs;
	BSSimpleArray<uint16_t>						kClosestPOVs;
	NavMeshGrid									kMeshGrid;
	BSSimpleArray<NiPointer<ObstacleUndoData>>	kObstacles;
	NiTMap<uint16_t, NiPointer<ObstacleData>>*	pTriangleToObstacleMap;
	BSSimpleArray<uint16_t>						kObstaclePOVs;
	BSSimpleArray<NavMeshStaticAvoidNode>		kStaticAvoidNodes;
	NavMeshInfo*								pNavMeshInfo;
#ifdef EDITOR
	BOOL										unk120;
#endif

	TESFORM_TYPE(NavMesh);

	NavMeshTriangle* GetTriangle(uint16_t ausTriangle) const;
	uint32_t GetTriangleCount() const;
	NiPoint3* GetVertex(uint16_t ausVertex) const;
	uint32_t GetVertexCount() const;
	EdgeExtraInfo* GetEdgeInfo(uint16_t ausTriangle, uint16_t ausEdge) const;
	uint32_t GetEdgeInfoCount() const;
	NiPoint3 GetTriangleCenter(uint16_t ausTriangle) const;

	bool GetMatchingEdge(uint16_t ausTriangle, uint32_t auiEdge, NavMesh*& arReturnNavMesh, uint16_t& arReturnTriangle, uint16_t& arReturnEdge) const;

	uint16_t FindTriangleForLocation(const NiPoint3& arLocation, FindTriangleForLocationFilter* apFilter) const;
	bool IsPointInsideTriangle(uint16_t ausTriangle, const NiPoint3& arLocatiom, float& arZDiff, FindTriangleForLocationFilter* apFilter) const;
	bool IsPointInsideTriangle(uint16_t ausTriangle, const NiPoint3& arLocatiom, float& arZDiff, float afMaxZdistAbove, float afMaxZdistBelow) const;
};

#ifdef GAME
ASSERT_SIZE(NavMesh, 0x108);
#else
ASSERT_SIZE(NavMesh, 0x124);
#endif

// Bizarre class
class NavMeshPtr : public NiPointer<NavMesh> {
public:
	using NiPointer<NavMesh>::NiPointer;
	NavMeshPtr& operator=(NavMesh* apObject) { NiPointer<NavMesh>::operator=(apObject); return *this; }

	static void MakeNavMeshPtr(NavMeshPtr& arNavMeshOut, NavMesh* apNavMesh);

	static NavMeshPtr MakeNavMeshPtr(NavMesh* apNavMesh);
};

ASSERT_SIZE(NavMeshPtr, 0x4);

class NavMeshArray  {
public:
	BSSimpleArray<NavMeshPtr> kNavMeshes;

	uint32_t AddNavMesh(NavMeshPtr aPtr);
#ifdef GAME
	void RemoveNavMesh(NavMeshPtr aPtr);
	void RemoveNavMeshByIndex(uint32_t auiIndex);
#endif

	uint32_t GetNavMeshIndex(NavMeshPtr aPtr) const;

	NavMeshPtr GetNavMeshByIndex(uint32_t auiIndex) const;

	uint32_t GetNavMeshCount() const;
	uint32_t GetNonDeletedNavMeshCount() const;
};

ASSERT_SIZE(NavMeshArray, 0x10);