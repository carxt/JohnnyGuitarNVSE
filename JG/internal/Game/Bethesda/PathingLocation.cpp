#include "PathingLocation.hpp"

// GAME - 0x6DCFE0
void PathingLocation::SetAllMeshesReachable(BOOL abVal) {
#ifdef GAME
	ThisCall(0x6DCFE0, this, abVal);
#else
	ucFlags.bAllMeshesReachable = abVal;
#endif
}

// GAME - 0x6DD280
// GECK - 0x6DEA50
void PathingLocation::SetupData(NiPoint3& arLocation, TESObjectCELL* apCell, TESWorldSpace* apWorld) {
#ifdef GAME
	ThisCall(0x6DD280, this, &arLocation, apCell, apWorld);
#else
	ThisCall(0x6DEA50, this, &arLocation, apCell, apWorld);
#endif
}

// GAEM - 0x6DD640
// GECK - 0x6DE9F0
bool PathingLocation::GetNavMeshAndTriangle(NavMeshPtr& arNavMesh, uint16_t& arTriangle) const {
#ifdef GAME
	return ThisCall<bool>(0x6DD640, this, &arNavMesh, &arTriangle);
#else
	return ThisCall<bool>(0x6DE9F0, this, &arNavMesh, &arTriangle);
#endif
}

// GAME - 0x6DD4F0
// GECK - 0x6DE950
TESObjectCELL* PathingLocation::GetCell() const {
#ifdef GAME
	return ThisCall<TESObjectCELL*>(0x6DD4F0, this);
#else
	return ThisCall<TESObjectCELL*>(0x6DE950, this);
#endif
}
