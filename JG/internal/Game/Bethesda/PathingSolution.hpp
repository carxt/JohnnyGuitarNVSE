#pragma once

#include "Gamebryo/NiRefObject.hpp"
#include "BSSimpleArray.hpp"
#include "PathingNode.hpp"
#include "VirtualPathingNode.hpp"

using FormID = uint32_t;

NiSmartPointer(PathingSolution);

class PathingSolution : public NiRefObject {
public:
	BSSimpleArray<VirtualPathingNode>	kVirtualPathingNodes;
	int32_t								iFirstLoadedVirtualNodeIndex;
	int32_t								iLastLoadedVirtualNodeIndex;
	BSSimpleArray<PathingNode>			kCurrentPathingNodes;
	BSSimpleArray<FormID>				kDoorFormIDs;
	bool								bIncompletePath;
};

ASSERT_SIZE(PathingSolution, 0x44);