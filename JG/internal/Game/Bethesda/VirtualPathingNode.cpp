#include "VirtualPathingNode.hpp"

// GAME - 0x6CA830
bool VirtualPathingNode::HasNavMesh() const {
	return uiFlags.bHasNavMesh;
}

// GAME - 0x6CAC70
bool VirtualPathingNode::HasActualLocation() const {
	return uiFlags.bHasActualLocation;
}

// GAME - 0x6CA0C0
bool VirtualPathingNode::IsVirtualTeleportDoorNode() const {
	return uiFlags.bHasTeleport;
}
