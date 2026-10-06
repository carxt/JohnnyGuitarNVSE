#pragma once

#include "BSSimpleArray.hpp"
#include "Gamebryo/NiPoint3.hpp"

class TESObjectCELL;
class TESWorldSpace;
class BGSSaveFormBuffer;
class BGSLoadGameBuffer;
class NavMeshInfo;
class NavMeshPtr;

class PathingLocation {
public:
	PathingLocation();
	~PathingLocation();

#ifdef GAME
	virtual void  SaveGame(BGSSaveFormBuffer* apBuffer);
	virtual void  LoadGame(BGSLoadGameBuffer* apBuffer);
#endif

	struct ALIGN1 _Flags {
		enum Flags {
			ALL_MESHES_REACHABLE = 1u << 0,
			UNUSED				 = 1u << 1,
		};

		bool bAllMeshesReachable	: 1;
		bool bUnused				: 1;
	};
	using Flags = _Flags::Flags;

	NiPoint3						kLocation;
	NavMeshInfo*					pNavMeshInfo;
	BSSimpleArray<NavMeshInfo*>*	pNavMeshes;
	TESObjectCELL*					pCell;
	TESWorldSpace*					pWorldSpace;
	uint32_t						uiCellCoords;
	uint16_t						usTriangle;
	Bitfield<_Flags>				ucFlags;
	uint8_t							ucClientData;
	
	void SetAllMeshesReachable(BOOL abVal);
	void SetupData(NiPoint3& arLocation, TESObjectCELL* apCell, TESWorldSpace* apWorld);

	bool GetNavMeshAndTriangle(NavMeshPtr& arNavMesh, uint16_t& arTriangle) const;

	TESObjectCELL* GetCell() const;
};

#ifdef GAME
ASSERT_SIZE(PathingLocation, 0x28);
#else
ASSERT_SIZE(PathingLocation, 0x24);
#endif