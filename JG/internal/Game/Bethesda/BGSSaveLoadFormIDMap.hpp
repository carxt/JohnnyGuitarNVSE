#pragma once

#include "FormID_View.hpp"
#include "Gamebryo/NiTMap.hpp"

class BGSSaveLoadFormIDMap {
public:
	NiTMap<FormID, uint32_t>	kFormIDToIndexMap;
	NiTMap<uint32_t, FormID>	kIndexToFormIDMap;
	uint32_t					uiCurrentIndex;

	FormID ConvertFormID(FormID auiFormID) const;
	uint32_t AddFormID(FormID auiFormID);
	FormID GetFormID(uint32_t auiIndex) const;
};

ASSERT_SIZE(BGSSaveLoadFormIDMap, 0x24);