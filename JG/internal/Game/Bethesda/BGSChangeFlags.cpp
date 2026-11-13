#include "BGSChangeFlags.hpp"

// GAME - 0x4280F0
bool BGSChangeFlags::CheckFlags(uint32_t auiFlag) const {
	return uiFlags.Get(auiFlag);
}

bool BGSChangeFlags::CheckBit(uint32_t auiBit) const {
	return uiFlags.GetBit(auiBit);
}

// GAME - 0x83FEF0
const char* BGSChangeFlags::GetFlagName(uint32_t auiFlag, FORM_TYPE aeFormType, bool abShortName) {
    return CdeclCall<const char*>(0x83FEF0, auiFlag, aeFormType, abShortName);
}
