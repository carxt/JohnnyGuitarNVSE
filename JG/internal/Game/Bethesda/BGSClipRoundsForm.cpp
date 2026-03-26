#include "BGSClipRoundsForm.hpp"

// GAME - 0x401170
uint8_t BGSClipRoundsForm::GetFormClipRounds() const {
	return ucClipRounds;
}

// GAME - 0x4F15A0
void BGSClipRoundsForm::SetFormClipRounds(uint8_t aucClipRounds) {
	ucClipRounds = aucClipRounds;
}
