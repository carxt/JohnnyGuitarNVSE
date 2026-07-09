#pragma once

#include "PathingLocation.hpp"

class TESObjectREFR;

class PathingNode {
public:
	PathingNode();
	~PathingNode();

	enum Flags {
		HAS_ACTION = 3,
		IS_TRANSITION = 1u << 2,
	};

	Bitfield32		uiFlags;
	PathingLocation kPathingLocation;
	NiPoint3		kTangent;
	TESObjectREFR*	pActionRef;

	bool HasActionAtNode() const;
	bool IsTransitionNode() const;
};

ASSERT_SIZE(PathingNode, 0x3C);