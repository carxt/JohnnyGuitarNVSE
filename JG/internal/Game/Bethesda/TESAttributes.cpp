#include "TESAttributes.hpp"

// GAME - 0x480160
uint8_t TESAttributes::GetAttributeValue(ActorValue::Index aeIndex) const {
	return ucAttributes[aeIndex - 5];
}

// GAME - 0x480180
void TESAttributes::SetAttributeValue(ActorValue::Index aeIndex, uint8_t aucValue, bool abMarkChange) {
	ThisCall(0x480180, this, aeIndex, aucValue, abMarkChange);
}
