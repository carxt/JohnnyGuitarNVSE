#include "TESClimate.hpp"

// GAME - 0x595F10
uint8_t TESClimate::GetTransTime(uint32_t auiType) const {
	if (auiType > 3)
		return 0;

	return ucData[auiType];
}

uint8_t TESClimate::GetMoonPhaseDays() const {
	return ucData[PHASE_LENGTH] & 0x3F;
}
