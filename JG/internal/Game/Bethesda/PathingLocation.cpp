#include "PathingLocation.hpp"

// GAME - 0x6DCBB0
// GECK - 0x6DE660
PathingLocation::PathingLocation() {
#ifdef GAME
	ThisCall(0x6DCBB0, this);
#else
	ThisCall(0x6DE660, this);
#endif
}

// GAME - 0x4FF7E0
PathingLocation::~PathingLocation() {
}

#ifdef GAME
// GAME - 0x6DEF40
void PathingLocation::SaveGame(BGSSaveFormBuffer* apBuffer) {
	ThisCall(0x6DEF40, this, apBuffer);
}

// GAME - 0x6DF010
void PathingLocation::LoadGame(BGSLoadGameBuffer* apBuffer) {
	ThisCall(0x6DF010, this, apBuffer);

}
#endif

// GAME - 0x6DCFE0
void PathingLocation::SetAllMeshesReachable(uint32_t aeFlags) {
	ThisCall(0x6DCFE0, this, aeFlags);
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
TESObjectCELL* PathingLocation::GetCell() const {
	return ThisCall<TESObjectCELL*>(0x6DD4F0, this);
}
