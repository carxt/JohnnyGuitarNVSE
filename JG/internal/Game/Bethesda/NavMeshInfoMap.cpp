#include "NavMeshInfoMap.hpp"

// GAME - 0x6B7850
// GECK - 0x6EA8C0
NavMeshInfoArray* NavMeshInfoMap::FindNavMeshInfoForCellKey(const TESWorldSpace* apWorld, uint32_t auiCoordinates) const {
#ifdef GAME
	return ThisCall<NavMeshInfoArray*>(0x6B7850, this, apWorld, auiCoordinates);
#else
	return ThisCall<NavMeshInfoArray*>(0x6EA8C0, this, apWorld, auiCoordinates);
#endif
}

// GAME - 0x6B78B0
// GECK - 0x6EA900
NavMeshInfoArray* NavMeshInfoMap::FindNavMeshInfoForInteriorCell(const TESObjectCELL* apCell) const {
#ifdef GAME
	return ThisCall<NavMeshInfoArray*>(0x6B78B0, this, apCell);
#else
	return ThisCall<NavMeshInfoArray*>(0x6EA900, this, apCell);
#endif
}

// GAME - 0x6B77E0
// GECK - 0x6EAD50
NavMeshInfoArray* NavMeshInfoMap::FindNavMeshInfoForCell(const TESObjectCELL* apCell) const {
#ifdef GAME
	return ThisCall<NavMeshInfoArray*>(0x6B77E0, this, apCell);
#else
	return ThisCall<NavMeshInfoArray*>(0x6EAD50, this, apCell);
#endif
}
