#include "ZoneEntry.hpp"

// GAME - 0x620180
ZoneEntry* ZoneEntry::GetNext() const {
#ifdef GAME
	return ThisCall<ZoneEntry*>(0x620180, this);
#else
	return static_cast<ZoneEntry*>(bhkTTNode::GetNext());
#endif
}

// GAME - 0x620300
ZoneEntry* ZoneEntry::GetZoneEntry(const hkpCollidable* apCollidable) {
#ifdef GAME
	return ThisCall<ZoneEntry*>(0x620300, this, apCollidable);
#else
	return static_cast<ZoneEntry*>(bhkTTNode::GetEntry(apCollidable));
#endif
}

// GAME - 0x576870
ZoneEntry* ZoneEntry::GetZoneEntry(const TESObjectREFR* apReference) {
#ifdef GAME
	return ThisCall<ZoneEntry*>(0x576870, this, apReference);
#else
	return static_cast<ZoneEntry*>(bhkTTNode::GetEntry(apReference));
#endif
}

#ifdef GAME
// GAME - 0x57B730
TargetEntry* ZoneEntry::GetTargetEntry(const TESObjectREFR* apReference) {
	return ThisCall<TargetEntry*>(0x57B730, this, apReference);
}
#endif
