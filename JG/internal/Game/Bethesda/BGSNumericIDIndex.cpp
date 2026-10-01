#include "BGSNumericIDIndex.hpp"

// GAME - 0x853500
FormID BGSNumericIDIndex::GetNumericID() const {
	return ThisCall<FormID>(0x853500, this);
}

// GAME - 0x853570
void BGSNumericIDIndex::SetNumericID(FormID auiID) {
	ThisCall(0x853570, this, auiID);
}