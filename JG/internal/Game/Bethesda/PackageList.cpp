#include "PackageList.hpp"

// GAME - 0x67E440
// GECK - 0x49DC30
void PackageList::Copy(const PackageList* apSource) {
#ifdef GAME
	ThisCall(0x67E440, this, apSource);
#else
	ThisCall(0x49DC30, this, apSource);
#endif
}

#ifdef GAME
// GAME - 0x67E780
TESPackage* PackageList::FindCurrentPackage(Actor* apActor) const {
	return ThisCall<TESPackage*>(0x67E780, this, apActor);
}

// GAME - 0x67EC40
void PackageList::FindMissedPackages(Actor* apActor, BSSimpleList<TESPackage*>& arOut, float afStartDate, float afHour) const {
	ThisCall(0x67EC40, this, apActor, &arOut, afStartDate, afHour);
}
#endif
