#pragma once

#include "BSSimpleList.hpp"
#include "BGSReconstructedForms.hpp"
#include "Gamebryo/NiTMap.hpp"

class TESFile;
class BGSReconstructFormsInFileMap;

class BGSReconstructFormsInAllFilesMap : public NiTMap<TESFile*, BGSReconstructFormsInFileMap*> {
public:
	BGSReconstructedForms	kConstructedForms;
	uint32_t				uiCount;
};

ASSERT_SIZE(BGSReconstructFormsInAllFilesMap, 0x34);