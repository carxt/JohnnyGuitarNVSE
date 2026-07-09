#pragma once

#include "TESRegionData.hpp"
#include "BSStringT.hpp"

class TESFile;

class TESRegionDataMap : public TESRegionData {
public:
	TESRegionDataMap();
	~TESRegionDataMap();

	virtual bool		LoadRegionDataMap(TESFile* apFile);
	virtual void		GetMapNameStr(BSString& arName) const;
	virtual const char* GetMapName() const;
	virtual bool		SetMapName(const char* apName);

	BSString strMapName;
};

ASSERT_SIZE(TESRegionDataMap, 0x10)