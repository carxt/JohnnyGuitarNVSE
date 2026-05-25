#include "TESRegionDataList.hpp"

// GAME - 0x4F33C0
bool TESRegionDataList::Add(TESRegionData* apData) {
	return ThisCall<bool>(0x4F33C0, this, apData);
}

// GAME - 0x4F3400
void TESRegionDataList::Clear() {
	ThisCall(0x4F3400, this);
}

// GAME - 0x4F35B0
TESRegionData* TESRegionDataList::Find(REGION_DATA_ID aeID) const {
	return ThisCall<TESRegionData*>(0x4F35B0, this, aeID);
}
