#pragma once

#include "ObstacleData.hpp"
#include "NavMeshEdgeHandle.hpp"
#include "Gamebryo/NiTMap.hpp"

class NavMeshInfo;
class ReferenceObstacleArray;
class bhkRigidBody;
class NiAVObject;

struct BoundsTriangleInfo {
	uint16_t	usTriangleIndex;
	bool		bPortals[3];
	uint16_t	usTriangles[3];
};

struct PortalEdgeSwap {
	NavMeshEdgeHandle	hOldEdge;
	NavMeshEdgeHandle	hNewEdge;
	bool				bFromAddition;
};
ASSERT_SIZE(PortalEdgeSwap, 0x1C);

class ObstacleUndoData : public NiRefObject {
public:
	struct _UndoState {
		enum State {
			INVALID			= 0,
			ACTIVE			= 1,
			WANT_TO_UNDO	= 2,
			UNDONE			= 3,
			DELETED			= 4,
		};
	};
	using UndoState = _UndoState::State;

	UndoState									eState;
	NiPointer<ObstacleData>						spObstacle;
	uint32_t									uiFirstAddedVertexIndex;
	uint32_t									uiAddedVertexCount;
	uint32_t									uiFirstAddedTriangleIndex;
	uint32_t									uiAddedTriangleCount;
	BSSimpleArray<uint16_t>						kOverlappedTriangles;
	BSSimpleArray<BoundsTriangleInfo>			kBoundsTriangles;
	NiTMap<uint16_t, NiPointer<ObstacleData>>	kRemovedTriangleToObstacleMap;
	BSSimpleArray<PortalEdgeSwap>				kEdgeSwaps;
	BSSimpleArray<uint16_t>						kAddedPOVs;
};

ASSERT_SIZE(ObstacleUndoData, 0x70);