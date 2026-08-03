#pragma once

#include "IOTask.hpp"
#include "Gamebryo/NiNode.hpp"

class TESObjectREFR;

class AttachDistant3DTask : public IOTask {
public:
	TESObjectREFR*	pRef;
	NiNodePtr		spNode;
};

ASSERT_SIZE(AttachDistant3DTask, 0x20);