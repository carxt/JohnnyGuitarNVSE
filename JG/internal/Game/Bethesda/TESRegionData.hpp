#pragma once

#include "BSMemObject.hpp"
#include "BSEnums.hpp"

class TESRegion;

struct BaseRegionData {
	REGION_DATA_ID	eDataTypeID;
	bool			bOverride;
	uint8_t			ucPriority;
};

class TESRegionData {
public:
	TESRegionData();
	virtual					~TESRegionData();
	virtual void			Save();
	virtual bool			LoadRegionData(BaseRegionData* apData);
	virtual void			Initialize(TESRegion* apRegion);
	virtual REGION_DATA_ID	GetID() const;
	virtual TESRegionData*	Copy();
	virtual TESRegionData*	Blend(TESRegionData* apRegionData);
	virtual void			BlendInto(TESRegionData* apRegionData, uint32_t auiTotalBlending);
	virtual bool			Validate() const;

	bool	bOverride;
	bool	bIgnore;
	uint8_t	ucPriority;

	bool GetOverride() const;
	void SetOverride(bool abOverride);

	bool GetIgnore() const;

	uint8_t GetPriority() const;
	bool SetPriority(uint8_t aucPriority);
};

ASSERT_SIZE(TESRegionData, 0x8)