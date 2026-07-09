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

	virtual void  SaveGame(BGSSaveFormBuffer* apBuffer);
	virtual void  LoadGame(BGSLoadGameBuffer* apBuffer);

	enum Flags {
		ALL_MESHES_REACHABLE = 1u << 0,
		UNUSED				 = 1u << 1,
	};

	NiPoint3						kLocation;
	NavMeshInfo*					pNavMeshInfo;
	BSSimpleArray<NavMeshInfo*>*	pNavMeshes;
	TESObjectCELL*					pCell;
	TESWorldSpace*					pWorldSpace;
	uint32_t						uiCellCoords;
	uint16_t						usTriangle;
	Bitfield8						ucFlags;
	uint8_t							ucClientData;
	
	void SetAllMeshesReachable(uint32_t aeFlags);
	void SetupData(NiPoint3& arLocation, TESObjectCELL* apCell, TESWorldSpace* apWorld);

	bool GetNavMeshAndTriangle(NavMeshPtr& arNavMesh, uint16_t& arTriangle) const;

	TESObjectCELL* GetCell() const;
};

ASSERT_SIZE(PathingLocation, 0x28);