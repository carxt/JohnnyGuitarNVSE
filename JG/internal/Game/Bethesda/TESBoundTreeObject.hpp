#pragma once

#include "TESBoundObject.hpp"

class BSTreeNode;

class TESBoundTreeObject : public TESBoundObject {
public:
	TESBoundTreeObject();
	~TESBoundTreeObject();

	virtual void RefreshBound(BSTreeNode* apNode);
};

ASSERT_SIZE(TESBoundTreeObject, sizeof(TESBoundObject));