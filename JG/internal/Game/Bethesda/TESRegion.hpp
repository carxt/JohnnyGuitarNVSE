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

	virtual TESRegion*	Copy(TESRegion* apCopy);
	virtual bool		Validate();

#ifdef EDITOR
	uint32_t							uiMapColor;
#endif
	TESRegionDataList*					pRegionDataList;
	BSSimpleList<TESRegionPointList*>*	pRegionPointLists;
	TESWorldSpace*						pWorldSpace;
	TESWeather*							pCurrentWeather;
	float								fLastWeatherUpdate;
	NiColor								kEmittanceColor;

	TESFORM_TYPE(TESRegion);

	TESRegionDataList* GetRegionDataList() const;

	BSSimpleList<TESRegionPointList*>* GetRegionPointLists() const;

	TESWorldSpace* GetWorldSpace() const;
	void SetWorldSpace(TESWorldSpace* apWorldSpace);

	TESWeather* GetCurrentWeather() const;
	void SetCurrentWeather(TESWeather* apWeather);

	float GetLastWeatherUpdate() const;
	void SetLastWeatherUpdate(float afVal);

	void UpdateWeather();
};

#ifdef GAME
ASSERT_SIZE(TESRegion, 0x38);
#else
ASSERT_SIZE(TESRegion, 0x50);
#endif