#pragma once

#include "Gamebryo/NiTPointerList.hpp"
#include "Gamebryo/NiAVObject.hpp"
#include "BSSimpleArray.hpp"
#include "BSOcclusionPlane.hpp"
#include "BSMultiBoundRoom.hpp"

class NiNode;
class ShadowSceneLight;
class BSPortal;

NiSmartPointer(BSPortalGraph);

class BSPortalGraph : public NiRefObject {
public:
	BSPortalGraph();
	virtual ~BSPortalGraph();

	NiTPointerList<BSOcclusionPlane*>	kOccluders;
	NiTPointerList<BSPortal*>			kPortals;
	NiTPointerList<BSMultiBoundRoomPtr>	kMultiBoundRooms;
	BSMultiBoundRoomPtr					spRoomRoot;
	NiTPointerList<BSMultiBoundRoomPtr>	kMultiBoundRoomAccumList;
	NiTObjectArray<NiAVObjectPtr>		kAlwaysRenderChildren;
	NiPointer<NiNode>					spPortalNodeRoot;
	NiTPointerList<ShadowSceneLight*>	kAttachAlwaysRenderQueue;
	NiTPointerList<ShadowSceneLight*>	kDetachAlwaysRenderQueue;
	BSSimpleArray<NiPointer<NiNode>>	kUnboundNodes;
};

ASSERT_SIZE(BSPortalGraph, 0x78);