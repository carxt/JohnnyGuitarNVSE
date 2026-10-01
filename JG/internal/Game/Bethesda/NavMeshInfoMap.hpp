#pragma once

#include "TESForm.hpp"
#include "BSSimpleArray.hpp"

class NavMeshInfo;
class TESWorldSpace;
class TESObjectCELL;

using NavMeshInfoArray = BSSimpleArray<NavMeshInfo*>;

class NavMeshInfoMap : public TESForm {
public:
	NavMeshInfoMap();
	~NavMeshInfoMap();

	bool													bOld;
	NiTPointerMap<FormID, NavMeshInfo*>						kNavMeshInfos;			// Form ID to NavMeshInfo
	NiTMap<FormID, NiTMap<uint32_t, NavMeshInfoArray*>*>	kWorldNavMeshInfos;		// World Form ID -> Cell Coords -> NavMeshInfo
	bool													bInit;

	TESFORM_TYPE(NavMeshInfoMap);

	NavMeshInfoArray* FindNavMeshInfoForCellKey(const TESWorldSpace* apWorld, uint32_t auiCoordinates) const;
	NavMeshInfoArray* FindNavMeshInfoForInteriorCell(const TESObjectCELL* apCell) const;
	NavMeshInfoArray* FindNavMeshInfoForCell(const TESObjectCELL* apCell) const;
};

#ifdef GAME
ASSERT_SIZE(NavMeshInfoMap, 0x40);
#else
ASSERT_SIZE(NavMeshInfoMap, 0x54);
#endif