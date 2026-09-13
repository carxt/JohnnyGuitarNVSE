#pragma once

#include "BSEnums.hpp"

class TESRegion;
class TESRegionData;
class TESRegionDataObjects;
class TESRegionDataWeather;
class TESRegionDataMap;
class TESRegionDataLandscape;
class TESRegionDataGrass;
class TESRegionDataSound;
class TESRegionDataImposter;
class TESFile;

class TESRegionDataManager {
public:
	virtual TESRegion*				GetLastLoadedRegion() const;
	virtual TESRegionData*			ConstructRegionData(REGION_DATA_ID aeID) const;
	virtual TESRegionDataObjects*	IsRegionDataObjects(TESRegionData* apData) const;
	virtual TESRegionDataWeather*	IsRegionDataWeather(TESRegionData* apData) const;
	virtual TESRegionDataMap*		IsRegionDataMap(TESRegionData* apData) const;
	virtual TESRegionDataLandscape* IsRegionDataLandscape(TESRegionData* apData) const;
	virtual TESRegionDataGrass*		IsRegionDataGrass(TESRegionData* apData) const;
	virtual TESRegionDataSound*		IsRegionDataSound(TESRegionData* apData) const;
	virtual TESRegionDataImposter*	IsRegionDataImposter(TESRegionData* apData) const;
	virtual bool					LoadRegionData(TESFile* apFile, TESRegion* apRegion);

	TESRegion* pLastLoadedRegion;
};

ASSERT_SIZE(TESRegionDataManager, 0x8);