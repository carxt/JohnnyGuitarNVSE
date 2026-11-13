#pragma once

#include "PathingLocation.hpp"

class TESObjectREFR;

class VirtualPathingNode {
public:
	struct ALIGN4 _Flags {
		enum Flags : uint32_t {
			HAS_NAVMESH			= 1u << 0,
			HAS_ACTUAL_LOCATION	= 1u << 1,
			HAS_TELEPORT		= 1u << 2,
		};

		bool bHasNavMesh			: 1;
		bool bHasActualLocation		: 1;
		bool bHasTeleport			: 1;
	};
	using Flags = _Flags::Flags;

	Bitfield<_Flags>	uiFlags;
	PathingLocation		kPathingLocation;
	TESObjectREFR*		pTeleportDoor;

	bool HasNavMesh() const;

	bool HasActualLocation() const;

	bool IsVirtualTeleportDoorNode() const;
};

#ifdef GAME
ASSERT_SIZE(VirtualPathingNode, 0x30);
#else
ASSERT_SIZE(VirtualPathingNode, 0x2C);
#endif