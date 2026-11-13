#include "TESRegionDataList.hpp"

// GAME - 0x4F33C0
// GECK - 0x53B970
bool TESRegionDataList::Add(TESRegionData* apData) {
#ifdef GAME
	return ThisCall<bool>(0x4F33C0, this, apData);
#else
	return ThisCall<bool>(0x53B970, this, apData);
#endif
}

// GECK - 0x53B9B0
bool TESRegionDataList::RemoveRDL(REGION_DATA_ID aeID) {
#ifdef GAME
	TESRegionData* pData = Find(aeID);
	if (!pData)
		return false;

	Remove(pData);

	if (bOwnsDataMemory)
		delete pData;

	return true;
#else
	return ThisCall<bool>(0x53B9B0, this, aeID);
#endif
}

// GAME - 0x4F3400
// GECK - 0x53BA00
void TESRegionDataList::Clear() {
#ifdef GAME
	ThisCall(0x4F3400, this);
#else
	ThisCall(0x53BA00, this);
#endif
}

// GAME - 0x4F35B0
// GECK - 0x53B910
TESRegionData* TESRegionDataList::Find(REGION_DATA_ID aeID) const {
#ifdef GAME
	return ThisCall<TESRegionData*>(0x4F35B0, this, aeID);
#else
	return ThisCall<TESRegionData*>(0x53B910, this, aeID);
#endif
}
