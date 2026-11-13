#include "PathingNode.hpp"

// GAME - 0x6E2330
bool PathingNode::IsTeleportDoorNode() const {
	return uiFlags.Get(Flags::HAS_TELEPORT) == Flags::HAS_TELEPORT;
}

// GAME - 0x6CA0C0
bool PathingNode::IsTransitionNode() const {
	return uiFlags.bHasTransition;
}
