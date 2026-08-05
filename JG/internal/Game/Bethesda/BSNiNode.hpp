#pragma once

#include "Gamebryo/NiNode.hpp"

class BSNiNode : public NiNode {
public:
	virtual ~BSNiNode();
	virtual void ReparentSkinInstances(NiNode* apRoot, NiNode* apNewParent);

	NIRTTI_ADDRESS(0x1204380);
};

ASSERT_SIZE(BSNiNode, sizeof(NiNode));