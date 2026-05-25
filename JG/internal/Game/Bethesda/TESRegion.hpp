#pragma once

#include "TESForm.hpp"
#include "TESRegionDataList.hpp"
#include "Gamebryo/NiColor.hpp"

class TESWeather;
class TESWorldSpace;
class TESRegionPointList;

class TESRegion : public TESForm {
public:
	TESRegion();
	~TESRegion();

	TESRegionDataList*					pDataList;
	BSSimpleList<TESRegionPointList*>*	pPointLists;
	TESWorldSpace*						pWorldSpace;
	TESWeather*							pCurrentWeather;
	float								fLastWeatherUpdate;
	NiColor								kEmittanceColor;

	TESFORM_TYPE(TESRegion);
};

ASSERT_SIZE(TESRegion, 0x38);