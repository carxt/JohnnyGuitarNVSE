#include "BGSHeadPart.hpp"

// GAME - 0x5E7A60
bool BGSHeadPart::GetPlayable() const {
    return ucHeadFlags.bPlayable;
}

void BGSHeadPart::SetPlayable(bool abVal) {
	ucHeadFlags.bPlayable = abVal;
}

// GAME - 0x624700
const BSSimpleList<BGSHeadPart*>* BGSHeadPart::GetExtraPartList() const {
	return &kExtraParts;
}

// GAME - 0x624700
BSSimpleList<BGSHeadPart*>* BGSHeadPart::GetExtraPartList() {
	return &kExtraParts;
}
