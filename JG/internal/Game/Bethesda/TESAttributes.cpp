#include "TESAttributes.hpp"

// GAME - 0x480160
// GECK - 0x4F1490
uint8_t TESAttributes::GetAttributeValue(ActorValue::Index aeIndex) const {
	return ucAttributes[aeIndex - 5];
}

// GAME - 0x480180
// GECK - 0x4F14A0
void TESAttributes::SetAttributeValue(ActorValue::Index aeIndex, uint8_t aucValue, bool abMarkChange) {
#ifdef GAME
	ThisCall(0x480180, this, aeIndex, aucValue, abMarkChange);
#else
	ThisCall(0x4F14A0, this, aeIndex, aucValue, abMarkChange);
#endif
}
