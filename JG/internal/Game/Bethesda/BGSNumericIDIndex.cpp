#include "BGSNumericIDIndex.hpp"

// GAME - 0x853500
uint32_t BGSNumericIDIndex::GetNumericID() const {
	return ThisCall<uint32_t>(0x853500, this);
}

// GAME - 0x853570
void BGSNumericIDIndex::SetNumericID(uint32_t auiID) {
	ThisCall(0x853570, this, auiID);
}