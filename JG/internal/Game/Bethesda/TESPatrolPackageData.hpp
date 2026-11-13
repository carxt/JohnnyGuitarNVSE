#pragma once

#include "TESPackageData.hpp"

class TESPatrolPackageData : public TESPackageData {
public:
	bool bRepeatable;
	bool bStartingLocationAtLinkedRef;
};

ASSERT_SIZE(TESPatrolPackageData, 0x8);