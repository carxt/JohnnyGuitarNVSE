#pragma once

#include "TESPackageData.hpp"

class PackageLocation;

class TESFollowPackageData : public TESPackageData {
public:
	TESFollowPackageData();
	~TESFollowPackageData();
	
	PackageLocation* pStartLocation;
	float			 fTriggerRadius;
};

ASSERT_SIZE(TESFollowPackageData, 0xC);