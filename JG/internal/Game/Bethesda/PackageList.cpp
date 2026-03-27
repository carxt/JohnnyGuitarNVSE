#include "PackageList.hpp"

#ifdef GAME
// GAME - 0x67E780
TESPackage* PackageList::FindCurrentPackage(Actor* apActor) const {
	return ThisCall<TESPackage*>(0x67E780, this, apActor);
}

// GAME - 0x67EC40
void PackageList::FindMissedPackages(Actor* apActor, BSSimpleList<TESPackage*>& arOut, float afLastProcessedTime, float afCurrentHour) const {
	ThisCall(0x67EC40, this, apActor, &arOut, afLastProcessedTime, afCurrentHour);
}
#endif
