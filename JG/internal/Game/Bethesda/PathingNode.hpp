#pragma once

#include "PathingLocation.hpp"

class TESObjectREFR;

class PathingNode {
public:
	struct ALIGN4 _Flags {
		enum Flags {
			HAS_TELEPORT	= 3,
			HAS_TRANSITION	= 1u << 2,
		};

		bool				: 2;
		bool bHasTransition : 1;
	};
	using Flags = _Flags::Flags;

	Bitfield<_Flags>	uiFlags;
	PathingLocation		kPathingLocation;
	NiPoint3			kTangent;
	TESObjectREFR*		pActionRef;

	bool IsTeleportDoorNode() const;

	bool IsTransitionNode() const;
};

#ifdef GAME
ASSERT_SIZE(PathingNode, 0x3C);
#else
ASSERT_SIZE(PathingNode, 0x38);
#endif