#pragma once

#include "BSExtraData.hpp"
#include "MapMarkerData.hpp"

class ExtraMapMarker : public BSExtraData {
public:
	ExtraMapMarker();
	~ExtraMapMarker();

	MapMarkerData* pData;

	BSEXTRA_TYPE(ExtraMapMarker);

	bool IsVisible() const			{ return pData->IsVisible(); }
	bool CanTravel() const			{ return pData->CanTravel(); }
	bool IsHidden() const			{ return pData->IsHidden(); }
	void SetVisible(bool abVal)		{ pData->SetVisible(abVal); }
	void SetCanTravel(bool abVal)	{ pData->SetCanTravel(abVal); }
	void SetHidden(bool abVal)		{ pData->SetHidden(abVal); }
};

ASSERT_SIZE(ExtraMapMarker, 0x10);