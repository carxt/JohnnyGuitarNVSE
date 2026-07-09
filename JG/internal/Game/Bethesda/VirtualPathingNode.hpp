#pragma once

#include "PathingLocation.hpp"

class TESObjectREFR;

class VirtualPathingNode {
public:
	struct ALIGN4 _VirtualPathingNodeFlags {
		enum Flags : uint32_t {
			HAS_NAVMESH			= 1u << 0,
			HAS_ACTUAL_LOCATION	= 1u << 1,
			HAS_DOOR			= 1u << 2,
		};

		bool bHasNavMesh			: 1;
		bool bHasActualLocation		: 1;
		bool bHasDoor				: 1;
	};
	using VirtualPathingNodeFlags = _VirtualPathingNodeFlags::Flags;

	Bitfield<_VirtualPathingNodeFlags>	uiFlags;
	PathingLocation						kPathingLocation;
	TESObjectREFR*						pTeleportDoor;
};

ASSERT_SIZE(VirtualPathingNode, 0x30);