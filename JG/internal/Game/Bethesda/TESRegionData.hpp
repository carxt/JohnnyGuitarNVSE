#pragma once

#include "BSMemObject.hpp"
#include "BSEnums.hpp"

class TESRegion;

struct RegionData {
	REGION_DATA_ID	eDataTypeID;
	bool			bOverride;
	uint8_t			cPriority;
};

class TESRegionData {
public:
	TESRegionData();
	virtual					~TESRegionData();
	virtual void			Save();
	virtual bool			LoadRegionData(RegionData* apData);
	virtual void			Initialize(TESRegion* apRegion);
	virtual REGION_DATA_ID	GetID() const;
	virtual TESRegionData*	Copy();
	virtual TESRegionData*	Blend(TESRegionData* apRegionData);
	virtual void			BlendInto(TESRegionData* apRegionData, uint32_t auiTotalBlending);
	virtual bool			Validate() const;

	bool	bOverride;
	bool	bIgnore;
	uint8_t	cPriority;
};

ASSERT_SIZE(TESRegionData, 0x8)