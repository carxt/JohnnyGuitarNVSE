#include "BGSSaveLoadFormIDMap.hpp"

// GAME - 0x846D80
FormID BGSSaveLoadFormIDMap::ConvertFormID(FormID auiFormID) const {
    return ThisCall<FormID>(0x846D80, this, auiFormID);
}

// GAME - 0x846C90
uint32_t BGSSaveLoadFormIDMap::AddFormID(FormID auiFormID) {
	return ThisCall<uint32_t>(0x846C90, this, auiFormID);
}

// GAME - 0x846D20
FormID BGSSaveLoadFormIDMap::GetFormID(uint32_t auiIndex) const {
    return ThisCall<FormID>(0x846D20, this, auiIndex);
}
