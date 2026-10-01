#pragma once

#include "Gamebryo/NiPoint3.hpp"
#include "BSSimpleArray.hpp"

class ParentSpaceNode;
class TeleportLink;

class TeleportPath {
public:
	BSSimpleArray<ParentSpaceNode*> pParentSpaceNodes;
	BSSimpleArray<TeleportLink*>	pTeleportLinks;
	NiPoint3						kStart;
	NiPoint3						kEnd;
};

ASSERT_SIZE(TeleportPath, 0x38);