#pragma once

#include "BSEnums.hpp"
#include "NavMeshBounds.hpp"

class TESForm;
class TESObjectCELL;
class TESObjectREFR;
class TESWorldSpace;
class NavMesh;
class NavMeshPtr;

class NavMeshInfo {
public:
	struct ALIGN4 _Flags {
		enum Flags {
			//					= 1u << 0,
			BLOCKED				= 1u << 1,
			HAS_ROAD			= 1u << 2,
			DOOR_PORTAL_ONLY	= 1u << 3,
			DISABLED			= 1u << 4,
			HAS_BOUNDS			= 1u << 5,
		};

		bool					: 1;
		bool bBlocked			: 1;
		bool bHasRoad			: 1;
		bool bDoorPortalOnly	: 1;
		bool bDisabled			: 1;
		bool bHasBounds			: 1;
	};
	using Flags = _Flags::Flags;

	FormID							uiNavMeshID;
	FormID							uiParentSpaceID;
	Bitfield<_Flags>				uiFlags;
	uint32_t						uiCellCoords;
	NiPoint3						kApproxLocation;
	union {
		TESForm*		 __restrict pParentSpace;
		TESObjectCELL*	 __restrict pParentCell;
		TESWorldSpace*	 __restrict pParentWorldspace;
	};
	float							fPreferredPercent;
	BSSimpleArray<NavMeshInfo*>		kAdjacentNavMeshes;
	BSSimpleArray<NavMeshInfo*>		kPreferredAdjacentNavMeshes;
	BSSimpleArray<TESObjectREFR*>	kConnectedDoors;
	NavMesh*						pNavMesh;
	NavMeshBounds*					pBoundData;
#ifdef EDITOR
	bool							bAltered;
#endif

	bool GetFlag(Flags aeFlag) const;

	bool GetDisabled() const;

	TESForm* GetParentSpace() const;
	TESObjectCELL* GetInteriorCell() const;
	TESWorldSpace* GetWorldSpace() const;

	float GetPreferredPercent() const;

	bool HasNavMesh() const;
	bool GetNavMesh(NavMeshPtr& arNavMesh) const;
	bool GetNavMeshEvenDisabled(NavMeshPtr& arNavMesh) const;
	bool GetNavMesh(NavMesh*& arNavMesh) const;
};

#ifdef GAME
ASSERT_SIZE(NavMeshInfo, 0x5C);
#else
ASSERT_SIZE(NavMeshInfo, 0x60);
#endif