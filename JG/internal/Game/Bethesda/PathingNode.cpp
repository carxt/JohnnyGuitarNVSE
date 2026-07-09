#include "PathingNode.hpp"

// GAME - 0x6E2210
PathingNode::PathingNode() {
	pActionRef = nullptr;
}

// GAME - 0x6E22D0
PathingNode::~PathingNode() {
}

// GAME - 0x6E2330
bool PathingNode::HasActionAtNode() const {
	return uiFlags.Get(HAS_ACTION) == HAS_ACTION;
}

// GAME - 0x6CA0C0
bool PathingNode::IsTransitionNode() const {
	return uiFlags.Get(IS_TRANSITION) == IS_TRANSITION;
}
