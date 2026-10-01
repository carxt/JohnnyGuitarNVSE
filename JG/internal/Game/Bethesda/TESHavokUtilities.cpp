#include "TESHavokUtilities.hpp"

// GAME - 0x62BC10
void TESHavokUtilities::RemoveHavokFromSceneGraph(NiAVObject* apObject) {
	CdeclCall(0x62BC10, apObject);
}

// GAME - 0x62B8D0
void TESHavokUtilities::AddVelocity(NiAVObject* apObject, const NiPoint3& arVector, bool abReset) {
	CdeclCall(0x62B8D0, apObject, &arVector, abReset);
}
